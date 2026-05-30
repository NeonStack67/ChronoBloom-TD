#include "CherryBomb.h"
#include "GameEvent.h"
#include "Config.h"
#include "DatabaseHelper.h"
#include <cmath>

CherryBomb::CherryBomb(int lane, EventManager& bus)
    : Plant(Entity::SpineTag{}, "CherryBomb", lane, 100.f, bus),
      fuseTime(1.2f),
      timer(0.f),
      exploded(false)
{
    const auto& stats = DataManager::getInstance().getStats("CherryBomb");
    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);

    if (spineComp) {
        spineComp->playAnimation("idle", true, 0);
    }
}

void CherryBomb::update(float dt) {
    //if (exploded) return;

    timer += dt;

    if (timer >= fuseTime) {
        exploded = true;

        sf::Vector2f center = Grid::gridToPixel(getGridPos());
        float halfW = Grid::CELL_WIDTH  * 1.5f;
        float halfH = Grid::CELL_HEIGHT * 1.5f;

        sf::FloatRect blastArea(
            sf::Vector2f(center.x - halfW, center.y - halfH),
            sf::Vector2f(halfW * 2.f, halfH * 2.f)
        );

        const auto& stats = DataManager::getInstance().getStats("CherryBomb");
        DamageEventData dmg;
        dmg.targetArea  = blastArea;
        dmg.damage      = 1800.f;
        dmg.targetMask  = Side::Zombie;

        eventBus.publish(GameEvent(EventType::ApplyDamage, dmg));

        // Spine 路径：播放爆炸动画后延迟销毁，由 dying/die 机制处理
        // 直接 destroy 即可（爆炸视觉由 Spine explode 动画表现）
        destroy();
        return;
    }

    Character::update(dt);
}

void CherryBomb::draw(sf::RenderWindow& window) {
    if (exploded) return;

    float progress = timer / fuseTime; // 0..1

    if (hasSpine() && spineComp) {
        // Spine 路径：用 scale 实现脉冲，用 tint 实现红色渐变
        float pulse = 1.f + 0.15f * std::sin(progress * 12.f);
        spineComp->setScale(pulse, pulse);

        auto g = static_cast<uint8_t>(255 * (1.f - progress * 0.6f));
        auto b = static_cast<uint8_t>(255 * (1.f - progress * 0.6f));
        spineComp->setTint(sf::Color(255, g, b));

        Plant::draw(window);

        // 重置 scale（不重置 tint，由 Plant::draw 的激发逻辑统一管理）
        spineComp->setScale(1.f, 1.f);
    } else {
        // Sprite 路径（fallback）
        if (sprite.has_value()) {
            float pulse = 1.f + 0.15f * std::sin(progress * 12.f);
            auto texSize = sprite->getTexture().getSize();
            float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
            float baseScale = Grid::CELL_MIN / maxDim;
            sprite->setScale(sf::Vector2f(baseScale * pulse, baseScale * pulse));

            auto r = static_cast<uint8_t>(255);
            auto g = static_cast<uint8_t>(255 * (1.f - progress * 0.6f));
            auto b = static_cast<uint8_t>(255 * (1.f - progress * 0.6f));
            sprite->setColor(sf::Color(r, g, b));
        }

        Plant::draw(window);

        if (sprite.has_value()) {
            sprite->setColor(sf::Color::White);
        }
    }
}

