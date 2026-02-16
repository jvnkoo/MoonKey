#pragma once
#include <sol/sol.hpp>
#include <windows.h>
#include <string>

// KeyCodes namespace provides key and modifier constants for Lua
// This creates two global Lua tables: MOD and KEY

namespace KeyCodes {
    // Binds key and modifier constants to Lua environment
    // Creates global MOD table with modifier constants (ALT, CTRL, SHIFT, WIN, NOREPEAT)
    // Creates global KEY table with all virtual key codes (A-Z, F1-F24, arrows, etc.)
    inline void Bind(sol::state& lua) {
        auto mods = lua.create_table();
        mods["NONE"]     = 0;
        mods["ALT"]      = MOD_ALT;
        mods["CTRL"]     = MOD_CONTROL;
        mods["SHIFT"]    = MOD_SHIFT;
        mods["WIN"]      = MOD_WIN;
        mods["NOREPEAT"] = MOD_NOREPEAT;
        lua["MOD"] = mods;

        auto keys = lua.create_table();
        keys["LBUTTON"]    = VK_LBUTTON;
        keys["RBUTTON"]    = VK_RBUTTON;
        keys["MBUTTON"]    = VK_MBUTTON;
        keys["XBUTTON1"]   = VK_XBUTTON1;
        keys["XBUTTON2"]   = VK_XBUTTON2;

        for (char c = 'A'; c <= 'Z'; ++c) keys[std::string(1, c)] = (int)c;
        for (char n = '0'; n <= '9'; ++n) keys["N" + std::string(1, n)] = (int)n;
        for (int i = 1; i <= 24; ++i) keys["F" + std::to_string(i)] = VK_F1 + (i - 1);
        for (int i = 0; i <= 9; ++i) keys["NUM" + std::to_string(i)] = VK_NUMPAD0 + i;

        keys["MULTIPLY"]   = VK_MULTIPLY;
        keys["ADD"]        = VK_ADD;
        keys["SEPARATOR"]  = VK_SEPARATOR;
        keys["SUBTRACT"]   = VK_SUBTRACT;
        keys["DECIMAL"]    = VK_DECIMAL;
        keys["DIVIDE"]     = VK_DIVIDE;
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