#ifndef COORDINATE_UTILS_H
#define COORDINATE_UTILS_H

#include "Vec2.h"
#include "managers/CameraManager.h"
#include "managers/WindowManager.h"
#include "utils/Constants.h"

// inline Vec2 worldToScreen(const Vec2 &worldPos, const CameraManager &camera, const WindowManager &window) {
//     Vec2 camCenter = camera.getCenter();
//     float zoom = camera.getZoom();
//     Vec2 viewport = camera.getViewportSize();

//     float left = camCenter.x - viewport.x / 2.0f / zoom;
//     float top = camCenter.y - viewport.y / 2.0f / zoom;

//     float screenX = (worldPos.x - left) * zoom;
//     float screenY = (worldPos.y - top) * zoom;

//     return Vec2(screenX, screenY);
// }

inline Vec2 fromWorldToRender(const Vec2 &worldPos) { return Vec2(worldPos.x * RENDER_SCALE, -worldPos.y * RENDER_SCALE); }
inline Vec2 fromRenderToWorld(const Vec2 &renderPos) { return Vec2(renderPos.x / RENDER_SCALE, -renderPos.y / RENDER_SCALE); }

inline Vec2 screenToWorld(const Vec2 &screenPos, const CameraManager &camera) {
    Vec2 camCenter = camera.getCenter();
    float zoom = camera.getZoom();
    Vec2 windowSize = camera.getViewportSize();
    Vec2 deltaScreenPos = screenPos - windowSize / 2.0f;
    Vec2 worldPos = camCenter + fromRenderToWorld(deltaScreenPos);
    // float zoom = camera.getZoom();
    // Vec2 viewport = camera.getViewportSize();
    // Vec2 viewportInGame = viewport / RENDER_SCALE;
    // Vec2 topLeft = camCenter - viewportInGame / 2.0f / zoom;
    // Vec2 worldPos = topLeft + fromRenderToWorld(screenPos);

    return worldPos;
}

inline Vec2 fromWorldToPhysics(const Vec2 &worldPos) { return Vec2(worldPos.x * PHYSIC_SCALE, worldPos.y * PHYSIC_SCALE); }
inline Vec2 fromPhysicsToWorld(const Vec2 &physicsPos) { return Vec2(physicsPos.x / PHYSIC_SCALE, physicsPos.y / PHYSIC_SCALE); }

inline float fromWorldAngleToPhysics(float deg) { return deg * DEG2RAD; }
inline float fromPhysicsAngleToWorld(float rad) { return rad * RAD2DEG; }

inline float fromWorldAngleToRender(float deg) { return -deg; }
inline float fromRenderAngleToWorld(float deg) { return -deg; }

#endif // COORDINATE_UTILS_H
