#include "systems/PhysicsSystem.h"
#include "core/Components/PhysicsComponent.h"
#include "utils/CoordinateUtils.h"

SystemSignal PhysicsSystem::update() {
    // 1. Делаем шаг симуляции Box2D
    physicsManager.getWorld().Step(PHYSICS_TIMESTEP, PHYSICS_VELOCITY_ITER, PHYSICS_POSITION_ITER);

    // 2. (Опционально) Синхронизируем ECS-позиции с Box2D (например, если нужен "read-back" для dummy-entity)
    for (auto *entity : entityManager.getAll()) {
        if (auto *phys = entity->getComponent<PhysicsComponent>()) {
            if (phys->body) {
                phys->position = fromPhysicsToWorld(Vec2(phys->body->GetPosition()));
                phys->rotation = fromPhysicsAngleToWorld(phys->body->GetAngle());
            }
        }
    }

    return SystemSignal::None;
}