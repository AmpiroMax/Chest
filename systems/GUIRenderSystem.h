#ifndef GUI_RENDER_SYSTEM_H
#define GUI_RENDER_SYSTEM_H

#include "managers/EntityManager.h"
#include "managers/EventManager.h"
#include "managers/ToolStateManager.h"
#include "managers/WindowManager.h"
#include "systems/ISystem.h"

class GUIRenderSystem : public ISystem {
  public:
    GUIRenderSystem(WindowManager &winMgr, EntityManager &guiEm, ToolStateManager &toolMgr, EventManager &evtMgr);

    SystemSignal update() override;

  private:
    void renderButtons();

    WindowManager &windowManager;
    EntityManager &guiEntitiesManager;
    ToolStateManager &toolStateManager;
    EventManager &eventManager;
};

#endif /* GUI_RENDER_SYSTEM_H */