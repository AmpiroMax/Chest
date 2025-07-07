#ifndef GUI_RENDER_SYSTEM_H
#define GUI_RENDER_SYSTEM_H

#include "managers/EntityManager.h"
#include "managers/GUIManager.h"
#include "systems/ISystem.h"

class GUIRenderSystem : public ISystem {
  public:
    GUIRenderSystem(GUIManager &g, EntityManager &guiEm) : gui_(g), guiEntities_(guiEm) {}

    SystemSignal update() override {
        // Тут позже будет ImGui-код для кнопок/окон.
        gui_.setStatus(GUIStatus::Render); // финал кадра ImGui
        return SystemSignal::None;
    }

  private:
    GUIManager &gui_;
    EntityManager &guiEntities_; // хранит только GUI-entity
};
#endif
