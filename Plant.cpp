#include "Plant.h"
#include "Enums.h" 

// Sprite 路径
Plant::Plant(const std::string& textureKey, int lane, float hp, EventManager& bus)
    : Character(textureKey, lane, hp, bus)
{
    side = Side::Plant;
}

// Spine 路径
Plant::Plant(Entity::SpineTag, const std::string& skelKey, int lane, float hp, EventManager& bus)
    : Character(Entity::SpineTag{}, skelKey, lane, hp, bus)
{
    side = Side::Plant;
}

void Plant::onBoost() {
    boosted = true;
}

void Plant::takeDamage(float amount) {
    if (boosted) return;
    Character::takeDamage(amount);
}

void Plant::draw(sf::RenderWindow& window) {
    if (hasSpine() && spineComp) {
        // Spine 路径：用着色实现激发绿色高亮
        if (boosted) {
            spineComp->setTint(sf::Color(150, 255, 150));
        } else if (hurtTimer <= 0.f) {
            // 不在受伤状态时恢复正常颜色（受伤颜色由 Character::update 管理）
            spineComp->resetTint();
        }
        Character::draw(window);
    } else {
        // Sprite 路径：原有逻辑
        if (boosted) {
            if (sprite.has_value()) sprite->setColor(sf::Color(150, 255, 150));
        }
        Character::draw(window);
        if (boosted) {
            if (sprite.has_value()) sprite->setColor(sf::Color(255, 255, 255));
        }
    }
}