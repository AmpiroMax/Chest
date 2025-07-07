#ifndef GUI_RENDER_SYSTEM_H
#define GUI_RENDER_SYSTEM_H

#include "managers/EntityManager.h"
#include "managers/TimeManager.h"
#include "managers/WindowManager.h"
#include "systems/ISystem.h"
#include <imgui-SFML.h>
#include <imgui.h>

class GUIRenderSystem : public ISystem {
  public:
    GUIRenderSystem(WindowManager &winMgr, EntityManager &guiEm, TimeManager &timeMgr)
        : windowManager(winMgr), guiEntitiesManager(guiEm), timeManager(timeMgr) {}

    SystemSignal update() override {
        ImGui::SFML::Render(windowManager.getWindow());
        return SystemSignal::None;
    }

  private:
    WindowManager &windowManager;
    EntityManager &guiEntitiesManager;
    TimeManager &timeManager;
};
#endif
