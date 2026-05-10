#pragma once
#include <cstdint>

namespace Side {
    enum Type : uint32_t {
        None    = 0,
        Plant   = 1 << 0, // 1
        Zombie  = 1 << 1, // 2
        Neutral = 1 << 2, // 4
        All     = 0xFFFFFFFF
    };
}

namespace Category {
    enum Type : uint32_t {
        Character   = 1 << 0,
        Projectile  = 1 << 1,
        Collectible = 1 << 2,
        Obstacle    = 1 << 3,
        Effect      = 1 << 4
    };
}

enum class EventType {
    SpawnEntity,
    EntityDead,
    ApplyDamage,
    CollectResource,
    ProduceSun,
    ApplyBoost
};
