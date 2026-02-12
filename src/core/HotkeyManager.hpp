#pragma once
/**
 * @defgroup hotkey_manager Hotkey Manager
 * @brief Manages global hotkey registration and handling
 * * This module handles the registration of global system hotkeys,
 * processes Windows messages for hotkey events, and executes
 * associated Lua callbacks.
 * @{
 */
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

/** @brief Data structure for hotkey registration */
struct HotKeyData {
    sol::function callback; ///< Lua function to call when hotkey is pressed
    std::string targetWindow; ///< Optional window title for context-sensitive hotkeys
};

/** @brief Hotkey registration request */
struct HotkeyRequest {
    int mods;           ///< Modifier keys (ALT, CTRL, etc.)
    int vk;             ///< Virtual key code
    sol::function cb;   ///< Callback function
    std::string windowTitle; ///< Target window title (empty for global)
};

/**
 * @class HotkeyManager
 * @brief Manages global hotkey registration and Windows message processing
 * * The HotkeyManager runs a separate thread to process Windows messages
 * and execute hotkey callbacks. It supports both global hotkeys and
 * context-sensitive hotkeys tied to specific windows.
 */
struct HotkeyManager {
    static inline std::map<int, HotKeyData> hotkeys; ///< Registered hotkeys by ID
    static inline int nextId = 1; ///< Next available hotkey ID
    static inline std::vector<HotkeyRequest> registrationQueue; ///< Queue for thread-safe registration
    static inline std::mutex queueMutex; ///< Mutex for queue synchronization
    static inline std::atomic<bool> shouldClear = false; ///< Flag to clear all hotkeys

    /**
     * @brief Windows message processing loop
     * @details Runs in a separate thread to handle WM_HOTKEY messages
     */
    static void MessageLoop();

    /**
     * @brief Registers a hotkey from Lua
     * @param mods Modifier keys (MOD.ALT, MOD.CTRL, etc.)
     * @param vk Virtual key code
     * @param cb Lua callback function
     * @param windowTitle Optional window title for context-sensitive hotkeys
     */
    static void Add(int mods, int vk, sol::function cb, std::string windowTitle = "");

    /**
     * @brief Clears all registered hotkeys
     * @details Used during script reload to clean up old hotkeys
     */
    static void Clear();
};
/** @} */