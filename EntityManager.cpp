#include "EntityManager.h"
#include "IClickable.h"
#include "Character.h"
#include "Plant.h"
#include "Projectile.h"
#include "PeaProjectile.h"
#include "Peashooter.h"
#include "Repeater.h"
#include "Sunflower.h"
#include "CherryBomb.h"
#include "Wallnut.h"
#include "NormalZombie.h"
#include "Armor.h"
#include "Config.h"
#include "DatabaseHelper.h"
#include <iostream>
#include <algorithm>

EntityManager::EntityManager(EventManager& bus) : eventBus(bus) {
    spawnSubscriptionId = eventBus.subscribe(EventType::SpawnEntity, [this](const GameEvent& e) {
        onSpawnEntity(e);
    });

    applyDamageSubscriptionId = eventBus.subscribe(EventType::ApplyDamage, [this](const GameEvent& e) {
        onApplyDamage(e);
    });

    applyBoostSubscriptionId = eventBus.subscribe(EventType::ApplyBoost, [this](const GameEvent& e) {
        onApplyBoost(e);
    });
}

EntityManager::~EntityManager() {
    if (spawnSubscriptionId) {
        eventBus.unsubscribe(EventType::SpawnEntity, spawnSubscriptionId);
        spawnSubscriptionId = 0;
    }
    if (applyDamageSubscriptionId) {
        eventBus.unsubscribe(EventType::ApplyDamage, applyDamageSubscriptionId);
        applyDamageSubscriptionId = 0;
    }
    if (applyBoostSubscriptionId) {
        eventBus.unsubscribe(EventType::ApplyBoost, applyBoostSubscriptionId);
        applyBoostSubscriptionId = 0;
    }
}

void EntityManager::addEntity(std::unique_ptr<Entity> entity) {
    pendingEntities.push_back(std::move(entity));
}

void EntityManager::update(float dt) {
    if (!pendingEntities.empty()) {
        for (auto& e : pendingEntities) {
            entities.push_back(std::move(e));
        }
        pendingEntities.clear();
    }

    // rebuild spatial index BEFORE updates so plants can query the grid
    rebuildSpatialIndex();

    for (auto it = entities.begin(); it != entities.end(); ) {
        if (!(*it)->isActive()) {
            it = entities.erase(it);
        }
        else {
            (*it)->update(dt);
            ++it;
        }
    }

    // sync grid positions to pixel sprites before collision detection
    for (auto& e : entities) {
        if (e->isActive()) e->syncSprite();
    }

    handleCollisions();
}

void EntityManager::rebuildSpatialIndex() {
    // Clear all cells
    for (auto& row : gridCells) {
        for (auto& cell : row) {
            cell.clear();
        }
    }
    clickables.clear();

    for (auto& e : entities) {
        if (!e->isActive()) continue;

        // Collectible + Neutral entities (Sun) go into clickables, not grid
        if ((e->getCategory() & Category::Collectible) &&
            (e->getSide() & Side::Neutral)) {
            auto* clickable = dynamic_cast<IClickable*>(e.get());
            if (clickable) {
                clickables.push_back(clickable);
            }
            continue;
        }

        // Bin into grid cell
        sf::Vector2f pos = e->getGridPos();
        int col = static_cast<int>(pos.x);
        int row = static_cast<int>(pos.y);
        if (col >= 0 && col < Grid::COLS && row >= 0 && row < Grid::ROWS) {
            gridCells[row][col].push_back(e.get());
        }
    }
}

void EntityManager::draw(sf::RenderWindow& window) {
    // Pass 1: non-collectible sprites (plants, zombies, projectiles)
    for (const auto& entity : entities) {
        if (entity->isActive() && !(entity->getCategory() & Category::Collectible)) {
            entity->draw(window);
        }
    }
    // Pass 2: non-collectible HUD (health bars, armor bars) on top of all sprites
    for (const auto& entity : entities) {
        if (entity->isActive() && !(entity->getCategory() & Category::Collectible)) {
            entity->drawHUD(window);
        }
    }
    // Pass 3: collectible entities (Sun) on top of everything
    for (const auto& entity : entities) {
        if (entity->isActive() && (entity->getCategory() & Category::Collectible)) {
            entity->draw(window);
        }
    }
}

