#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H
#include <SFML/System/Clock.hpp>

class TimeManager : public IManager {
  public:
    void tick() { delta_ = clock_.restart().asSeconds(); }
    float delta() const { return delta_; }

  private:
    sf::Clock clock_;
    float delta_ = 0.f;
};
#endif
