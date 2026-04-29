#pragma once
#include "utils.h"

namespace sm {

enum class State {
  Gameplay,
  Win,
  Loss,
  Idle,
};

class StateManager {
public:
  void loop();

private:
  void selectState();
  void runGameplayAnim();
  void runWinAnim();
  void runLossAnim();
  void runGameplaySound();

private:
  bool m_LastGameplayRead = false;
  bool m_LastWinRead = false;
  bool m_LastLossRead = false;

  State m_State = State::Idle;

  const u32 m_WinLossAnimTime = 1000;
  u32 m_StateStartTime = 0;

  u16 m_LedIdx = 0;
  u32 m_LastTime = 0;
  u32 m_LastToneTime = 0;
  const u32 m_LedLitupTime = 30;

  u8 m_ToneIndex = 0;
};

}