#pragma once
#include <windows.h>
#include <sol/sol.hpp>
#include <map>
#include <iostream>

struct HotkeyManager {
    static inline std::map<int, sol::function> callbacks;
    static inline int nextId = 1;

    // Windows Message Loop
    // idk why this has to be static but whatever
    static void MessageLoop() {
        MSG msg = { 0 };
        while (GetMessage(&msg, NULL, 0, 0)) {
            if (msg.message == WM_HOTKEY) {
                int id = (int)msg.wParam;
                if (callbacks.count(id)) { 
                    callbacks[id](); // Call the Lua callback
                }
            }
        }
    }

    // Bridge function for Lua
    static void Add(int mods, int vk, sol::function cb) {
        int id = nextId++;
        if (RegisterHotKey(NULL, id, mods | MOD_NOREPEAT, vk)) {
            callbacks[id] = cb;
            std::cout << "[System] Registered Hotkey ID: " << id << std::endl;
        } else {
            std::cerr << "[Error] Could not register Hotkey ID: " << id << std::endl;
        }
    }

    // Simulate Key Press
    static void SimulateKeyPress(int vk) {
        INPUT inputs[2] = {};

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = (WORD)vk;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = (WORD)vk;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        SendInput(2, inputs, sizeof(INPUT));
    }
};