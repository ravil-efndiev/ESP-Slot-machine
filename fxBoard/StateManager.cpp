#include "StateManager.h"

namespace sm {

void StateManager::loop() {
  selectState();

  switch (m_State) {
    case State::Gameplay:
      SM_PRINTLN("state: gp");
      runGameplayAnim();
      break;
    case State::Win:
      SM_PRINTLN("state: win");
      runWinAnim();
      if (millis() - m_StateStartTime >= m_WinLossAnimTime) {
        m_State = State::Idle;
        writeAllLeds(LOW);
      }
      break;
    case State::Loss:
      SM_PRINTLN("state: loss");
      runLossAnim();
      if (millis() - m_StateStartTime >= m_WinLossAnimTime) {
        m_State = State::Idle;
        writeAllLeds(LOW);
      }
      break;
  }
}

void StateManager::selectState() {
  bool gameplay = digitalRead(pins::gameplay);
  bool currentW = digitalRead(pins::win);
  bool currentL = digitalRead(pins::loss);

  if (gameplay) {
    if (m_State != State::Gameplay) {
      m_LastTime = millis();
      m_LedIdx = 0;
    }
    m_State = State::Gameplay;
  }

  else if (m_State != State::Win && m_State != State::Loss) {
    if (!currentW && m_LastWinRead) {
      m_State = State::Win;
      m_StateStartTime = millis();
    } else if (!currentL && m_LastLossRead) {
      m_State = State::Loss;
      m_StateStartTime = millis();
    } else if (m_State != State::Gameplay) {
      m_State = State::Idle;
    }
  }

  m_LastWinRead = currentW;
  m_LastLossRead = currentL;
}

void StateManager::runGameplayAnim() {
  auto now = millis();

  if (now - m_LastTime >= m_LedLitupTime) {
    if (m_LedIdx == 0) {
      digitalWrite(pins::leds[LED_COUNT - 1], LOW);
    } else {
      digitalWrite(pins::leds[m_LedIdx - 1], LOW);
    }
    digitalWrite(pins::leds[m_LedIdx], HIGH);
    if (m_LedIdx == LED_COUNT - 1) {
      m_LedIdx = 0;
    } else {
      m_LedIdx++;
    }
    m_LastTime = now;
  }
}

void StateManager::runWinAnim() {
  writeAllLeds(LOW);
  writeAllLedsBlue(HIGH);
  writeAllLedsGreen(HIGH);
}

void StateManager::runLossAnim() {
  writeAllLeds(LOW);
  writeAllLedsRed(HIGH);
}

}
