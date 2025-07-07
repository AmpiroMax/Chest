#ifndef TOOL_SYSTEM_H
#define TOOL_SYSTEM_H

#include "managers/EntityManager.h"
#include "managers/HIDManager.h"
#include "systems/ISystem.h"
#include <imgui.h>

class ToolSystem : public ISystem {
  public:
    enum class Mode { Cursor, Rect, Poly, Circle };

    ToolSystem(EntityManager &guiEm, HIDManager &hid) : guiEntities_(guiEm), hid_(hid) {}

    SystemSignal update() override {
        drawToolbar();
        // геометрическая логика будет позже
        return SystemSignal::None;
    }

  private:
    void drawToolbar() {
        ImGui::Begin("Tools", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos({8.f, 50.f});
        ImGui::SetWindowSize({110.f, 180.f});

        auto btn = [&](const char *n, Mode m) {
            if (ImGui::Selectable(n, mode_ == m))
                mode_ = m;
        };
        btn("Cursor", Mode::Cursor);
        btn("Rect", Mode::Rect);
        btn("Poly", Mode::Poly);
        btn("Circle", Mode::Circle);

        ImGui::End();
    }

    EntityManager &guiEntities_;
    HIDManager &hid_;
    Mode mode_ = Mode::Cursor;
};
#endif
