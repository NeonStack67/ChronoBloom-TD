#include "Plant.h"
#include "Enums.h" 

Plant::Plant(const std::string& textureKey, int lane, float hp, EventManager& bus)
    : Character(textureKey, lane, hp, bus)
{
    side = Side::Plant;
}

void Plant::onBoost() {
    boosted = true;
}

void Plant::takeDamage(float amount) {
    if (boosted) return;
    Character::takeDamage(amount);
}

void Plant::draw(sf::RenderWindow& window) {
    if (boosted) {
        sprite.setColor(sf::Color(150, 255, 150));
    }
    Character::draw(window);
    if (boosted) {
        sprite.setColor(sf::Color(255, 255, 255));
    }
}