#ifndef TIME_SYSTEM_H
#define TIME_SYSTEM_H

#include "managers/TimeManager.h"
#include "systems/ISystem.h"

class TimeSystem : public ISystem {
  public:
    explicit TimeSystem(TimeManager &t) : tm_(t) {}
    SystemSignal update() override {
        tm_.tick();
        return SystemSignal::None;
    }

  private:
    TimeManager &tm_;
};
#endif
