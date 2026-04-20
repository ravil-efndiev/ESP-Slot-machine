#pragma once
#include "macros.h"

namespace sm {

// Pins are only allowed to declare and use from here to avoid possible overlap
namespace pins {

const pin testButton = 17;
const pin servoLockPin = 26;

}

namespace globals {

constexpr std::array<char, 5> REEL_CHARACTERS = { 'A', 'B', 'C', 'D', 'E' };
constexpr i8 REEL_COUNT = 3;

constexpr u16 SCREEN_WIDTH = 480;
constexpr u16 SCREEN_HEIGHT = 320;

}

}
