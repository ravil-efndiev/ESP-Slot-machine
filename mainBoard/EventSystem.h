#pragma once
#include "macros.h"

namespace sm {

enum class EventType {
  GameStateDecide,
  ReelsEndAndWin,
  ReelsEndAndLoss,
};

struct Event {
  EventType type;
  Reels* reels;
  const char* debugInfo;

  Event(EventType type, Reels* reels, const char* debugInfo)
    : type(type), reels(reels), debugInfo(debugInfo) {}
};

class EventSystem {
public:
  static EventSystem& create();
  static EventSystem& getInstance();

  void subscribe(const std::function<void(const Event*)>& eventHandler);
  void emit(Event* event);

private:
  EventSystem() = default;
  EventSystem(const EventSystem&) = delete;
  EventSystem(EventSystem&&) = delete;

private:
  static EventSystem* s_Instance;

  std::vector<std::function<void(const Event*)>> m_Handlers;
};

}
