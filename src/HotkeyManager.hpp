#pragma once
#include <windows.h>
#include <sol/sol.hpp>
#include <map>
#include <iostream>

struct HotkeyManager {
    // inline?
    static inline std::map<int, sol::function> callbacks;
    static inline int nextId = 1;

    // Windows Message Loop
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

    static void SetFocusToWindow(std::string windowTitle) {
        HWND hwnd = FindWindow(NULL, windowTitle.c_str());

        if (hwnd == NULL) {
            std::cerr << "[Error] Window not found: " << windowTitle << std::endl;
            
            hwnd = FindWindow(windowTitle.c_str(), NULL);
            if (hwnd == NULL) {
                std::cerr << "[Error] Window not found using alternative method: " << windowTitle << std::endl;
                return;
            }
        }

        if (SetForegroundWindow(hwnd)) {
            std::cout << "Successfully set focus to the window." << std::endl;
            
            ShowWindow(hwnd, SW_RESTORE);
        } else {
            std::cerr << "[Error] Failed to set focus to the window: " << windowTitle << std::endl;
        }
    }

    static void WriteText(const std::string& text) {
        for (char c : text) {
            SHORT vk = VkKeyScan(c);
            BYTE vkCode = LOBYTE(vk);
            BYTE shiftState = HIBYTE(vk);

            // Press Shift if needed
            if (shiftState & 1) {
                INPUT shiftDown = {};
                shiftDown.type = INPUT_KEYBOARD;
                shiftDown.ki.wVk = VK_SHIFT;
                SendInput(1, &shiftDown, sizeof(INPUT));
            }

            // Key down
            INPUT keyDown = {};
            keyDown.type = INPUT_KEYBOARD;
            keyDown.ki.wVk = vkCode;
            SendInput(1, &keyDown, sizeof(INPUT));

            // Key up
            INPUT keyUp = {};
            keyUp.type = INPUT_KEYBOARD;
            keyUp.ki.wVk = vkCode;
            keyUp.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &keyUp, sizeof(INPUT));

            std::this_thread::sleep_for(std::chrono::milliseconds(15));

            // Release Shift if it was pressed
            if (shiftState & 1) {
                INPUT shiftUp = {};
                shiftUp.type = INPUT_KEYBOARD;
                shiftUp.ki.wVk = VK_SHIFT;
                shiftUp.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &shiftUp, sizeof(INPUT));
            }
        }
    }
};