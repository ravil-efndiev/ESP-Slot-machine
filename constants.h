#pragma once
#include "macros.h"

namespace sm {

// Pins are only allowed to declare and use from here to avoid possible overlap
namespace pins {

const pin testButton = 17;

}

const std::array<char, 5> reelCharacters { 'A', 'B', 'C', 'D', 'E' };

}