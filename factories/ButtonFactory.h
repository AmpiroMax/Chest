#ifndef BUTTON_FACTORY_H
#define BUTTON_FACTORY_H

#include "core/Components/UIButtonComponent.h"
#include "core/Entity.h"
#include "utils/Vec2.h"

class ButtonFactory {
  public:
    static Entity *create(const Vec2 &windowSize);
    static Entity *makeButton(const std::string &id, const std::string &label, const Vec2 &posPx);
};

#endif // BUTTON_FACTORY_H
