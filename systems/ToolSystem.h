#ifndef TOOL_SYSTEM_H
#define TOOL_SYSTEM_H

#include "managers/EntityManager.h"
#include "managers/HIDManager.h"
#include "systems/ISystem.h"
#include <imgui.h>

class ToolSystem : public ISystem {
  public:
    enum class Mode { Cursor, Rect, Poly, Circle };

    ToolSystem(EntityManager &guiEntMgr, HIDManager &hidMgr) : guiEntitiesManager(guiEntMgr), hidManager(hidMgr) {}

    SystemSignal update() override {
        drawToolbar();
        return SystemSignal::None;
    }

  private:
    void drawToolbar() {
        ImGui::Begin("Tools", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos({8.f, 50.f});
        ImGui::SetWindowSize({110.f, 180.f});

        auto btn = [&](const char *n, Mode m) {
            if (ImGui::Selectable(n, mode == m))
                mode = m;
        };
        btn("Cursor", Mode::Cursor);
        btn("Rect", Mode::Rect);
        btn("Poly", Mode::Poly);
        btn("Circle", Mode::Circle);

        ImGui::End();
    }

    EntityManager &guiEntitiesManager;
    HIDManager &hidManager;
    Mode mode = Mode::Cursor;
};
#endif
