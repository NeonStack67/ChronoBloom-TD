#pragma once
#include "Entity.h"

class Projectile : public Entity {
protected:
    sf::Vector2f velocity; // 子弹速度（包含方向）
    float damage;          // 造成的伤害值
    uint32_t targetMask;   // 目标掩码（能打谁？）

public:
    Projectile(const std::string& textureKey, uint32_t s, int l, sf::Vector2f vel, float dmg, uint32_t mask, EventManager& bus);

    void update(float dt) override;

    void onCollision(Entity* other) override;

    float getDamage() const { return damage; }
    uint32_t getTargetMask() const { return targetMask; }
    sf::Vector2f getVelocity() const { return velocity; }
};