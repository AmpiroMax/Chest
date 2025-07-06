#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <nlohmann/json.hpp>
#include <string>

class GameConfig {
  public:
    explicit GameConfig(const std::string &filename);
    void reload();

    // Files
    std::string getResourcePath() const;
    std::string getMapPath() const;
    std::string getTexturePath() const;
    std::string getDefaultLevel() const;

    // Entities
    float getPlayerSpeed() const;
    std::string playerSpriteName() const;

    // Window
    std::vector<int> getWindowSize() const;
    std::string getWindowName() const;

    std::vector<std::string> allTextureNames() const;

  private:
    std::string filename;
    nlohmann::json config;
};

#endif // GAME_CONFIG_H
