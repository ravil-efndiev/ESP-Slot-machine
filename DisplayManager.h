#pragma once
#include "constants.h"

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
  void startSpin();

private:
  DisplayManagerSpec m_Specification;
  TFT_eSPI m_Display;
  Reels* m_CurrentReels;
  u32 m_LastTime = 0;
  bool m_LoopRunning = false;
  bool m_StateWin = false;

  TFT_eSprite m_SpriteA;
  TFT_eSprite m_SpriteB;
  TFT_eSprite m_SpriteC;
  TFT_eSprite* m_ReelSprites[globals::REEL_COUNT];

  u8 m_ReelOffsets[globals::REEL_COUNT] = { 0, 0, 0 };
  bool m_ReelSpinning[globals::REEL_COUNT] = { true, true, true };
  bool m_HasLooped[3] = {false, false, false};
  float m_ScrollY[globals::REEL_COUNT] = { 0, 0, 0 };
  float m_ReelSpeeds[globals::REEL_COUNT] = { 50.0f, 60.0f, 70.0f };

  const u8 m_IconWidth = 160;
  const u8 m_IconHeight = 100;
  const i16 m_CenterY = globals::SCREEN_HEIGHT / 2 - m_IconHeight / 2;
  const u32 m_FrameTime = 8;
};

}
