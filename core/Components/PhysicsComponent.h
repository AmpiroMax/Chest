#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "IComponent.h"
#include "utils/CoordinateUtils.h"
#include "utils/PhysicBodyDef.h"
#include "utils/Vec2.h"
#include <box2d/box2d.h>

struct PhysicsComponent : public IComponent {
    // Вернёт позицию в мировых координатах (Vec2)
    Vec2 getPosition() const {
        if (body) {
            // Каким бы не был физический движок есть мировые координаты
            // в которых мы работаем
            return fromPhysicsToWorld(Vec2(body->GetPosition()));
        } else {
            return position;
        }
    }
    // Вернёт угол в градусах ПРОТИВ часовой стрелки
    float getRotation() const {
        if (body) {
            return fromPhysicsAngleToWorld(body->GetAngle());
        } else {
            return rotation;
        }
    }
    void setPosition(const Vec2 &position) {
        this->position = position;
        if (body) {
            body->SetTransform(fromWorldToPhysics(position), rotation);
        }
    }

    // --- Служебные поля ---
    b2Body *body = nullptr; // Box2D, если физика есть
    PhysicBodyDef dynamicProperties;

    Vec2 position = {0.0f, 0.0f}; // В мировых координатах всегда!
    float rotation = 0.0f;        // В мировых координатах всегда!
};

#endif // PHYSICS_COMPONENT_H
