#include "Sunflower.h"
#include "Config.h"
#include "GameEvent.h"
#include "DatabaseHelper.h"

Sunflower::Sunflower(int lane, EventManager& bus)
    : Plant(Entity::SpineTag{}, "Sunflower", lane, 100.f, bus),
      produceCooldown(SunConfig::SUNFLOWER_PRODUCE_INTERVAL),
      timeSinceLastProduce(0.f)
{
    const auto& stats = DataManager::getInstance().getStats("Sunflower");
    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);

    if (spineComp) {
        spineComp->playAnimation("idle", true, 0);
    }
}

void Sunflower::update(float dt) {
    if (dying) { Plant::update(dt); return; }

    timeSinceLastProduce += dt;

    if (timeSinceLastProduce >= produceCooldown) {
        sf::Vector2f pos = Grid::gridToPixel(getGridPos());
        pos.y -= 20.f;
        eventBus.publish(GameEvent(EventType::ProduceSun,
            ProduceSunData{ pos, SunConfig::PLANT_SUN_VALUE }));
        timeSinceLastProduce = 0.f;

        // 触发产出动画（单次），结束后回到 idle
        if (spineComp) {
            spineComp->playAnimation("attack", false, 0);
            spineComp->addAnimation("idle", true, 0);
        }
    }

    Plant::update(dt);
}

