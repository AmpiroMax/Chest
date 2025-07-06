#include "systems/WindowEventSystem.h"
#include <SFML/Graphics.hpp>

SystemSignal WindowEventSystem::update() {
    sf::Event event;
    while (windowManager.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return SystemSignal::Quit;
    }
    return SystemSignal::None;
}
