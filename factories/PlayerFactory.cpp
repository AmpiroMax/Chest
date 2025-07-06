#include "factories/PlayerFactory.h"
#include "core/Components/PhysicsComponent.h"
#include "core/Components/RenderComponent.h"
#include "utils/PhysicBodyDef.h"

Entity *PlayerFactory::create(const GameConfig &config, ResourceManager &resourceManager,
                              PhysicsManager &physicsManager) {
    auto *player = new Entity();

    auto rend = std::make_unique<RenderComponent>();
    rend->textureName = config.playerSpriteName();
    player->addComponent(std::move(rend));

    // TODO: read from config
    PhysicBodyDef bodyDef;
    // bodyDef.position = Vec2(config.getPlayerSpawnX(), config.getPlayerSpawnY());
    bodyDef.position = Vec2(0, 0);
    // bodyDef.mass = config.getPlayerMass(); // или 1.0f;
    bodyDef.density = 1.0f;
    bodyDef.friction = 0.3f;
    bodyDef.linearDamping = 0.09f;
    // Размеры физического тела в мировых единицах (пиксели)
    bodyDef.bodySize = Vec2(1.0f, 2.0f); // 32x32 пикселя = 1x1 метр в Box2D
    bodyDef.canRotate = false;
    bodyDef.bodyShape = PhysicBodyDef::BodyShape::Box;

    auto phys = std::make_unique<PhysicsComponent>();
    phys->dynamicProperties = bodyDef;
    phys->body = physicsManager.createDynamicBody(bodyDef);
    player->addComponent(std::move(phys));

    return player;
}
