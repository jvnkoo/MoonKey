#pragma once
#include <windows.h>
#include <string>
#include <iostream>

struct WindowManager {
    static std::string GetActiveWindowTitle() {
        char title[256];
        HWND hwnd = GetForegroundWindow();
        GetWindowTextA(hwnd, title, sizeof(title));
        return std::string(title);
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
};