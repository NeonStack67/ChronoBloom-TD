#include "Zombie.h"
#include "Enums.h"
#include "GameEvent.h"
#include "ResourceManager.h"
#include "Config.h"
#include <algorithm>

Zombie::Zombie(const std::string& textureKey, int lane, float hp, float speed, EventManager& bus)
    : Character(textureKey, lane, hp, bus), moveSpeed(speed)
{
    side = Side::Zombie;
}

void Zombie::update(float dt) {
    if (!isEating) {
        moveGrid(sf::Vector2f(-moveSpeed * dt, 0.f));
    }
    isEating = false;

    if (timeSinceLastAttack < attackCooldown) timeSinceLastAttack += dt;

    Character::update(dt);
}

void Zombie::onCollision(Entity* other) {
    if (!other || !other->isActive()) return;

    if ((other->getSide() & Side::Plant) != 0) {
        isEating = true;
        if (timeSinceLastAttack >= attackCooldown) {
            DirectDamageData data = { other, attackDamage };
            eventBus.publish(GameEvent(EventType::ApplyDamage, data));
            timeSinceLastAttack = 0.f;
        }
    }
}

void Zombie::draw(sf::RenderWindow& window) {
    // draw sprite + hp bar + armor bar via Character
    Character::draw(window);

    // draw armor sprite on top of zombie if equipped and not destroyed
    if (hasArmor()) {
        auto& armorTex = ResourceManager::getInstance().getTexture(equippedArmor->getTextureKey());
        sf::Sprite armorSprite(armorTex);
        auto texSize = armorTex.getSize();
        armorSprite.setOrigin(sf::Vector2f(texSize.x / 2.f, texSize.y / 2.f));
        float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
        float armorScale = (Grid::CELL_MIN * 0.45f) / maxDim;
        armorSprite.setScale(sf::Vector2f(armorScale, armorScale));
        sf::Vector2f pos = sprite.getPosition();
        armorSprite.setPosition(sf::Vector2f(pos.x, pos.y - Grid::CELL_HEIGHT * 0.55f));
        window.draw(armorSprite);
    }
}
