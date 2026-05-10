#include "Sunflower.h"
#include "Config.h"
#include "GameEvent.h"
#include "DatabaseHelper.h"

Sunflower::Sunflower(int lane, EventManager& bus)
    : Plant("Sunflower", lane, 100.f, bus),
      produceCooldown(SunConfig::SUNFLOWER_PRODUCE_INTERVAL),
      timeSinceLastProduce(0.f)
{
    // --- 新增：从数据库同步血量 ---
    // PlantStats stats = getPlantStatsFromDB("Sunflower");
    const auto& stats = DataManager::getInstance().getStats("Sunflower");
    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);
    // ----------------------------
}

void Sunflower::update(float dt) {
    timeSinceLastProduce += dt;

    if (timeSinceLastProduce >= produceCooldown) {
        // Publish ProduceSun event instead of setting a flag
        sf::Vector2f pos = Grid::gridToPixel(getGridPos());
        pos.y -= 20.f;
        eventBus.publish(GameEvent(EventType::ProduceSun,
            ProduceSunData{ pos, SunConfig::PLANT_SUN_VALUE }));
        timeSinceLastProduce = 0.f;
    }

    Plant::update(dt);
}
