#include "GameState.h"
#include "EventSystem.h"

namespace sm {

GameState::GameState(const PRDPreset& prdPreset)
  : m_ActivePreset(prdPreset) {}

void GameState::setup() {
  pinMode(m_TestButtonPin, OUTPUT);
}

void GameState::loop() {
  m_ButtonPressed = digitalRead(m_TestButtonPin);
  if (!m_ButtonPressed && m_ButtonLastPressed) {
    EventSystem::getInstance().emit(Event(EventType::GameStart));
  }
  m_ButtonLastPressed = m_ButtonPressed;
}

}
