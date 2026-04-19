#include "DisplayManager.h"
#include "EventSystem.h"
#include "GameState.h"
#include "constants.h"
#include "iconMappings.h"

namespace sm {

DisplayManager::DisplayManager(const DisplayManagerSpec& spec)
  : m_Specification(spec), m_SpriteA(&m_Display),
    m_SpriteB(&m_Display),
    m_SpriteC(&m_Display),
    m_ReelSprites{ &m_SpriteA, &m_SpriteB, &m_SpriteC } {}

void DisplayManager::setup() {
  m_Display.init();
  m_Display.setRotation(1);
  for (u8 i = 0; i < 3; i++) {
    m_ReelSprites[i]->setColorDepth(8);
    m_ReelSprites[i]->createSprite(m_IconWidth, globals::SCREEN_HEIGHT);
    if (!m_ReelSprites[i]->created()) {
      Serial.printf("Sprite %d FAILED to create!\n", i);
    }
    Serial.printf("Free heap after sprite %d: %d\n", i, ESP.getFreeHeap());
  }

  m_Display.fillScreen(m_Specification.backgroundColor);
  m_Display.setTextColor(m_Specification.foregroundColor);

  EventSystem::getInstance().subscribeToGameWin([this](const EventGameWin* event) {
    m_CurrentReels = event->reels;
    Serial.println(event->debugInfo);
    startSpin();
  });
  EventSystem::getInstance().subscribeToGameLoss([this](const EventGameLoss* event) {
    m_CurrentReels = event->reels;
    Serial.println(event->debugInfo);
    startSpin();
  });
}

void DisplayManager::loop() {
  if (!m_LoopRunning) return;
  Serial.println("loop");

  auto now = millis();
  if (now - m_LastTime >= m_FrameTime) {
    auto frameStart = millis();

    std::array<Reel*, globals::REEL_COUNT> reelPtrs = { &m_CurrentReels->a, &m_CurrentReels->b, &m_CurrentReels->c };

    for (u8 i = 0; i < reelPtrs.size(); i++) {
      if (m_ReelSpinning[i]) {
        m_ScrollY[i] += m_ReelSpeeds[i];

        if (m_ScrollY[i] >= m_IconHeight) {
          m_ScrollY[i] = fmod(m_ScrollY[i], m_IconHeight);
          m_ReelOffsets[i] = (m_ReelOffsets[i] + 1) % reelPtrs[i]->size();

          if (m_ReelOffsets[i] == 0) {
            m_ReelSpinning[i] = false;
            m_ScrollY[i] = 0;
          }
        }
      }

      m_ReelSprites[i]->fillSprite(m_Specification.backgroundColor);
      auto afterFill = millis();
      Serial.printf("Fill: %dms\n", afterFill - frameStart);

      u8 prevIdx = (m_ReelOffsets[i] == 0) ? reelPtrs[i]->size() - 1 : m_ReelOffsets[i] - 1;
      u8 nextIdx = (m_ReelOffsets[i] + 1) % reelPtrs[i]->size();
      u8 prev2Idx = (prevIdx == 0) ? reelPtrs[i]->size() - 1 : prevIdx - 1;
      i16 scrollOffset = (i16)m_ScrollY[i];

      const u16* img = getCharacterIcon((*reelPtrs[i])[m_ReelOffsets[i]]);
      const u16* prevImg = getCharacterIcon((*reelPtrs[i])[prevIdx]);
      const u16* prev2Img = getCharacterIcon((*reelPtrs[i])[prev2Idx]);
      const u16* nextImg = getCharacterIcon((*reelPtrs[i])[nextIdx]);

      m_ReelSprites[i]->pushImage(0, m_CenterY - m_IconHeight * 2 + scrollOffset, m_IconWidth, m_IconHeight, prev2Img);
      m_ReelSprites[i]->pushImage(0, m_CenterY - m_IconHeight + scrollOffset, m_IconWidth, m_IconHeight, prevImg);
      m_ReelSprites[i]->pushImage(0, m_CenterY + scrollOffset, m_IconWidth, m_IconHeight, img);
      m_ReelSprites[i]->pushImage(0, m_CenterY + m_IconHeight + scrollOffset, m_IconWidth, m_IconHeight, nextImg);
      auto afterPush = millis();
      Serial.printf("PushImage: %dms\n", afterPush - afterFill);

      m_ReelSprites[i]->pushSprite(i * m_IconWidth, 0);
      auto afterSprite = millis();
      Serial.printf("PushSprite: %dms, Total: %dms\n", afterSprite - afterPush, afterSprite - frameStart);
    }

    bool anySpinning = false;
    for (u8 i = 0; i < 3; i++) {
      if (m_ReelSpinning[i]) {
        anySpinning = true;
        break;
      }
    }

    if (!anySpinning) m_LoopRunning = false;

    m_LastTime = now;
  }
}

void DisplayManager::startSpin() {
  for (u8 i = 0; i < 3; i++) {
    m_ScrollY[i] = 0;
    m_ReelOffsets[i] = 0;
    m_ReelSpinning[i] = true;
  }
  m_LoopRunning = true;
}

}
