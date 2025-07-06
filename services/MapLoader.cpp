#include "services/MapLoader.h"
#include "core/Components/MapSectorComponent.h"
#include "core/Components/PhysicsComponent.h"
#include "core/Components/RenderComponent.h"
#include "utils/PhysicBodyDef.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

std::unique_ptr<MapSectorComponent> makeMapSectorComponent(const nlohmann::json &sector) {
    auto mapComp = std::make_unique<MapSectorComponent>();
    // Имя и текстура
    mapComp->name = sector.value("name", "UNNAMED SECTOR ENTITY");
    mapComp->texture = sector.value("texture", "");

    // Shape type
    std::string shapeStr = sector.value("bodyShape", "Unknown");
    if (shapeStr == "Box")
        mapComp->shape = MapSectorComponent::ShapeType::Box;
    else if (shapeStr == "Polygon")
        mapComp->shape = MapSectorComponent::ShapeType::Polygon;
    else if (shapeStr == "Circle")
        mapComp->shape = MapSectorComponent::ShapeType::Circle;
    else
        mapComp->shape = MapSectorComponent::ShapeType::Unknown;

    // Позиция (всегда есть)
    if (sector.contains("position") && sector["position"].is_array())
        mapComp->position = Vec2(sector["position"][0], sector["position"][1]);

    // Box
    if (mapComp->shape == MapSectorComponent::ShapeType::Box && sector.contains("size")) {
        mapComp->size = Vec2(sector["size"][0], sector["size"][1]);
    }
    // Polygon
    if (mapComp->shape == MapSectorComponent::ShapeType::Polygon && sector.contains("vertices")) {
        for (const auto &v : sector["vertices"])
            mapComp->vertices.push_back(Vec2(v[0], v[1]));
    }
    // Circle
    if (mapComp->shape == MapSectorComponent::ShapeType::Circle && sector.contains("radius")) {
        mapComp->radius = sector["radius"];
    }

    // Physics-поля (в physics-объекте)
    if (sector.contains("physics")) {
        const auto &phys = sector["physics"];
        std::string bodyTypeStr = phys.value("bodyType", "Unknown");
        if (bodyTypeStr == "Static")
            mapComp->bodyType = MapSectorComponent::BodyType::Static;
        else if (bodyTypeStr == "Dynamic")
            mapComp->bodyType = MapSectorComponent::BodyType::Dynamic;
        else if (bodyTypeStr == "Kinematic")
            mapComp->bodyType = MapSectorComponent::BodyType::Kinematic;
        else
            mapComp->bodyType = MapSectorComponent::BodyType::Unknown;

        mapComp->density = phys.value("density", 1.0f);
        mapComp->friction = phys.value("friction", 0.5f);
        mapComp->restitution = phys.value("restitution", 0.1f);
        mapComp->linearDamping = phys.value("linearDamping", 0.0f);
        mapComp->canRotate = phys.value("canRotate", true);
        mapComp->isSensor = phys.value("isSensor", false);

        // Extra: сохраним все неизвестные поля physics (для расширяемости)
        for (auto it = phys.begin(); it != phys.end(); ++it) {
            std::string key = it.key();
            if (key != "bodyType" && key != "density" && key != "friction" && key != "restitution" && key != "linearDamping" && key != "canRotate" &&
                key != "isSensor") {
                mapComp->extra[key] = it.value().dump();
            }
        }
    }

    // TextureMapping (если есть)
    if (sector.contains("textureMapping")) {
        const auto &tm = sector["textureMapping"];
        MapSectorComponent::TextureMapping mapping;
        mapping.mode = tm.value("mode", "stretch");
        if (tm.contains("offset"))
            mapping.offset = Vec2(tm["offset"][0], tm["offset"][1]);
        if (tm.contains("scale"))
            mapping.scale = Vec2(tm["scale"][0], tm["scale"][1]);
        mapping.rotation = tm.value("rotation", 0.0f);
        mapComp->textureMapping = mapping;
    }

    // Можно добавить extra для любых других верхнеуровневых ключей, если появятся

    return mapComp;
}

std::unique_ptr<RenderComponent> makeRenderComponent(const nlohmann::json &sector, ResourceManager &resourceManager) {
    auto rendComp = std::make_unique<RenderComponent>();
    rendComp->textureName = sector.value("texture", "bad_texture");
    return rendComp;
}

std::unique_ptr<PhysicsComponent> makePhysicsComponent(const nlohmann::json &sector, PhysicsManager &physicsManager) {
    auto physComp = std::make_unique<PhysicsComponent>();

    const auto &bodyShape = sector["bodyShape"].get<std::string>();
    const auto &bodyType = sector["physics"]["bodyType"].get<std::string>();
    const auto &phys = sector["physics"];
    const auto &secPos = sector["position"];

    PhysicBodyDef def;
    def.position = Vec2(secPos[0], secPos[1]);

    // Rewritten in if-else style
    if (bodyShape == "Box") {
        def.bodyShape = PhysicBodyDef::BodyShape::Box;
        def.bodySize = Vec2(sector["size"][0], sector["size"][1]);
    } else if (bodyShape == "Circle") {
        def.bodyShape = PhysicBodyDef::BodyShape::Circle;
        def.bodyRadius = sector["radius"];
    } else if (bodyShape == "Polygon") {
        def.bodyShape = PhysicBodyDef::BodyShape::Polygon;
        for (const auto &v : sector["vertices"])
            def.bodyVertices.push_back(Vec2(v[0], v[1]));
    } else {
        throw std::runtime_error("Unknown shape type in sector: " + sector.value("shape", "UNKNOWN"));
    }

    if (bodyType == "Static") {
        def.bodyType = PhysicBodyDef::BodyType::Static;
        physComp->body = physicsManager.createStaticBody(def);

    } else if (bodyType == "Dynamic") {
        def.density = phys.value("density", 1.0f);
        def.friction = phys.value("friction", 0.5f);
        def.restitution = phys.value("restitution", 0.1f);
        def.linearDamping = phys.value("linearDamping", 0.0f);
        def.canRotate = phys.value("canRotate", false);
        def.isSensor = phys.value("isSensor", false);

        def.bodyType = PhysicBodyDef::BodyType::Dynamic;
        physComp->body = physicsManager.createDynamicBody(def);

    } else {
        throw std::runtime_error("Unknown body type in sector: " + bodyType);
    }
    physComp->dynamicProperties = def;
    return physComp;
}

Entity *createSectorEntity(const nlohmann::json &sector, ResourceManager &resourceManager, PhysicsManager &physicsManager) {
    auto *ent = new Entity();

    ent->addComponent(std::move(makeMapSectorComponent(sector)));
    ent->addComponent(std::move(makeRenderComponent(sector, resourceManager)));
    ent->addComponent(std::move(makePhysicsComponent(sector, physicsManager)));

    return ent;
}

std::vector<Entity *> MapLoader::loadMap(const std::string &filename, ResourceManager &resourceManager, PhysicsManager &physicsManager) {
    std::ifstream file(filename);
    nlohmann::json json;
    file >> json;
    std::vector<Entity *> entities;

    for (const auto &sector : json["sectors"]) {
        auto *ent = createSectorEntity(sector, resourceManager, physicsManager);
        entities.push_back(ent);
    }

    return entities;
}