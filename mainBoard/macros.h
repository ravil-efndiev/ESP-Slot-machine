#pragma once
#include <TFT_eSPI.h>
#include <array>
#include <vector>
#include <functional>
#include <string>
#include <tuple>

#define SM_SERIAL_BAND_RATE 115200

#define SM_ASSERT(cond, err) \
  if (!(cond)) { \
    Serial.println(err); \
    abort(); \
  }

#define SM_DEBUG

#ifdef SM_DEBUG 
  #define SM_USE_SERIAL Serial.begin(SM_SERIAL_BAND_RATE);

  #define SM_PRINT(v) Serial.print(v);
  #define SM_PRINTLN(v) Serial.println(v);
  #define SM_PRINTF(fmt, ...) Serial.printf(fmt, ##__VA_ARGS__);
#else
  #define SM_USE_SERIAL

  #define SM_PRINT(v)
  #define SM_PRINTLN(v)
  #define SM_PRINTF(fmt, ...)
#endif

namespace sm {

using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;
using pin = u8;

using Reel = std::array<char, 10>;
struct Reels {
  Reel a {0};
  Reel b {0};
  Reel c {0};
};

}
