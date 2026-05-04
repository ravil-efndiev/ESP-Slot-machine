#include "DisplayManager.h"
#include "EventSystem.h"
#include "GameState.h"
#include "constants.h"
#include "utils.h"

namespace sm {

DisplayManager::DisplayManager(const DisplayManagerSpec& spec)
  : m_Spec(spec),
    m_SpriteA(&m_Display),
    m_SpriteB(&m_Display),
    m_SpriteC(&m_Display),
    m_ReelSprites{ &m_SpriteA, &m_SpriteB, &m_SpriteC } {
  initRectBounds();
}

void DisplayManager::initRectBounds() {
  m_ReelScreenOffset = { (globals::SCREEN_WIDTH - m_Spec.reelScreenWidth) / 2, (globals::SCREEN_HEIGHT - m_Spec.reelScreenHeight) / 2 };

  m_TopBar = { 0, 0, globals::SCREEN_WIDTH, m_ReelScreenOffset.y };
  m_BotBar = { 0, m_ReelScreenOffset.y + m_Spec.reelScreenHeight, globals::SCREEN_WIDTH, m_ReelScreenOffset.y };
  m_LeftBar = { 0, m_ReelScreenOffset.y, m_ReelScreenOffset.x, m_Spec.reelScreenHeight };
  m_RightBar = { globals::SCREEN_WIDTH - m_ReelScreenOffset.x, m_ReelScreenOffset.y, m_ReelScreenOffset.x, m_Spec.reelScreenHeight };
}

void DisplayManager::setup() {
  setupDisplay();

  EventSystem::getInstance().subscribe([this](const Event* event) {
    if (event->type == EventType::GameStateDecide) {
      SM_ASSERT(event->reels != nullptr, "reels (Reels*) is nullptr in GameStateDecide event")

      m_CurrentReels = event->reels;
      SM_PRINTLN(event->debugInfo)
      startSpin();
    }
  });

  drawBorders();
}

std::tuple<u16*, u16*> DisplayManager::flipLeftAndTopBars() {
  const u16 rightBarSize = m_RightBar.width() * m_RightBar.height();
  const u16 botBarSize = m_BotBar.width() * m_BotBar.height();
  u16* leftImgCpy = new u16[rightBarSize];
  u16* topImgCpy = new u16[botBarSize];

  memcpy(leftImgCpy, iconBmps::leftbar, rightBarSize * sizeof(u16));
  memcpy(topImgCpy, iconBmps::topbar, botBarSize * sizeof(u16));

  flipImageHorizontal(iconBmps::leftbar, leftImgCpy, m_RightBar.size);
  flipImageVertical(iconBmps::topbar, topImgCpy, m_BotBar.size);
  return { leftImgCpy, topImgCpy };
}

void DisplayManager::setupDisplay() {
  m_Display.init();
  m_Display.setRotation(1);
  m_Display.setSwapBytes(true);
  for (u8 i = 0; i < globals::REEL_COUNT; i++) {
    m_ReelSprites[i]->setSwapBytes(true);
    m_ReelSprites[i]->setColorDepth(8);
    m_ReelSprites[i]->createSprite(m_Spec.imageWidth, m_Spec.reelScreenHeight);
    if (!m_ReelSprites[i]->created()) {
      SM_PRINTF("Sprite %d FAILED to create!\n", i)
    }
    SM_PRINTF("Free heap after sprite %d: %d\n", i, ESP.getFreeHeap())
  }

  m_Display.fillScreen(m_Spec.backgroundColor);
  m_Display.setTextColor(m_Spec.foregroundColor);
}

void DisplayManager::drawBorders() {
  auto [rightBar, botBar] = flipLeftAndTopBars();
  m_Display.pushImage(m_TopBar.left(), m_TopBar.top(), m_TopBar.width(), m_TopBar.height(), iconBmps::topbar);
  m_Display.pushImage(m_LeftBar.left(), m_LeftBar.top(), m_LeftBar.width(), m_LeftBar.height(), iconBmps::leftbar);
  m_Display.pushImage(m_BotBar.left(), m_BotBar.top(), m_BotBar.width(), m_BotBar.height(), botBar);
  m_Display.pushImage(m_RightBar.left(), m_RightBar.top(), m_RightBar.width(), m_RightBar.height(), rightBar);
  delete[] rightBar;
  delete[] botBar;
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

  for (u8 i = 0; i < globals::REEL_COUNT; i++) {
    Reel* reel = reelPtrs[i];
    u8 size = reel->size();

    if (m_ReelSpinning[i]) {
      m_ScrollY[i] += m_ReelSpeeds[i];

      while (m_ScrollY[i] >= m_Spec.imageHeight) {
        m_ScrollY[i] -= m_Spec.imageHeight;
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
    sprite.fillSprite(m_Spec.backgroundColor);

    const u16* img = getCharacterIcon((*reel)[curr]);
    const u16* prevImg = getCharacterIcon((*reel)[prev]);
    const u16* prev2Img = getCharacterIcon((*reel)[prev2]);
    const u16* nextImg = getCharacterIcon((*reel)[next]);

    sprite.pushImage(0, m_CenterY - m_Spec.imageHeight * 2 + scrollOffset, m_Spec.imageWidth, m_Spec.imageHeight, prev2Img);
    sprite.pushImage(0, m_CenterY - m_Spec.imageHeight + scrollOffset, m_Spec.imageWidth, m_Spec.imageHeight, prevImg);
    sprite.pushImage(0, m_CenterY + scrollOffset, m_Spec.imageWidth, m_Spec.imageHeight, img);
    sprite.pushImage(0, m_CenterY + m_Spec.imageHeight + scrollOffset, m_Spec.imageWidth, m_Spec.imageHeight, nextImg);

    sprite.pushSprite((i * m_Spec.imageWidth) + m_ReelScreenOffset.x, m_ReelScreenOffset.y);
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
    EventSystem::getInstance().emit(&event);
    m_LoopRunning = false;
  }
}

void DisplayManager::startSpin() {
  for (u8 i = 0; i < globals::REEL_COUNT; i++) {
    m_ScrollY[i] = 0;
    m_ReelOffsets[i] = 0;
    m_ReelSpinning[i] = true;
    m_HasLooped[i] = false;
  }
  m_LoopRunning = true;
  m_StateWin = areReelsWinning(*m_CurrentReels);
  SM_PRINTLN(m_StateWin)
}

}
