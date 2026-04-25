#include "pins.h"
#include "StateManager.h"

sm::StateManager stateManager;

void setup() {
  sm::setupPins();
  stateManager.setup();
}

void loop() {
  stateManager.loop();
}
