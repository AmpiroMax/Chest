#include "systems/CameraSystem.h"
#include "core/Components/PhysicsComponent.h"

SystemSignal CameraSystem::update() {
    auto *player = entityManager.getPlayer();
    if (!player) {
        return SystemSignal::None;
    }

    auto *phys = player->getComponent<PhysicsComponent>();
    if (!phys) {
        return SystemSignal::None;
    }

    float cameraZoom = cameraManager.getZoom();
    if (hidManager.getKeyboardButtonStatus(KeyboardButtons::Z) == ButtonStatus::Pressed)
        cameraZoom *= 1.0005f;
    if (hidManager.getKeyboardButtonStatus(KeyboardButtons::X) == ButtonStatus::Pressed)
        cameraZoom *= 0.9995f;
    cameraManager.setZoom(cameraZoom);

    cameraManager.setCenter(phys->getPosition());

    return SystemSignal::None;
}