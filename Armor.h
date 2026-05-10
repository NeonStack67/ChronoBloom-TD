#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Armor {
public:
    Armor(const std::string& name, const std::string& textureKey, float hp);

    // apply damage to armor; returns overflow damage that passes through
    float takeDamage(float amount);

    bool isDestroyed() const { return hp <= 0.f; }
    float getHp() const { return hp; }
    float getMaxHp() const { return maxHp; }
    const std::string& getName() const { return name; }
    const std::string& getTextureKey() const { return textureKey; }

private:
    std::string name;
    std::string textureKey;
    float hp;
    float maxHp;
};
