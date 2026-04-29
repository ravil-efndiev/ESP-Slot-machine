#pragma once
#include "macros.h"

namespace sm {

// Pins are only allowed to declare and use from here to avoid possible overlap
namespace pins {

constexpr pin testButton = 17;
constexpr pin servoLock = 25;
constexpr pin notifyArduinoFXGameplay = 26;
constexpr pin notifyArduinoFXWin = 13;
constexpr pin notifyArduinoFXLoss = 16;
constexpr pin photores = 36;

}

namespace globals {

constexpr std::array<char, 5> REEL_CHARACTERS = { 'A', 'B', 'C', 'D', 'E' };
constexpr i8 REEL_COUNT = 3;

constexpr u16 SCREEN_WIDTH = 480;
constexpr u16 SCREEN_HEIGHT = 320;

}

}
