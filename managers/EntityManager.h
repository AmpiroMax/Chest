#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "core/Entity.h"
#include <vector>

class EntityManager {
  public:
    void addEntity(Entity *entity) { entities.push_back(entity); }
    void addPlayerEntity(Entity *entity) {
        playerEntity = entity;
        entities.push_back(entity);
    }
    const std::vector<Entity *> &getAll() const { return entities; }
    Entity *getPlayer() const { return playerEntity; }

  private:
    std::vector<Entity *> entities;
    Entity *playerEntity = nullptr;
};

#endif // ENTITY_MANAGER_H
