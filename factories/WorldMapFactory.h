#ifndef WORLD_MAP_FACTORY_H
#define WORLD_MAP_FACTORY_H

#include "core/Entity.h"
#include "managers/PhysicsManager.h"
#include "managers/ResourceManager.h"
#include "services/GameConfig.h"
#include <vector>

class WorldMapFactory {
  public:
    static std::vector<Entity *> create(const GameConfig &config, ResourceManager &resourceManager,
                                        PhysicsManager &physicsManager);
};

#endif // WORLD_MAP_FACTORY_H