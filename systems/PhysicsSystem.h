#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "managers/EntityManager.h"
#include "managers/PhysicsManager.h"
#include "systems/ISystem.h"
#include "utils/Constants.h"

class PhysicsSystem : public ISystem {
  public:
    PhysicsSystem(PhysicsManager &physicsManager, EntityManager &entityManager)
        : physicsManager(physicsManager), entityManager(entityManager) {}

    SystemSignal update() override;

  private:
    PhysicsManager &physicsManager;
    EntityManager &entityManager;
};

#endif // PHYSICS_SYSTEM_H