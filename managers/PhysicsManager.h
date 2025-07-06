#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "utils/PhysicBodyDef.h"
#include "utils/Vec2.h"
#include <box2d/box2d.h>
#include <vector>

class PhysicsManager {
  public:
    PhysicsManager();
    b2World &getWorld();

    // Создать статический полигональный коллайдер (пример)
    b2PolygonShape makeBoxShape(const PhysicBodyDef &def);
    b2CircleShape makeCircleShape(const PhysicBodyDef &def);
    b2PolygonShape makePolygonShape(const PhysicBodyDef &def);

    void createFixtureByShape(PhysicBodyDef::BodyShape bodyShape, const PhysicBodyDef &def, b2Body *body,
                              b2FixtureDef &fixtureDef);
    b2Body *createStaticBody(const PhysicBodyDef &def);
    b2Body *createDynamicBody(const PhysicBodyDef &def);

  private:
    b2World world;
};

#endif // PHYSICS_MANAGER_H