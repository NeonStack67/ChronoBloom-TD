#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include "Enums.h"
#include "EventManager.h"

class Entity {
public:
    // 标签分发：用于 Spine 路径的构造函数，不加载静态纹理
    struct SpineTag {};

protected:
    std::optional<sf::Sprite> sprite;   // 仅 Sprite 模式（Sun/Projectile）有值
    bool active;

    uint32_t side;
    uint32_t category;
    int lane;

    sf::Vector2f gridPos;   // authoritative position in grid coordinates

    EventManager& eventBus;

public:
    // Sprite 路径构造函数（Sun、PeaProjectile 等）
    Entity(const std::string& textureKey, int lane, EventManager& bus);

    // Spine 路径构造函数（Plant、Zombie 等）—— sprite 保持 nullopt
    Entity(SpineTag, int lane, EventManager& bus);

    virtual ~Entity() = default;

    // Non-copyable, movable (unique members prevent implicit copy)
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    uint32_t getSide() const { return side; }
    uint32_t getCategory() const { return category; }
    int getLane() const { return lane; }
    bool isActive() const { return active; }

    // grid-based position interface
    sf::Vector2f getGridPos() const { return gridPos; }
    void setGridPos(sf::Vector2f pos) { gridPos = pos; }
    void moveGrid(sf::Vector2f offset) { gridPos += offset; }

    // pixel helpers
    sf::Vector2f getPixelPosition() const;
    virtual sf::FloatRect getBounds() const;

    // sync sprite pixel position from gridPos; call after all movement
    virtual void syncSprite();

    // set sprite scale as a multiplier of cell size (only for Sprite mode)
    void setSpriteScaleMultiplier(float mult);

    virtual void destroy() { active = false; }

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window);
    virtual void drawHUD(sf::RenderWindow& window) {}

    virtual void onCollision(Entity* other) {}

protected:
    bool hasSpriteMode() const { return sprite.has_value(); }
};
