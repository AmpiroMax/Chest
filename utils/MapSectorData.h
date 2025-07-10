#ifndef MAP_SECTOR_DATA_H
#define MAP_SECTOR_DATA_H

#include "Vec2.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

struct MapRenderData {
    struct TextureMappingType {
        std::string mode = "stretch"; // "stretch", "tile", "customUV"
        Vec2 offset{0, 0};
        Vec2 scale{1, 1};
        float rotation = 0.0f;
    };

    TextureMappingType textureMapping;
    std::string texture;
};

struct MapPhysicsData {
    enum class BodyType { Static, Dynamic, Kinematic, Unknown };
    BodyType bodyType = BodyType::Unknown;
    float density = 1.0f;
    float friction = 0.5f;
    float restitution = 0.1f;
    float linearDamping = 0.0f;
    bool canRotate = true;
    bool isSensor = false;
};

struct MapShapeData {
    enum class ShapeType { Box, Polygon, Circle, Unknown };
    ShapeType shape = ShapeType::Unknown;
    Vec2 size{0, 0};            // ширина и высота (Box)
    float radius = 0.0f;        // радиус (Circle)
    std::vector<Vec2> vertices; // вершины (Polygon)
};

struct MapSectorData {
    std::string name;
    Vec2 position;

    MapRenderData renderData;
    MapPhysicsData physicsData;
    MapShapeData shapeData;

    std::unordered_map<std::string, std::string> extra;
};

MapSectorData makeMapSectorData(const nlohmann::json &sector);
std::string mapSectorDataToString(const MapSectorData &data);

#endif // MAP_SECTOR_DATA_H