bool EntityManager::isCellOccupied(int col, int row) const {
    if (col < 0 || col >= Grid::COLS || row < 0 || row >= Grid::ROWS)
        return false;
    for (Entity* e : gridCells[row][col]) {
        if (e->isActive() && (e->getSide() & Side::Plant))
            return true;
    }
    return false;
}

bool EntityManager::hasEnemyInLane(int row, int fromCol, int toCol, uint32_t sideMask) const {
    if (row < 0 || row >= Grid::ROWS) return false;
    int cMin = std::max(0, fromCol);
    int cMax = std::min(Grid::COLS - 1, toCol);
    for (int c = cMin; c <= cMax; ++c) {
        for (Entity* e : gridCells[row][c]) {
            if (e->isActive() && (e->getSide() & sideMask))
                return true;
        }
    }
    return false;
}

IClickable* EntityManager::findClickableAt(sf::Vector2f pixelPos) const {
    for (IClickable* c : clickables) {
        if (c->containsPoint(pixelPos))
            return c;
    }
    return nullptr;
}

void EntityManager::handleCollisions() {
    // Use spatial grid: only check pairs within the same or adjacent cells
    for (int row = 0; row < Grid::ROWS; ++row) {
        for (int col = 0; col < Grid::COLS; ++col) {
            auto& cell = gridCells[row][col];

            // Pairs within this cell
            for (size_t i = 0; i < cell.size(); ++i) {
                for (size_t j = i + 1; j < cell.size(); ++j) {
                    Entity* a = cell[i];
                    Entity* b = cell[j];
                    if (!a->isActive() || !b->isActive()) continue;
                    if ((a->getCategory() & Category::Collectible) ||
                        (b->getCategory() & Category::Collectible)) continue;
                    if (a->getBounds().findIntersection(b->getBounds()).has_value()) {
                        a->onCollision(b);
                        b->onCollision(a);
                    }
                }
            }

            // Cross-cell pairs: check right neighbor only (avids double-checking)
            if (col + 1 < Grid::COLS) {
                auto& right = gridCells[row][col + 1];
                for (Entity* a : cell) {
                    for (Entity* b : right) {
                        if (!a->isActive() || !b->isActive()) continue;
                        if ((a->getCategory() & Category::Collectible) ||
                            (b->getCategory() & Category::Collectible)) continue;
                        if (a->getLane() != b->getLane()) continue;
                        if (a->getBounds().findIntersection(b->getBounds()).has_value()) {
                            a->onCollision(b);
                            b->onCollision(a);
                        }
                    }
                }
            }
        }
    }
}

