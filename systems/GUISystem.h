#ifndef GUI_SYSTEM_H
#define GUI_SYSTEM_H

#include "managers/TimeManager.h"
#include "managers/WindowManager.h"
#include "systems/ISystem.h"
#include <imgui-SFML.h>
#include <imgui.h>

class GUISystem : public ISystem {
  public:
    explicit GUISystem(WindowManager &winMgr, TimeManager &timeMgr) : windowManager(winMgr), timeManager(timeMgr) {
        wasCreated = ImGui::SFML::Init(windowManager.getWindow());
    }
    SystemSignal update() override {
        ImGui::SFML::Update(windowManager.getWindow(), sf::milliseconds(timeManager.getElapsedTime()));
        return SystemSignal::None;
    }

    void shutdown() override {
        if (wasCreated) {
            ImGui::SFML::Shutdown();
            wasCreated = false;
        }
    }

  private:
    WindowManager &windowManager;
    TimeManager &timeManager;
    bool wasCreated = false;
};
#endif
