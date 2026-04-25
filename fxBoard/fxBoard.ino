#include "pins.h"
#include "StateManager.h"

sm::StateManager stateManager;

void setup() {
  SM_USE_DEBUG;
  sm::setupPins();
}

void loop() {
  stateManager.loop();
}
