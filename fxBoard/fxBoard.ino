#include "StateManager.h"

sm::StateManager stateManager;

void setup() {
  SM_USE_SERIAL
  sm::setupPins();
}

void loop() {
  stateManager.loop();
}
