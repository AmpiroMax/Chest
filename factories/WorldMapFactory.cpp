#include "factories/WorldMapFactory.h"
#include "core/Components/MapSectorComponent.h"
#include "core/Components/PhysicsComponent.h"
#include "core/Components/RenderComponent.h"
#include "utils/PhysicBodyDef.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

std::unique_ptr<MapSectorComponent> makeMapSectorComponent(const MapSectorData &sectorData) {
    auto mapComp = std::make_unique<MapSectorComponent>();
    mapComp->mapSectorData = sectorData;
    // Имя и текстура
    mapComp->name = sectorData.name;
    mapComp->texture = sectorData.renderData.texture;

    // Shape type
    if (sectorData.shapeData.shape == MapShapeData::ShapeType::Box)
        mapComp->shape = MapSectorComponent::ShapeType::Box;
    else if (sectorData.shapeData.shape == MapShapeData::ShapeType::Polygon)
        mapComp->shape = MapSectorComponent::ShapeType::Polygon;
    else if (sectorData.shapeData.shape == MapShapeData::ShapeType::Circle)
        mapComp->shape = MapSectorComponent::ShapeType::Circle;
    else
        mapComp->shape = MapSectorComponent::ShapeType::Unknown;

    // Позиция (всегда есть)
    mapComp->position = sectorData.position;

    // Box
    if (mapComp->shape == MapSectorComponent::ShapeType::Box) {
        mapComp->size = sectorData.shapeData.size;
    }
    // Polygon
    if (mapComp->shape == MapSectorComponent::ShapeType::Polygon) {
        for (const auto &v : sectorData.shapeData.vertices)
            mapComp->vertices.push_back(v);
    }
    // Circle
    if (mapComp->shape == MapSectorComponent::ShapeType::Circle) {
        mapComp->radius = sectorData.shapeData.radius;
    }

    // Physics-поля (в physics-объекте)
    if (sectorData.physicsData.bodyType == MapPhysicsData::BodyType::Static)
        mapComp->bodyType = MapSectorComponent::BodyType::Static;
    else if (sectorData.physicsData.bodyType == MapPhysicsData::BodyType::Dynamic)
        mapComp->bodyType = MapSectorComponent::BodyType::Dynamic;
    else if (sectorData.physicsData.bodyType == MapPhysicsData::BodyType::Kinematic)
        mapComp->bodyType = MapSectorComponent::BodyType::Kinematic;
    else
        mapComp->bodyType = MapSectorComponent::BodyType::Unknown;

    mapComp->density = sectorData.physicsData.density;
    mapComp->friction = sectorData.physicsData.friction;
    mapComp->restitution = sectorData.physicsData.restitution;
    mapComp->linearDamping = sectorData.physicsData.linearDamping;
    mapComp->canRotate = sectorData.physicsData.canRotate;
    mapComp->isSensor = sectorData.physicsData.isSensor;

    // Extra: сохраним все неизвестные поля physics (для расширяемости)
    for (auto it = sectorData.extra.begin(); it != sectorData.extra.end(); ++it) {
        std::string key = it->first;
        if (key != "bodyType" && key != "density" && key != "friction" && key != "restitution" && key != "linearDamping" && key != "canRotate" &&
            key != "isSensor")
            mapComp->extra[key] = it->second;
    }

    // TextureMapping (если есть)
    const auto &tm = sectorData.renderData.textureMapping;
    MapSectorComponent::TextureMapping mapping;
    mapping.mode = tm.mode;
    mapping.offset = tm.offset;
    mapping.scale = tm.scale;
    mapping.rotation = tm.rotation;
    mapComp->textureMapping = mapping;

    // Можно добавить extra для любых других верхнеуровневых ключей, если появятся
    for (auto it = sectorData.extra.begin(); it != sectorData.extra.end(); ++it) {
        std::string key = it->first;
        if (key != "bodyType" && key != "density" && key != "friction" && key != "restitution" && key != "linearDamping" && key != "canRotate" &&
            key != "isSensor") {
            mapComp->extra[key] = it->second;
        }
    }

    return mapComp;
}

std::unique_ptr<RenderComponent> makeRenderComponent(const MapSectorData &sectorData, ResourceManager &resourceManager) {
    auto rendComp = std::make_unique<RenderComponent>();
    rendComp->textureName = sectorData.renderData.texture;
    return rendComp;
}

