#include "utils/MapSectorData.h"
#include <sstream>

MapSectorData makeMapSectorDataOld(const nlohmann::json &sector) {
    MapSectorData data;
    // Name and position
    data.name = sector.value("name", "UNNAMED SECTOR ENTITY");
    if (sector.contains("position") && sector["position"].is_array())
        data.position = Vec2(sector["position"][0], sector["position"][1]);

    // Render data
    data.renderData.texture = sector.value("texture", "");
    if (sector.contains("textureMapping")) {
        const auto &tm = sector["textureMapping"];
        data.renderData.textureMapping.mode = tm.value("mode", "stretch");
        if (tm.contains("offset"))
            data.renderData.textureMapping.offset = Vec2(tm["offset"][0], tm["offset"][1]);
        if (tm.contains("scale"))
            data.renderData.textureMapping.scale = Vec2(tm["scale"][0], tm["scale"][1]);
        data.renderData.textureMapping.rotation = tm.value("rotation", 0.0f);
    }

    // Shape data
    std::string shapeStr = sector.value("bodyShape", "Unknown");
    if (shapeStr == "Box")
        data.shapeData.shape = MapShapeData::ShapeType::Box;
    else if (shapeStr == "Polygon")
        data.shapeData.shape = MapShapeData::ShapeType::Polygon;
    else if (shapeStr == "Circle")
        data.shapeData.shape = MapShapeData::ShapeType::Circle;
    else
        data.shapeData.shape = MapShapeData::ShapeType::Unknown;

    if (data.shapeData.shape == MapShapeData::ShapeType::Box && sector.contains("size")) {
        data.shapeData.size = Vec2(sector["size"][0], sector["size"][1]);
    }
    if (data.shapeData.shape == MapShapeData::ShapeType::Polygon && sector.contains("vertices")) {
        for (const auto &v : sector["vertices"])
            data.shapeData.vertices.push_back(Vec2(v[0], v[1]));
    }
    if (data.shapeData.shape == MapShapeData::ShapeType::Circle && sector.contains("radius")) {
        data.shapeData.radius = sector["radius"];
    }

    // Physics data
    if (sector.contains("physics")) {
        const auto &phys = sector["physics"];
        std::string bodyTypeStr = phys.value("bodyType", "Unknown");
        if (bodyTypeStr == "Static")
            data.physicsData.bodyType = MapPhysicsData::BodyType::Static;
        else if (bodyTypeStr == "Dynamic")
            data.physicsData.bodyType = MapPhysicsData::BodyType::Dynamic;
        else if (bodyTypeStr == "Kinematic")
            data.physicsData.bodyType = MapPhysicsData::BodyType::Kinematic;
        else
            data.physicsData.bodyType = MapPhysicsData::BodyType::Unknown;

        data.physicsData.density = phys.value("density", 1.0f);
        data.physicsData.friction = phys.value("friction", 0.5f);
        data.physicsData.restitution = phys.value("restitution", 0.1f);
        data.physicsData.linearDamping = phys.value("linearDamping", 0.0f);
        data.physicsData.canRotate = phys.value("canRotate", true);
        data.physicsData.isSensor = phys.value("isSensor", false);

        // Save all unknown physics fields to extra
        for (auto it = phys.begin(); it != phys.end(); ++it) {
            std::string key = it.key();
            if (key != "bodyType" && key != "density" && key != "friction" && key != "restitution" && key != "linearDamping" && key != "canRotate" &&
                key != "isSensor") {
                data.extra[key] = it.value().dump();
            }
        }
    }

    // Можно добавить extra для любых других верхнеуровневых ключей, если появятся

    return data;
}

