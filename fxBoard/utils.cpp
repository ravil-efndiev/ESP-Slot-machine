#include "utils.h"
#include <avr/wdt.h>

namespace sm {

void setupPins() {
  pinMode(pins::gameplay, INPUT);
  pinMode(pins::win, INPUT);
  pinMode(pins::loss, INPUT);

  for (i16 i = 0; i < LED_COUNT; i++) {
    pinMode(pins::leds[i], OUTPUT);
  }
}

void writeAllLeds(bool val) {
  for (i16 i = 0; i < LED_COUNT; i++) {
    digitalWrite(pins::leds[i], val);
  }
}

void writeAllLedsBlue(bool val) {
  for (i16 i = 0; i < LED_PER_COL_COUNT; i++) {
    digitalWrite(pins::ledsB[i], val);
  }
}

void writeAllLedsGreen(bool val) {
  for (i16 i = 0; i < LED_PER_COL_COUNT; i++) {
    digitalWrite(pins::ledsG[i], val);
  }
}

void writeAllLedsRed(bool val) {
  for (i16 i = 0; i < LED_PER_COL_COUNT; i++) {
    digitalWrite(pins::ledsR[i], val);
  }
}

void reset() {
  wdt_enable(WDTO_15MS);
  while (1) {}
}

}

using namespace sm;
i16 getFreeRam() {
  extern i16 __heap_start, *__brkval;
  i16 v;
  return (i16)&v - (__brkval == 0 ? (i16)&__heap_start : (i16)__brkval);
}
