#pragma once
#include "Plant.h"

class EntityManager;

class Peashooter : public Plant {
public:
    Peashooter(int lane, EventManager& bus, const EntityManager& em);

    bool canBoost() const override { return !boosted; }
    void onBoost() override;
    void endBoost() override;
    void update(float dt) override;

private:
    const EntityManager& entityMgr;
    float shootCooldown;
    float timeSinceLastShot;
    float shootRange = 8.0f;
    int boostPeasRemaining;
};