#include "StateManager.h"
#include "pins.h"

namespace sm {

void StateManager::setup() {
}

void StateManager::loop() {
  selectState();

  switch (m_State) {
    case State::Idle:
      writeAllLeds(LOW);
      break;

    case State::Gameplay:
      runGameplayAnim();
      break;

    case State::Win:
      runWinAnim();
      if (millis() - m_StateStartTime >= m_WinLossAnimTime) {
        m_State = State::Idle;
      }
      break;

    case State::Loss:
      runLossAnim();
      if (millis() - m_StateStartTime >= m_WinLossAnimTime) {
        m_State = State::Idle;
      }
      break;
  }
}

void StateManager::selectState() {
  bool gameplay = digitalRead(pins::gameplay);
  bool currentW = digitalRead(pins::win);
  bool currentL = digitalRead(pins::loss);

  if (gameplay) {
    m_State = State::Gameplay;
  }

  else if (m_State != State::Win && m_State != State::Loss) {
    if (currentW && !m_LastWinRead) {
      m_State = State::Win;
      m_StateStartTime = millis();
    } else if (currentL && !m_LastLossRead) {
      m_State = State::Loss;
      m_StateStartTime = millis();
    } else if (m_State != State::Gameplay) {
      m_State = State::Idle;
    }
  }

  m_LastWinRead = currentW;
  m_LastLossRead = currentL;
}

void StateManager::writeAllLeds(int val) {
  for (int i = 0; i < SM_LED_COUNT; i++) {
    digitalWrite(pins::leds[i], val);
  }
}

void StateManager::runGameplayAnim() {
  for (int i = 0; i < SM_LED_COUNT; i++) {
    digitalWrite(pins::leds[i], HIGH);
    delay(10);
    digitalWrite(pins::leds[i], LOW);
  }
}

void StateManager::runWinAnim() {
}

void StateManager::runLossAnim() {
}

}
