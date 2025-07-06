#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "IComponent.h"
#include <SFML/Graphics.hpp>
#include <string>

struct RenderComponent : public IComponent {
    std::string textureName;
    // Можно добавить: color, z-order, эффекты, флаг “скрыт/отключен” и т.д.
};

#endif // RENDER_COMPONENT_H
