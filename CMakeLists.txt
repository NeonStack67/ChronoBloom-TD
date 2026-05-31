cmake_minimum_required(VERSION 3.15)
project(ChronoBloom_TD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# spine-cpp
add_subdirectory(third_party/spine-runtimes/spine-cpp)

# SQLite3 amalgamation
add_library(sqlite3_embed STATIC third_party/sqlite3/sqlite3.c)
target_include_directories(sqlite3_embed PUBLIC third_party/sqlite3)
if(MSVC)
    target_compile_options(sqlite3_embed PRIVATE /W0)
endif()

# Explicit source list (avoids GLOB anti-pattern: new files require cmake reconfigure)
set(SOURCES
    Main.cpp
    Entity.cpp
    Character.cpp
    Plant.cpp
    Zombie.cpp
    NormalZombie.cpp
    Peashooter.cpp
    Sunflower.cpp
    Repeater.cpp
    CherryBomb.cpp
    Wallnut.cpp
    Projectile.cpp
    PeaProjectile.cpp
    Sun.cpp
    SunSystem.cpp
    CardBar.cpp
    EntityManager.cpp
    InputHandler.cpp
    SpineManager.cpp
    SpineComponent.cpp
    ResourceManager.cpp
    EventManager.cpp
    Card.cpp
    Armor.cpp
    ChlorophyllButton.cpp
)
set(SPINE_SFML_SRC third_party/spine-runtimes/spine-sfml/src/spine-sfml.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${SPINE_SFML_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE
    third_party/spine-runtimes/spine-cpp/include
    third_party/spine-runtimes/spine-sfml/src
    third_party/sqlite3
)

find_package(SFML COMPONENTS Graphics Window System REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics SFML::Window SFML::System
    sqlite3_embed
    spine-cpp
)

file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
