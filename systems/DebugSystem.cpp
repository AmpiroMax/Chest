#include "systems/DebugSystem.h"
#include "core/Components/MapSectorComponent.h"
#include "core/Components/PhysicsComponent.h"
#include "core/Components/RenderComponent.h"

#include <iostream>
#include <sstream>

SystemSignal DebugSystem::update() {
    std::stringstream ss;

    // Камера
    Vec2 cam = cameraManager.getCenter();
    ss << "[DEBUG] Camera center: (" << cam.x << ", " << cam.y << "), zoom: " << cameraManager.getZoom() << '\n';

    // Окно
    auto &win = windowManager.getWindow();
    ss << "[DEBUG] Window size: " << win.getSize().x << "x" << win.getSize().y << '\n';

    // Entity
    int entityCount = 0, withPhys = 0, withMap = 0;
    for (auto *e : entityManager.getAll()) {
        ++entityCount;
        bool p = (e->getComponent<PhysicsComponent>() != nullptr);
        bool m = (e->getComponent<MapSectorComponent>() != nullptr);
        if (p)
            ++withPhys;
        if (m)
            ++withMap;
    }
    ss << "[DEBUG] Total entities: " << entityCount << ", with Physics: " << withPhys << ", with MapSector: " << withMap
       << '\n';

    for (auto *e : entityManager.getAll()) {
        auto *phys = e->getComponent<PhysicsComponent>();
        if (phys && phys->body) {
            auto pos = phys->getPosition();
            auto entId = e->getId();
            ss << "[DEBUG] Physics entity [" << entId << "] pos: (" << pos.x << ", " << pos.y << ")\n";
        }
    }

    // Print pressed keyboard buttons and their statuses
    ss << "[DEBUG] Keyboard buttons status:\n";
    for (int btn = 0; btn < static_cast<int>(KeyboardButtons::Count); ++btn) {
        KeyboardButtons button = static_cast<KeyboardButtons>(btn);
        ButtonStatus status = hidManager.getKeyboardButtonStatus(button);
        ss << KeyboardButtonToString.at(button) << ": " << ButtonStatusToString.at(status) << '\n';
    }

    // Print mouse buttons status
    ss << "[DEBUG] Mouse buttons status:\n";
    for (int btn = 0; btn < static_cast<int>(MouseButtons::Count); ++btn) {
        MouseButtons button = static_cast<MouseButtons>(btn);
        ButtonStatus status = hidManager.getMouseButtonStatus(button);
        ss << MouseButtonToString.at(button) << ": " << ButtonStatusToString.at(status) << '\n';
    }

    auto mousePos = hidManager.getMousePosition();
    ss << "[DEBUG] Mouse position: (" << mousePos.x << ", " << mousePos.y << ")\n";

    // Устанавливаем статусы работы дебаг манагера
    if (hidManager.getKeyboardButtonStatus(KeyboardButtons::C) == ButtonStatus::Pressed) {
        if (!debugManager.wasStatusChanged()) {
            debugManager.setVisible(!debugManager.isVisible());
            debugManager.setChangeStatus(true);
        }
    } else {
        debugManager.setChangeStatus(false);
    }
    debugManager.setString(ss.str());

    return SystemSignal::None;
}
