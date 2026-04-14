#pragma once
#include "macros.h"
#include <functional>

namespace sm {

enum class EventType {
  GameStart,
  GameWin,
  GameLoose,
};

struct Event {
  EventType type;
};

class EventSystem {
public:
  static EventSystem& create();
  static EventSystem& getInstance();

  void subscribe(const std::function<void(Event)>& eventHandler);
  void emit(Event event);

private:
  EventSystem() = default;
  EventSystem(const EventSystem&) = delete;
  EventSystem(EventSystem&&) = delete;

private:
  static EventSystem* s_Instance;

  std::vector<std::function<void(Event)>> m_EventHandlers;
};

}
