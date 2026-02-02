#pragma once
#include <vector>
#include <functional>
#include <map>
#include <string>

class EventDispatcher {
public:
    using Callback = std::function<void()>;

    void subscribe(std::string eventType, Callback cb) {
        listeners[eventType].push_back(cb);
    }

    void dispatch(std::string eventType) {
        for (auto& cb : listeners[eventType]) {
            cb();
        }
    }
private:
    std::unordered_map<std::string, std::vector<Callback>> listeners;
};