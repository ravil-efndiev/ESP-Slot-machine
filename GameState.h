#pragma once
#include "PRD.h"

namespace sm {

enum class GameResult {
  Win, Loss,
};

class GameState {
public:
  GameState(const PRDPreset& prdPreset);

  void setup();
  void loop();

private:
  GameResult decideGameResult(String& debugInfo) const;
  void goToNextPRDChance(GameResult result);
  void resetPRDChance();
  Reels generateReelArrays(GameResult result, String& debugInfo) const;
  void fillReelArray(Reel& reel, char lastChar) const;
  void fillReelArraysAllDifferent(Reels& reels) const;
  char rollCharacter() const;

private:
  PRDPreset m_ActivePreset;
  
  bool m_ButtonPressed = false;
  bool m_ButtonLastPressed = false;
  u16 m_CurrentWinChance;
  u16 m_CurrentHardcodedChanceIndex = 0;
  const u8 m_AlmostWinChance = 35;

  Reels m_CurrentReels{};
};

}
