#include "applications/EditorApp.h"

#include "factories/ButtonFactory.h"
#include "services/GameConfig.h"
#include "systems/ButtonSystem.h"
#include "systems/DebugSystem.h"
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
    initUI();
}

void EditorApp::buildManagers() {
    GameConfig gameConfig("config/game.json");

    auto windowSize = gameConfig.getWindowSize();
    auto windowName = gameConfig.getWindowName();
    auto textureNames = gameConfig.allTextureNames();

    windowManager.recreate(windowSize, windowName);
    cameraManager.setViewportSize(windowManager.getWindowSize());
    resourceManager.loadTexturesFromList(textureNames, gameConfig.getTexturePath());
}

void EditorApp::initUI() {
    ButtonFactory bf;

    // Place buttons 200 pixels from the right edge of the window
    float buttonOffsetX = windowManager.getWindowSize().x - 150.0f;
    entityManager.addEntity(bf.makeButton("cursor", "Cursor", {buttonOffsetX, 10}));
    entityManager.addEntity(bf.makeButton("rect", "Rect", {buttonOffsetX, 46}));
    entityManager.addEntity(bf.makeButton("poly", "Poly", {buttonOffsetX, 82}));
    entityManager.addEntity(bf.makeButton("circle", "Circle", {buttonOffsetX, 118}));
}

void EditorApp::buildSystems() {
    systems.push_back(std::make_unique<TimeSystem>(timeManager));
    systems.push_back(std::make_unique<WindowEventSystem>(windowManager));
    systems.push_back(std::make_unique<HIDSystem>(hidManager, windowManager));
    systems.push_back(std::make_unique<ButtonSystem>(entityManager, hidManager, eventManager));
    systems.push_back(std::make_unique<EventSystem>(eventManager));
    systems.push_back(std::make_unique<ToolSystem>(entityManager, toolStateManager, hidManager, eventManager, resourceManager, physicsManager, cameraManager));
    systems.push_back(std::make_unique<GUISystem>(windowManager));
    systems.push_back(std::make_unique<RenderSystem>(windowManager, entityManager, resourceManager, cameraManager, debugManager));
    systems.push_back(std::make_unique<GUIRenderSystem>(windowManager, entityManager, toolStateManager, eventManager));
    systems.push_back(std::make_unique<OverlayRenderSystem>(windowManager));
    systems.push_back(std::make_unique<DebugSystem>(entityManager, cameraManager, physicsManager, windowManager, hidManager, debugManager));
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
