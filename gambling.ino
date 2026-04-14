#include "DisplayManager.h"
#include "EventSystem.h"
#include "GameState.h"

sm::EventSystem& eventSystem = sm::EventSystem::create();

sm::DisplayManager displayManager(
  (sm::DisplayManagerSpec){
    .backgroundColor = TFT_BLACK,
    .foregroundColor = TFT_WHITE,
  });

sm::GameState gameState(sm::PRDPresets::normal);

void setup() {
  Serial.begin(SM_SERIAL_BAND_RATE);
  gameState.setup();
  displayManager.setup();
}

void loop() {
  gameState.loop();
  displayManager.loop();
}
