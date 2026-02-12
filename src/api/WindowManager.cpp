#include "WindowManager.hpp"

std::string WindowManager::GetActiveWindowTitle() {
    char title[256];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextA(hwnd, title, sizeof(title));
    return std::string(title);
}

void WindowManager::SetFocusToWindow(std::string windowTitle) {
    // First try: Find window by title
    HWND hwnd = FindWindow(NULL, windowTitle.c_str());

    if (hwnd == NULL) {
        std::cerr << "[Error] Window not found by title: " << windowTitle << std::endl;
        
        // Second try: Find window by class name
        hwnd = FindWindow(windowTitle.c_str(), NULL);
        if (hwnd == NULL) {
            std::cerr << "[Error] Window not found by class name: " << windowTitle << std::endl;
            return;
        }
    }

    if (SetForegroundWindow(hwnd)) {
        std::cout << "[System] Successfully focused window: " << windowTitle << std::endl;
        
        // Restore window if minimized
        ShowWindow(hwnd, SW_RESTORE);
    } else {
        DWORD error = GetLastError();
        std::cerr << "[Error] Failed to set focus to window: " << windowTitle 
                  << " (Error: " << error << ")" << std::endl;
    }
}