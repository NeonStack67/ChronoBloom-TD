#include "Sun.h"
#include "ResourceManager.h"
#include "GameEvent.h"
#include <algorithm>
#include <cmath>

// sky sun constructor
Sun::Sun(sf::Vector2f startPixelPos, float targetPixelY, int value,
         sf::Vector2f flyTarget, EventManager& bus)
    : Entity("Sun", 0, bus), value(value), targetY(targetPixelY),
      state(State::Falling), flyTarget(flyTarget), pixelPos(startPixelPos)
{
    side = Side::Neutral;
    category = Category::Collectible;

    auto texSize = sprite.getTexture().getSize();
    float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
    float scale = SunConfig::SUN_SPRITE_SIZE / maxDim;
    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setPosition(pixelPos);
}

// plant sun constructor
Sun::Sun(sf::Vector2f pixelPos, int value,
         sf::Vector2f flyTarget, EventManager& bus)
    : Entity("Sun", 0, bus), value(value), targetY(pixelPos.y),
      state(State::Idle), flyTarget(flyTarget), pixelPos(pixelPos)
{
    side = Side::Neutral;
    category = Category::Collectible;

    auto texSize = sprite.getTexture().getSize();
    float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
    float scale = SunConfig::SUN_SPRITE_SIZE / maxDim;
    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setPosition(pixelPos);
}

void Sun::update(float dt) {
    switch (state) {
    case State::Falling:
        pixelPos.y += SunConfig::SKY_FALL_SPEED * dt;
        if (pixelPos.y >= targetY) {
            pixelPos.y = targetY;
            state = State::Idle;
            idleTimer = 0.f;
        }
        sprite.setPosition(pixelPos);
        break;

    case State::Idle:
        idleTimer += dt;
        if (idleTimer >= SunConfig::IDLE_LIFETIME) {
            active = false;
        }
        break;

    case State::Flying: {
        sf::Vector2f diff = flyTarget - pixelPos;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (dist < 5.f) {
            // Publish CollectResource event
            eventBus.publish(GameEvent(EventType::CollectResource,
                CollectResourceData{ value }));
            active = false;
        } else {
            sf::Vector2f dir = diff / dist;
            pixelPos += dir * SunConfig::FLY_SPEED * dt;
            sprite.setPosition(pixelPos);
        }
        break;
    }
    }
}

void Sun::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

bool Sun::containsPoint(sf::Vector2f point) const {
    if (!active || state == State::Flying) return false;
    return sprite.getGlobalBounds().contains(point);
}

bool Sun::onClick(sf::Vector2f /*pixelPos*/) {
    if (!active || state == State::Flying) return false;
    state = State::Flying;
    return true;
}
