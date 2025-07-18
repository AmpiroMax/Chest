#ifndef EDITOR_APP_H
#define EDITOR_APP_H

#include "managers/CameraManager.h"
#include "managers/DebugManager.h"
#include "managers/EntityManager.h"
#include "managers/EventManager.h"
#include "managers/HIDManager.h"
#include "managers/PhysicsManager.h"
#include "managers/ResourceManager.h"
#include "managers/TimeManager.h"
#include "managers/ToolStateManager.h"
#include "managers/WindowManager.h"
#include "systems/ISystem.h"

class EditorApp {
  public:
    EditorApp();
    void run();

  private:
    void buildManagers();
    void buildSystems();
    void initUI();

    WindowManager windowManager;
    TimeManager timeManager;
    HIDManager hidManager;
    EntityManager entityManager;
    EventManager eventManager;
    ResourceManager resourceManager;
    CameraManager cameraManager;
    DebugManager debugManager;
    ToolStateManager toolStateManager;
    PhysicsManager physicsManager;

    std::vector<std::unique_ptr<ISystem>> systems;
};
#endif
