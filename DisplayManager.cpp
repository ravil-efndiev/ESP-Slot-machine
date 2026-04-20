#include "DisplayManager.h"
#include "EventSystem.h"
#include "GameState.h"
#include "constants.h"
#include "utils.h"

namespace sm {

DisplayManager::DisplayManager(const DisplayManagerSpec& spec)
  : m_Specification(spec),
    m_SpriteA(&m_Display),
    m_SpriteB(&m_Display),
    m_SpriteC(&m_Display),
    m_ReelSprites{ &m_SpriteA, &m_SpriteB, &m_SpriteC } {}

void DisplayManager::setup() {
  m_Display.init();
  m_Display.setRotation(1);
  for (u8 i = 0; i < 3; i++) {
    m_ReelSprites[i]->setColorDepth(8);
    m_ReelSprites[i]->createSprite(m_IconWidth, globals::SCREEN_HEIGHT);
    m_ReelSprites[i]->setSwapBytes(true);
    if (!m_ReelSprites[i]->created()) {
      Serial.printf("Sprite %d FAILED to create!\n", i);
    }
    Serial.printf("Free heap after sprite %d: %d\n", i, ESP.getFreeHeap());
  }

  m_Display.fillScreen(m_Specification.backgroundColor);
  m_Display.setTextColor(m_Specification.foregroundColor);

  EventSystem::getInstance().subscribe([this](const Event* event) {
    if (event->type == EventType::GameStateDecide) {
      SM_ASSERT(event->reels != nullptr, "reels (Reels*) is nullptr in GameStateDecide event")

      m_CurrentReels = event->reels;
      Serial.println(event->debugInfo);
      startSpin();
    }
  });
}

void DisplayManager::loop() {
  if (!m_LoopRunning) return;

  auto now = millis();
  if (now - m_LastTime < m_FrameTime) return;
  m_LastTime = now;

  std::array<Reel*, globals::REEL_COUNT> reelPtrs = {
    &m_CurrentReels->a,
    &m_CurrentReels->b,
    &m_CurrentReels->c
  };

  for (u8 i = 0; i < reelPtrs.size(); i++) {
    Reel* reel = reelPtrs[i];
    u8 size = reel->size();

    if (m_ReelSpinning[i]) {
      m_ScrollY[i] += m_ReelSpeeds[i];

      while (m_ScrollY[i] >= m_IconHeight) {
        m_ScrollY[i] -= m_IconHeight;
        m_ReelOffsets[i] = (m_ReelOffsets[i] - 1 + size) % size;

        if (m_ReelOffsets[i] == 0) {
          m_HasLooped[i] = true;
        }

        if (m_HasLooped[i] && m_ReelOffsets[i] == size - 1) {
          m_ReelSpinning[i] = false;
          m_ScrollY[i] = 0;
          break;
        }
      }
    }

    u8 curr = m_ReelOffsets[i];
    u8 prev = (curr == 0) ? size - 1 : curr - 1;
    u8 prev2 = (prev == 0) ? size - 1 : prev - 1;
    u8 next = (curr + 1) % size;

    i16 scrollOffset = (i16)m_ScrollY[i];

    auto& sprite = *m_ReelSprites[i];
    sprite.fillSprite(m_Specification.backgroundColor);

    const u16* img = getCharacterIcon((*reel)[curr]);
    const u16* prevImg = getCharacterIcon((*reel)[prev]);
    const u16* prev2Img = getCharacterIcon((*reel)[prev2]);
    const u16* nextImg = getCharacterIcon((*reel)[next]);

    sprite.pushImage(0, m_CenterY - m_IconHeight * 2 + scrollOffset, m_IconWidth, m_IconHeight, prev2Img);
    sprite.pushImage(0, m_CenterY - m_IconHeight + scrollOffset, m_IconWidth, m_IconHeight, prevImg);
    sprite.pushImage(0, m_CenterY + scrollOffset, m_IconWidth, m_IconHeight, img);
    sprite.pushImage(0, m_CenterY + m_IconHeight + scrollOffset, m_IconWidth, m_IconHeight, nextImg);

    sprite.pushSprite(i * m_IconWidth, 0);
  }

  bool anySpinning = false;
  for (u8 i = 0; i < 3; i++) {
    if (m_ReelSpinning[i]) {
      anySpinning = true;
      break;
    }
  }

  if (!anySpinning) {
    Event event(m_StateWin ? EventType::ReelsEndAndWin : EventType::ReelsEndAndLoss, nullptr, nullptr);
    EventSystem::getInstance().emit(&even);
    m_LoopRunning = false;
  }
}

void DisplayManager::startSpin() {
  for (u8 i = 0; i < 3; i++) {
    m_ScrollY[i] = 0;
    m_ReelOffsets[i] = 0;
    m_ReelSpinning[i] = true;
    m_HasLooped[i] = false;
  }
  m_LoopRunning = true;
  m_StateWin = areReelsWinning(*m_CurrentReels);
}

}
