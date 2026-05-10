#pragma once
#include "Plant.h"

class CherryBomb : public Plant {
public:
    CherryBomb(int lane, EventManager& bus);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    float fuseTime;
    float timer;
    bool exploded;
};
