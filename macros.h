#pragma once
#include <TFT_eSPI.h>
#include <array>
#include <vector>
#include <functional>

#define SM_SERIAL_BAND_RATE 115200

#define SM_ASSERT(cond, err) \
  if (!(cond)) { \
    Serial.println(err); \
    abort(); \
  }

namespace sm {

using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;
using pin = u8;

}
