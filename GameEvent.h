#pragma once
#include <variant>
#include <SFML/Graphics.hpp>
#include <string>
#include "Enums.h"

class Entity;

// --- Event payloads ---

struct SpawnEventData {
    std::string entityType;
    sf::Vector2f position;
    int lane;
    uint32_t side;
};

struct DirectDamageData {
    Entity* target;
    float damage;
};

struct DamageEventData {
    sf::FloatRect targetArea;
    float damage;
    uint32_t targetMask;
};

struct EntityDeadData {
    Entity* entity;
    sf::Vector2f position;
};

struct ProduceSunData {
    sf::Vector2f pixelPos;
    int value;
};

struct CollectResourceData {
    int value;
};

struct BoostEventData {
    int col;
    int row;
};

// Type-safe event data: each EventType maps to exactly one payload type.
// This replaces std::any with std::variant, giving compile-time type safety.
using EventData = std::variant<
    std::monostate,       // no payload
    SpawnEventData,
    DirectDamageData,
    DamageEventData,
    EntityDeadData,
    ProduceSunData,
    CollectResourceData,
    BoostEventData
>;

struct GameEvent {
    EventType type;
    EventData data;
    uint32_t senderId = 0;

    GameEvent(EventType t, EventData d = {}, uint32_t sender = 0)
        : type(t), data(std::move(d)), senderId(sender) {}
};
