#include "GameState.h"
#include "EventSystem.h"

namespace sm {

GameState::GameState(const PRDPreset& prdPreset)
  : m_ActivePreset(prdPreset), m_CurrentWinChance(prdPreset.startChance) {}

void GameState::setup() {
  pinMode(pins::testButton, OUTPUT);
  randomSeed(esp_random());
}

void GameState::loop() {
  m_ButtonPressed = digitalRead(pins::testButton);
  if (!m_ButtonPressed && m_ButtonLastPressed) {
    Event event;
    auto result = decideGameResult();
    goToNextPRDChance();
    EventSystem::getInstance().emit();
  }
  m_ButtonLastPressed = m_ButtonPressed;
}

GameResult GameState::decideGameResult() const {
  const roll = random(0, 100);
  return roll < m_CurrentWinChance ? GameResult::Win : GameResult::Loss;
}

void GameState::goToNextPRDChance(GameResult currentResult) {
  if (currentResult == GameResult::Win) {
    resetPRDChance();
    return;
  }

  if (m_ActivePreset.type == PRDPresetType::Incrementing) {
    if (m_CurrentWinChance >= m_ActivePreset.maxChance) {
      resetPRDChance();
      return;
    }
    m_CurrentWinChance += m_ActivePreset.increment;
  } else if (m_ActivePreset.type == PRDPresetType::Hardcoded) {
    auto& values = m_ActivePreset.hardcodedValues;
    if (m_CurrentHardcodedChanceIndex >= values.size() - 1) {
      resetPRDChance();
      return;
    }
    m_CurrentHardcodedChanceIndex++;
    m_CurrentWinChance = values[m_CurrentHardcodedChanceIndex];
  }
}

void GameState::resetPRDChance() {
  m_CurrentWinChance = m_ActivePreset.fallback != -1 ? m_ActivePreset.fallback : m_ActivePreset.startChance;
  m_CurrentHardcodedChanceIndex = 0;
}

Reels GameState::generateReelArrays(GameResult result) const {
  Reels reels{};
  if (result == GameResult::Loss) {
    bool almostWin = random(0, 100) < m_AlmostWinChance;
    // TODO: implement almost win and loss cases
  } else {
    // TODO: implement win case
  }
}

void GameState::fillReelArray(std::array<char, 10>& reel, std::optional<char> lastChar) const {
  for (auto& el : reel) {
    el = reelCharacters[random(0, reelCharacters.size())];
  }

  if (lastChar.has_value()) {
    reel.back() = *lastChar;
  }
}

}
