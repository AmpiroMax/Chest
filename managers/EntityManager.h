#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "core/Entity.h"
#include <algorithm>
#include <vector>

class EntityManager {
  public:
    void addEntity(Entity *entity) { entities.push_back(entity); }
    void addPlayerEntity(Entity *entity) {
        playerEntity = entity;
        entities.push_back(entity);
    }
    void removeEntity(size_t entityId) {
        auto it = std::find_if(entities.begin(), entities.end(), [entityId](Entity *e) { return e->getId() == entityId; });
        if (it != entities.end()) {
            delete *it;
            entities.erase(it);
        }
    }

    const std::vector<Entity *> &getAll() const { return entities; }
    Entity *getPlayer() const { return playerEntity; }
    Entity *getEntity(size_t entityId) const {
        auto it = std::find_if(entities.begin(), entities.end(), [entityId](Entity *e) { return e->getId() == entityId; });
        return it != entities.end() ? *it : nullptr;
    }

  private:
    std::vector<Entity *> entities;
    Entity *playerEntity = nullptr;
};

#endif // ENTITY_MANAGER_H
