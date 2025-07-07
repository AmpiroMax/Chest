#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "managers/IManager.h"
#include <SFML/System/Clock.hpp>

class TimeManager : public IManager {
  public:
    void restart() { delta = innerClock.restart().asMilliseconds(); }
    float getElapsedTime() const { return innerClock.getElapsedTime().asMilliseconds() + 1.0f; }

  private:
    sf::Clock innerClock;
    float delta = 0.f;
};
#endif
