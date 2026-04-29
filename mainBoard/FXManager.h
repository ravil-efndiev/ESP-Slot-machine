#pragma once

namespace sm {

class FXManager {
public:
  FXManager() = default;

  void setup();
  
private:
  void startGameplayFX();
  void stopGameplayFX();
  void startPostGameFX(bool isWin);
  void pulldownAll();
};

}