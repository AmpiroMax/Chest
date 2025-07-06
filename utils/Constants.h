#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr float PI = 3.14159265358979323846f;
constexpr float DEG2RAD = PI / 180.0f;
constexpr float RAD2DEG = 180.0f / PI;

constexpr float PHYSIC_SCALE = 1.0f;  // 1 метр в игре == PHYSIC_SCALE в физике
constexpr float RENDER_SCALE = 64.0f; // 1 метр в игре == RENDER_SCALE в графике (пикселей)

constexpr float PHYSICS_TIMESTEP = 1.0f / 60.0f;
constexpr int PHYSICS_VELOCITY_ITER = 6;
constexpr int PHYSICS_POSITION_ITER = 2;

#endif // CONSTANTS_H
