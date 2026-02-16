#pragma once
#include <sol/sol.hpp>
#include <windows.h>
#include <string>
#include <thread>
#include <vector>

// Input simulation for keyboard and mouse
// Provides cross-platform input simulation using Windows SendInput API
// Supports keyboard events, text typing, and mouse operations
struct InputManager {
    // Simulate a single key press and release
    // vk: Virtual key code (use KEY constants)
    // Simulates pressing and immediately releasing a key
    // Equivalent to a quick tap on the keyboard
    static void SimulateKeyPress(int vk);

    // Type text as if from keyboard
    // text: String to type
    // Simulates typing complete strings with proper shift key handling
    // for uppercase and special characters. Includes small delays between
    // keystrokes for reliability with some applications.
    // Handles shift states for characters like @, !, %, etc.
    // Includes 15ms delay between keystrokes
    static void WriteText(const std::string& text);

    // Move mouse cursor to absolute screen coordinates
    // x: X coordinate (0 = left edge, screen width = right edge)
    // y: Y coordinate (0 = top edge, screen height = bottom edge)
    // Moves cursor instantly to specified position using absolute coordinates
    // Coordinates are transformed to Windows' virtual screen space (0-65535)
    // Coordinates outside screen bounds are clamped by Windows
    static void SetMousePos(int x, int y);

    // Simulate mouse button click
    // button: Button to click (0 = left, 1 = right, 2 = middle)
    // Simulates pressing and immediately releasing the specified mouse button
    // Includes both down and up events for complete click simulation
    static void MouseClick(int button);

    // Get current mouse cursor position
    // ts: Lua state (automatically passed)
    // Returns: Lua table with {x = number, y = number}
    // Returns the current cursor position in screen coordinates
    // Position is relative to the primary monitor
    static sol::table GetMousePos(sol::this_state ts);
};