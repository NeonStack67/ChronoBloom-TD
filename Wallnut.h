#pragma once
#include "Plant.h"

class Wallnut : public Plant {
public:
    Wallnut(int lane, EventManager& bus);

    bool canBoost() const override;
    void onBoost() override;
    void update(float dt) override;

private:
    float boostTimer = 0.f;
    static constexpr float BOOST_DURATION = 3.f;
    static constexpr float ARMOR_HP = 500.f;
};