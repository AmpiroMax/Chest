#include "ToolSystem.h"
#include "core/Components/PhysicsComponent.h"
#include "utils/CoordinateUtils.h"

ToolSystem::ToolSystem(EntityManager &entityManager, ToolStateManager &ts, HIDManager &hid, EventManager &em, ResourceManager &resourceManager,
                       PhysicsManager &physicsManager, CameraManager &cameraManager)
    : entityManager(entityManager), toolState(ts), hidMgr(hid), evtMgr(em), resourceManager(resourceManager), physicsManager(physicsManager),
      cameraManager(cameraManager) {
    evtMgr.subscribe<ButtonClickedEvent>([this](const ButtonClickedEvent &e) { onButtonClick(e); });
}

void ToolSystem::onButtonClick(const ButtonClickedEvent &e) {
    ToolType t;
    if (e.id == "cursor")
        t = ToolType::Cursor;
    else if (e.id == "rect")
        t = ToolType::Rect;
    else if (e.id == "poly")
        t = ToolType::Polygon;
    else if (e.id == "circle")
        t = ToolType::Circle;
    else
        return;

    toolState.setActiveTool(t);
    evtMgr.emit(ToolChangedEvent{t});
}

SystemSignal ToolSystem::update() {
    switch (toolState.getActiveTool()) {
    case ToolType::Cursor:
        tickCursor();
        break;
    case ToolType::Rect:
        tickRect();
        break;
    case ToolType::Polygon:
        tickPolygon();
        break;
    case ToolType::Circle:
        tickCircle();
        break;
    }
    return SystemSignal::None;
}

/* ───────────────────────────────────────────── *
 *  Ниже – минимальные заглушки логики           *
 * ───────────────────────────────────────────── */

// <========================================= Cursor tool =========================================>
void ToolSystem::tickCursor() {
    // std::cout << "Cursor tool selected" << std::endl;
}

// <========================================= Rect tool =========================================>
Entity *ToolSystem::createRectSector(const Vec2 &firstPointInGameCoordinates) {
    MapSectorData sectorData;
    sectorData.position = firstPointInGameCoordinates;
    sectorData.shapeData.size = Vec2(2, 2);

    sectorData.renderData.texture = "wall_brick";
    sectorData.name = "static brick box wall";
    sectorData.shapeData.shape = MapShapeData::ShapeType::Box;
    sectorData.physicsData.bodyType = MapPhysicsData::BodyType::Static;
    Entity *rectSector = WorldMapFactory::createSectorEntity(sectorData, resourceManager, physicsManager);
    return rectSector;
}

// <========================================= Rect tool =========================================>
void ToolSystem::tickRect() {
    Vec2 mousePosition = hidMgr.getMousePosition();
    bool isLeftMouseButtonPressed = hidMgr.getMouseButtonStatus(MouseButtons::Left) == ButtonStatus::Pressed;

    switch (state.rect.state) {
    case RectToolSystemState::State::Idle: {
        if (isLeftMouseButtonPressed) {
            state.rect.state = RectToolSystemState::State::Drawing;

            state.rect.firstPointCoordinatesInGame = screenToWorld(mousePosition, cameraManager);
            state.rect.secondPointCoordinatesInGame = state.rect.firstPointCoordinatesInGame;

            Entity *rectSectorPreview = createRectSector(state.rect.firstPointCoordinatesInGame);
            state.rect.previewEntityId = rectSectorPreview->getId();
            entityManager.addEntity(rectSectorPreview);
        }
        break;
    }

    case RectToolSystemState::State::Drawing: {
        if (isLeftMouseButtonPressed) {
            auto *entity = entityManager.getEntity(state.rect.previewEntityId);
            state.rect.secondPointCoordinatesInGame = screenToWorld(mousePosition, cameraManager);
            Vec2 size = state.rect.secondPointCoordinatesInGame - state.rect.firstPointCoordinatesInGame;
            Vec2 position = (state.rect.firstPointCoordinatesInGame + state.rect.secondPointCoordinatesInGame) / 2.0f;
            entity->getComponent<PhysicsComponent>()->dynamicProperties.bodySize = size;
            entity->getComponent<PhysicsComponent>()->setPosition(position);
        } else {
            state.rect.state = RectToolSystemState::State::Idle;
            state.rect.previewEntityId = -1;
        }
        break;
    }
    }
}

// <========================================= Polygon tool =========================================>
void ToolSystem::tickPolygon() {
    // std::cout << "Polygon tool selected" << std::endl;
}

// <========================================= Circle tool =========================================>
void ToolSystem::tickCircle() {
    // std::cout << "Circle tool selected" << std::endl;
}