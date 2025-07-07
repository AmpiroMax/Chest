#ifndef TIME_SYSTEM_H
#define TIME_SYSTEM_H

#include "managers/TimeManager.h"
#include "systems/ISystem.h"

class TimeSystem : public ISystem {
  public:
    explicit TimeSystem(TimeManager &tmMgr) : timeManager(tmMgr) {}
    SystemSignal update() override {
        timeManager.restart();
        return SystemSignal::None;
    }

  private:
    TimeManager &timeManager;
};
#endif
