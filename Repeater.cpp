#include "Repeater.h"
#include "EntityManager.h"
#include "GameEvent.h"
#include "DatabaseHelper.h"

Repeater::Repeater(int lane, EventManager& bus, const EntityManager& em)
    : Plant("Repeater", lane, 100.f, bus),
    entityMgr(em),
    shootCooldown(1.5f),
    repeatCooldown(0.2f),
    timeSinceLastShot(0.f)
{
    // 【新增】从数据中心读取真实的血量
    const auto& stats = DataManager::getInstance().getStats("Repeater");

    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);
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
        }

        if (boosted && --boostPeasRemaining <= 0) {
            endBoost();
        }
    }

    Plant::update(dt);
}