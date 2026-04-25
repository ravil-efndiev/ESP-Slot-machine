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
  void setup();
  void loop();


private:
  void selectState();
  void runGameplayAnim();
  void runWinAnim();
  void runLossAnim();
  void writeAllLeds(int val);

private:
  bool m_LastGameplayRead = false;
  bool m_LastWinRead = false;
  bool m_LastLossRead = false;

  State m_State = State::Idle;

  const int m_WinLossAnimTime = 1000;
  int m_StateStartTime = 0;
};

}