#pragma once
/**
 * @defgroup hotkey_manager Hotkey Manager
 * @brief Manages global hotkey registration and handling
 * 
 * This module handles the registration of global system hotkeys,
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
#include "WindowManager.hpp"

/** @brief Data structure for hotkey registration *//** @brief Data structure for hotkey registration */
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
 * 
 * The HotkeyManager runs a separate thread to process Windows messages
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
     * 
     * This function:
     * 1. Processes hotkey registration requests from the queue
     * 2. Handles WM_HOTKEY messages from Windows
     * 3. Executes appropriate Lua callbacks
     * 4. Supports hotkey clearing on script reload
     */
    static void MessageLoop() {
        MSG msg = { 0 };
        PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

        while (true) {
            if (shouldClear) {
                for (const auto& [id, _] : hotkeys) {
                    UnregisterHotKey(NULL, id);
                }
                hotkeys.clear();
                nextId = 1;
                shouldClear = false;
                std::cout << "[System] Hotkeys cleared in MessageLoop." << std::endl;
            }
                     {
                std::lock_guard<std::mutex> lock(queueMutex);
                for (auto& req : registrationQueue) {
                    int id = nextId++;
                    if (RegisterHotKey(NULL, id, req.mods | MOD_NOREPEAT, req.vk)) {
                        hotkeys[id] = { req.cb, req.windowTitle };
                        std::cout << "[System] Registered ID: " << id << " | Window: " 
                                  << (req.windowTitle.empty() ? "Global" : req.windowTitle) << std::endl;
                    } else {
                        std::cerr << "[Error] Failed to register hotkey. Error code: " << GetLastError() << std::endl;
                    }
                }
                registrationQueue.clear();
            }

            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_HOTKEY) {
                    int id = (int)msg.wParam;
                    if (hotkeys.count(id)) { 
                        auto& data = hotkeys[id];
                        if (data.targetWindow.empty() ) {
                            data.callback();
                        } else {
                            std::string currentTitle = WindowManager::GetActiveWindowTitle();
                            if (currentTitle.find(data.targetWindow) != std::string::npos) {
                                data.callback();
                            }
                        }
                    }
                }
                if (msg.message == WM_QUIT) return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    /**
     * @brief Registers a hotkey from Lua
     * @param mods Modifier keys (MOD.ALT, MOD.CTRL, etc.)
     * @param vk Virtual key code
     * @param cb Lua callback function
     * @param windowTitle Optional window title for context-sensitive hotkeys
     * 
     * This function is thread-safe and adds hotkey requests to a queue
     * for processing in the message loop thread.
     */
    static void Add(int mods, int vk, sol::function cb, std::string windowTitle = "") {
        std::lock_guard<std::mutex> lock(queueMutex);
        registrationQueue.push_back({ mods, vk, cb, windowTitle });
    }

    /**
     * @brief Clears all registered hotkeys
     * @details Used during script reload to clean up old hotkeys
     */
    static void Clear() {
        shouldClear = true;
        
        while(shouldClear) { std::this_thread::yield(); }
    }
};

/** @} */ // end of hotkey_manager group