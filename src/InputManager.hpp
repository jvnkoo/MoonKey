#pragma once
#include <sol/sol.hpp>
#include <windows.h>
#include <string>
#include <thread>
#include <vector>

struct InputManager {
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

    static sol::table GetMousePos(sol::this_state ts) {
        POINT p;
        GetCursorPos(&p);
        
        sol::state_view lua(ts);
        sol::table pos_table = lua.create_table();
        pos_table["x"] = p.x;
        pos_table["y"] = p.y;
        
        return pos_table;
    }
};