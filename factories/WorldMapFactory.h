#ifndef WORLD_MAP_FACTORY_H
#define WORLD_MAP_FACTORY_H

#include "core/Entity.h"
#include "managers/PhysicsManager.h"
#include "managers/ResourceManager.h"
#include "services/GameConfig.h"
#include "utils/MapSectorData.h"
#include "utils/Vec2.h"
#include <vector>

class WorldMapFactory {
  public:
    static Entity *createSectorEntity(const MapSectorData &sectorData, ResourceManager &resourceManager, PhysicsManager &physicsManager);
    static std::vector<Entity *> loadGameMap(const GameConfig &config, ResourceManager &resourceManager, PhysicsManager &physicsManager);

  private:
    static std::vector<Entity *> createSectorsForMap(const std::string &filename, ResourceManager &resourceManager, PhysicsManager &physicsManager);
};

#endif // WORLD_MAP_FACTORY_H