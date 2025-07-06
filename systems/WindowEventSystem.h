#ifndef WINDOW_EVENT_SYSTEM_H
#define WINDOW_EVENT_SYSTEM_H

#include "ISystem.h"
#include "WindowManager.h"

class WindowEventSystem : public ISystem {
  public:
    explicit WindowEventSystem(WindowManager &windowManager) : windowManager(windowManager) {}

    SystemSignal update() override;

  private:
    WindowManager &windowManager;
};

#endif // WINDOW_EVENT_SYSTEM_H
