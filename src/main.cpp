/**
 * @mainpage API Reference
 *
 * ### Core Functions
 *
 * | Function | Description | Example |
 * | :--- | :--- | :--- |
 * | **log** | Prints a message to console | `log("System ready")` |
 * | **bind** | Registers a global hotkey. Window title is optional. See @ref keys_page "Full Key List". | `bind(MOD.ALT, KEY.F1, function() end, "Notepad")` |
 * | **send** | Simulates a key tap. See @ref keys_page "Full Key List". | `send(KEY.ENTER)` |
 * | **focus** | Brings window to foreground | `focus("Notepad")` |
 * | **write** | Types a string of text | `write("Hello, World!")` |
 * | **wait** | Pauses script (seconds) | `wait(1.5)` |
 * | **sleep** | Pauses script (ms) | `sleep(500)` |
 * | **mouse_move** | Sets cursor to absolute X, Y | `mouse_move(1920, 1080)` |
 * | **mouse_click** | Clicks (0: Left, 1: Right, 2: Mid) | `mouse_click(0)` |
 * | **mouse_pos** | Returns table with current {x, y} | `local p = mouse_pos()` |
 *
 * ---
 * ### Quick Example
 * @code
 * bind(MOD.ALT, KEY.T, function()
 * focus("Notepad")
 * write("Done!")
 * end)
 * @endcode
 */

#include <sol/sol.hpp>
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include "HotkeyManager.hpp"
#include "InputManager.hpp"
#include "WindowManager.hpp"
#include "KeyCodes.hpp"

/** @brief Internal API Registration */
void SetupLuaEnvironment(sol::state& lua) {
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

    lua.set_function("log", [](const std::string& m) { std::cout << "[Lua]: " << m << std::endl; });
    lua.set_function("bind", &HotkeyManager::Add);
    lua.set_function("send", &InputManager::SimulateKeyPress);
    lua.set_function("focus", [](const std::string& windowTitle) { WindowManager::SetFocusToWindow(windowTitle); });
    lua.set_function("write", [](const std::string& text) { InputManager::WriteText(text); });
    lua.set_function("wait", [](float seconds) { std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(seconds * 1000))); });
    lua.set_function("sleep", [](float milliseconds) { std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(milliseconds))); });
    lua.set_function("mouse_move", &InputManager::SetMousePos);
    lua.set_function("mouse_click", &InputManager::MouseClick);
    lua.set_function("mouse_pos", &InputManager::GetMousePos);

    KeyCodes::Bind(lua);
}

int main() {
    std::thread msgThread(HotkeyManager::MessageLoop);
    msgThread.detach();

    sol::state lua;
    SetupLuaEnvironment(lua);

    const std::string path = "scripts/main.lua";
    if (std::filesystem::exists(path)) {
        try { lua.script_file(path); } 
        catch (const sol::error& e) { std::cerr << "[Lua Error] " << e.what() << std::endl; }
    }

    std::cout << "Engine active. Press Enter to stop." << std::endl;
    std::cin.get();
    return 0;
}