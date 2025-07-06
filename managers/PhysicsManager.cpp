#include "managers/PhysicsManager.h"
#include "utils/Constants.h"
#include "utils/CoordinateUtils.h"

inline b2Vec2 computeCentroid(const std::vector<b2Vec2> &verts) {
    float area = 0.0f, cx = 0.0f, cy = 0.0f;
    int n = verts.size();
    for (int i = 0; i < n; ++i) {
        float xi = verts[i].x, yi = verts[i].y;
        float xi1 = verts[(i + 1) % n].x, yi1 = verts[(i + 1) % n].y;
        float a = xi * yi1 - xi1 * yi;
        area += a;
        cx += (xi + xi1) * a;
        cy += (yi + yi1) * a;
    }
    area *= 0.5f;
    cx /= (6 * area);
    cy /= (6 * area);
    return b2Vec2(cx, cy);
}

PhysicsManager::PhysicsManager()
    : world(b2Vec2(0.0f, 0.0f)) // без гравитации для top-down, или укажи нужную
{}

b2World &PhysicsManager::getWorld() { return world; }

b2PolygonShape PhysicsManager::makeBoxShape(const PhysicBodyDef &def) {
    b2PolygonShape shape;
    shape.SetAsBox(def.bodySize.x * 0.5f / PHYSIC_SCALE, def.bodySize.y * 0.5f / PHYSIC_SCALE);
    return shape;
}

b2CircleShape PhysicsManager::makeCircleShape(const PhysicBodyDef &def) {
    b2CircleShape shape;
    shape.m_radius = def.bodyRadius / PHYSIC_SCALE;
    return shape;
}

b2PolygonShape PhysicsManager::makePolygonShape(const PhysicBodyDef &def) {
    std::vector<b2Vec2> b2verts;
    for (const auto &v : def.bodyVertices)
        b2verts.push_back(fromWorldToPhysics(v));
    if (b2verts.size() < 3 || b2verts.size() > b2_maxPolygonVertices)
        throw std::runtime_error("Polygon must have 3..8 vertices");
    // Центроид и локальные вершины — если надо сместить body
    // (но Box2D сам вычисляет для динамики, а для статики лучше центроид)
    b2PolygonShape shape;
    shape.Set(b2verts.data(), b2verts.size());
    return shape;
}

void PhysicsManager::createFixtureByShape(PhysicBodyDef::BodyShape bodyShape, const PhysicBodyDef &def, b2Body *body,
                                          b2FixtureDef &fixtureDef) {
    switch (bodyShape) {
    case PhysicBodyDef::BodyShape::Box: {
        b2PolygonShape shape = makeBoxShape(def);
        fixtureDef.shape = &shape;
        body->CreateFixture(&fixtureDef);
        break;
    }
    case PhysicBodyDef::BodyShape::Circle: {
        b2CircleShape shape = makeCircleShape(def);
        fixtureDef.shape = &shape;
        body->CreateFixture(&fixtureDef);
        break;
    }
    case PhysicBodyDef::BodyShape::Polygon: {
        b2PolygonShape shape = makePolygonShape(def);
        fixtureDef.shape = &shape;
        body->CreateFixture(&fixtureDef);
        break;
    }
    }
}

b2Body *PhysicsManager::createStaticBody(const PhysicBodyDef &def) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = fromWorldToPhysics(def.position);
    bodyDef.angle = def.angle * DEG2RAD;
    b2Body *body = world.CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0f; // Static bodies — always 0
    fixtureDef.friction = def.friction;
    fixtureDef.restitution = def.restitution;
    fixtureDef.isSensor = def.isSensor;

    createFixtureByShape(def.bodyShape, def, body, fixtureDef);

    return body;
}

b2Body *PhysicsManager::createDynamicBody(const PhysicBodyDef &def) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = fromWorldToPhysics(def.position);
    bodyDef.angle = def.angle * DEG2RAD;
    bodyDef.linearDamping = def.linearDamping;
    bodyDef.angularDamping = def.angularDamping;
    bodyDef.fixedRotation = !def.canRotate;

    b2Body *body = world.CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.density = def.density; // В Box2D это плотность, а не масса!
    fixtureDef.friction = def.friction;
    fixtureDef.restitution = def.restitution;
    fixtureDef.isSensor = def.isSensor;

    createFixtureByShape(def.bodyShape, def, body, fixtureDef);

    return body;
}
