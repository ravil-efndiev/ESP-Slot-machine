#include "DisplayManager.h"
#include "EventSystem.h"
#include "GameState.h"
#include "DoorLockManager.h"
#include "BLE.h"

sm::EventSystem& eventSystem = sm::EventSystem::create();

sm::DisplayManager displayManager(
  (sm::DisplayManagerSpec){
    .backgroundColor = TFT_BLACK,
    .foregroundColor = TFT_WHITE,
  });

sm::GameState gameState(sm::PRDPresets::normal);

sm::DoorLockManager doorLockManager;

void setup() {
  Serial.begin(SM_SERIAL_BAND_RATE);
  gameState.setup();
  setupBLEforPresetSelect(gameState);
  displayManager.setup();
  doorLockManager.setup();
}

void loop() {
  gameState.loop();
  displayManager.loop();
  doorLockManager.loop();
}
