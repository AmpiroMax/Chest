// core/Components/MapSectorComponent.h

#ifndef MAP_SECTOR_COMPONENT_H
#define MAP_SECTOR_COMPONENT_H

#include "IComponent.h"
#include "Vec2.h"
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

struct MapSectorComponent : public IComponent {
    std::string name;
    std::string texture;

    enum class ShapeType { Box, Polygon, Circle, Unknown };
    ShapeType shape = ShapeType::Unknown;

    Vec2 position; // Центр объекта (мировые координаты)

    Vec2 size{0, 0}; // ширина и высота (Box)

    std::vector<Vec2> vertices; // вершины (Polygon)

    float radius = 0.0f; // радиус (Circle)

    enum class BodyType { Static, Dynamic, Kinematic, Unknown };
    BodyType bodyType = BodyType::Unknown;
    float density = 1.0f;
    float friction = 0.5f;
    float restitution = 0.1f;
    float linearDamping = 0.0f;
    bool canRotate = true;
    bool isSensor = false;

    std::unordered_map<std::string, std::string> extra;

    struct TextureMapping {
        std::string mode = "stretch"; // "stretch", "tile", "customUV"
        Vec2 offset{0, 0};
        Vec2 scale{1, 1};
        float rotation = 0.0f;
    };
    std::optional<TextureMapping> textureMapping;
};

#endif // MAP_SECTOR_COMPONENT_H
