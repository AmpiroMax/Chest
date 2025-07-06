#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class ResourceManager {
  public:
    void loadTexture(const std::string &name, const std::string &filePath) {
        auto tex = std::make_unique<sf::Texture>();
        if (!tex->loadFromFile(filePath)) {
            throw std::runtime_error("Can't load texture: " + filePath);
        }
        textures[name] = std::move(tex);
    }

    bool hasTexture(const std::string &name) const { return textures.find(name) != textures.end(); }

    sf::Texture &getTexture(const std::string &name) {
        if (textures.find(name) == textures.end()) {
            std::cerr << "Texture not found: " << name << std::endl;
            throw std::runtime_error("Texture not found: " + name);
        }
        return *textures.at(name);
    }

    // Optional: попытка безопасно получить текстуру (если не уверен, что она есть)
    sf::Texture *tryGetTexture(const std::string &name) {
        auto it = textures.find(name);
        if (it != textures.end())
            return it->second.get();
        return nullptr;
    }

    void loadTexturesFromList(const std::vector<std::string> &names, const std::string &basePath) {
        for (const auto &name : names) {
            // Можно расширить: проверять расширения (png, jpg, и т.д.)
            std::string fullPath = basePath + name + ".png"; // или другой шаблон
            try {
                loadTexture(name, fullPath);
            } catch (const std::exception &e) {
                std::cerr << "[ResourceManager] Failed to load texture: " << fullPath << " (" << e.what() << ")\n";
            }
        }
    }

  private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
};

#endif // RESOURCE_MANAGER_H
