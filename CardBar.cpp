#include "CardBar.h"
#include "ResourceManager.h"
#include "Config.h"

CardBar::CardBar() {}

void CardBar::addCard(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}

Card* CardBar::getCard(int index) {
    if (index < 0 || index >= static_cast<int>(cards.size())) return nullptr;
    return cards[index].get();
}

Card* CardBar::getSelectedCard() {
    if (selectedIndex < 0 || selectedIndex >= static_cast<int>(cards.size()))
        return nullptr;
    return cards[selectedIndex].get();
}

void CardBar::deselectAll() {
    for (auto& card : cards) {
        card->setSelected(false);
    }
    selectedIndex = -1;
}

sf::FloatRect CardBar::getCardRect(int index) const {
    using namespace CardBarConfig;
    float cardX = BAR_X + SUN_COUNTER_WIDTH + CARD_PADDING
                  + index * (CARD_WIDTH + CARD_PADDING);
    float cardY = BAR_Y + (BAR_HEIGHT - CARD_HEIGHT) / 2.f;
    return sf::FloatRect(sf::Vector2f(cardX, cardY), sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
}

bool CardBar::handleClick(sf::Vector2f mousePos) {
    for (int i = 0; i < static_cast<int>(cards.size()); ++i) {
        sf::FloatRect rect = getCardRect(i);
        if (rect.contains(mousePos)) {
            if (selectedIndex == i) {
                // clicking the same card deselects it
                deselectAll();
            } else {
                deselectAll();
                if (cards[i]->canUse(sunCount)) {
                    cards[i]->setSelected(true);
                    selectedIndex = i;
                }
            }
            return true; // click was on the card bar
        }
    }
    // check if click was within the bar background area
    using namespace CardBarConfig;
    float totalWidth = SUN_COUNTER_WIDTH + cards.size() * (CARD_WIDTH + CARD_PADDING) + CARD_PADDING;
    sf::FloatRect barRect(sf::Vector2f(BAR_X, BAR_Y), sf::Vector2f(totalWidth, BAR_HEIGHT));
    if (barRect.contains(mousePos)) {
        return true; // click on bar background, consume it
    }
    return false;
}

void CardBar::update(float dt) {
    for (auto& card : cards) {
        card->update(dt);
    }
}

void CardBar::draw(sf::RenderWindow& window) {
    using namespace CardBarConfig;

    // calculate total bar width
    float totalCardsWidth = SUN_COUNTER_WIDTH + cards.size() * (CARD_WIDTH + CARD_PADDING) + CARD_PADDING;
    float barWidth = totalCardsWidth;

    // draw bar background
    sf::RectangleShape barBg(sf::Vector2f(barWidth, BAR_HEIGHT));
    barBg.setFillColor(sf::Color(50, 30, 10, 220));
    barBg.setOutlineColor(sf::Color(100, 70, 30));
    barBg.setOutlineThickness(2.f);
    barBg.setPosition(sf::Vector2f(BAR_X, BAR_Y));
    window.draw(barBg);

    // draw sun counter
    auto& font = ResourceManager::getInstance().getFont("default");

    sf::Text sunLabel(font, "Sun", 10u);
    sunLabel.setFillColor(sf::Color(255, 200, 50));
    sunLabel.setPosition(sf::Vector2f(BAR_X + 8.f, BAR_Y + 10.f));
    window.draw(sunLabel);

    sf::Text sunText(font, std::to_string(sunCount), 16u);
    sunText.setFillColor(sf::Color::Yellow);
    sunText.setOutlineColor(sf::Color::Black);
    sunText.setOutlineThickness(1.f);
    sf::FloatRect sunBounds = sunText.getLocalBounds();
    sunText.setPosition(sf::Vector2f(
        BAR_X + (SUN_COUNTER_WIDTH - sunBounds.size.x) / 2.f - sunBounds.position.x,
        BAR_Y + 35.f
    ));
    window.draw(sunText);

    // draw separator line
    sf::RectangleShape sep(sf::Vector2f(1.f, BAR_HEIGHT - 10.f));
    sep.setFillColor(sf::Color(100, 70, 30));
    sep.setPosition(sf::Vector2f(BAR_X + SUN_COUNTER_WIDTH, BAR_Y + 5.f));
    window.draw(sep);

    // draw each card
    for (int i = 0; i < static_cast<int>(cards.size()); ++i) {
        sf::FloatRect rect = getCardRect(i);
        cards[i]->draw(window, rect.position, rect.size);
    }
}
