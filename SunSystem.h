#pragma once
#include <SFML/System/Vector2.hpp>
#include "EventManager.h"
#include "GameEvent.h"

class EntityManager;
class CardBar;

class SunSystem {
public:
    SunSystem(EventManager& bus, EntityManager& mgr, CardBar& bar);
    ~SunSystem();
    void update(float dt);

private:
    void onProduceSun(const GameEvent& event);
    void onCollectResource(const GameEvent& event);

    EventManager& eventBus;
    EntityManager& entityMgr;
    CardBar& cardBar;

    float skySunTimer = 5.f;
    sf::Vector2f sunFlyTarget;

    size_t produceSunSubId = 0;
    size_t collectResSubId = 0;
};
