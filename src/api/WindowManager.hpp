#pragma once
#include <windows.h>
#include <string>
#include <iostream>

// Window management and focus control
// Provides functionality to find, activate, and manage application windows
// using Windows API functions
struct WindowManager {
    // Get title of currently active window
    // Returns: Window title as string
    // Retrieves the title of the foreground window (window with user focus)
    // Returns empty string if no window is active or title cannot be retrieved
    // Uses GetForegroundWindow() and GetWindowTextA()
    // Maximum title length is 255 characters
    static std::string GetActiveWindowTitle();

    // Bring window to foreground and give it focus
    // windowTitle: Window title or class name to find
    // Searches for a window with the specified title or class name and
    // attempts to bring it to the foreground. Tries two search methods:
    // 1. By window title (caption)
    // 2. By window class name
    // Uses FindWindow() with NULL class name, then with NULL window name
    // Shows window with SW_RESTORE if minimized
    // May fail due to Windows security restrictions on foreground changes
    // WARNING: Some applications block foreground window changes for security
    // WARNING: UWP/Store apps may not be accessible with this method
    static void SetFocusToWindow(std::string windowTitle);
};