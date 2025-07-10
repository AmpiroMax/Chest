#ifndef GAME_APP_H
#define GAME_APP_H

#include "events/Events.h"
#include "managers/CameraManager.h"
#include "managers/DebugManager.h"
#include "managers/EntityManager.h"
#include "managers/EventManager.h"
#include "managers/HIDManager.h"
#include "managers/PhysicsManager.h"
#include "managers/ResourceManager.h"
#include "managers/ToolStateManager.h"
#include "managers/WindowManager.h"

#include "systems/ISystem.h"
#include <memory>
#include <vector>

class GameApp {
  public:
    GameApp();
    void run();

  private:
    PhysicsManager physicsManager;
    ResourceManager resourceManager;
    EntityManager entityManager;
    WindowManager windowManager;
    CameraManager cameraManager;
    HIDManager hidManager;
    DebugManager debugManager;
    EventManager eventManager;
    ToolStateManager toolStateManager;
    std::vector<std::unique_ptr<ISystem>> systems;
};

#endif // GAME_APP_H
