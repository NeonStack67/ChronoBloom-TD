#include "CherryBomb.h"
#include "GameEvent.h"
#include "Config.h"
#include "DatabaseHelper.h"
#include <cmath>

CherryBomb::CherryBomb(int lane, EventManager& bus)
    : Plant("CherryBomb", lane, 100.f, bus),
      fuseTime(1.2f),
      timer(0.f),
      exploded(false)
{
    // 【新增】从数据中心读取真实的血量
    const auto& stats = DataManager::getInstance().getStats("CherryBomb");
    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);
}

void CherryBomb::update(float dt) {
    if (exploded) return;

    timer += dt;

    if (timer >= fuseTime) {
        exploded = true;

        // Calculate blast area in pixel coordinates centered on this plant
        // BLAST_RADIUS = 1.5 cells means a 3x3 cell area (1.5 cells each side from center)
        sf::Vector2f center = Grid::gridToPixel(getGridPos());
        float halfW = Grid::CELL_WIDTH  * 1.5f;
        float halfH = Grid::CELL_HEIGHT * 1.5f;

        sf::FloatRect blastArea(
            sf::Vector2f(center.x - halfW, center.y - halfH),
            sf::Vector2f(halfW * 2.f, halfH * 2.f)
        );

        // 【新增】在引爆前，再次获取数据库中的伤害数值
        const auto& stats = DataManager::getInstance().getStats("CherryBomb");
        // Publish AOE damage event via DamageEventData
        DamageEventData dmg;
        dmg.targetArea  = blastArea;
        dmg.damage      = 1800.f;
        dmg.targetMask  = Side::Zombie;

        eventBus.publish(GameEvent(EventType::ApplyDamage, dmg));

        // Destroy self after exploding
        destroy();
        return;
    }

    Character::update(dt);
}

void CherryBomb::draw(sf::RenderWindow& window) {
    if (exploded) return;

    // Pulsating scale effect during fuse countdown
    float progress = timer / fuseTime;           // 0..1
    float pulse = 1.f + 0.15f * std::sin(progress * 12.f);
    auto texSize = sprite.getTexture().getSize();
    float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
    float baseScale = Grid::CELL_MIN / maxDim;
    sprite.setScale(sf::Vector2f(baseScale * pulse, baseScale * pulse));

    // Tint increasingly red as fuse progresses
    auto r = static_cast<uint8_t>(255);
    auto g = static_cast<uint8_t>(255 * (1.f - progress * 0.6f));
    auto b = static_cast<uint8_t>(255 * (1.f - progress * 0.6f));
    sprite.setColor(sf::Color(r, g, b));

    Plant::draw(window);

    // Reset color
    sprite.setColor(sf::Color::White);
}
