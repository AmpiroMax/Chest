#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "managers/IManager.h"
#include <SFML/System/Clock.hpp>

class TimeManager : public IManager {
  public:
    void restart() { deltaSec = std::max(innerClock.restart().asSeconds(), 0.000001f); }

    float delta() const { return deltaSec; }

  private:
    sf::Clock innerClock;
    float deltaSec = 1.0f / 60.0f;
};
#endif
