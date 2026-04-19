#pragma once
#include "icons.h"
#include "constants.h"

namespace sm {

const u16* getCharacterIcon(char character) {
  switch (character) {
    case globals::REEL_CHARACTERS[0]: return iconBmps::seven;
    case globals::REEL_CHARACTERS[1]: return iconBmps::bar;
    case globals::REEL_CHARACTERS[2]: return iconBmps::banana;
    case globals::REEL_CHARACTERS[3]: return iconBmps::strawberry;
    case globals::REEL_CHARACTERS[4]: return iconBmps::diamond;
    default:
      SM_ASSERT(false, "unsupported character passed to getCharacterIcon")
  }
}

}
