#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "core/Components/PhysicsComponent.h"
#include "managers/CameraManager.h"
#include "managers/EntityManager.h"
#include "managers/HIDManager.h"
#include "systems/ISystem.h"
#include "utils/CoordinateUtils.h"
#include <SFML/Window/Keyboard.hpp>

class HIDSystem : public ISystem {
  public:
    HIDSystem(HIDManager &hidMgr, WindowManager &wdMgr) : hidManager(hidMgr), windowMgr(wdMgr) {}

    SystemSignal update() override {
        Vec2 mouseWorld(sf::Mouse::getPosition(windowMgr.getWindow()));
        hidManager.setMousePosition(mouseWorld);

        for (auto btn : {MouseButtons::Left, MouseButtons::Right}) {
            sf::Mouse::Button sfBtn = (btn == MouseButtons::Left) ? sf::Mouse::Left : sf::Mouse::Right;
            bool pressed = sf::Mouse::isButtonPressed(sfBtn);
            ButtonStatus status = pressed ? ButtonStatus::Pressed : ButtonStatus::Default;
            hidManager.setMouseButtonStatus(btn, status);
        }

        struct KeyMap {
            KeyboardButtons k;
            sf::Keyboard::Key sfk;
        };
        static const KeyMap keys[] = {
            {KeyboardButtons::W, sf::Keyboard::W}, {KeyboardButtons::A, sf::Keyboard::A},
            {KeyboardButtons::S, sf::Keyboard::S}, {KeyboardButtons::D, sf::Keyboard::D},
            {KeyboardButtons::Z, sf::Keyboard::Z}, {KeyboardButtons::X, sf::Keyboard::X},
            {KeyboardButtons::C, sf::Keyboard::C} // Added C key
        };
        for (const auto &map : keys) {
            bool pressed = sf::Keyboard::isKeyPressed(map.sfk);
            ButtonStatus status = pressed ? ButtonStatus::Pressed : ButtonStatus::Default;
            hidManager.setKeyboardButtonStatus(map.k, status);
        }

        return SystemSignal::None;
    }

  private:
    HIDManager &hidManager;
    WindowManager &windowMgr;
};

#endif // INPUT_SYSTEM_H
