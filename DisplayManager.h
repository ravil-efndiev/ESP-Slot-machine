#pragma once
#include "macros.h"

namespace sm {

struct DisplayManagerSpec {
  u16 backgroundColor;
  u16 foregroundColor;
};

class DisplayManager {
public:
  DisplayManager(const DisplayManagerSpec& spec);

  void setup();
  void loop();

private:
  DisplayManagerSpec m_Specification;
  TFT_eSPI m_Display;
  Reels* m_CurrentReels;
  bool m_LoopRunning = false;

  const u16 m_FrameTime = 1000;
  u16 m_LastTime = 0;
};

}
