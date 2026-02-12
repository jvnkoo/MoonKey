#include "TimerManager.hpp"

void TimerManager::Add(int ms, sol::function callback, std::string targetWindow) {
    long long now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
    timers.push_back({ callback, (long long)ms, now, targetWindow });
}

void TimerManager::Update() {
    long long now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();

    for (auto& timer : timers) {
        if (now - timer.lastTick >= timer.interval) {
            if (timer.targetWindow.empty() || WindowManager::GetActiveWindowTitle() == timer.targetWindow) {
                timer.callback();
            }
            timer.lastTick = now;
        }
    }
}

void TimerManager::Clear() {
    timers.clear();
}