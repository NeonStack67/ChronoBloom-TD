#pragma once
#include "Character.h"

class Plant : public Character {
protected:
    bool boosted = false;

    virtual void endBoost() { boosted = false; }

public:
    // Sprite 路径
    Plant(const std::string& textureKey, int lane, float hp, EventManager& bus);

    // Spine 路径
    Plant(Entity::SpineTag, const std::string& skelKey, int lane, float hp, EventManager& bus);

    virtual ~Plant() = default;

    virtual bool canBoost() const { return false; }
    virtual void onBoost();
    bool isBoosted() const { return boosted; }

    void takeDamage(float amount) override;
    void draw(sf::RenderWindow& window) override;
};