#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "IComponent.h"

struct PositionComponent : public IComponent {
    float x;
    float y;
    PositionComponent(float xx, float yy) : x(xx), y(yy) {}
};

#endif // POSITION_COMPONENT_H
