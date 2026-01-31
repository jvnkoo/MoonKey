#pragma once
#include <thread>
#include <windows.h>
#include <sol/sol.hpp>
#include <map>
#include <iostream>
#include <vector>
#include <mutex>

struct HotkeyRequest {
    int mods;
    int vk;
    sol::function cb;
};

struct HotkeyManager {
    // inline?
    static inline std::map<int, sol::function> callbacks;
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
                        callbacks[id] = req.cb;
                        std::cout << "[System] Registered Hotkey ID: " << id << std::endl;
                    } else {
                        std::cerr << "[Error] Could not register Hotkey ID: " << id << std::endl;
                    }
                }
                registrationQueue.clear();
            }

            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_HOTKEY) {
                    int id = (int)msg.wParam;
                    if (callbacks.count(id)) { 
                        callbacks[id](); // Call the Lua callback
                    }
                }
                if (msg.message == WM_QUIT) return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    // Bridge function for Lua
    static void Add(int mods, int vk, sol::function cb) {
        std::lock_guard<std::mutex> lock(queueMutex);
        registrationQueue.push_back({ mods, vk, cb });
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

    static void SetMousePos(int x, int y) {
        double screenWidth = GetSystemMetrics(SM_CXSCREEN);
        double screenHeight = GetSystemMetrics(SM_CYSCREEN);

        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = (long)(x * (65535.0 / screenWidth));
        input.mi.dy = (long)(y * (65535.0 / screenHeight));

        SendInput(1, &input, sizeof(INPUT));
    }

    static void MouseClick(int button) {
        INPUT inputs[2] = { 0 };
        inputs[0].type = INPUT_MOUSE;
        inputs[1].type = INPUT_MOUSE;

        if (button == 0) {
            inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        } else if (button == 1) {
            inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        } else {
            inputs[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
            inputs[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
        }

        SendInput(2, inputs, sizeof(INPUT));
    }

    static std::pair<int, int> GetMousePos() {
        POINT p;
        if (GetCursorPos(&p)) {
            return { p.x, p.y };
        }
        return { 0, 0 };
    }
};