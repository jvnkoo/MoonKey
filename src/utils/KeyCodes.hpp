#pragma once
#include <sol/sol.hpp>
#include <windows.h>
#include <string>

/**
 * @page keys_page Key & Modifier Reference
 * 
 * ## Modifiers (MOD)
 * 
 * Available in Lua as `MOD`. Used as the first argument in `bind()`.
 * Modifiers can be combined using `+` operator.
 * 
 * | Constant | Value | Description |
 * | :--- | :--- | :--- |
 * | `MOD.NONE` | 0 | No modifier |
 * | `MOD.ALT` | MOD_ALT | Alt key |
 * | `MOD.CTRL` | MOD_CONTROL | Control key |
 * | `MOD.SHIFT` | MOD_SHIFT | Shift key |
 * | `MOD.WIN` | MOD_WIN | Windows key |
 * | `MOD.NOREPEAT` | 0x4000 | Prevents repeated hotkey triggers |
 * 
 * ### Usage Examples:
 * @code
 * bind(MOD.ALT, KEY.F1, function() end)           -- Alt + F1
 * bind(MOD.CTRL + MOD.SHIFT, KEY.T, function() end) -- Ctrl + Shift + T
 * bind(MOD.WIN, KEY.R, function() end)             -- Windows + R
 * @endcode
 * 
 * ## Virtual Keys (KEY)
 * 
 * Available in Lua as `KEY`. Used in `send()` and as the second argument in `bind()`.
 * 
 * ### Letters and Numbers
 * - **Letters:** `KEY.A` through `KEY.Z`
 * - **Numbers:** `KEY.N0` through `KEY.N9` (top row)
 * - **Numpad:** `KEY.NUM0` through `KEY.NUM9`
 * 
 * ### Function Keys
 * - `KEY.F1` through `KEY.F24`
 * 
 * ### Navigation Keys
 * | Key | Description |
 * | :--- | :--- |
 * | `KEY.UP`, `KEY.DOWN` | Arrow keys |
 * | `KEY.LEFT`, `KEY.RIGHT` | Arrow keys |
 * | `KEY.HOME`, `KEY.END` | Home/End |
 * | `KEY.PAGEUP`, `KEY.PAGEDOWN` | Page Up/Down |
 * 
 * ### Special Keys
 * | Key | Description |
 * | :--- | :--- |
 * | `KEY.ENTER`, `KEY.SPACE` | Enter and Space |
 * | `KEY.ESCAPE`, `KEY.TAB` | Escape and Tab |
 * | `KEY.BACKSPACE`, `KEY.DELETE` | Backspace and Delete |
 * | `KEY.INSERT` | Insert key |
 * 
 * ### Mouse Buttons
 * | Key | Description |
 * | :--- | :--- |
 * | `KEY.LBUTTON` | Left mouse button |
 * | `KEY.RBUTTON` | Right mouse button |
 * | `KEY.MBUTTON` | Middle mouse button |
 * 
 * ### Modifier Keys (Individual)
 * | Key | Description |
 * | :--- | :--- |
 * | `KEY.LSHIFT`, `KEY.RSHIFT` | Left/Right Shift |
 * | `KEY.LCTRL`, `KEY.RCTRL` | Left/Right Control |
 * | `KEY.LALT`, `KEY.RALT` | Left/Right Alt |
 * | `KEY.LWIN`, `KEY.RWIN` | Left/Right Windows |
 * 
 * ### Numpad Operations
 * | Key | Description |
 * | :--- | :--- |
 * | `KEY.MULTIPLY`, `KEY.DIVIDE` | * and / |
 * | `KEY.ADD`, `KEY.SUBTRACT` | + and - |
 * | `KEY.DECIMAL` | Decimal point |
 * 
 * ### Lock Keys
 * | Key | Description |
 * | :--- | :--- |
 * | `KEY.CAPSLOCK` | Caps Lock |
 * | `KEY.NUMLOCK` | Num Lock |
 * | `KEY.SCROLLLOCK` | Scroll Lock |
 */

namespace KeyCodes {
    /**
     * @brief Binds key and modifier constants to Lua environment
     * @param lua Lua state to bind constants to
     * @internal
     * This function creates two global Lua tables: `MOD` and `KEY`
     */
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