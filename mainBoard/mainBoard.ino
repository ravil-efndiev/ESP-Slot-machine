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
    .reelScreenWidth = 360, // 480
    .reelScreenHeight = 240, // 320
    .imageWidth = 120, // 160
    .imageHeight = 75, // 100
  });
  
sm::DoorLockManager doorLockManager;
sm::FXManager fxManager;

void setup() {
  SM_USE_SERIAL
  gameState.setup();
  displayManager.setup();
  doorLockManager.setup();
  fxManager.setup();
  setupBLEControls(gameState, doorLockManager);
}

void loop() {
  gameState.loop();
  displayManager.loop();
  doorLockManager.loop();
}
