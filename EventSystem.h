#pragma once
#include "macros.h"

namespace sm {

enum class EventType {
  GameWin,
  GameLoss,
};

struct Event {
  EventType type;
  Reels* reels;
  String debugInfo;

  Event(EventType type, Reels* reels, const String& debugInfo)
    : type(type), reels(reels), debugInfo(debugInfo) {}
};

struct EventGameWin : public Event {
  EventGameWin(Reels* reels, const String& debugInfo)
    : Event(EventType::GameWin, reels, debugInfo) {}
};

struct EventGameLoss : public Event {
  EventGameLoss(Reels* reels, const String& debugInfo)
    : Event(EventType::GameLoss, reels, debugInfo) {}
};

class EventSystem {
public:
  static EventSystem& create();
  static EventSystem& getInstance();

  void subscribeToGameWin(const std::function<void(const EventGameWin*)>& eventHandler);
  void subscribeToGameLoss(const std::function<void(const EventGameLoss*)>& eventHandler);

  // emits event to its correspoding subscribers and deletes it from memory after use
  void emit(Event* event);

private:
  EventSystem() = default;
  EventSystem(const EventSystem&) = delete;
  EventSystem(EventSystem&&) = delete;

private:
  static EventSystem* s_Instance;

  std::vector<std::function<void(const EventGameWin*)>> m_GameWinHandlers;
  std::vector<std::function<void(const EventGameLoss*)>> m_GameLossHandlers;
};

}
