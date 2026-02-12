#pragma once
/**
 * @brief Event dispatcher for inter-component communication
 * @ingroup internal
 * 
 * Implements a simple publisher-subscriber pattern for loose coupling
 * between system components. Used primarily for hot-reload notifications.
 */

#include <vector>
#include <functional>
#include <map>
#include <string>
#include <unordered_map>

/**
 * @class EventDispatcher
 * @brief Manages event subscriptions and dispatch
 * 
 * Allows components to subscribe to events by name and receive callbacks
 * when those events are dispatched. Thread-safe for single producer,
 * single consumer scenarios.
 */
class EventDispatcher {
public:
    using Callback = std::function<void()>; ///< Type for event callbacks

    /**
     * @brief Subscribe to an event
     * @param eventType Event name to subscribe to
     * @param cb Callback function to execute when event is dispatched
     * 
     * Multiple callbacks can be registered for the same event type.
     * Callbacks are executed in registration order.
     */
    void subscribe(std::string eventType, Callback cb) {
        listeners[eventType].push_back(cb);
    }

    /**
     * @brief Dispatch an event to all subscribers
     * @param eventType Event name to dispatch
     * 
     * Synchronously executes all callbacks registered for the event type.
     * Exceptions in callbacks are not caught and will propagate.
     */
    void dispatch(std::string eventType) {
        auto it = listeners.find(eventType);
        if (it != listeners.end()) {
            for (auto& cb : it->second) {
                cb();
            }
        }
    }
    
private:
    std::unordered_map<std::string, std::vector<Callback>> listeners; ///< Event subscriptions
};