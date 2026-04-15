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
  EventSystem::getInstance().subscribe([this](Event event) {
    EventType evtType = event.type;
    m_CurrentReels = static_cast<Reels*>(event.payload);
    m_LoopRunning = true;
  });
}

void DisplayManager::loop() {

  if (m_LoopRunning) {
    std::array<Reel*, 3> reelPtrs = {
      &m_CurrentReels->a, &m_CurrentReels->b, &m_CurrentReels->c
    };

    for (const auto* reel : reelPtrs) {
      Serial.print(String(reel->back()));
    }
    Serial.println();
  }
}

}
