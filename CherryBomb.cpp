#include "CherryBomb.h"
#include "GameEvent.h"
#include "Config.h"
#include "DatabaseHelper.h"

CherryBomb::CherryBomb(int lane, EventManager& bus)
    : Plant(Entity::SpineTag{}, "CherryBomb", lane, 0.f, bus)
{
    const auto& stats = DataManager::getInstance().getStats("CherryBomb");
    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);

    // Born dying: the "die" animation IS the fuse
    dying = true;
    dyingTimer = 0.f;

    if (hasSpine()) {
        if (spineComp->hasAnimationName("die")) {
            spineComp->playAnimation("die", false, 0);
        }
    }
}

void CherryBomb::destroy() {
    sf::Vector2f center = Grid::gridToPixel(getGridPos());
    float halfW = Grid::CELL_WIDTH * 1.5f;
    float halfH = Grid::CELL_HEIGHT * 1.5f;

    sf::FloatRect blastArea(
        sf::Vector2f(center.x - halfW, center.y - halfH),
        sf::Vector2f(halfW * 2.f, halfH * 2.f)
    );

    DamageEventData dmg;
    dmg.targetArea = blastArea;
    dmg.damage = 1800.f;
    dmg.targetMask = Side::Zombie;
    eventBus.publish(GameEvent(EventType::ApplyDamage, dmg));
    Plant::destroy();
}

