#include "pins.h"
#include <avr/wdt.h>

namespace sm {

void setupPins() {
  pinMode(pins::gameplay, INPUT);
  pinMode(pins::win, INPUT);
  pinMode(pins::loss, INPUT);

  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(pins::leds[i], OUTPUT);
  }
}

void writeAllLeds(int val) {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(pins::leds[i], val);
  }
}

void writeAllLedsBlue(int val) {
  for (int i = 0; i < LED_COUNT / COLORS_COUNT; i++) {
    digitalWrite(pins::ledsB[i], val);
  }
}

void writeAllLedsGreen(int val) {
  for (int i = 0; i < LED_COUNT / COLORS_COUNT; i++) {
    digitalWrite(pins::ledsG[i], val);
  }
}

void writeAllLedsRed(int val) {
  for (int i = 0; i < LED_COUNT / COLORS_COUNT; i++) {
    digitalWrite(pins::ledsR[i], val);
  }
}

void reset() {
  wdt_enable(WDTO_15MS);
  while (1) {}
}

}