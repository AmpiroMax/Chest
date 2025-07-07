#ifndef DEBUG_SYSTEM_H
#define DEBUG_SYSTEM_H

#include "managers/CameraManager.h"
#include "managers/DebugManager.h"
#include "managers/EntityManager.h"
#include "managers/HIDManager.h"
#include "managers/PhysicsManager.h"
#include "managers/WindowManager.h"
#include "systems/ISystem.h"

class DebugSystem : public ISystem {
  public:
    DebugSystem(EntityManager &entMgr, CameraManager &camMgr, PhysicsManager &physMgr, WindowManager &winMgr, HIDManager &hidMgr, DebugManager &debMgr)
        : entityManager(entMgr), cameraManager(camMgr), physicsManager(physMgr), windowManager(winMgr), hidManager(hidMgr), debugManager(debMgr) {}

    SystemSignal update() override;

  private:
    EntityManager &entityManager;
    CameraManager &cameraManager;
    PhysicsManager &physicsManager;
    WindowManager &windowManager;
    HIDManager &hidManager;
    DebugManager &debugManager;
};

#endif // DEBUG_SYSTEM_H