#ifndef RECT_PREVIEW_COMPONENT_H
#define RECT_PREVIEW_COMPONENT_H
#include "utils/Vec2.h"

#include "IComponent.h"

struct RectPreviewComponent : IComponent {
    Vec2 firstPoint{0.f, 0.f};
    Vec2 secondPoint{0.f, 0.f};
};

#endif // RECT_PREVIEW_COMPONENT_H
