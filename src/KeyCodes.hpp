#pragma once
#include <sol/sol.hpp>
#include <windows.h>
#include <string>

namespace KeyCodes {
    // why this way? because lua tables are ugly to build in c++  
    inline void Bind(sol::state& lua) {
        // --- MODIFIERS (Used for register_hotkey first argument) ---
        auto mods = lua.create_table();
        mods["NONE"]     = 0;
        mods["ALT"]      = MOD_ALT;      // 0x0001
        mods["CTRL"]     = MOD_CONTROL;  // 0x0002
        mods["SHIFT"]    = MOD_SHIFT;    // 0x0004
        mods["WIN"]      = MOD_WIN;      // 0x0008
        mods["NOREPEAT"] = MOD_NOREPEAT; // 0x4000
        lua["MOD"] = mods;

        // --- KEYS (Used for simulate_key_press and register_hotkey second argument) ---
        auto keys = lua.create_table();
        
        // Mouse buttons
        keys["LBUTTON"]    = VK_LBUTTON;
        keys["RBUTTON"]    = VK_RBUTTON;
        keys["MBUTTON"]    = VK_MBUTTON;
        keys["XBUTTON1"]   = VK_XBUTTON1;
        keys["XBUTTON2"]   = VK_XBUTTON2;

        // Letters A-Z
        for (char c = 'A'; c <= 'Z'; ++c) {
            keys[std::string(1, c)] = (int)c;
        }

        // Top-row Numbers (N0-N9)
        for (char n = '0'; n <= '9'; ++n) {
            keys["N" + std::string(1, n)] = (int)n;
        }

        // Function Keys (F1-F24)
        for (int i = 1; i <= 24; ++i) {
            keys["F" + std::to_string(i)] = VK_F1 + (i - 1);
        }

        // Numpad Keys
        for (int i = 0; i <= 9; ++i) {
            keys["NUM" + std::to_string(i)] = VK_NUMPAD0 + i;
        }
        keys["MULTIPLY"]   = VK_MULTIPLY;
        keys["ADD"]        = VK_ADD;
        keys["SEPARATOR"]  = VK_SEPARATOR;
        keys["SUBTRACT"]   = VK_SUBTRACT;
        keys["DECIMAL"]    = VK_DECIMAL;
        keys["DIVIDE"]     = VK_DIVIDE;

        // Navigation & Control
        keys["SPACE"]      = VK_SPACE;
        keys["ENTER"]      = VK_RETURN;
        keys["ESCAPE"]     = VK_ESCAPE;
        keys["BACKSPACE"]  = VK_BACK;
        keys["TAB"]        = VK_TAB;
        keys["CAPSLOCK"]   = VK_CAPITAL;
        keys["NUMLOCK"]    = VK_NUMLOCK;
        keys["SCROLLLOCK"] = VK_SCROLL;
        keys["PRINTSCREEN"] = VK_SNAPSHOT;
        keys["PAUSE"]      = VK_PAUSE;

        // Directional keys
        keys["LEFT"]       = VK_LEFT;
        keys["RIGHT"]      = VK_RIGHT;
        keys["UP"]         = VK_UP;
        keys["DOWN"]       = VK_DOWN;
        keys["INSERT"]     = VK_INSERT;
        keys["DELETE"]     = VK_DELETE;
        keys["HOME"]       = VK_HOME;
        keys["END"]        = VK_END;
        keys["PAGEUP"]     = VK_PRIOR;
        keys["PAGEDOWN"]   = VK_NEXT;

        // Specific Modifiers (Useful for simulate_key_press)
        keys["LSHIFT"]     = VK_LSHIFT;
        keys["RSHIFT"]     = VK_RSHIFT;
        keys["LCTRL"]      = VK_LCONTROL;
        keys["RCTRL"]      = VK_RCONTROL;
        keys["LALT"]       = VK_LMENU;
        keys["RALT"]       = VK_RMENU;
        keys["LWIN"]       = VK_LWIN;
        keys["RWIN"]       = VK_RWIN;

        lua["KEY"] = keys;
    }
}