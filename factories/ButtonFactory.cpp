#include "factories/ButtonFactory.h"

Entity *ButtonFactory::create(const Vec2 &windowSize) {
    constexpr float kWidth = 90.f;
    constexpr float kHeight = 30.f;
    constexpr float kPadding = 8.f;

    auto *buttonEnt = new Entity();

    auto btn = std::make_unique<UIButtonComponent>();
    btn->id = "pause";
    btn->label = "Pause";                            // если поле label ещё не ввели — удалите эту строку
    btn->bounds = {windowSize.x - kWidth - kPadding, // правый-верхний угол
                   kPadding, kWidth, kHeight};

    buttonEnt->addComponent(std::move(btn));
    return buttonEnt;
}
