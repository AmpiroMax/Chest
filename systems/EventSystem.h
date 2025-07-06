// EventSystem.h
#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "managers/EventManager.h"
#include "systems/ISystem.h"

class EventSystem : public ISystem {
  public:
    explicit EventSystem(EventManager &em) : events(em) {}
    SystemSignal update() override {
        events.update();
        return SystemSignal::None;
    }

  private:
    EventManager &events;
};

#endif // EVENT_SYSTEM_H
