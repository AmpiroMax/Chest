#include "services/GameConfig.h"
#include <fstream>

GameConfig::GameConfig(const std::string &filename) : filename(filename) { reload(); }

void GameConfig::reload() {
    std::ifstream file(filename);
    file >> config;
}

std::string GameConfig::getResourcePath() const { return config["resources_path"]; }

std::string GameConfig::getMapPath() const { return config["resources_path"].get<std::string>() + config["map_foulder"].get<std::string>(); }

std::string GameConfig::getTexturePath() const { return config["resources_path"].get<std::string>() + config["textures_path"].get<std::string>(); }

std::string GameConfig::getDefaultLevel() const { return config["default_level"]; }

float GameConfig::getPlayerSpeed() const { return config["player"]["speed"]; }

std::string GameConfig::playerSpriteName() const { return config["player"]["sprite"]; }

std::vector<int> GameConfig::getWindowSize() const {
    // Возвращает [width, height]
    std::vector<int> size(2, 0);
    if (config.contains("window") && config["window"].contains("size")) {
        size[0] = config["window"]["size"][0];
        size[1] = config["window"]["size"][1];
    }
    return size;
}

std::string GameConfig::getWindowName() const {
    if (config.contains("window") && config["window"].contains("window_name")) {
        return config["window"]["window_name"];
    }
    return "Game";
}

std::vector<std::string> GameConfig::allTextureNames() const {
    std::vector<std::string> names;
    // Добавь сюда все текстуры, которые точно нужны на старте:
    names.push_back(config["player"]["sprite"].get<std::string>());
    // Можно пройтись по всем мобам, декорациям и т.д.
    if (config.contains("mob_defaults")) {
        for (const auto &mob : config["mob_defaults"].items()) {
            if (mob.value().contains("sprite")) {
                names.push_back(mob.value()["sprite"].get<std::string>());
            }
        }
    }
    for (const auto &texture : config["map_textures"].items()) {
        names.push_back(texture.value().get<std::string>());
    }
    // Аналогично можно добавить текстуры карты, тайлов, UI и т.д.
    return names;
}
