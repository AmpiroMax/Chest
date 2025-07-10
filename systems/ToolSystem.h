#ifndef TOOL_SYSTEM_H
#define TOOL_SYSTEM_H

#include "core/Components/RectPreviewComponent.h"
#include "core/Entity.h"
#include "events/Events.h"
#include "factories/WorldMapFactory.h"
#include "managers/EntityManager.h"
#include "managers/EventManager.h"
#include "managers/HIDManager.h"
#include "managers/PhysicsManager.h"
#include "managers/ResourceManager.h"
#include "managers/ToolStateManager.h"
#include "systems/ISystem.h"
#include "utils/Vec2.h"

struct RectToolSystemState {
    enum class State { Idle, Drawing } state = State::Idle;
    Vec2 firstPointCoordinatesInGame;
    Vec2 secondPointCoordinatesInGame;
    size_t previewEntityId = -1;
};

struct ToolSystemState {
    RectToolSystemState rect;
};

class ToolSystem : public ISystem {
  public:
    ToolSystem(EntityManager &entityManager, ToolStateManager &ts, HIDManager &hid, EventManager &em, ResourceManager &resourceManager,
               PhysicsManager &physicsManager, CameraManager &cameraManager);

    SystemSignal update() override;

  private:
    void onButtonClick(const ButtonClickedEvent &);

    // логика инструментов внутри одной системы
    void tickCursor();
    void tickRect();
    void tickPolygon();
    void tickCircle();

    Entity *createRectSector(const Vec2 &firstPointInGameCoordinates);

    EntityManager &entityManager;
    ToolStateManager &toolState;
    HIDManager &hidMgr;
    EventManager &evtMgr;
    ResourceManager &resourceManager;
    PhysicsManager &physicsManager;
    CameraManager &cameraManager;

    ToolSystemState state;
};

#endif /* TOOL_SYSTEM_H */