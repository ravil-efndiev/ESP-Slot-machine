#include "utils.h"

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

bool areReelsWinning(const Reels& reels) {
  return reels.a.back() == reels.b.back() && reels.b.back() == reels.c.back();
}

void flipImageHorizontal(const u16* src, u16* dst, const Vec2<u16>& size) {
  for (u32 y = 0; y < size.height; y++) {
    for (u32 x = 0; x < size.width; x++) {
      dst[y * size.width + x] =
        src[y * size.width + (size.width - 1 - x)];
    }
  }
}

void flipImageVertical(const u16* src, u16* dst, const Vec2<u16>& size) {
  for (u32 y = 0; y < size.height; y++) {
    for (u32 x = 0; x < size.width; x++) {
      dst[y * size.width + x] =
        src[(size.height - 1 - y) * size.width + x];
    }
  }
}

}
