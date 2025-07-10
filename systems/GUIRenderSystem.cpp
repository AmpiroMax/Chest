#include "systems/GUIRenderSystem.h"
#include "core/Components/UIButtonComponent.h"
#include "events/Events.h"

GUIRenderSystem::GUIRenderSystem(WindowManager &winMgr, EntityManager &guiEm, ToolStateManager &toolMgr, EventManager &evtMgr)
    : windowManager(winMgr), guiEntitiesManager(guiEm), toolStateManager(toolMgr), eventManager(evtMgr) {}

SystemSignal GUIRenderSystem::update() {
    renderButtons();
    windowManager.getWindow().display();
    return SystemSignal::None;
}

void GUIRenderSystem::renderButtons() {
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        font.loadFromFile("resources/fonts/RobotoMono-VariableFont_wght.ttf");
        fontLoaded = true;
    }

    sf::View oldView = windowManager.getWindow().getView();
    windowManager.getWindow().setView(windowManager.getWindow().getDefaultView());

    for (auto *ent : guiEntitiesManager.getAll()) {
        auto *btn = ent->getComponent<UIButtonComponent>();
        if (!btn || !btn->enabled)
            continue;

        sf::RectangleShape rect({btn->size.x, btn->size.y});
        rect.setPosition(btn->pos.x, btn->pos.y);

        switch (btn->state) {
        case UIButtonComponent::State::Default: {
            sf::Color defaultColor{btn->colorDefault.r, btn->colorDefault.g, btn->colorDefault.b};
            rect.setFillColor(defaultColor);
            break;
        }
        case UIButtonComponent::State::Hover: {
            sf::Color hoverColor{btn->colorHover.r, btn->colorHover.g, btn->colorHover.b};
            rect.setFillColor(hoverColor);
            break;
        }
        case UIButtonComponent::State::Pressed: {
            sf::Color pressedColor{btn->colorPressed.r, btn->colorPressed.g, btn->colorPressed.b};
            rect.setFillColor(pressedColor);
            break;
        }
        }

        windowManager.getWindow().draw(rect);

        sf::Text txt;
        txt.setFont(font);
        txt.setCharacterSize(14);
        txt.setFillColor(sf::Color::White);
        txt.setString(btn->label.empty() ? btn->id : btn->label);

        sf::FloatRect t = txt.getLocalBounds();
        txt.setOrigin(t.left + t.width * 0.5f, t.top + t.height * 0.5f);
        txt.setPosition(btn->pos.x + btn->size.x * 0.5f, btn->pos.y + btn->size.y * 0.5f);

        windowManager.getWindow().draw(txt);
    }
    windowManager.getWindow().setView(oldView);
}
