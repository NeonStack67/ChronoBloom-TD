#include "ChlorophyllButton.h"
#include "ResourceManager.h"

ChlorophyllButton::ChlorophyllButton(float x)
    : buttonX(x)
{
}

sf::FloatRect ChlorophyllButton::getButtonRect() const {
    return sf::FloatRect(
        sf::Vector2f(buttonX, ChlorophyllConfig::BUTTON_Y),
        sf::Vector2f(ChlorophyllConfig::BUTTON_WIDTH, ChlorophyllConfig::BUTTON_HEIGHT)
    );
}

bool ChlorophyllButton::handleClick(sf::Vector2f mousePos) {
    sf::FloatRect rect = getButtonRect();
    if (!rect.contains(mousePos)) return false;

    if (canUseBoost()) {
        aimingMode = !aimingMode;
    }
    return true;
}

void ChlorophyllButton::draw(sf::RenderWindow& window) {
    using namespace ChlorophyllConfig;

    sf::FloatRect rect = getButtonRect();

    // button background
    sf::RectangleShape bg(rect.size);
    bg.setPosition(rect.position);
    if (aimingMode) {
        bg.setFillColor(sf::Color(50, 150, 50, 230));
        bg.setOutlineColor(sf::Color(100, 255, 100));
    } else if (canUseBoost()) {
        bg.setFillColor(sf::Color(30, 80, 30, 220));
        bg.setOutlineColor(sf::Color(60, 140, 60));
    } else {
        bg.setFillColor(sf::Color(50, 50, 50, 200));
        bg.setOutlineColor(sf::Color(80, 80, 80));
    }
    bg.setOutlineThickness(2.f);
    window.draw(bg);

    // label + count
    auto& font = ResourceManager::getInstance().getFont("default");

    sf::Text label(font, "Boost", 10u);
    label.setFillColor(sf::Color(150, 255, 150));
    label.setPosition(sf::Vector2f(rect.position.x + 4.f, rect.position.y + 2.f));
    window.draw(label);

    sf::Text countText(font, std::to_string(chlorophyllCount), 14u);
    countText.setFillColor(sf::Color::White);
    countText.setOutlineColor(sf::Color::Black);
    countText.setOutlineThickness(1.f);
    sf::FloatRect cBounds = countText.getLocalBounds();
    countText.setPosition(sf::Vector2f(
        rect.position.x + (rect.size.x - cBounds.size.x) / 2.f - cBounds.position.x,
        rect.position.y + 18.f
    ));
    window.draw(countText);
}
