// systems/ButtonSystem.h
#ifndef BUTTON_SYSTEM_H
#define BUTTON_SYSTEM_H

#include "core/Components/UIButtonComponent.h"
#include "events/Events.h"
#include "managers/EntityManager.h"
#include "managers/EventManager.h"
#include "managers/HIDManager.h"
#include "systems/ISystem.h"

class ButtonSystem : public ISystem {
  public:
    ButtonSystem(EntityManager &em, HIDManager &hid, EventManager &ev) : entityManager(em), hidManager(hid), eventManager(ev) {}

    SystemSignal update() override {
        Vec2 mouse = hidManager.getMousePosition();
        bool lmb = (hidManager.getMouseButtonStatus(MouseButtons::Left) == ButtonStatus::Pressed);

        for (auto *e : entityManager.getAll()) {
            auto *btn = e->getComponent<UIButtonComponent>();
            if (!btn || !btn->enabled)
                continue;

            bool inside = btn->bounds.contains(mouse.x, mouse.y);

            switch (btn->state) {
            case UIButtonComponent::State::Default:
                if (inside)
                    btn->state = UIButtonComponent::State::Hover;
                break;
            case UIButtonComponent::State::Hover:
                if (!inside)
                    btn->state = UIButtonComponent::State::Default;
                else if (lmb)
                    btn->state = UIButtonComponent::State::Pressed;
                break;
            case UIButtonComponent::State::Pressed:
                if (!lmb) {
                    // отпускание ― публикуем событие
                    eventManager.emit(ButtonClickedEvent{btn->id});
                    btn->state = inside ? UIButtonComponent::State::Hover : UIButtonComponent::State::Default;
                }
                break;
            }
        }
        return SystemSignal::None;
    }

  private:
    EntityManager &entityManager;
    HIDManager &hidManager;
    EventManager &eventManager;
};
#endif
