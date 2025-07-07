#ifndef GUI_SYSTEM_H
#define GUI_SYSTEM_H

#include "managers/GUIManager.h"
#include "systems/ISystem.h"

class GUISystem : public ISystem {
  public:
    explicit GUISystem(GUIManager &g) : gui_(g) {}
    SystemSignal update() override {
        gui_.setStatus(GUIStatus::Start); // начало ImGui-кадра
        return SystemSignal::None;
    }

  private:
    GUIManager &gui_;
};
#endif
