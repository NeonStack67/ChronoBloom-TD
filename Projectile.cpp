#include "Projectile.h"
#include "Character.h"
#include "Enums.h"
#include "ResourceManager.h"
#include "Config.h"

Projectile::Projectile(const std::string& textureKey, uint32_t s, int l, sf::Vector2f vel, float dmg, uint32_t mask, EventManager& bus)
    : Entity(textureKey, l, bus),
    velocity(vel),
    damage(dmg),
    targetMask(mask)
{
    side = s;
    category = Category::Projectile;
}

void Projectile::update(float dt) {
    if (!active) return;

    moveGrid(velocity * dt);

    // boundary check in grid coordinates
    sf::Vector2f pos = getGridPos();
    if (pos.x > Grid::COLS + 2.f || pos.x < -2.f ||
        pos.y > Grid::ROWS + 2.f || pos.y < -2.f) {
        destroy();
    }
}

void Projectile::onCollision(Entity* other) {
    if (!active || !other->isActive()) return;

    if ((other->getSide() & targetMask) != 0) {
        DirectDamageData data = { other, damage };
        eventBus.publish(GameEvent(EventType::ApplyDamage, data));
        destroy();
    }
}
