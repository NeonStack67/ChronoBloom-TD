#pragma once
#include <SFML/System/Vector2.hpp>

class IClickable {
public:
    virtual ~IClickable() = default;
    virtual bool containsPoint(sf::Vector2f pixelPos) const = 0;
    virtual bool onClick(sf::Vector2f pixelPos) = 0;
};
