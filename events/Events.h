#ifndef EVENTS_H
#define EVENTS_H

#include "core/Entity.h" // если нужен Entity, иначе убери
#include <string>

// --- GUI --------------------------------------------------
struct ButtonClickedEvent {
    std::string id; // "pause", "tool_brush", ...
};

struct ToolChangedEvent {
    enum class Tool { Brush, Fill, Eraser } newTool;
};

// --- Gameplay ---------------------------------------------
struct TriggerEnteredEvent {
    Entity trigger;
    Entity actor;
};

struct BossDiedEvent {
    Entity boss;
    Entity killer;
};

// --- System -----------------------------------------------
struct GamePauseEvent {
    bool paused;
};

#endif // EVENTS_H
