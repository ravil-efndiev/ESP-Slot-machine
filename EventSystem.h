#pragma once
#include "macros.h"

namespace sm {

enum class EventType {
  GameStart,
  GameWin,
  GameLoose,
};

struct Event {
  EventType type;
  void* payload;
};

class EventSystem {
public:
  static EventSystem& create();
  static EventSystem& getInstance();

  void subscribe(const std::function<void(const Event&)>& eventHandler);
  void emit(const Event& event);

private:
  EventSystem() = default;
  EventSystem(const EventSystem&) = delete;
  EventSystem(EventSystem&&) = delete;

private:
  static EventSystem* s_Instance;

  std::vector<std::function<void(const Event&)>> m_EventHandlers;
};

}
