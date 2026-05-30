#pragma once
#include "Character.h"
#include <memory>

class Zombie : public Character {
public:
    // Sprite 路径
    Zombie(const std::string& textureKey, int lane, float hp, float speed, EventManager& bus);

    // Spine 路径
    Zombie(Entity::SpineTag, const std::string& skelKey, int lane, float hp, float speed, EventManager& bus);

    virtual ~Zombie() = default;

    void update(float dt) override;
    void onCollision(Entity* other) override;
    void draw(sf::RenderWindow& window) override;

protected:
    float moveSpeed;

    float attackDamage = 10.f;
    float attackCooldown = 0.5f;
    float timeSinceLastAttack = 0.f;
    bool isEating = false;

private:
    // 记录上一帧的进食状态，用于检测状态变化触发动画切换
    bool wasEating = false;
};
