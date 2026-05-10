#pragma once
#include <vector>
#include <array>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EventManager.h"
#include "GameEvent.h"
#include "Config.h"

class IClickable;
class Plant;

class EntityManager {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> pendingEntities;

    EventManager& eventBus;

    // subscription ids returned by EventManager::subscribe
    size_t spawnSubscriptionId = 0;
    size_t applyDamageSubscriptionId = 0;
    size_t applyBoostSubscriptionId = 0;

    // Grid-based spatial index (non-owning pointers, rebuilt each frame)
    std::array<std::array<std::vector<Entity*>, Grid::COLS>, Grid::ROWS> gridCells;
    std::vector<IClickable*> clickables;

    void rebuildSpatialIndex();

public:
    explicit EntityManager(EventManager& bus);
    ~EntityManager();

    void update(float dt);
    void draw(sf::RenderWindow& window);

    // check if a grid cell is occupied by a plant
    bool isCellOccupied(int col, int row) const;

    // check if any entity matching sideMask exists in a lane between [fromCol, toCol]
    bool hasEnemyInLane(int row, int fromCol, int toCol, uint32_t sideMask) const;

    // find a clickable entity at the given pixel position
    IClickable* findClickableAt(sf::Vector2f pixelPos) const;

    // find a plant at the given grid cell
    Plant* findPlantAt(int col, int row) const;

    // add a sun (or other non-factory entity) to pending
    void addEntity(std::unique_ptr<Entity> entity);

private:
    void handleCollisions();

    void onSpawnEntity(const GameEvent& event);
    void onApplyDamage(const GameEvent& event);
    void onApplyBoost(const GameEvent& event);
};
