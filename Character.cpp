#include "Character.h"
#include <iostream>
#include "ResourceManager.h"
#include "Config.h"

Character::Character(const std::string& textureKey, int l, float initialHp, EventManager& bus)
    : Entity(textureKey, l, bus),
    hp(initialHp),
    maxHp(initialHp)
{
    category = Category::Character;
}

void Character::takeDamage(float amount) {
    if (!active) return;
    hurtTimer = hurtDuration;

    if (hasArmor()) {
        float overflow = equippedArmor->takeDamage(amount);
        if (overflow <= 0.f) return;
        amount = overflow;
    }

    hp -= amount;
    if (hp <= 0) {
        hp = 0;
        die();
    }
}

void Character::equipArmor(std::unique_ptr<Armor> armor) {
    equippedArmor = std::move(armor);
}

void Character::die() {
    EntityDeadData data = { this, getGridPos() };
    eventBus.publish(GameEvent(EventType::EntityDead, data));
    destroy();
}

void Character::update(float dt) {
    if (hurtTimer > 0.f) {
        hurtTimer -= dt;
        sprite.setColor(sf::Color(255, 150, 150));
        if (hurtTimer <= 0.f) {
            sprite.setColor(sf::Color(255, 255, 255));
            hurtTimer = 0.f;
        }
    }
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Character::drawHUD(sf::RenderWindow& window) {
    if (!Config::DEBUG_SHOW_HEALTH) return;

    sf::FloatRect bounds = sprite.getGlobalBounds();

    float barWidth = bounds.size.x;
    float barHeight = 4.f;
    float padding = 2.f;
    float left = bounds.position.x;
    float top = bounds.position.y;

    sf::RectangleShape back(sf::Vector2f(barWidth, barHeight));
    back.setFillColor(sf::Color(80, 80, 80, 200));
    back.setPosition(sf::Vector2f(left, top - barHeight - padding));

    float ratio = (maxHp > 0.f) ? (hp / maxHp) : 0.f;
    if (ratio < 0.f) ratio = 0.f;
    if (ratio > 1.f) ratio = 1.f;

    sf::RectangleShape fg(sf::Vector2f(barWidth * ratio, barHeight));
    fg.setFillColor(sf::Color(200, 40, 40));
    fg.setPosition(sf::Vector2f(left, top - barHeight - padding));

    window.draw(back);
    window.draw(fg);

    try {
        auto& font = ResourceManager::getInstance().getFont("default");
        sf::Text txt(font, std::to_string(static_cast<int>(hp)) + "/" + std::to_string(static_cast<int>(maxHp)), 10u);
        txt.setFillColor(sf::Color::White);
        txt.setOutlineColor(sf::Color::Black);
        txt.setOutlineThickness(1.f);
        sf::FloatRect trect = txt.getLocalBounds();
        float textWidth = trect.size.x;
        float textHeight = trect.size.y;
        float textLeft = trect.position.x;
        txt.setPosition(sf::Vector2f(left + (barWidth - textWidth) / 2.f - textLeft, top - barHeight - padding - textHeight - 2.f));
        window.draw(txt);
    }
    catch (const std::exception& e) {
        (void)e;
    }

    if (equippedArmor && equippedArmor->getMaxHp() > 0.f) {
        float armorBarY = top - barHeight - padding - 14.f - barHeight - padding;

        sf::RectangleShape armorBack(sf::Vector2f(barWidth, barHeight));
        armorBack.setFillColor(sf::Color(60, 60, 80, 200));
        armorBack.setPosition(sf::Vector2f(left, armorBarY));

        float armorRatio = equippedArmor->getHp() / equippedArmor->getMaxHp();
        if (armorRatio < 0.f) armorRatio = 0.f;
        if (armorRatio > 1.f) armorRatio = 1.f;

        sf::RectangleShape armorFg(sf::Vector2f(barWidth * armorRatio, barHeight));
        armorFg.setFillColor(sf::Color(80, 140, 220));
        armorFg.setPosition(sf::Vector2f(left, armorBarY));

        window.draw(armorBack);
        window.draw(armorFg);
    }
}
