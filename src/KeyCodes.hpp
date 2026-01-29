#pragma once
#include <sol/sol.hpp>
#include <windows.h>
#include <string>

/**
 * @page keys_page Key & Modifier Codes
 * @tableofcontents
 * * @section mod_sec MOD (Modifiers)
 * Available in Lua as `MOD`. Used as the first argument in `bind()`.
 * - `MOD.ALT`, `MOD.CTRL`, `MOD.SHIFT`, `MOD.WIN`, `MOD.NONE`
 * * @section key_sec KEY (Virtual Keys)
 * Available in Lua as `KEY`. Used in `send()` and as the second argument in `bind()`.
 * - **Letters:** `KEY.A` ... `KEY.Z`
 * - **Numbers:** `KEY.N0` ... `KEY.N9`, `KEY.NUM0` ... `KEY.NUM9`
 * - **Function Keys:** `KEY.F1` ... `KEY.F24`
 * - **System:** `KEY.ENTER`, `KEY.SPACE`, `KEY.ESCAPE`, `KEY.BACKSPACE`, `KEY.TAB`
 * - **Arrows:** `KEY.UP`, `KEY.DOWN`, `KEY.LEFT`, `KEY.RIGHT`
 * - **Mouse:** `KEY.LBUTTON`, `KEY.RBUTTON`, `KEY.MBUTTON`
 */

namespace KeyCodes {
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