//cat *.h *.cpp > pvz_all_code.txt
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Config.h"
#include "ResourceManager.h"
#include "SpineManager.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "GameEvent.h"
#include "CardBar.h"
#include "Card.h"
#include "SunSystem.h"
#include "InputHandler.h"
#include "ChlorophyllButton.h"
#include "DatabaseHelper.h"

int main() {
    // 1. Window
    sf::RenderWindow window(sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }), Config::WINDOW_TITLE);
    window.setFramerateLimit(Config::FPS_LIMIT);

    // 2. SFML 静态纹理资源（仅保留不使用 Spine 的实体）
    auto& resMgr = ResourceManager::getInstance();
    try {
        // 护甲（仍使用 sf::Sprite 叠加在骨骼上）
        resMgr.loadTexture("ConeArmor",    "Assets/cone_armor.png");
        resMgr.loadTexture("BucketArmor",  "Assets/bucket_armor.png");
        // 投射物
        resMgr.loadTexture("PeaProjectile","Assets/pea.png");
        // 太阳
        resMgr.loadTexture("Sun",          "Assets/sun.png");
        // UI
        resMgr.loadTexture("CardBg",       "Assets/card_bg.png");
        resMgr.loadTexture("Background",   "Assets/background.png");
        // 卡牌缩略图（CardBar 显示用，仍用静态图）
        resMgr.loadTexture("Peashooter",   "Assets/peashooter.png");
        resMgr.loadTexture("Sunflower",    "Assets/sunflower.png");
        resMgr.loadTexture("Repeater",     "Assets/repeater.png");
        resMgr.loadTexture("CherryBomb",   "Assets/cherry_bomb.png");
        resMgr.loadTexture("Wallnut",      "Assets/wallnut.png");
        resMgr.loadFont("default",         "Assets/ARLRDBD.TTF");
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal Error (textures): " << e.what() << std::endl;
        return -1;
    }

    // 3. Spine 骨骼动画资源（植物 + 僵尸）
    // 注意：当 partner 提供 .skel/.atlas 文件后，放入对应目录即可生效
    // 文件路径约定：Assets/spine/<EntityName>/<EntityName>.atlas 和 .skel
    {
        auto& spineMgr = SpineManager::getInstance();
        bool spineOk = true;

        // 植物
        spineOk &= spineMgr.loadSkeleton("Peashooter",
            "Assets/spine/Peashooter/Peashooter.atlas",
            "Assets/spine/Peashooter/Peashooter.skel");
        spineOk &= spineMgr.loadSkeleton("Sunflower",
            "Assets/spine/Sunflower/Sunflower.atlas",
            "Assets/spine/Sunflower/Sunflower.skel");
        spineOk &= spineMgr.loadSkeleton("Repeater",
            "Assets/spine/Repeater/Repeater.atlas",
            "Assets/spine/Repeater/Repeater.skel");
        spineOk &= spineMgr.loadSkeleton("CherryBomb",
            "Assets/spine/CherryBomb/CherryBomb.atlas",
            "Assets/spine/CherryBomb/CherryBomb.skel");
        spineOk &= spineMgr.loadSkeleton("Wallnut",
            "Assets/spine/Wallnut/Wallnut.atlas",
            "Assets/spine/Wallnut/Wallnut.skel");

        // 僵尸
        spineOk &= spineMgr.loadSkeleton("NormalZombie",
            "Assets/spine/NormalZombie/NormalZombie.atlas",
            "Assets/spine/NormalZombie/NormalZombie.skel");
        spineOk &= spineMgr.loadSkeleton("ConeheadZombie",
            "Assets/spine/ConeheadZombie/ConeheadZombie.atlas",
            "Assets/spine/ConeheadZombie/ConeheadZombie.skel");
        spineOk &= spineMgr.loadSkeleton("BucketheadZombie",
            "Assets/spine/BucketheadZombie/BucketheadZombie.atlas",
            "Assets/spine/BucketheadZombie/BucketheadZombie.skel");

        if (!spineOk) {
            std::cerr << "[Main] Warning: Some Spine assets failed to load.\n"
                      << "  Entities without Spine data will not render until assets are provided.\n";
            // 不 return -1，允许游戏在无 Spine 资产时继续运行（实体不可见但逻辑正常）
        }
    }

    // 4. Core systems
    EventManager eventBus;
    EntityManager entityManager(eventBus);

    // 【修改点 1】：在这里，在游戏核心系统初始化后，一次性加载所有数据库数据！
    DataManager::getInstance().loadAllData();

    // 4. Card bar
    CardBar cardBar;
    cardBar.setSunCount(999999);

    // --- 数据库接入测试 ---
    // PlantStats peaStats = getPlantStatsFromDB("Peashooter");
    // PlantStats sunStats = getPlantStatsFromDB("Sunflower"); // 新增：读取向日葵
    // ----------------------------------------

    const auto& peaStats = DataManager::getInstance().getStats("Peashooter");
    const auto& sunStats = DataManager::getInstance().getStats("Sunflower");
    const auto& nutStats = DataManager::getInstance().getStats("Wallnut");
    const auto& repStats = DataManager::getInstance().getStats("Repeater");
    const auto& cherryStats = DataManager::getInstance().getStats("CherryBomb");
    // cardBar.addCard(std::make_unique<Card>("Sunflower", "Sunflower", 50, "Sunflower", "CardBg", 7.5f));
    cardBar.addCard(std::make_unique<Card>("Sunflower", "Sunflower", sunStats.cost, "Sunflower", "CardBg", sunStats.cooldown));
    // 这里的 cost 和 cooldown 换成了从数据库读取的变量
    cardBar.addCard(std::make_unique<Card>("Peashooter", "Peashooter", peaStats.cost, "Peashooter", "CardBg", peaStats.cooldown));
    // cardBar.addCard(std::make_unique<Card>("Peashooter", "Peashooter", 100, "Peashooter", "CardBg", 7.5f));
    // cardBar.addCard(std::make_unique<Card>("Repeater", "Repeater", 150, "Repeater", "CardBg", 7.5f));
    cardBar.addCard(std::make_unique<Card>("Repeater", "Repeater", repStats.cost, "Repeater", "CardBg", repStats.cooldown));
    // cardBar.addCard(std::make_unique<Card>("CherryBomb", "CherryBomb", 150, "CherryBomb", "CardBg", 30.f));
    cardBar.addCard(std::make_unique<Card>("CherryBomb", "CherryBomb", cherryStats.cost, "CherryBomb", "CardBg", cherryStats.cooldown));
    cardBar.addCard(std::make_unique<Card>("Wallnut", "Wallnut", nutStats.cost, "Wallnut", "CardBg", nutStats.cooldown));
    // cardBar.addCard(std::make_unique<Card>("Wallnut", "Wallnut", 50, "Wallnut", "CardBg", 7.5f));

    // 5. Chlorophyll button (positioned after card bar)
    float cardBarWidth = CardBarConfig::SUN_COUNTER_WIDTH
        + cardBar.getCardCount() * (CardBarConfig::CARD_WIDTH + CardBarConfig::CARD_PADDING)
        + CardBarConfig::CARD_PADDING;
    float chloroX = CardBarConfig::BAR_X + cardBarWidth + ChlorophyllConfig::BUTTON_MARGIN;
    ChlorophyllButton chloroButton(chloroX);
    chloroButton.setChlorophyllCount(10);

    // 6. Systems
    SunSystem sunSystem(eventBus, entityManager, cardBar);
    InputHandler input(eventBus, entityManager, cardBar, chloroButton);

    // 6. Background sprite
    sf::Sprite bgSprite(resMgr.getTexture("Background"));
    {
        auto bgSize = bgSprite.getTexture().getSize();
        bgSprite.setScale(sf::Vector2f(
            static_cast<float>(Config::WINDOW_WIDTH) / bgSize.x,
            static_cast<float>(Config::WINDOW_HEIGHT) / bgSize.y
        ));
    }

    // Pre-build grid lines (debug overlay)
    std::vector<sf::Vertex> gridLines;
    sf::Color lineColor(30, 70, 30, 80);

    for (int c = 0; c <= Grid::COLS; ++c) {
        float x = Grid::ORIGIN_X + c * Grid::CELL_WIDTH;
        float y0 = Grid::ORIGIN_Y;
        float y1 = Grid::ORIGIN_Y + Grid::GRID_PIXEL_HEIGHT;
        gridLines.push_back({sf::Vector2f(x, y0), lineColor});
        gridLines.push_back({sf::Vector2f(x, y1), lineColor});
    }
    for (int r = 0; r <= Grid::ROWS; ++r) {
        float y = Grid::ORIGIN_Y + r * Grid::CELL_HEIGHT;
        float x0 = Grid::ORIGIN_X;
        float x1 = Grid::ORIGIN_X + Grid::GRID_PIXEL_WIDTH;
        gridLines.push_back({sf::Vector2f(x0, y), lineColor});
        gridLines.push_back({sf::Vector2f(x1, y), lineColor});
    }

    srand(static_cast<unsigned int>(time(0)));

    // Fixed game view: always map to 800x600 logical coords regardless of window size
    sf::View gameView(sf::FloatRect({0.f, 0.f},
        {static_cast<float>(Config::WINDOW_WIDTH), static_cast<float>(Config::WINDOW_HEIGHT)}));
    window.setView(gameView);

    // 7. Game loop
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        // --- Event polling ---
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (event->is<sf::Event::Resized>()) {
                window.setView(gameView);
            }
            else if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mousePos = window.mapPixelToCoords(
                    sf::Vector2i(mouseBtn->position.x, mouseBtn->position.y));
                input.handleClick(mousePos, mouseBtn->button);
            }
        }

        // --- Update ---
        sunSystem.update(dt);
        cardBar.update(dt);
        entityManager.update(dt);

        // TODO: extract to WaveManager
        if (rand() % 300 == 5) {
            int lane = rand() % 5;
            int roll = rand() % 100;
            std::string zombieType;
            if (roll < 60) zombieType = "NormalZombie";
            else if (roll < 85) zombieType = "ConeheadZombie";
            else zombieType = "BucketheadZombie";

            SpawnEventData zData = { zombieType,
                {static_cast<float>(Grid::COLS) + 1.f, lane + 0.5f},
                lane, Side::Zombie };
            eventBus.publish(GameEvent(EventType::SpawnEntity, zData));
        }

        // --- Render ---
        window.clear();
        window.draw(bgSprite);
        window.draw(gridLines.data(), gridLines.size(), sf::PrimitiveType::Lines);
        input.drawHoverHighlight(window, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        entityManager.draw(window);
        cardBar.draw(window);
        chloroButton.draw(window);
        window.display();
    }

    return 0;
}