std::unique_ptr<PhysicsComponent> makePhysicsComponent(const MapSectorData &sectorData, PhysicsManager &physicsManager) {
    auto physComp = std::make_unique<PhysicsComponent>();

    PhysicBodyDef def;
    def.position = sectorData.position;
    physComp->position = sectorData.position;

    // Rewritten in if-else style
    if (sectorData.shapeData.shape == MapShapeData::ShapeType::Box) {
        def.bodyShape = PhysicBodyDef::BodyShape::Box;
        def.bodySize = sectorData.shapeData.size;
    } else if (sectorData.shapeData.shape == MapShapeData::ShapeType::Circle) {
        def.bodyShape = PhysicBodyDef::BodyShape::Circle;
        def.bodyRadius = sectorData.shapeData.radius;
    } else if (sectorData.shapeData.shape == MapShapeData::ShapeType::Polygon) {
        def.bodyShape = PhysicBodyDef::BodyShape::Polygon;
        for (const auto &v : sectorData.shapeData.vertices)
            def.bodyVertices.push_back(v);
    } else {
        throw std::runtime_error("Unknown shape type in sector: ...");
    }

    if (sectorData.physicsData.bodyType == MapPhysicsData::BodyType::Static) {
        def.bodyType = PhysicBodyDef::BodyType::Static;
        physComp->body = physicsManager.createStaticBody(def);

    } else if (sectorData.physicsData.bodyType == MapPhysicsData::BodyType::Dynamic) {
        def.density = sectorData.physicsData.density;
        def.friction = sectorData.physicsData.friction;
        def.restitution = sectorData.physicsData.restitution;
        def.linearDamping = sectorData.physicsData.linearDamping;
        def.canRotate = sectorData.physicsData.canRotate;
        def.isSensor = sectorData.physicsData.isSensor;

        def.bodyType = PhysicBodyDef::BodyType::Dynamic;
        physComp->body = physicsManager.createDynamicBody(def);

    } else if (sectorData.physicsData.bodyType == MapPhysicsData::BodyType::Kinematic) {
        // Kinematic bodies are not supported yet, treat as static for now
        def.bodyType = PhysicBodyDef::BodyType::Static;
        physComp->body = physicsManager.createStaticBody(def);
    } else {
        throw std::runtime_error("Unknown body type in sector: " + sectorData.name);
    }
    physComp->dynamicProperties = def;
    return physComp;
}

Entity *WorldMapFactory::createSectorEntity(const MapSectorData &sectorData, ResourceManager &resourceManager, PhysicsManager &physicsManager) {
    auto *ent = new Entity();

    ent->addComponent(std::move(makeMapSectorComponent(sectorData)));
    ent->addComponent(std::move(makeRenderComponent(sectorData, resourceManager)));
    ent->addComponent(std::move(makePhysicsComponent(sectorData, physicsManager)));

    return ent;
}

std::vector<Entity *> WorldMapFactory::createSectorsForMap(const std::string &filename, ResourceManager &resourceManager, PhysicsManager &physicsManager) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open map file: " << filename << std::endl;
        return {};
    }

    nlohmann::json json;
    try {
        file >> json;
    } catch (const std::exception &e) {
        std::cerr << "Error: Invalid JSON in map file: " << filename << " - " << e.what() << std::endl;
        return {};
    }

    if (!json.contains("sectors") || !json["sectors"].is_array()) {
        std::cerr << "Error: Map file must contain 'sectors' array: " << filename << std::endl;
        return {};
    }

    std::vector<Entity *> entities;

    for (const auto &sector : json["sectors"]) {
        try {
            MapSectorData sectorData = makeMapSectorData(sector);
            auto *ent = WorldMapFactory::createSectorEntity(sectorData, resourceManager, physicsManager);
            entities.push_back(ent);
        } catch (const std::exception &e) {
            std::cerr << "Error: Failed to create sector entity: " << e.what() << std::endl;
        }
    }

    return entities;
}
std::vector<Entity *> WorldMapFactory::loadGameMap(const GameConfig &config, ResourceManager &resourceManager, PhysicsManager &physicsManager) {
    std::string mapFile = config.getMapPath() + config.getDefaultLevel();
    return WorldMapFactory::createSectorsForMap(mapFile, resourceManager, physicsManager);
}