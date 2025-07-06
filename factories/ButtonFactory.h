#ifndef BUTTON_FACTORY_H
#define BUTTON_FACTORY_H

#include "core/Components/UIButtonComponent.h"
#include "core/Entity.h"
#include "utils/Vec2.h"

class ButtonFactory {
  public:
    static Entity *create(const Vec2 &windowSize);
};

#endif // BUTTON_FACTORY_H
