// systems/RenderSystemUI.h
#ifndef RENDER_SYSTEM_UI_H
#define RENDER_SYSTEM_UI_H
#include "core/Components/UIButtonComponent.h"
#include "managers/EntityManager.h"

// Абстрактный интерфейс-провайдер для рисования (инъекция!)
struct UIDrawContext {
    // Эти методы нужно реализовать отдельно для SFML, OpenGL, чего угодно!
    virtual void drawRect(float x, float y, float w, float h, bool hovered, bool pressed) = 0;
    virtual void drawText(const std::string &text, float x, float y) = 0;
    virtual ~UIDrawContext() = default;
};

class RenderSystemUI {
  public:
    RenderSystemUI(EntityManager &entities) : entityManager(entities) {}

    // Главное: всё через UIDrawContext!
    void draw(UIDrawContext &ctx) {
        for (auto *e : entityManager.getAll()) {
            auto *btn = e->getComponent<UIButtonComponent>();
            if (!btn)
                continue;
            ctx.drawRect(btn->x, btn->y, btn->w, btn->h, btn->hovered, btn->pressed);
            ctx.drawText(btn->label, btn->x + 10, btn->y + btn->h / 2); // Смести для красоты!
        }
    }

  private:
    EntityManager &entityManager;
};

#endif // RENDER_SYSTEM_UI_H