// core/Components/UIButtonComponent.h
#ifndef UI_BUTTON_COMPONENT_H
#define UI_BUTTON_COMPONENT_H

#include "IComponent.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>

struct UIButtonComponent : public IComponent {
    std::string id;       // "pause", "tool_brush" …
    std::string label;    // что писать на кнопке
    sf::FloatRect bounds; // экранные координаты (px)
    bool enabled = true;

    enum class State { Default, Hover, Pressed } state = State::Default;

    // цвета для каждого состояния – можно подменять из конфига
    sf::Color colorDefault = {20, 120, 255};
    sf::Color colorHover = {50, 150, 255};
    sf::Color colorPressed = {10, 90, 200};
};
#endif
