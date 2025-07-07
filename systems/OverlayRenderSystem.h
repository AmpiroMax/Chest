#ifndef OVERLAY_RENDER_SYSTEM_H
#define OVERLAY_RENDER_SYSTEM_H

#include "managers/WindowManager.h"
#include "systems/ISystem.h"

class OverlayRenderSystem : public ISystem {
  public:
    explicit OverlayRenderSystem(WindowManager &winMgr) : windowManager(winMgr) {}
    SystemSignal update() override { return SystemSignal::None; }

  private:
    WindowManager &windowManager;
};
#endif
