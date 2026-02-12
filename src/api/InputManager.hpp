#pragma once
/**
 * @brief Input simulation for keyboard and mouse
 * @ingroup api
 * * Provides cross-platform input simulation using Windows SendInput API.
 * Supports keyboard events, text typing, and mouse operations.
 */

#include <sol/sol.hpp>
#include <windows.h>
#include <string>
#include <thread>
#include <vector>

/**
 * @struct InputManager
 * @brief Static methods for simulating user input
 * * All methods are thread-safe for use from Lua callbacks.
 * Input is simulated at system level, not application level.
 */
struct InputManager {
    /**
     * @brief Simulate a single key press and release
     * @param vk Virtual key code (use KEY constants)
     * * Simulates pressing and immediately releasing a key.
     * Equivalent to a quick tap on the keyboard.
     * * @note Uses Windows SendInput() with KEYDOWN and KEYUP events
     * @note For modifier keys, consider holding them with multiple calls
     * * @code
     * send(KEY.ENTER)      // Press and release Enter
     * send(KEY.ESCAPE)     // Press and release Escape
     * @endcode
     */
    static void SimulateKeyPress(int vk);

    /**
     * @brief Type text as if from keyboard
     * @param text String to type
     * * Simulates typing complete strings with proper shift key handling
     * for uppercase and special characters. Includes small delays between
     * keystrokes for reliability with some applications.
     * * @note Handles shift states for characters like @, !, %, etc.
     * @note Includes 15ms delay between keystrokes
     * @note Not suitable for extremely fast typing simulation
     * * @code
     * write("Hello, World!")  // Types with proper shift for '!' and 'H'
     * write("test@example.com") // Handles @ symbol with shift
     * @endcode
     */
    static void WriteText(const std::string& text);

    /**
     * @brief Move mouse cursor to absolute screen coordinates
     * @param x X coordinate (0 = left edge, screen width = right edge)
     * @param y Y coordinate (0 = top edge, screen height = bottom edge)
     * * Moves cursor instantly to specified position using absolute coordinates.
     * Coordinates are transformed to Windows' virtual screen space (0-65535).
     * * @note Uses MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE flags
     * @note Coordinates outside screen bounds are clamped by Windows
     * * @code
     * mouse_move(1920, 1080)  // Move to bottom-right corner of 1080p screen
     * mouse_move(0, 0)        // Move to top-left corner
     * @endcode
     */
    static void SetMousePos(int x, int y);

    /**
     * @brief Simulate mouse button click
     * @param button Button to click (0 = left, 1 = right, 2 = middle)
     * * Simulates pressing and immediately releasing the specified mouse button.
     * Includes both down and up events for complete click simulation.
     * * @code
     * mouse_click(0)  // Left click
     * mouse_click(1)  // Right click
     * mouse_click(2)  // Middle click
     * @endcode
     */
    static void MouseClick(int button);

    /**
     * @brief Get current mouse cursor position
     * @param ts Lua state (automatically passed)
     * @return Lua table with {x = number, y = number}
     * * Returns the current cursor position in screen coordinates.
     * Position is relative to the primary monitor.
     * * @code
     * local pos = mouse_pos()
     * log("Mouse at: " .. pos.x .. ", " .. pos.y)
     * @endcode
     */
    static sol::table GetMousePos(sol::this_state ts);
};