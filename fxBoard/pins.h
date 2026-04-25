#pragma once
#include <Arduino.h>
#include "macros.h"

namespace sm {

constexpr int LED_COUNT = 12;
constexpr int COLORS_COUNT = 3;

using pin = char;

namespace pins {

constexpr pin gameplay = A5;
constexpr pin win = A4;
constexpr pin loss = A3;

// pin D9 is skipped because it is broken on my board
constexpr pin leds[LED_COUNT] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12 };

constexpr pin ledsB[LED_COUNT / COLORS_COUNT] = { 0, 3, 6, 10 };
constexpr pin ledsG[LED_COUNT / COLORS_COUNT] = { 1, 4, 7, 11 };
constexpr pin ledsR[LED_COUNT / COLORS_COUNT] = { 2, 5, 8, 12 };

}

void writeAllLeds(int val);
void writeAllLedsBlue(int val);
void writeAllLedsGreen(int val);
void writeAllLedsRed(int val);

void setupPins();

void reset();

}
