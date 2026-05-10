#pragma once
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class EntityManager;
class CardBar;
class ChlorophyllButton;

class InputHandler {
public:
    InputHandler(EventManager& bus, EntityManager& mgr, CardBar& bar, ChlorophyllButton& chloro);
    void handleClick(sf::Vector2f mousePos, sf::Mouse::Button button);
    void drawHoverHighlight(sf::RenderWindow& window, sf::Vector2f worldMousePos);

private:
    EventManager& eventBus;
    EntityManager& entityMgr;
    CardBar& cardBar;
    ChlorophyllButton& chloroButton;
};