void EntityManager::onSpawnEntity(const GameEvent& event) {
    auto* pdata = std::get_if<SpawnEventData>(&event.data);
    if (!pdata) return;
    const auto& data = *pdata;

        std::unique_ptr<Entity> newEntity = nullptr;

        if (data.entityType == "Peashooter") {
            newEntity = std::make_unique<Peashooter>(data.lane, eventBus, *this);
        }
        else if (data.entityType == "Sunflower") {
            newEntity = std::make_unique<Sunflower>(data.lane, eventBus);
        }
        else if (data.entityType == "Repeater") {
            newEntity = std::make_unique<Repeater>(data.lane, eventBus, *this);
        }
        else if (data.entityType == "CherryBomb") {
            newEntity = std::make_unique<CherryBomb>(data.lane, eventBus);
        }
        else if (data.entityType == "Wallnut") {
            newEntity = std::make_unique<Wallnut>(data.lane, eventBus);
		}
        else if (data.entityType == "NormalZombie") {
            newEntity = std::make_unique<NormalZombie>(data.lane, eventBus);
        }
        else if (data.entityType == "ConeheadZombie") {
            auto zombie = std::make_unique<NormalZombie>(data.lane, eventBus);

            // 【新增】：动态计算路障护甲的血量 = 路障总血量 - 普通僵尸血量
            const auto& baseStats = DataManager::getInstance().getZombieStats("NormalZombie");
            const auto& coneStats = DataManager::getInstance().getZombieStats("ConeheadZombie");
            float armorHp = static_cast<float>(coneStats.hp - baseStats.hp);

            // zombie->equipArmor(std::make_unique<Armor>("Cone", "ConeArmor", 370.f));
            // 【修改这行】把 370.f 换成 armorHp
            zombie->equipArmor(std::make_unique<Armor>("Cone", "ConeArmor", armorHp));
            newEntity = std::move(zombie);
        }
        else if (data.entityType == "BucketheadZombie") {
            auto zombie = std::make_unique<NormalZombie>(data.lane, eventBus);

            // 【新增】：动态计算铁桶护甲的血量 = 铁桶总血量 - 普通僵尸血量
            const auto& baseStats = DataManager::getInstance().getZombieStats("NormalZombie");
            const auto& bucketStats = DataManager::getInstance().getZombieStats("BucketheadZombie");
            float armorHp = static_cast<float>(bucketStats.hp - baseStats.hp);

            // zombie->equipArmor(std::make_unique<Armor>("Bucket", "BucketArmor", 1100.f));
            // 【修改这行】把 1100.f 换成 armorHp
            zombie->equipArmor(std::make_unique<Armor>("Bucket", "BucketArmor", armorHp));
            newEntity = std::move(zombie);
        }
        else if (data.entityType == "PeaProjectile") {
            newEntity = std::make_unique<PeaProjectile>(data.position, data.lane, data.side, eventBus);
        }

        if (newEntity) {
            newEntity->setGridPos(data.position);
            newEntity->syncSprite();
            pendingEntities.push_back(std::move(newEntity));
        }
}

void EntityManager::onApplyDamage(const GameEvent& event) {
    if (auto* dptr = std::get_if<DirectDamageData>(&event.data)) {
        const auto& data = *dptr;
        auto* character = dynamic_cast<Character*>(data.target);
        if (character) {
            character->takeDamage(data.damage);
        }
    }
    else if (auto* dptr = std::get_if<DamageEventData>(&event.data)) {
        const auto& data = *dptr;

        // Convert pixel-space targetArea to grid cell range
        sf::Vector2f areaTopLeft = data.targetArea.position;
        sf::Vector2f areaSize = data.targetArea.size;
        sf::Vector2f gridMin = Grid::pixelToGrid(areaTopLeft);
        sf::Vector2f gridMax = Grid::pixelToGrid(
            sf::Vector2f(areaTopLeft.x + areaSize.x, areaTopLeft.y + areaSize.y));

        int colMin = std::max(0, static_cast<int>(gridMin.x));
        int colMax = std::min(Grid::COLS - 1, static_cast<int>(gridMax.x));
        int rowMin = std::max(0, static_cast<int>(gridMin.y));
        int rowMax = std::min(Grid::ROWS - 1, static_cast<int>(gridMax.y));

        // Only visit entities in affected cells
        for (int r = rowMin; r <= rowMax; ++r) {
            for (int c = colMin; c <= colMax; ++c) {
                for (Entity* ent : gridCells[r][c]) {
                    if (!ent->isActive()) continue;
                    if ((ent->getSide() & data.targetMask) == 0) continue;

                    sf::FloatRect entBounds = ent->getBounds();
                    if (data.targetArea.findIntersection(entBounds).has_value()) {
                        auto* character = dynamic_cast<Character*>(ent);
                        if (character) {
                            character->takeDamage(data.damage);
                        }
                    }
                }
            }
        }
    }
}

Plant* EntityManager::findPlantAt(int col, int row) const {
    if (col < 0 || col >= Grid::COLS || row < 0 || row >= Grid::ROWS)
        return nullptr;
    for (Entity* e : gridCells[row][col]) {
        if (e->isActive() && (e->getSide() & Side::Plant)) {
            auto* plant = dynamic_cast<Plant*>(e);
            if (plant) return plant;
        }
    }
    return nullptr;
}

void EntityManager::onApplyBoost(const GameEvent& event) {
    auto* bptr = std::get_if<BoostEventData>(&event.data);
    if (!bptr) return;
    Plant* plant = findPlantAt(bptr->col, bptr->row);
    if (plant && plant->canBoost() && !plant->isBoosted()) {
        plant->onBoost();
    }
}
