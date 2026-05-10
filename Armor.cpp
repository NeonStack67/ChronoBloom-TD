#include "Armor.h"

Armor::Armor(const std::string& name, const std::string& textureKey, float hp)
    : name(name), textureKey(textureKey), hp(hp), maxHp(hp)
{
}

float Armor::takeDamage(float amount) {
    if (amount <= hp) {
        hp -= amount;
        return 0.f;
    }
    float overflow = amount - hp;
    hp = 0.f;
    return overflow;
}
