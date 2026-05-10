#include "EventManager.h"
#include <algorithm>
#include <iostream>

size_t EventManager::subscribe(EventType type, Handler handler) {
    size_t id = nextId++;
    subscribers[type].emplace_back(id, std::move(handler));
    return id;
}

void EventManager::unsubscribe(EventType type, size_t subscriptionId) {
    auto it = subscribers.find(type);
    if (it == subscribers.end()) return;
    auto& vec = it->second;
    vec.erase(std::remove_if(vec.begin(), vec.end(),
        [subscriptionId](const auto& p) { return p.first == subscriptionId; }), vec.end());
    if (vec.empty()) subscribers.erase(it);
}

void EventManager::publish(const GameEvent& event) {
    auto it = subscribers.find(event.type);
    if (it == subscribers.end()) return;

    // copy handlers so modifications to subscriber list during publish won't affect iteration
    auto handlers = it->second;

    for (auto& entry : handlers) {
        try {
            entry.second(event);
        } catch (const std::exception& ex) {
            std::cerr << "[EventManager] Handler threw exception: " << ex.what() << std::endl;
        } catch (...) {
            std::cerr << "[EventManager] Handler threw unknown exception\n";
        }
    }
}
