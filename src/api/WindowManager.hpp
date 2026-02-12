#pragma once
/**
 * @brief Window management and focus control
 * @ingroup api
 * * Provides functionality to find, activate, and manage application windows
 * using Windows API functions.
 */

#include <windows.h>
#include <string>
#include <iostream>

/**
 * @struct WindowManager
 * @brief Static methods for window operations
 * * Supports finding windows by title and bringing them to foreground.
 * All methods are thread-safe.
 */
struct WindowManager {
    /**
     * @brief Get title of currently active window
     * @return Window title as string
     * * Retrieves the title of the foreground window (window with user focus).
     * Returns empty string if no window is active or title cannot be retrieved.
     * * @note Uses GetForegroundWindow() and GetWindowTextA()
     * @note Maximum title length is 255 characters
     * * @internal Used primarily for context-sensitive hotkeys
     */
    static std::string GetActiveWindowTitle();

    /**
     * @brief Bring window to foreground and give it focus
     * @param windowTitle Window title or class name to find
     * * Searches for a window with the specified title or class name and
     * attempts to bring it to the foreground. Tries two search methods:
     * 1. By window title (caption)
     * 2. By window class name
     * * @note Uses FindWindow() with NULL class name, then with NULL window name
     * @note Shows window with SW_RESTORE if minimized
     * @note May fail due to Windows security restrictions on foreground changes
     * * @warning Some applications block foreground window changes for security
     * @warning UWP/Store apps may not be accessible with this method
     * * @code
     * focus("Notepad")                 // Find by title
     * focus("Notepad++")              // Find Notepad++ window
     * focus("Chrome_WidgetWin_1")    // Find by class name
     * @endcode
     */
    static void SetFocusToWindow(std::string windowTitle);
};