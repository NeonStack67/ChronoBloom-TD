#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Enums.h"
#include "EventManager.h"

class Entity {
protected:
    sf::Sprite sprite;
    bool active;

    uint32_t side;
    uint32_t category;
    int lane;

    sf::Vector2f gridPos;   // authoritative position in grid coordinates

    EventManager& eventBus;

public:
    Entity(const std::string& textureKey, int lane, EventManager& bus);
    virtual ~Entity() = default;

    uint32_t getSide() const { return side; }
    uint32_t getCategory() const { return category; }
    int getLane() const { return lane; }
    bool isActive() const { return active; }

    // grid-based position interface
    sf::Vector2f getGridPos() const { return gridPos; }
    void setGridPos(sf::Vector2f pos) { gridPos = pos; }
    void moveGrid(sf::Vector2f offset) { gridPos += offset; }

    // pixel helpers (derived from gridPos after syncSprite)
    sf::Vector2f getPixelPosition() const { return sprite.getPosition(); }
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    // sync sprite pixel position/scale from gridPos; call after all movement
    virtual void syncSprite();

    // set sprite scale as a multiplier of cell size (default 1.0 = fit one cell)
    void setSpriteScaleMultiplier(float mult);

    virtual void destroy() { active = false; }

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) { window.draw(sprite); }
    virtual void drawHUD(sf::RenderWindow& window) {}

    virtual void onCollision(Entity* other) {}
};
