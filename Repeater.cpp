#include "Repeater.h"
#include "EntityManager.h"
#include "GameEvent.h"
#include "DatabaseHelper.h"

Repeater::Repeater(int lane, EventManager& bus, const EntityManager& em)
    : Plant(Entity::SpineTag{}, "Repeater", lane, 100.f, bus),
    entityMgr(em),
    shootCooldown(1.5f),
    repeatCooldown(0.2f),
    timeSinceLastShot(0.f)
{
    const auto& stats = DataManager::getInstance().getStats("Repeater");

    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);

    if (spineComp) {
        spineComp->playAnimation("idle", true, 0);
    }
}

void Repeater::onBoost() {
    Plant::onBoost();
    if (shootCooldown < repeatCooldown) std::swap(shootCooldown, repeatCooldown);
    shootCooldown *= 0.025f;
    boostPeasRemaining = 120;
}

void Repeater::endBoost() {
    Plant::endBoost();
    shootCooldown /= 0.025f;
}

void Repeater::update(float dt) {
    if (dying) { Plant::update(dt); return; }

    timeSinceLastShot += dt;

    if (timeSinceLastShot >= shootCooldown) {
        int col = static_cast<int>(getGridPos().x);
        int row = getLane();

        if (entityMgr.hasEnemyInLane(row, col, col + static_cast<int>(shootRange), Side::Zombie) || boosted) {
            SpawnEventData spawn = {
                "PeaProjectile",
                getGridPos() + sf::Vector2f(0.3f, 0.f),
                getLane(),
                getSide()
            };
            eventBus.publish(GameEvent(EventType::SpawnEntity, spawn));
            if (!boosted) std::swap(shootCooldown, repeatCooldown);
            timeSinceLastShot = 0.f;

            // 触发射击动画
            if (spineComp) {
                spineComp->playAnimation("attack", false, 0);
                spineComp->addAnimation("idle", true, 0);
            }
        }

        if (boosted && --boostPeasRemaining <= 0) {
            endBoost();
        }
    }

    Plant::update(dt);
}
