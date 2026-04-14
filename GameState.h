#pragma once
#include "PRD.h"

namespace sm {

class GameState {
public:
  GameState(const PRDPreset& prdPreset);

  void setup();
  void loop();

private:
  PRDPreset m_ActivePreset;
  const pin m_TestButtonPin = 17;
  bool m_ButtonPressed = false;
  bool m_ButtonLastPressed = false;
};

}
