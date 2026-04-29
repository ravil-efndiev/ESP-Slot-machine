#pragma once
#include "PRD.h"

namespace sm {

enum class GameResult {
  Win,
  Loss,
};

class GameState {
public:
  GameState(const PRDPreset& prdPreset);

  void setup();
  void loop();

  void setPRDPreset(const PRDPreset& prdPreset);

private:
  GameResult decideGameResult(char* debugInfo) const;
  void goToNextPRDChance(GameResult result);
  void resetPRDChance();
  Reels generateReelArrays(GameResult result, char* debugInfo) const;
  void fillReelArray(Reel& reel, char lastChar) const;
  void fillReelArraysAllDifferent(Reels& reels) const;
  char rollCharacter() const;
  void addReelDataToDebugInfo(const char* state, const Reels& reels, char* debugInfo) const;

private:
  PRDPreset m_ActivePreset;

  bool m_LaserReads = false;
  bool m_PrevLaserReads = false;
  u16 m_CurrentWinChance;
  u16 m_CurrentHardcodedChanceIndex = 0;
  const u8 m_AlmostWinChance = 35;
  const u16 m_LightThreshold = 1000;

  Reels m_CurrentReels{};
};

}
