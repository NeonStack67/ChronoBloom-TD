#pragma once
#include "Projectile.h"

class PeaProjectile : public Projectile {
public:
    PeaProjectile(const sf::Vector2f& pos, int lane, uint32_t ownerSide, EventManager& bus);
};
