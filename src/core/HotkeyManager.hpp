#pragma once
#include <functional>
#include <thread>
#include <windows.h>
#include <sol/sol.hpp>
#include <map>
#include <iostream>
#include <vector>
#include <mutex>
#include <atomic>
#include "../api/WindowManager.hpp"
#include "../api/TimerManager.hpp"

// Data structure for hotkey registration
struct HotKeyData {
    sol::function callback;       // Lua function to call when hotkey is pressed
    std::string targetWindow;     // Optional window title for context-sensitive hotkeys
};

// Hotkey registration request
struct HotkeyRequest {
    int mods;                     // Modifier keys (ALT, CTRL, etc.)
    int vk;                       // Virtual key code
    sol::function cb;             // Callback function
    std::string windowTitle;      // Target window title (empty for global)
};

// Manages global hotkey registration and Windows message processing
// The HotkeyManager runs a separate thread to process Windows messages
// and execute hotkey callbacks. It supports both global hotkeys and
// context-sensitive hotkeys tied to specific windows
struct HotkeyManager {
    static inline std::map<int, HotKeyData> hotkeys;            // Registered hotkeys by ID
    static inline int nextId = 1;                               // Next available hotkey ID
    static inline std::vector<HotkeyRequest> registrationQueue; // Queue for thread-safe registration
    static inline std::mutex queueMutex;                        // Mutex for queue synchronization
    static inline std::atomic<bool> shouldClear = false;        // Flag to clear all hotkeys

    // Windows message processing loop
    // Runs in a separate thread to handle WM_HOTKEY messages
    static void MessageLoop();

    // Registers a hotkey from Lua
    // mods: Modifier keys (MOD.ALT, MOD.CTRL, etc.)
    // vk: Virtual key code
    // cb: Lua callback function
    // windowTitle: Optional window title for context-sensitive hotkeys
    static void Add(int mods, int vk, sol::function cb, std::string windowTitle = "");

    // Clears all registered hotkeys
    // Used during script reload to clean up old hotkeys
    static void Clear();
};