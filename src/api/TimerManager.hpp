#pragma once
#include <sol/sol.hpp>
#include <windows.h>
#include <string>
#include <chrono>
#include "WindowManager.hpp"

// Timer management for scheduled callbacks
// Provides functionality to set up repeating timers that execute Lua callbacks
// Timers can be global or tied to specific window titles for context-sensitive execution
struct TimerData {
    sol::function callback;
    long long interval;
    long long lastTick;
    std::string targetWindow;
};

class TimerManager {
public:
    // Store active timers
    static inline std::vector<TimerData> timers;

    // Add a new timer
    // ms: Interval in milliseconds between callback executions
    // callback: Lua function to call when timer ticks
    // targetWindow: Optional window title for context-sensitive timers
    // If targetWindow is specified, the callback will only execute when that window is active
    // If empty, the timer will execute regardless of active window
    static void Add(int ms, sol::function callback, std::string targetWindow = "");

    // Update timers and execute callbacks as needed
    // This should be called regularly (e.g., in the main loop) to check timers
    // It checks if the interval has passed for each timer and executes the callback if so
    // For context-sensitive timers, it also checks if the target window is active before executing
    static void Update();

    // Clear all timers
    // Removes all active timers from the system
    // Use with caution as this will stop all scheduled callbacks
    static void Clear();
};