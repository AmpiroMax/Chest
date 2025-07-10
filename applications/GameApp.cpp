#include "applications/GameApp.h"
#include "core/Entity.h"
#include "factories/ButtonFactory.h"
#include "factories/PlayerFactory.h"
#include "factories/WorldMapFactory.h"
#include "managers/PhysicsManager.h"
#include "services/GameConfig.h"
#include "systems/ButtonSystem.h"
#include "systems/CameraSystem.h"
#include "systems/DebugSystem.h"
#include "systems/EntityControlSystem.h"
#include "systems/EventSystem.h"
#include "systems/GUIRenderSystem.h"
#include "systems/HIDSystem.h"
#include "systems/PhysicsSystem.h"
#include "systems/RenderSystem.h"
#include "systems/WindowEventSystem.h"

GameApp::GameApp() {
    // 0. Загружаем конфиг игры
    GameConfig gameConfig("config/game.json");

    auto windowSize = gameConfig.getWindowSize();
    auto windowName = gameConfig.getWindowName();
    windowManager.recreate(windowSize, windowName);

    // Инициализируем размер viewport камеры
    cameraManager.setViewportSize(Vec2(windowSize));

    auto textureNames = gameConfig.allTextureNames();
    resourceManager.loadTexturesFromList(textureNames, gameConfig.getTexturePath());

    // 2. Загружаем карту, создаём WorldMap entity (physicsManager используется для добавления физики)
    auto worldEntities = WorldMapFactory::loadGameMap(gameConfig, resourceManager, physicsManager);
    for (Entity *ent : worldEntities)
        entityManager.addEntity(ent);

    // 3. Создаём игрока (и мобов, если появятся)
    Entity *player = PlayerFactory::create(gameConfig, resourceManager, physicsManager);
    entityManager.addPlayerEntity(player);

    Entity *pauseBtn = ButtonFactory::create(Vec2(windowSize));
    entityManager.addEntity(pauseBtn);

    eventManager.subscribe<ButtonClickedEvent>([](const auto &e) {
        if (e.id == "pause")
            std::cout << "Кнопка нажата\n";
        if (e.id == "test")
            std::cout << "Тестовая кнопка нажата";
    });

    // 4. Создаём системы
    systems.push_back(std::make_unique<WindowEventSystem>(windowManager));
    systems.push_back(std::make_unique<HIDSystem>(hidManager, windowManager));
    systems.push_back(std::make_unique<ButtonSystem>(entityManager, hidManager, eventManager));
    systems.push_back(std::make_unique<EntityControlSystem>(entityManager, hidManager));
    systems.push_back(std::make_unique<PhysicsSystem>(physicsManager, entityManager));
    systems.push_back(std::make_unique<CameraSystem>(cameraManager, entityManager, hidManager));
    systems.push_back(std::make_unique<EventSystem>(eventManager));
    systems.push_back(std::make_unique<DebugSystem>(entityManager, cameraManager, physicsManager, windowManager, hidManager, debugManager));
    systems.push_back(std::make_unique<RenderSystem>(windowManager, entityManager, resourceManager, cameraManager, debugManager));
    systems.push_back(std::make_unique<GUIRenderSystem>(windowManager, entityManager, toolStateManager, eventManager));
}

void GameApp::run() {
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
}
