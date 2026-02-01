#pragma once
#include <thread>
#include <windows.h>
#include <sol/sol.hpp>
#include <map>
#include <iostream>
#include <vector>
#include <mutex>
#include "WindowManager.hpp"

struct HotKeyData {
    sol::function callback;
    std::string targetWindow;
};

struct HotkeyRequest {
    int mods;
    int vk;
    sol::function cb;
    std::string windowTitle;
};

struct HotkeyManager {
    // inline?
    static inline std::map<int, HotKeyData> hotkeys;
    static inline int nextId = 1;
    static inline std::vector<HotkeyRequest> registrationQueue;
    static inline std::mutex queueMutex;

    // Windows Message Loop
    static void MessageLoop() {
        MSG msg = { 0 };
        PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

        while (true) {
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

    // Bridge function for Lua
    static void Add(int mods, int vk, sol::function cb, std::string windowTitle = "") {
        std::lock_guard<std::mutex> lock(queueMutex);
        registrationQueue.push_back({ mods, vk, cb, windowTitle });
    }
};