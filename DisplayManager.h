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
};

}
