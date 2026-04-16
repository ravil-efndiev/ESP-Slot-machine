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

void EventSystem::subscribeToGameWin(const std::function<void(const EventGameWin*)>& eventHandler) {
  m_GameWinHandlers.push_back(eventHandler);
}

void EventSystem::subscribeToGameLoss(const std::function<void(const EventGameLoss*)>& eventHandler) {
  m_GameLossHandlers.push_back(eventHandler);
}

void EventSystem::emit(Event* event) {
  if (event->type == EventType::GameWin) {
    const auto* castedEvt = static_cast<const EventGameWin*>(event);
    for (auto& evtHandler : m_GameWinHandlers) {
      evtHandler(castedEvt);
    }
  }
  else if (event->type == EventType::GameLoss) {
    const auto* castedEvt = static_cast<const EventGameLoss*>(event);
    for (auto& evtHandler : m_GameLossHandlers) {
      evtHandler(castedEvt);
    }
  }
  delete event;
}

}
