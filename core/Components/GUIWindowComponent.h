#ifndef GUI_WINDOW_COMPONENT_H
#define GUI_WINDOW_COMPONENT_H
#include "utils/Vec2.h"
#include <string>

struct GUIWindowComponent {
    enum class Type { Inspector /*, Inventory*/ };

    Type type = Type::Inspector;
    std::string title = "Inspector";

    Vec2 pos{800.f, 50.f};
    Vec2 size{300.f, 400.f};

    bool movable = true;
    bool closable = true;
    bool visible = true;
};
#endif
