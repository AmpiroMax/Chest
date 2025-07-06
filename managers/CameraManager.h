#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "utils/Vec2.h"

enum class CameraMode {
    LockedToTarget, // жёстко за игроком
    FreePan         // свободное перемещение (мышь/клавиши)
};

class CameraManager {
  public:
    void setCenter(const Vec2 &center) { this->center = center; }
    Vec2 getCenter() const { return center; }
    void setViewportSize(const Vec2 &sz) { viewportSize = sz; }
    Vec2 getViewportSize() const { return viewportSize; }
    void setZoom(float z) { zoom = z; }
    float getZoom() const { return zoom; }
    void setMode(CameraMode m) { mode = m; }
    CameraMode getMode() const { return mode; }

  private:
    Vec2 center{0, 0};
    Vec2 viewportSize{800, 600};
    float zoom = 1.0f;
    CameraMode mode = CameraMode::LockedToTarget;
};

#endif // CAMERA_MANAGER_H
