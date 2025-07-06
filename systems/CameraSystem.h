#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "managers/CameraManager.h"
#include "managers/EntityManager.h"
#include "managers/HIDManager.h"
#include "systems/ISystem.h"

class CameraSystem : public ISystem {
  public:
    CameraSystem(CameraManager &camMgr, EntityManager &entMgr, HIDManager &hidMgr)
        : cameraManager(camMgr), entityManager(entMgr), hidManager(hidMgr) {}

    SystemSignal update() override;

  private:
    CameraManager &cameraManager;
    EntityManager &entityManager;
    HIDManager &hidManager;
};

#endif // CAMERA_SYSTEM_H