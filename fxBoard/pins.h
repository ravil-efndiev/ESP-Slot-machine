#pragma once
#include <Arduino.h>

#define SM_LED_COUNT 12

namespace sm {

using pin = char;

namespace pins {

constexpr pin gameplay = A5;
constexpr pin win = A4;
constexpr pin loss = A3;

constexpr pin leds[SM_LED_COUNT] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12 };

}

void setupPins();

}
