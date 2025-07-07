#ifndef OVERLAY_RENDER_SYSTEM_H
#define OVERLAY_RENDER_SYSTEM_H

#include "managers/WindowManager.h"
#include "systems/ISystem.h"

class OverlayRenderSystem : public ISystem {
  public:
    explicit OverlayRenderSystem(WindowManager &w) : wnd_(w) {}
    SystemSignal update() override {
        // пока пусто: сетка / превью / подсветка появятся позже
        return SystemSignal::None;
    }

  private:
    WindowManager &wnd_;
};
#endif
