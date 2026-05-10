#pragma once
#include <functional>
#include <vector>
#include <map>
#include <utility>
#include <cstddef>
#include "GameEvent.h"

class EventManager {
public:
    using Handler = std::function<void(const GameEvent&)>;

    EventManager() = default;
    ~EventManager() = default;

    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    // Subscribe returns a subscription id that can be used to unsubscribe later
    size_t subscribe(EventType type, Handler handler);
    void unsubscribe(EventType type, size_t subscriptionId);
    void publish(const GameEvent& event);

private:
    // store (id, handler) pairs so subscribers can be removed safely
    std::map<EventType, std::vector<std::pair<size_t, Handler>>> subscribers;
    size_t nextId{1};
};