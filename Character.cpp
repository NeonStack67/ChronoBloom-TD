#include "Character.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "ResourceManager.h"
#include "Config.h"
#include "SpineManager.h"
#include "GameEvent.h"

// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------

// Sprite path
Character::Character(const std::string& textureKey, int l, float initialHp, EventManager& bus)
    : Entity(textureKey, l, bus),
      hp(initialHp),
      maxHp(initialHp)
{
    category = Category::Character;
    // winkInterval stays at default 3.f (wink code is gated on hasSpine(), so irrelevant)
}

// Spine path
Character::Character(Entity::SpineTag, const std::string& skelKey, int l, float initialHp, EventManager& bus)
    : Entity(Entity::SpineTag{}, l, bus),
      hp(initialHp),
      maxHp(initialHp)
{
    category = Category::Character;

    auto* skeletonData  = SpineManager::getInstance().getSkeletonData(skelKey);
    auto* animStateData = SpineManager::getInstance().getAnimationStateData(skelKey);
    if (skeletonData && animStateData) {
        spineComp = std::make_unique<SpineComponent>(skeletonData, animStateData);

        // Auto-scale: fit skeleton to grid cell size
        spineComp->update(0.f);
        sf::FloatRect bounds = spineComp->getBounds();
        if (bounds.size.x > 0.f && bounds.size.y > 0.f) {
            float maxDim    = std::max(bounds.size.x, bounds.size.y);
            float scaleFactor = Grid::CELL_MIN / maxDim;
            spineComp->setScale(scaleFactor, scaleFactor);
        }
    } else {
        std::cerr << "[Character] Warning: SpineComponent not created for '" << skelKey << "'\n";
    }

    // Stagger wink timers so multiple entities don't blink in sync (2 ~ 5 s)
    winkInterval = 2.f + static_cast<float>(std::rand() % 300) / 100.f;
    winkTimer    = 0.f;
}

// ---------------------------------------------------------------------------
// Combat
// ---------------------------------------------------------------------------

void Character::takeDamage(float amount) {
    if (!active || dying) return;

    hurtTimer = hurtDuration;
    if (hasSpine()) {
        spineComp->setTint(sf::Color(255, 150, 150));
        spineComp->playAnimation("hit", false, 1);
    }

    if (hasArmor()) {
        float overflow = equippedArmor->takeDamage(amount);
        if (overflow <= 0.f) return;
        amount = overflow;
    }

    hp -= amount;
    if (hp <= 0.f) {
        hp = 0.f;
        die();
    }
}

void Character::equipArmor(std::unique_ptr<Armor> armor) {
    equippedArmor = std::move(armor);
}

void Character::destroy() {
    if (!active) return;   // prevent double-publish
    EntityDeadData data = { this, getGridPos() };
    eventBus.publish(GameEvent(EventType::EntityDead, data));
    Entity::destroy();
}

void Character::die() {
    if (dying) return;

    if (hasSpine() && spineComp->hasAnimationName("die")) {
        dying      = true;
        dyingTimer = 0.f;
        spineComp->clearTrack(0);
        spineComp->clearTrack(1);
        spineComp->resetTint();
        hurtTimer = 0.f;
        spineComp->playAnimation("die", false, 0);
    } else {
        destroy();
    }
}

// ---------------------------------------------------------------------------
// Update helpers
// ---------------------------------------------------------------------------

void Character::updateDying(float dt) {
    spineComp->update(dt);
    dyingTimer += dt;

    if (spineComp->isAnimationComplete(0) || dyingTimer > dyingTimeout) {
        destroy();
    }
}

void Character::updateWink(float dt) {
    winkTimer += dt;
    if (winkTimer < winkInterval) return;

    winkTimer = 0.f;
    // Only blink when not hurt and Track 1 is free
    if (hurtTimer <= 0.f && spineComp->isAnimationComplete(1)) {
        if (spineComp->hasAnimationName("wink")) {
            spineComp->playAnimation("wink", false, 1);
        }
    }
    // Randomise next interval (2 ~ 5 s)
    winkInterval = 2.f + static_cast<float>(std::rand() % 300) / 100.f;
}

