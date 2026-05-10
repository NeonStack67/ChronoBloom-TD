#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

class ChlorophyllButton {
public:
    ChlorophyllButton(float x);

    bool handleClick(sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window);

    bool isAiming() const { return aimingMode; }
    void cancelAiming() { aimingMode = false; }

    bool canUseBoost() const { return chlorophyllCount >= ChlorophyllConfig::BOOST_COST; }
    void spendChlorophyll() { chlorophyllCount -= ChlorophyllConfig::BOOST_COST; }

    void setChlorophyllCount(int count) { chlorophyllCount = count; }
    int getChlorophyllCount() const { return chlorophyllCount; }

private:
    float buttonX;
    int chlorophyllCount = 0;
    bool aimingMode = false;

    sf::FloatRect getButtonRect() const;
};