MapSectorData makeMapSectorData(const nlohmann::json &sector) {
    MapSectorData data;

    // Name and position
    data.name = sector.value("name", "UNNAMED SECTOR ENTITY");
    if (sector.contains("position") && sector["position"].is_array() && sector["position"].size() >= 2) {
        data.position = Vec2(sector["position"][0], sector["position"][1]);
    }

    // Render data
    data.renderData.texture = sector.value("texture", "");
    if (sector.contains("textureMapping")) {
        const auto &tm = sector["textureMapping"];
        data.renderData.textureMapping.mode = tm.value("mode", "stretch");
        if (tm.contains("offset") && tm["offset"].is_array() && tm["offset"].size() >= 2) {
            data.renderData.textureMapping.offset = Vec2(tm["offset"][0], tm["offset"][1]);
        }
        if (tm.contains("scale") && tm["scale"].is_array() && tm["scale"].size() >= 2) {
            data.renderData.textureMapping.scale = Vec2(tm["scale"][0], tm["scale"][1]);
        }
        data.renderData.textureMapping.rotation = tm.value("rotation", 0.0f);
    }

    // Shape data
    std::string shapeStr = sector.value("bodyShape", "Unknown");
    if (shapeStr == "Box")
        data.shapeData.shape = MapShapeData::ShapeType::Box;
    else if (shapeStr == "Polygon")
        data.shapeData.shape = MapShapeData::ShapeType::Polygon;
    else if (shapeStr == "Circle")
        data.shapeData.shape = MapShapeData::ShapeType::Circle;
    else
        data.shapeData.shape = MapShapeData::ShapeType::Unknown;

    if (data.shapeData.shape == MapShapeData::ShapeType::Box && sector.contains("size") && sector["size"].is_array() && sector["size"].size() >= 2) {
        data.shapeData.size = Vec2(sector["size"][0], sector["size"][1]);
    }
    if (data.shapeData.shape == MapShapeData::ShapeType::Polygon && sector.contains("vertices") && sector["vertices"].is_array()) {
        for (const auto &v : sector["vertices"]) {
            if (v.is_array() && v.size() >= 2) {
                data.shapeData.vertices.push_back(Vec2(v[0], v[1]));
            }
        }
    }
    if (data.shapeData.shape == MapShapeData::ShapeType::Circle && sector.contains("radius")) {
        data.shapeData.radius = sector["radius"];
    }

    // Physics data
    if (sector.contains("physics")) {
        const auto &phys = sector["physics"];
        std::string bodyTypeStr = phys.value("bodyType", "Unknown");
        if (bodyTypeStr == "Static")
            data.physicsData.bodyType = MapPhysicsData::BodyType::Static;
        else if (bodyTypeStr == "Dynamic")
            data.physicsData.bodyType = MapPhysicsData::BodyType::Dynamic;
        else if (bodyTypeStr == "Kinematic")
            data.physicsData.bodyType = MapPhysicsData::BodyType::Kinematic;
        else
            data.physicsData.bodyType = MapPhysicsData::BodyType::Unknown;

        data.physicsData.density = phys.value("density", 1.0f);
        data.physicsData.friction = phys.value("friction", 0.5f);
        data.physicsData.restitution = phys.value("restitution", 0.1f);
        data.physicsData.linearDamping = phys.value("linearDamping", 0.0f);
        data.physicsData.canRotate = phys.value("canRotate", true);
        data.physicsData.isSensor = phys.value("isSensor", false);

        // Save all unknown physics fields to extra
        for (auto it = phys.begin(); it != phys.end(); ++it) {
            std::string key = it.key();
            if (key != "bodyType" && key != "density" && key != "friction" && key != "restitution" && key != "linearDamping" && key != "canRotate" &&
                key != "isSensor") {
                data.extra["physics." + key] = it.value().dump();
            }
        }
    }

    // Save all unknown top-level fields to extra
    for (auto it = sector.begin(); it != sector.end(); ++it) {
        std::string key = it.key();
        if (key != "name" && key != "position" && key != "texture" && key != "textureMapping" && key != "bodyShape" && key != "size" && key != "vertices" &&
            key != "radius" && key != "physics") {
            data.extra[key] = it.value().dump();
        }
    }

    return data;
}

std::string mapSectorDataToString(const MapSectorData &data) {
    std::stringstream ss;
    ss << "MapSectorData:" << std::endl;
    ss << "  name: " << data.name << std::endl;
    ss << "  position: " << data.position.x << ", " << data.position.y << std::endl;
    ss << "  texture: " << data.renderData.texture << std::endl;
    // ss << "  textureMapping: " << data.renderData.textureMapping.mode << std::endl;
    // ss << "  bodyShape: " << data.shapeData.shape << std::endl;
    ss << "  size: " << data.shapeData.size.x << ", " << data.shapeData.size.y << std::endl;
    ss << "  vertices: " << data.shapeData.vertices.size() << std::endl;
    ss << "  radius: " << data.shapeData.radius << std::endl;
    ss << "  physics:" << std::endl;
    // ss << "    bodyType: " << data.physicsData.bodyType << std::endl;
    ss << "    density: " << data.physicsData.density << std::endl;
    ss << "    friction: " << data.physicsData.friction << std::endl;
    ss << "    restitution: " << data.physicsData.restitution << std::endl;
    ss << "    linearDamping: " << data.physicsData.linearDamping << std::endl;
    ss << "    canRotate: " << data.physicsData.canRotate << std::endl;
    ss << "    isSensor: " << data.physicsData.isSensor << std::endl;
    ss << "  extra:" << std::endl;
    for (const auto &[key, value] : data.extra) {
        ss << "    " << key << ": " << value << std::endl;
    }
    return ss.str();
}