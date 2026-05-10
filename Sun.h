#pragma once
#include "Entity.h"
#include "IClickable.h"
#include "Config.h"

class Sun : public Entity, public IClickable {
public:
    enum class State { Falling, Idle, Flying };

    // sky sun: falls from startPixelY to targetPixelY
    Sun(sf::Vector2f startPixelPos, float targetPixelY, int value,
        sf::Vector2f flyTarget, EventManager& bus);

    // plant sun: spawns at plant position, goes to idle immediately
    Sun(sf::Vector2f pixelPos, int value,
        sf::Vector2f flyTarget, EventManager& bus);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void onCollision(Entity* other) override {}

    // Sun manages its own pixel position; skip grid-based sync
    void syncSprite() override {}

    // IClickable
    bool containsPoint(sf::Vector2f pixelPos) const override;
    bool onClick(sf::Vector2f pixelPos) override;

    State getState() const { return state; }
    int getValue() const { return value; }

private:
    State state;
    int value;
    float targetY;
    sf::Vector2f flyTarget;
    float idleTimer = 0.f;
    sf::Vector2f pixelPos;
};
