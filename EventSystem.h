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

  // emits event to its correspoding subscribers and deletes it from memory after use
  void emit(Event* event);
  void subscribe(const std::function<void(const Event*)>& eventHandler);

private:
  EventSystem() = default;
  EventSystem(const EventSystem&) = delete;
  EventSystem(EventSystem&&) = delete;

private:
  static EventSystem* s_Instance;

  std::vector<std::function<void(const Event*)>> m_Handlers;
};

}
