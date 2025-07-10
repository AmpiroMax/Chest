#ifndef EVENTS_H
#define EVENTS_H

#include "core/Entity.h"
#include "managers/ToolStateManager.h"
#include <string>

// --- GUI --------------------------------------------------
struct ButtonClickedEvent {
    std::string id;
};

// --- Tools -----------------------------------------------
struct ToolChangedEvent {
    ToolType tool;
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
