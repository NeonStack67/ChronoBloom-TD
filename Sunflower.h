#pragma once
#include "Plant.h"

class Sunflower : public Plant {
public:
    Sunflower(int lane, EventManager& bus);
    void update(float dt) override;

private:
    float produceCooldown;
    float timeSinceLastProduce;
};
