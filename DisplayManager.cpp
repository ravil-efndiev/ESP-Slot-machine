#include "DisplayManager.h"
#include "EventSystem.h"

namespace sm {

DisplayManager::DisplayManager(const DisplayManagerSpec& spec)
  : m_Specification(spec) {}

void DisplayManager::setup() {
  m_Display.init();
  m_Display.fillScreen(m_Specification.backgroundColor);
  m_Display.setTextColor(m_Specification.foregroundColor);
  EventSystem::getInstance().subscribe([](Event event) {
    Serial.println("display manager got notified of event");
  });
}

void DisplayManager::loop() {
}

}
