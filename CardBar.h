#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Card.h"

class CardBar {
public:
    CardBar();

    void addCard(std::unique_ptr<Card> card);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    // returns true if the click was consumed by the card bar
    bool handleClick(sf::Vector2f mousePos);
    void deselectAll();

    Card* getSelectedCard();
    int getSelectedCardIndex() const { return selectedIndex; }

    void setSunCount(int sun) { sunCount = sun; }
    int getSunCount() const { return sunCount; }
    void spendSun(int amount) { sunCount -= amount; }

    int getCardCount() const { return static_cast<int>(cards.size()); }
    Card* getCard(int index);

private:
    std::vector<std::unique_ptr<Card>> cards;
    int sunCount = 50;
    int selectedIndex = -1;

    // cached card positions for hit testing
    sf::FloatRect getCardRect(int index) const;
};
