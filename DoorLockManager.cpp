#include "DoorLockManager.h"
#include "EventSystem.h"

namespace sm {

void DoorLockManager::setup() {
  m_Servo.attach(pins::servoLockPin);
  EventSystem::getInstance().subscribe([this](const Event* event) {
    if (event->type == EventType::ReelsEndAndWin) {
      m_LockOpening = true;
    }
  });
}

void DoorLockManager::loop() {
  if (!m_LockOpening && !m_LockClosing) return;

  if (m_LockOpening) {
    for (i8 i = 0; i < 180; i++) {
      m_Servo.write(i);
      delay(15);
    }
    m_LockOpening = false;
    return;
  }

  if (m_LockClosing) {
    for (i8 i = 179; i >= 0; i--) {
      m_Servo.write(i);
      delay(15);
    }
    m_LockClosing = false;
    return;
  }
}

}
