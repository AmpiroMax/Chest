#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "core/Entity.h"
#include "managers/PhysicsManager.h"
#include "managers/ResourceManager.h"
#include <string>
#include <vector>

class MapLoader {
  public:
    static std::vector<Entity *> loadMap(const std::string &filename, ResourceManager &resourceManager,
                                         PhysicsManager &physicsManager);
};

#endif // MAP_LOADER_H