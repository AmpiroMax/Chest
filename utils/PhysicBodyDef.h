#ifndef DYNAMIC_BODY_DEF_H
#define DYNAMIC_BODY_DEF_H

#include "utils/Vec2.h"
#include <string>
#include <vector>

struct PhysicBodyDef {
    enum class BodyShape { Box, Circle, Polygon };
    enum class BodyType { Static, Dynamic };

    BodyShape bodyShape = BodyShape::Box;
    BodyType bodyType = BodyType::Static;

    Vec2 position;
    float angle = 0.0f;

    Vec2 bodySize;                  // ширина, высота (в МИРОВЫХ единицах!)
    float bodyRadius;               // радиус (если круг)
    std::vector<Vec2> bodyVertices; // вершины (если полигон)

    // Dynamic body parametrs
    float maxSpeed = 0.2f;
    float density;               // масса (или плотность, если хочешь)
    float friction;              // трение
    float restitution = 0.1f;    // упругость
    float linearDamping = 0.1f;  // "вязкость", замедление линейное
    float angularDamping = 0.1f; // замедление вращения
    bool canRotate = true;
    bool isSensor = false;
};

#endif // DYNAMIC_BODY_DEF_H