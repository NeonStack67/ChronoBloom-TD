#include "ResourceManager.h"
#include <iostream>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
    if (textures.find(name) != textures.end()) {
        std::cout << "[ResourceManager] Warning: Texture '" << name << "' is already loaded.\n";
        return true;
    }

    auto texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile(filename)) {
        textures[name] = texture;
        std::cout << "[ResourceManager] Loaded: " << name << " -> " << filename << "\n";
        return true;
    }

    std::cerr << "[ResourceManager] Error: Failed to load " << filename << "\n";
    return false;
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end() && it->second) {
        return *(it->second);
    }

    std::string errorMsg = "[ResourceManager] Fatal Error: Texture missing for '" + name + "'";
    std::cerr << errorMsg << "\n";
    throw std::runtime_error(errorMsg);
}

bool ResourceManager::loadFont(const std::string& name, const std::string& filename) {
    if (fonts.find(name) != fonts.end()) {
        std::cout << "[ResourceManager] Warning: Font '" << name << "' is already loaded.\n";
        return true;
    }

    auto font = std::make_shared<sf::Font>();
    if (font->openFromFile(filename)) {
        fonts[name] = font;
        std::cout << "[ResourceManager] Loaded font: " << name << " -> " << filename << "\n";
        return true;
    }

    std::cerr << "[ResourceManager] Error: Failed to load font " << filename << "\n";
    return false;
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    auto it = fonts.find(name);
    if (it != fonts.end() && it->second) {
        return *(it->second);
    }

    std::string errorMsg = "[ResourceManager] Fatal Error: Font missing for '" + name + "'";
    std::cerr << errorMsg << "\n";
    throw std::runtime_error(errorMsg);
}

void ResourceManager::clear() {
    textures.clear();
    fonts.clear();
    std::cout << "[ResourceManager] All resources cleared.\n";
}