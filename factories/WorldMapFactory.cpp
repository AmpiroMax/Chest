// WorldMapFactory.cpp
#include "factories/WorldMapFactory.h"
#include "services/MapLoader.h"

std::vector<Entity *> WorldMapFactory::create(const GameConfig &config, ResourceManager &resourceManager,
                                              PhysicsManager &physicsManager) {
    std::string mapFile = config.getMapPath() + config.getDefaultLevel();
    return MapLoader::loadMap(mapFile, resourceManager, physicsManager);
}