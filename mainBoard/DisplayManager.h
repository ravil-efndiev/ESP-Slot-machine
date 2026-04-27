#pragma once
#include "constants.h"
#include "utils.h"

namespace sm {

struct DisplayManagerSpec {
  u16 backgroundColor;
  u16 foregroundColor;
  u16 reelScreenWidth;
  u16 reelScreenHeight;
  u16 imageWidth;
  u16 imageHeight;
};

class DisplayManager {
public:
  DisplayManager(const DisplayManagerSpec& spec);

  void setup();
  void loop();

private:
  void startSpin();
  void initRectBounds();

private:
  DisplayManagerSpec m_Spec;
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
  bool m_HasLooped[globals::REEL_COUNT] = { false, false, false };
  float m_ScrollY[globals::REEL_COUNT] = { 0, 0, 0 };
  float m_ReelSpeeds[globals::REEL_COUNT] = { 30.0f, 40.0f, 50.0f };

  u16 m_CenterY = m_Spec.reelScreenHeight / 2 - m_Spec.imageHeight / 2;
  const u32 m_FrameTime = 33;

  Vec2<u16> m_ReelScreenOffset;
  Rect<u16> m_TopBar;
  Rect<u16> m_BotBar;
  Rect<u16> m_LeftBar;
  Rect<u16> m_RightBar;
};

}
