#include "DisplayManager.h"
#include "EventSystem.h"
#include "GameState.h"

namespace sm {

DisplayManager::DisplayManager(const DisplayManagerSpec& spec)
  : m_Specification(spec) {}

void DisplayManager::setup() {
  m_Display.init();
  m_Display.fillScreen(m_Specification.backgroundColor);
  m_Display.setTextColor(m_Specification.foregroundColor);
  EventSystem::getInstance().subscribeToGameWin([this](const EventGameWin* event) {
    m_CurrentReels = event->reels;
    Serial.println(event->debugInfo);
    m_LoopRunning = true;
  });
  EventSystem::getInstance().subscribeToGameLoss([this](const EventGameLoss* event) {
    m_CurrentReels = event->reels;
    Serial.println(event->debugInfo);
    m_LoopRunning = true;
  });
}

void DisplayManager::loop() {

  if (m_LoopRunning) {
    auto now = millis();
    if (now - m_LastTime >= m_FrameTime) {
      m_Display.fillScreen(m_Specification.backgroundColor);
      std::array<Reel*, 3> reelPtrs = {
        &m_CurrentReels->a, &m_CurrentReels->b, &m_CurrentReels->c
      };
      m_Display.setTextColor(m_Specification.foregroundColor);

      for (u16 i = 0; i < 3; i++) {
        m_Display.drawString(String(reelPtrs[i]->back()), 10 + (i * 10 * 4), 10, 4);
      }
      m_LastTime = now;
    }
  }
}

}
