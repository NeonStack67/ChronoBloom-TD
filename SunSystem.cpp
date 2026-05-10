#include "SunSystem.h"
#include "EntityManager.h"
#include "CardBar.h"
#include "Sun.h"
#include "Config.h"
#include <cstdlib>
#include <memory>

SunSystem::SunSystem(EventManager& bus, EntityManager& mgr, CardBar& bar)
    : eventBus(bus), entityMgr(mgr), cardBar(bar)
{
    sunFlyTarget = sf::Vector2f(
        CardBarConfig::BAR_X + CardBarConfig::SUN_COUNTER_WIDTH / 2.f,
        CardBarConfig::BAR_Y + CardBarConfig::BAR_HEIGHT / 2.f
    );

    produceSunSubId = eventBus.subscribe(EventType::ProduceSun,
        [this](const GameEvent& e) { onProduceSun(e); });

    collectResSubId = eventBus.subscribe(EventType::CollectResource,
        [this](const GameEvent& e) { onCollectResource(e); });
}

SunSystem::~SunSystem() {
    if (produceSunSubId)
        eventBus.unsubscribe(EventType::ProduceSun, produceSunSubId);
    if (collectResSubId)
        eventBus.unsubscribe(EventType::CollectResource, collectResSubId);
}

void SunSystem::update(float dt) {
    skySunTimer -= dt;
    if (skySunTimer <= 0.f) {
        float randomX = Grid::ORIGIN_X +
            static_cast<float>(rand() % static_cast<int>(Grid::GRID_PIXEL_WIDTH));
        float startY = -20.f;
        float targetY = Grid::ORIGIN_Y +
            static_cast<float>(rand() % static_cast<int>(Grid::GRID_PIXEL_HEIGHT));

        auto sun = std::make_unique<Sun>(
            sf::Vector2f(randomX, startY), targetY,
            SunConfig::SKY_SUN_VALUE, sunFlyTarget, eventBus
        );
        entityMgr.addEntity(std::move(sun));

        skySunTimer = SunConfig::SKY_SPAWN_INTERVAL;
    }
}

void SunSystem::onProduceSun(const GameEvent& event) {
    if (auto pdata = std::any_cast<ProduceSunData>(&event.data)) {
        auto sun = std::make_unique<Sun>(
            pdata->pixelPos, pdata->value, sunFlyTarget, eventBus
        );
        entityMgr.addEntity(std::move(sun));
    }
}

void SunSystem::onCollectResource(const GameEvent& event) {
    if (auto cdata = std::any_cast<CollectResourceData>(&event.data)) {
        cardBar.setSunCount(cardBar.getSunCount() + cdata->value);
    }
}
