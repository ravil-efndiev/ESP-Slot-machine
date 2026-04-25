#include "DisplayManager.h"
#include "EventSystem.h"
#include "GameState.h"
#include "DoorLockManager.h"
#include "FXManager.h"
#include "BLE.h"

sm::EventSystem& eventSystem = sm::EventSystem::create();

sm::GameState gameState(sm::PRDPresets::normal);
sm::DisplayManager displayManager(
  (sm::DisplayManagerSpec){
    .backgroundColor = TFT_BLACK,
    .foregroundColor = TFT_WHITE,
  });
sm::DoorLockManager doorLockManager;
sm::FXManager fxManager;

void setup() {
  Serial.begin(SM_SERIAL_BAND_RATE);
  gameState.setup();
  setupBLEforPresetSelect(gameState);
  displayManager.setup();
  doorLockManager.setup();
  fxManager.setup();
}

void loop() {
  gameState.loop();
  displayManager.loop();
  doorLockManager.loop();
}
