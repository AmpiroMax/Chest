#ifndef GUI_SYSTEM_H
#define GUI_SYSTEM_H

#include "managers/WindowManager.h"
#include "systems/ISystem.h"

class GUISystem : public ISystem {
  public:
    explicit GUISystem(WindowManager &winMgr) : windowManager(winMgr) {}
    SystemSignal update() override { return SystemSignal::None; }

  private:
    WindowManager &windowManager;
};
#endif
