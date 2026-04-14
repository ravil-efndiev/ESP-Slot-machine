#pragma once
#include "macros.h"
#include <tuple>

namespace sm {

enum class PRDPresetType {
  Incrementing,
  Hardcoded,
};

// Pseudorandom distribution system handles controlled win chances by
// increasing and lowering win chances based on results before (or setting fixed win loss values)
struct PRDPreset {
  PRDPresetType type;

  u16 startChance;
  u16 increment;
  u16 maxChance;
  // fallback is the chance that you reset with after a win (lower then the start chance)
  // if fallback is -1 then chance will restart from start value
  i16 fallback;

  std::vector<u16> hardcodedValues;

  PRDPreset(u16 startChance, u16 increment, u16 maxChance, i16 fallback = -1)
    : type(PRDPresetType::Incrementing), startChance(startChance),
      increment(increment), maxChance(maxChance), fallback(fallback) {}

  PRDPreset(const std::initializer_list<u16>& hardcodedValues, i16 fallback = -1)
    : type(PRDPresetType::Hardcoded), hardcodedValues(hardcodedValues), fallback(fallback) {}
};

namespace PRDPresets {
  const PRDPreset normal(25, 10, 90);
  const PRDPreset extraLucky(40, 10, 100);
  const PRDPreset twoThenWin({0, 0, 100});
  const PRDPreset threeThenWin({0, 0, 0, 100});
  const PRDPreset wl2({0, 100, 0, 100});
  const PRDPreset wl3({0, 100, 0, 100, 0, 100});
};

}