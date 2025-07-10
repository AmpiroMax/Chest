// core/Components/UIButtonComponent.h
#ifndef UI_BUTTON_COMPONENT_H
#define UI_BUTTON_COMPONENT_H

#include "IComponent.h"
#include "utils/Vec2.h"
#include <string>

struct UIButtonComponent : public IComponent {
    struct Color {
        uint8_t r{50};
        uint8_t g{150};
        uint8_t b{255};
    };

    std::string id;    // "pause", "tool_brush" …
    std::string label; // что писать на кнопке
    Vec2 pos;
    Vec2 size;
    bool enabled = true;

    enum class State { Default, Hover, Pressed };
    State state = State::Default;

    // цвета для каждого состояния – можно подменять из конфига
    Color colorDefault{20, 120, 255};
    Color colorHover{50, 150, 255};
    Color colorPressed{10, 90, 200};
};
#endif
