#pragma once
#include "icons.h"
#include "constants.h"

namespace sm {

template <class T>
struct Vec2 {
  union { T x; T width; };
  union { T y; T height; };

  Vec2(T x, T y) : x(x), y(y) {}
  Vec2(T scalar) : x(scalar), y(scalar) {}
  Vec2() : Vec2(0) {}
};

template <class T>
struct Rect {
  Vec2<T> pos;
  Vec2<T> size;

  Rect(T x, T y, T w, T h) : pos(x, y), size(w, h) {}
  Rect() = default;

  T left() const { return pos.x; }
  T top() const { return pos.y; }
  T width() const { return size.width; }
  T height() const { return size.height; }
};

const u16* getCharacterIcon(char character);

bool areReelsWinning(const Reels& reels);

void flipImageHorizontal(const u16* src, u16* dst, const Vec2<u16>& size);
void flipImageVertical(const u16* src, u16* dst, const Vec2<u16>& size);

}