void Character::updateHurt(float dt) {
    if (hurtTimer <= 0.f) return;

    hurtTimer -= dt;
    if (!hasSpine()) {
        if (sprite.has_value()) sprite->setColor(sf::Color(255, 150, 150));
    }

    if (hurtTimer <= 0.f) {
        hurtTimer = 0.f;
        if (!hasSpine()) {
            if (sprite.has_value()) sprite->setColor(sf::Color(255, 255, 255));
        } else {
            spineComp->resetTint();
            spineComp->addAnimation("", false, 1, 0.f);  // clear Track 1
        }
    }
}

// ---------------------------------------------------------------------------
// Main update
// ---------------------------------------------------------------------------

void Character::update(float dt) {
    if (dying) {
        if (hasSpine()) updateDying(dt);
        else            destroy();
        return;
    }

    if (hasSpine()) {
        spineComp->update(dt);
        updateWink(dt);
    }

    updateHurt(dt);
}

// ---------------------------------------------------------------------------
// Draw
// ---------------------------------------------------------------------------

void Character::draw(sf::RenderWindow& window) {
    if (hasSpine()) {
        spineComp->draw(window, Grid::gridToPixel(gridPos));
    } else {
        if (sprite.has_value()) window.draw(*sprite);
    }
}

void Character::drawHUD(sf::RenderWindow& window) {
    if (!Config::DEBUG_SHOW_HEALTH) return;

    sf::FloatRect bounds;
    if (hasSpine()) {
        bounds = spineComp->getBounds();
    } else if (sprite.has_value()) {
        bounds = sprite->getGlobalBounds();
    } else {
        return;
    }

    const float barWidth  = bounds.size.x;
    const float barHeight = 4.f;
    const float padding   = 2.f;
    const float left      = bounds.position.x;
    const float top       = bounds.position.y;

    sf::RectangleShape back(sf::Vector2f(barWidth, barHeight));
    back.setFillColor(sf::Color(80, 80, 80, 200));
    back.setPosition(sf::Vector2f(left, top - barHeight - padding));

    float ratio = (maxHp > 0.f) ? std::clamp(hp / maxHp, 0.f, 1.f) : 0.f;

    sf::RectangleShape fg(sf::Vector2f(barWidth * ratio, barHeight));
    fg.setFillColor(sf::Color(200, 40, 40));
    fg.setPosition(sf::Vector2f(left, top - barHeight - padding));

    window.draw(back);
    window.draw(fg);

    try {
        auto& font = ResourceManager::getInstance().getFont("default");
        sf::Text txt(font,
            std::to_string(static_cast<int>(hp)) + "/" + std::to_string(static_cast<int>(maxHp)),
            10u);
        txt.setFillColor(sf::Color::White);
        txt.setOutlineColor(sf::Color::Black);
        txt.setOutlineThickness(1.f);
        sf::FloatRect tr = txt.getLocalBounds();
        txt.setPosition(sf::Vector2f(
            left + (barWidth - tr.size.x) / 2.f - tr.position.x,
            top - barHeight - padding - tr.size.y - 2.f));
        window.draw(txt);
    } catch (const std::exception&) {}

    if (equippedArmor && equippedArmor->getMaxHp() > 0.f) {
        const float armorBarY = top - barHeight - padding - 14.f - barHeight - padding;

        sf::RectangleShape armorBack(sf::Vector2f(barWidth, barHeight));
        armorBack.setFillColor(sf::Color(60, 60, 80, 200));
        armorBack.setPosition(sf::Vector2f(left, armorBarY));

        float armorRatio = std::clamp(equippedArmor->getHp() / equippedArmor->getMaxHp(), 0.f, 1.f);

        sf::RectangleShape armorFg(sf::Vector2f(barWidth * armorRatio, barHeight));
        armorFg.setFillColor(sf::Color(80, 140, 220));
        armorFg.setPosition(sf::Vector2f(left, armorBarY));

        window.draw(armorBack);
        window.draw(armorFg);
    }
}
