#pragma once
#include <ESP32Servo.h>

namespace sm {

class DoorLockManager {
public:
  DoorLockManager() = default;

  void setup();
  void loop();

private:
  Servo m_Servo;
  bool m_LockOpening = false;
  bool m_LockClosing = false;
};

}