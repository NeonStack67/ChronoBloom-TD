#include "Peashooter.h"
#include "EntityManager.h"
#include "GameEvent.h"
#include "DatabaseHelper.h"

Peashooter::Peashooter(int lane, EventManager& bus, const EntityManager& em)
    : Plant("Peashooter", lane, 100.f, bus),
    entityMgr(em),
    shootCooldown(1.5f),
    timeSinceLastShot(0.f)
{
    // 从数据库同步战斗数值
    // PlantStats stats = getPlantStatsFromDB("Peashooter");
    const auto& stats = DataManager::getInstance().getStats("Peashooter");
    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);
}

void Peashooter::onBoost() {
    Plant::onBoost();
    shootCooldown *= 0.05f; 
    boostPeasRemaining = 60;
}

void Peashooter::endBoost() {
    Plant::endBoost();
    shootCooldown /= 0.05f; 
}

void Peashooter::update(float dt) {
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
            timeSinceLastShot = 0.f;
        }

        if (boosted && --boostPeasRemaining <= 0) {
            endBoost();
		}
    }

    Plant::update(dt);
}