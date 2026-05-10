#pragma once
#include "Entity.h"
#include "Armor.h"
#include <memory>

class Character : public Entity {
protected:
    float hp;
    float maxHp;

    // hurt visual feedback
    float hurtTimer = 0.f;            // time left to show hurt flash
    static constexpr float hurtDuration = 0.15f; // seconds

    // armor component: independent, composable
    std::unique_ptr<Armor> equippedArmor;

public:
    Character(const std::string& textureKey, int lane, float initialHp, EventManager& bus);

    void update(float dt) override;
    virtual void takeDamage(float amount);
    virtual void die();

    void equipArmor(std::unique_ptr<Armor> armor);
    bool hasArmor() const { return equippedArmor && !equippedArmor->isDestroyed(); }
    Armor* getArmor() const { return equippedArmor.get(); }

    void draw(sf::RenderWindow& window) override;    // draw sprite only
    void drawHUD(sf::RenderWindow& window) override; // draw health bar + armor bar
};