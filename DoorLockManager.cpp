#include "DoorLockManager.h"
#include "EventSystem.h"
#include "constants.h"

namespace sm {

void DoorLockManager::setup() {
  ESP32PWM::allocateTimer(0);
  m_Servo.setPeriodHertz(50);
  m_Servo.attach(pins::servoLockPin, 500, 2400);
  m_Servo.write(0);

  EventSystem::getInstance().subscribe([this](const Event* event) {
    if (event->type == EventType::ReelsEndAndWin) {
      m_LockOpening = true;
    }
  });
}

void DoorLockManager::loop() {
  if (!m_LockOpening && !m_LockClosing) return;

  if (m_LockOpening) {
    m_Servo.write(180);
    m_LockOpening = false;
    return;
  }

  if (m_LockClosing) {
    m_Servo.write(0);
    m_LockClosing = false;
    return;
  }
}

}
