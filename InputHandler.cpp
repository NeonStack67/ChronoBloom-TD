#include "InputHandler.h"
#include "EntityManager.h"
#include "CardBar.h"
#include "Card.h"
#include "ChlorophyllButton.h"
#include "Plant.h"
#include "IClickable.h"
#include "GameEvent.h"
#include "Config.h"

InputHandler::InputHandler(EventManager& bus, EntityManager& mgr, CardBar& bar, ChlorophyllButton& chloro)
    : eventBus(bus), entityMgr(mgr), cardBar(bar), chloroButton(chloro)
{
}

void InputHandler::handleClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
    if (button == sf::Mouse::Button::Right) {
        cardBar.deselectAll();
        chloroButton.cancelAiming();
        return;
    }

    if (button != sf::Mouse::Button::Left) return;

    // Priority 1: Clickable entities (Sun)
    IClickable* target = entityMgr.findClickableAt(mousePos);
    if (target) {
        target->onClick(mousePos);
        return;
    }

    // Priority 2: ChlorophyllButton
    if (chloroButton.handleClick(mousePos)) {
        cardBar.deselectAll();
        return;
    }

    // Priority 3: Card bar UI
    if (cardBar.handleClick(mousePos)) {
        chloroButton.cancelAiming();
        return;
    }

    // Priority 4: Boost aiming mode - click grid to apply boost
    if (chloroButton.isAiming()) {
        sf::Vector2f gridCoord = Grid::pixelToGrid(mousePos);
        int col = static_cast<int>(gridCoord.x);
        int row = static_cast<int>(gridCoord.y);

        if (col >= 0 && col < Grid::COLS && row >= 0 && row < Grid::ROWS) {
            Plant* plant = entityMgr.findPlantAt(col, row);
            if (plant && plant->canBoost() && !plant->isBoosted()) {
                BoostEventData boostData = { col, row };
                eventBus.publish(GameEvent(EventType::ApplyBoost, boostData));
                chloroButton.spendChlorophyll();
                chloroButton.cancelAiming();
            }
        }
        return;
    }

    // Priority 5: Plant placement on grid
    Card* selected = cardBar.getSelectedCard();
    if (!selected) return;

    sf::Vector2f gridCoord = Grid::pixelToGrid(mousePos);
    int col = static_cast<int>(gridCoord.x);
    int row = static_cast<int>(gridCoord.y);

    if (col < 0 || col >= Grid::COLS || row < 0 || row >= Grid::ROWS) return;
    if (entityMgr.isCellOccupied(col, row)) return;

    SpawnEventData plantData = {
        selected->getPlantType(),
        Grid::cellCenter(col, row),
        row,
        Side::Plant
    };
    eventBus.publish(GameEvent(EventType::SpawnEntity, plantData));

    cardBar.spendSun(selected->getSunCost());
    selected->startCooldown();
    cardBar.deselectAll();
}

void InputHandler::drawHoverHighlight(sf::RenderWindow& window, sf::Vector2f worldMousePos) {
    sf::Vector2f gridCoord = Grid::pixelToGrid(worldMousePos);
    int hCol = static_cast<int>(gridCoord.x);
    int hRow = static_cast<int>(gridCoord.y);

    if (hCol < 0 || hCol >= Grid::COLS || hRow < 0 || hRow >= Grid::ROWS) return;

    // Boost aiming mode highlight
    if (chloroButton.isAiming()) {
        sf::RectangleShape hover(sf::Vector2f(Grid::CELL_WIDTH, Grid::CELL_HEIGHT));
        float px = Grid::ORIGIN_X + hCol * Grid::CELL_WIDTH;
        float py = Grid::ORIGIN_Y + hRow * Grid::CELL_HEIGHT;
        hover.setPosition(sf::Vector2f(px, py));

        Plant* plant = entityMgr.findPlantAt(hCol, hRow);
        if (plant && plant->canBoost() && !plant->isBoosted()) {
            hover.setFillColor(sf::Color(50, 255, 50, 50));
        } else if (plant) {
            hover.setFillColor(sf::Color(255, 50, 50, 40));
        } else {
            hover.setFillColor(sf::Color(100, 100, 100, 30));
        }
        window.draw(hover);
        return;
    }

    // Card placement highlight
    Card* selected = cardBar.getSelectedCard();
    if (!selected) return;

    sf::RectangleShape hover(sf::Vector2f(Grid::CELL_WIDTH, Grid::CELL_HEIGHT));
    float px = Grid::ORIGIN_X + hCol * Grid::CELL_WIDTH;
    float py = Grid::ORIGIN_Y + hRow * Grid::CELL_HEIGHT;
    hover.setPosition(sf::Vector2f(px, py));

    if (entityMgr.isCellOccupied(hCol, hRow)) {
        hover.setFillColor(sf::Color(255, 0, 0, 40));
    } else {
        hover.setFillColor(sf::Color(255, 255, 255, 40));
    }
    window.draw(hover);
}
