#include "FXManager.h"
#include "EventSystem.h"
#include "constants.h"

namespace sm {

void FXManager::setup() {
  pinMode(pins::notifyArduinoFXGameplay, OUTPUT);
  pinMode(pins::notifyArduinoFXWin, OUTPUT);
  pinMode(pins::notifyArduinoFXLoss, OUTPUT);

  pulldownAll();

  EventSystem::getInstance().subscribe([this](const Event* event) {
    if (event->type == EventType::GameStateDecide) {
      startGameplayFX();
    } else {
      if (event->type == EventType::ReelsEndAndWin) {
        stopGameplayFX();
        startPostGameFX(true);
      } else if (event->type == EventType::ReelsEndAndLoss) {
        stopGameplayFX();
        startPostGameFX(false);
      }
    }
  });
}

void FXManager::startGameplayFX() {
  digitalWrite(pins::notifyArduinoFXGameplay, HIGH);
}

void FXManager::stopGameplayFX() {
  digitalWrite(pins::notifyArduinoFXGameplay, LOW);
}

void FXManager::startPostGameFX(bool isWin) {
  pin arduinoLedPin = isWin ? pins::notifyArduinoFXWin : pins::notifyArduinoFXLoss;
  digitalWrite(arduinoLedPin, HIGH);
  delay(100);
  digitalWrite(arduinoLedPin, LOW);
}

void FXManager::pulldownAll() {
  digitalWrite(pins::notifyArduinoFXWin, LOW);
  digitalWrite(pins::notifyArduinoFXLoss, LOW);
  stopGameplayFX();
}

}
