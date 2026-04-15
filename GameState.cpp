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
    goToNextPRDChance(result);
    m_CurrentReels = generateReelArrays(result);
    event.type = result == GameResult::Win ? EventType::GameWin : EventType::GameLoss;
    event.payload = &m_CurrentReels;
    EventSystem::getInstance().emit(event);
  }
  m_ButtonLastPressed = m_ButtonPressed;
}

GameResult GameState::decideGameResult() const {
  auto roll = random(0, 100);
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
    if (almostWin) {
      char repeatedCharacter = rollCharacter();
      i16 first = random(0, 3);
      i16 second;
      do {
        second = random(0, 3);
      } while (second == first);

      i16 third = 3 - first - second;

      std::array<Reel*, 3> reelPtrs = {
        &reels.a, &reels.b, &reels.c
      };

      char otherCharacter;
      do {
        otherCharacter = rollCharacter();
      } while (otherCharacter == repeatedCharacter);

      fillReelArray(*reelPtrs[first], repeatedCharacter);
      fillReelArray(*reelPtrs[second], repeatedCharacter);
      fillReelArray(*reelPtrs[third], otherCharacter);
      return reels;
    }
    fillReelArraysAllDifferent(reels);
    return reels;
  } else {
    char winCharacter = rollCharacter();
    fillReelArray(reels.a, winCharacter);
    fillReelArray(reels.b, winCharacter);
    fillReelArray(reels.c, winCharacter);
    return reels;
  }
}

void GameState::fillReelArray(Reel& reel, char lastChar) const {
  for (auto& el : reel) {
    el = rollCharacter();
  }

  reel.back() = lastChar;
}

void GameState::fillReelArraysAllDifferent(Reels& reels) const {
  char charA = rollCharacter();
  char charB;
  do {
    charB = rollCharacter();
  } while (charB == charA);
  char charC;
  do {
    charC = rollCharacter();
  } while (charC == charA || charC == charB);

  fillReelArray(reels.a, charA);
  fillReelArray(reels.b, charB);
  fillReelArray(reels.c, charC);
}

char GameState::rollCharacter() const {
  return reelCharacters[random(0, reelCharacters.size())];
}

}
