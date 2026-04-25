#include "pins.h"

namespace sm {

void setupPins() {
  pinMode(pins::gameplay, INPUT);
  pinMode(pins::win, INPUT);
  pinMode(pins::loss, INPUT);

  for (int i = 0; i < SM_LED_COUNT; i++) {
    pinMode(pins::leds[i], OUTPUT);
  }
}

}