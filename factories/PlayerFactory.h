#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "core/Entity.h"
#include "managers/PhysicsManager.h"
#include "managers/ResourceManager.h"
#include "services/GameConfig.h"

class PlayerFactory {
  public:
    static Entity *create(const GameConfig &config, ResourceManager &resources, PhysicsManager &physicsManager);
};

#endif // PLAYER_FACTORY_H
