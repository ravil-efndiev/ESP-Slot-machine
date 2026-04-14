#pragma once
#include "PRD.h"

namespace sm {

enum class GameResult {
  Win, Loss,
};

struct Reels {
  std::array<char, 10> a {0};
  std::array<char, 10> b {0};
  std::array<char, 10> c {0};
};

class GameState {
public:
  GameState(const PRDPreset& prdPreset);

  void setup();
  void loop();

private:
  GameResult decideGameResult() const;
  void goToNextPRDChance();
  void resetPRDChance();
  Reels generateReelArrays(GameResult result) const;
  void fillReelArray(std::array<char, 10>& reel, std::optional<char> lastChar) const;

private:
  PRDPreset m_ActivePreset;
  
  bool m_ButtonPressed = false;
  bool m_ButtonLastPressed = false;
  u16 m_CurrentWinChance;
  u16 m_CurrentHardcodedChanceIndex = 0;
  const u8 m_AlmostWinChance = 35;
};

}
