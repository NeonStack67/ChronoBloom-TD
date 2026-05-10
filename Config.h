#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>

namespace Config {
    constexpr unsigned int WINDOW_WIDTH = 800;
    constexpr unsigned int WINDOW_HEIGHT = 600;
    inline const std::string WINDOW_TITLE = "PVZ - QianHeShiKong";
    constexpr unsigned int FPS_LIMIT = 60;

    constexpr bool DEBUG_SHOW_HEALTH = true;
}

namespace CardBarConfig {
    constexpr float BAR_X = 10.f;
    constexpr float BAR_Y = 5.f;
    constexpr float BAR_HEIGHT = 88.f;
    constexpr float CARD_WIDTH = 56.f;
    constexpr float CARD_HEIGHT = 72.f;
    constexpr float CARD_PADDING = 4.f;
    constexpr float SUN_COUNTER_WIDTH = 64.f;
}

namespace Grid {
    constexpr float CELL_WIDTH  = 63.f;
    constexpr float CELL_HEIGHT = 77.f;
    constexpr int ROWS = 5;
    constexpr int COLS = 9;
    constexpr float ORIGIN_X = 90.f;
    constexpr float ORIGIN_Y = 156.f;

    constexpr float GRID_PIXEL_WIDTH  = CELL_WIDTH  * COLS;  // 657
    constexpr float GRID_PIXEL_HEIGHT = CELL_HEIGHT * ROWS;  // 400

    // grid coord -> pixel coord
    inline sf::Vector2f gridToPixel(sf::Vector2f gridPos) {
        return { ORIGIN_X + gridPos.x * CELL_WIDTH,
                 ORIGIN_Y + gridPos.y * CELL_HEIGHT };
    }

    // pixel coord -> grid coord
    inline sf::Vector2f pixelToGrid(sf::Vector2f pixel) {
        return { (pixel.x - ORIGIN_X) / CELL_WIDTH,
                 (pixel.y - ORIGIN_Y) / CELL_HEIGHT };
    }

    // cell center in grid coords (col, row order, matching x/y)
    inline sf::Vector2f cellCenter(int col, int row) {
        return { col + 0.5f, row + 0.5f };
    }

    // minimum cell dimension (for square-ish sprite scaling)
    constexpr float CELL_MIN = CELL_WIDTH < CELL_HEIGHT ? CELL_WIDTH : CELL_HEIGHT;
}

namespace SunConfig {
    constexpr int SKY_SUN_VALUE = 25;
    constexpr int PLANT_SUN_VALUE = 25;
    constexpr float SKY_SPAWN_INTERVAL = 10.f;     // seconds between sky sun spawns
    constexpr float SKY_FALL_SPEED = 60.f;          // pixels/s falling speed
    constexpr float FLY_SPEED = 400.f;              // pixels/s fly-to-counter speed
    constexpr float IDLE_LIFETIME = 8.f;            // seconds before uncollected sun vanishes
    constexpr float SUN_SPRITE_SIZE = 40.f;         // pixel size of sun sprite
    constexpr float SUNFLOWER_PRODUCE_INTERVAL = 24.f; // seconds between sunflower sun production
}

namespace ChlorophyllConfig {
    constexpr float BUTTON_WIDTH = 64.f;
    constexpr float BUTTON_HEIGHT = 40.f;
    constexpr float BUTTON_Y = 5.f;
    constexpr float BUTTON_MARGIN = 10.f;
    constexpr int BOOST_COST = 1;
}
