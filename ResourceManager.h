#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <memory>

class ResourceManager {
public:
    static ResourceManager& getInstance();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    bool loadTexture(const std::string& name, const std::string& filename);

    // keep same signature for compatibility; returns reference to texture
    sf::Texture& getTexture(const std::string& name);

    // font support
    bool loadFont(const std::string& name, const std::string& filename);
    sf::Font& getFont(const std::string& name);

    void clear();

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts;
};