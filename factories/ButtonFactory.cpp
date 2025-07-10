#include "factories/ButtonFactory.h"

Entity *ButtonFactory::create(const Vec2 &windowSize) {
    constexpr float kWidth = 90.f;
    constexpr float kHeight = 30.f;
    constexpr float kPadding = 8.f;

    auto *buttonEnt = new Entity();

    auto btn = std::make_unique<UIButtonComponent>();
    btn->id = "pause";
    btn->label = "Pause";
    btn->pos = {windowSize.x - kWidth - kPadding, kPadding};
    btn->size = {kWidth, kHeight};

    buttonEnt->addComponent(std::move(btn));
    return buttonEnt;
}

Entity *ButtonFactory::makeButton(const std::string &id, const std::string &label, const Vec2 &posPx) {
    constexpr float w = 120.f;
    constexpr float h = 32.f;

    auto *buttonEnt = new Entity();
    auto btn = std::make_unique<UIButtonComponent>();

    btn->id = id;
    btn->label = label;
    btn->pos = {posPx.x, posPx.y};
    btn->size = {w, h};
    btn->enabled = true;
    btn->state = UIButtonComponent::State::Default;

    buttonEnt->addComponent(std::move(btn));
    return buttonEnt;
}