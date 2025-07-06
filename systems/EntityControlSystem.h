#ifndef ENTITY_CONTROL_SYSTEM_H
#define ENTITY_CONTROL_SYSTEM_H

#include "core/Components/PhysicsComponent.h"
#include "managers/EntityManager.h"
#include "managers/HIDManager.h"
#include "systems/ISystem.h"

// System for controlling entities based on input
class EntityControlSystem : public ISystem {
  public:
    EntityControlSystem(EntityManager &entityMgr, HIDManager &hidMgr) : entityManager(entityMgr), hidManager(hidMgr) {}

    SystemSignal update() override {
        auto *player = entityManager.getPlayer();
        if (!player) {
            return SystemSignal::None;
        }

        auto *phys = player->getComponent<PhysicsComponent>();
        if (!phys) {
            return SystemSignal::None;
        }

        if (phys && phys->body) {
            b2Vec2 velocity = phys->body->GetLinearVelocity();
            float speed = phys->dynamicProperties.maxSpeed;

            velocity.SetZero();
            if (hidManager.getKeyboardButtonStatus(KeyboardButtons::W) == ButtonStatus::Pressed) {
                velocity.y = 1;
            }
            if (hidManager.getKeyboardButtonStatus(KeyboardButtons::S) == ButtonStatus::Pressed) {
                velocity.y = -1;
            }
            if (hidManager.getKeyboardButtonStatus(KeyboardButtons::A) == ButtonStatus::Pressed) {
                velocity.x = -1;
            }
            if (hidManager.getKeyboardButtonStatus(KeyboardButtons::D) == ButtonStatus::Pressed) {
                velocity.x = 1;
            }
            velocity.Normalize();
            velocity *= speed;
            phys->body->SetLinearVelocity(velocity);
        }

        return SystemSignal::None;
    }

  private:
    EntityManager &entityManager;
    HIDManager &hidManager;
    float moveSpeed = 2.0f; // Default movement speed
};

#endif // ENTITY_CONTROL_SYSTEM_H
