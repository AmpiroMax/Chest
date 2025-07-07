#include "applications/EditorApp.h"

#include "services/GameConfig.h"
#include "systems/EventSystem.h"
#include "systems/GUIRenderSystem.h"
#include "systems/GUISystem.h"
#include "systems/HIDSystem.h"
#include "systems/OverlayRenderSystem.h"
#include "systems/RenderSystem.h"
#include "systems/TimeSystem.h"
#include "systems/ToolSystem.h"
#include "systems/WindowEventSystem.h"

EditorApp::EditorApp() {
    buildManagers();
    buildSystems();
}

void EditorApp::buildManagers() {
    GameConfig gameConfig("config/game.json");

    auto windowSize = gameConfig.getWindowSize();
    auto windowName = gameConfig.getWindowName();
    windowManager.recreate(windowSize, windowName);
}

void EditorApp::buildSystems() {
    systems.push_back(std::make_unique<TimeSystem>(timeManager));
    systems.push_back(std::make_unique<WindowEventSystem>(windowManager));
    systems.push_back(std::make_unique<HIDSystem>(hidManager, windowManager));
    systems.push_back(std::make_unique<GUISystem>(windowManager, timeManager));
    systems.push_back(std::make_unique<ToolSystem>(guiEntities, hidManager));
    systems.push_back(std::make_unique<OverlayRenderSystem>(windowManager));
    systems.push_back(std::make_unique<GUIRenderSystem>(windowManager, guiEntities, timeManager));
    systems.push_back(std::make_unique<EventSystem>(eventManager));
    systems.push_back(std::make_unique<RenderSystem>(windowManager, gameEntities, resourceManager, cameraManager, debugManager));
    // systems.push_back(std::make_unique<DebugSystem>(gameEntities, cameraManager, nullptr, windowManager, hidManager, debugManager));
}

void EditorApp::run() {
    bool running = true;
    while (running) {
        for (auto &system : systems) {
            SystemSignal signal = system->update();
            if (signal == SystemSignal::Quit) {
                running = false;
                break;
            }
        }
    }
    for (auto &system : systems) {
        system->shutdown();
    }
}
