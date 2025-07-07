#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "IManager.h"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

enum class GUIStatus { Start, Render };

class GUIManager : public IManager {
  public:
    void init(sf::RenderWindow &w) {
        bool wasCreated = ImGui::SFML::Init(w);
        window_ = &w;
    }

    void setStatus(GUIStatus s) {
        if (!window_)
            return;
        switch (s) {
        case GUIStatus::Start:
            ImGui::SFML::Update(*window_, sf::seconds(1.f));
            break;
        case GUIStatus::Render:
            ImGui::SFML::Render(*window_);
            break;
        }
    }

    void shutdown() override { ImGui::SFML::Shutdown(); }

  private:
    sf::RenderWindow *window_ = nullptr;
};
#endif
