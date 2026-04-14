#include "EventSystem.h"

namespace sm {

EventSystem* EventSystem::s_Instance = nullptr;

EventSystem& EventSystem::create() {
  SM_ASSERT(!s_Instance, "Event system can only be created once");

  s_Instance = new EventSystem();
  return *s_Instance;
}

EventSystem& EventSystem::getInstance() {
  SM_ASSERT(s_Instance, "Event system instance hasn't been created");

  return *s_Instance;
}

void EventSystem::subscribe(const std::function<void(Event)>& eventHandler) {
  m_EventHandlers.push_back(eventHandler);
}

void EventSystem::emit(Event event) {
  for (auto& evtHandler : m_EventHandlers) {
    evtHandler(event);
  }
}

}
