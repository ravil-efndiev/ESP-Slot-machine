#pragma once

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

private:
  bool m_LastGameplayRead = false;
  bool m_LastWinRead = false;
  bool m_LastLossRead = false;

  State m_State = State::Idle;

  const int m_WinLossAnimTime = 1000;
  int m_StateStartTime = 0;

  int m_LedIdx = 0;
  int m_LastTime = 0;
  const int m_LedLitupTime = 30;
};

}