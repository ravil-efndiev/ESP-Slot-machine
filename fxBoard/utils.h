#pragma once
#include <Arduino.h>
#include "macros.h"

namespace sm {

using pin = uint8_t;

using u16 = uint16_t;
using u32 = uint32_t;
using i16 = int16_t;

constexpr i16 LED_COUNT = 12;
constexpr i16 COLORS_COUNT = 3;
constexpr i16 LED_PER_COL_COUNT = LED_COUNT / COLORS_COUNT;

namespace pins {

constexpr pin gameplay = A5;
constexpr pin win = A4;
constexpr pin loss = A3;
constexpr pin buzzer = A2;

// pin D9 is skipped because it is broken on my board
constexpr pin leds[LED_COUNT] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12 };

constexpr pin ledsB[LED_PER_COL_COUNT] = { 0, 3, 6, 10 };
constexpr pin ledsG[LED_PER_COL_COUNT] = { 1, 4, 7, 11 };
constexpr pin ledsR[LED_PER_COL_COUNT] = { 2, 5, 8, 12 };

}

void writeAllLeds(bool val);
void writeAllLedsBlue(bool val);
void writeAllLedsGreen(bool val);
void writeAllLedsRed(bool val);

void setupPins();

void reset();

}

int getFreeRam();
