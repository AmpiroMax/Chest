#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

class WindowManager {
  public:
    WindowManager() {};
    WindowManager(int width, int height, const std::string &title) : window(sf::VideoMode(width, height), title) {
        view = window.getDefaultView();
    }

    WindowManager(const std::vector<int> &size, const std::string &title)
        : window((size.size() >= 2) ? sf::VideoMode(size[0], size[1]) : sf::VideoMode(800, 600), title) {
        view = window.getDefaultView();
    }

    sf::RenderWindow &getWindow() { return window; }
    sf::View &getView() { return view; }

    void recreate(int width, int height, const std::string &title) {
        window.create(sf::VideoMode(width, height), title);
        view = window.getDefaultView();
    }

    void recreate(const std::vector<int> &size, const std::string &title) {
        int w = (size.size() >= 2) ? size[0] : 800;
        int h = (size.size() >= 2) ? size[1] : 600;
        window.create(sf::VideoMode(w, h), title);
        view = window.getDefaultView();
    }

    void setView(const sf::View &newView) {
        view = newView;
        window.setView(view);
    }

  private:
    sf::RenderWindow window;
    sf::View view;
};

#endif // WINDOW_MANAGER_H
