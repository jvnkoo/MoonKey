/**
 * @mainpage User Documentation
 * 
 * ## Overview
 * MoonKey provides automation capabilities through Lua scripting. 
 * Scripts execute in a managed environment with hot-reload functionality.
 * 
 * 
 * ## Quick Start
 * 
 * 1. Create a `scripts` folder in the same directory as the executable
 * 2. Create `main.lua` inside that folder
 * 3. Write your automation script using the API below
 * 4. Run the executable - it will automatically reload when you save your script
 * 
 * ### Core Functions
 * 
 * | Function | Description | Example |
 * | :--- | :--- | :--- |
 * | **log** | Prints a message to console | `log("System ready")` |
 * | **bind** | Registers a global hotkey. | `bind(MOD.ALT, KEY.F1, function() end, "Notepad")` |
 * | **send** | Simulates a key press | `send(KEY.ENTER)` |
 * | **focus** | Brings window to foreground | `focus("Notepad")` |
 * | **write** | Types text | `write("Hello, World!")` |
 * | **wait** | Pauses script (seconds) | `wait(1.5)` |
 * | **sleep** | Pauses script (milliseconds) | `sleep(500)` |
 * | **mouse_move** | Moves cursor to X, Y coordinates | `mouse_move(1920, 1080)` |
 * | **mouse_click** | Clicks mouse button | `mouse_click(0)` |
 * | **mouse_pos** | Returns current mouse position | `local p = mouse_pos()` |
 * | **set_interval** | Sets a repeating timer | `set_interval(1000, function() log("Tick") end, "Notepad")` |
 * 
 * 
 * Note: Window title in the last parameter is optional
 *
 * ## Example Script
 * 
 * @code
 * -- Simple automation example
 * bind(MOD.ALT, KEY.T, function()
 *     focus("Notepad")
 *     write("Automation complete!")
 *     send(KEY.ENTER)
 * end)
 * 
 * -- Wait and click
 * bind(MOD.CTRL + MOD.SHIFT, KEY.M, function()
 *     mouse_move(100, 100)
 *     wait(0.5)
 *     mouse_click(0)
 * end)
 * @endcode
 * 
 * ## Key Reference
 * 
 * See @ref keys_page for complete list of available keys and modifiers.
 */

#include <sol/sol.hpp>
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include "core/HotkeyManager.hpp"
#include "api/InputManager.hpp"
#include "api/WindowManager.hpp"
#include "utils/KeyCodes.hpp"
#include "core/Directory.hpp"
#include "api/TimerManager.hpp"

std::atomic<bool> needReload = false;

/** 
 * @brief Initializes the Lua environment with all API functions
 * @internal
 * This function is for internal use only and sets up the Lua state
 * with all exposed C++ functions and constants.
 */
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
    lua.set_function("set_interval", &TimerManager::Add);

    KeyCodes::Bind(lua);
}

/**
 * @brief Cleans and reinitializes the Lua environment
 * @internal
 * Called during hot-reload to reset the scripting environment.
 */
void ResetLuaEnvironment(sol::state& lua) {
    lua.collect_garbage();
    SetupLuaEnvironment(lua);
}

/** 
 * @brief Main application entry point
 * @return Exit code
 * 
 * Initializes all subsystems and runs the main loop with hot-reload capability.
 */
int main() {
    EventDispatcher dispatcher;

    // Subscribe for hot-reload 
    dispatcher.subscribe("OnDirectoryChange", [&]() {
        needReload = true;
    });
    
    std::thread msgThread(HotkeyManager::MessageLoop);
    msgThread.detach();

    // Start directory monitoring thread
    std::thread dirThread(Directory::DirectoryChangesLoop, L"scripts", std::ref(dispatcher));
    dirThread.detach();

    const std::string path = "scripts/main.lua";

    while (true) {
        sol::state lua;
        SetupLuaEnvironment(lua);
        needReload = false;

        std::cout << "[System] Loading script..." << std::endl;

        try { 
            lua.script_file(path); 
        } 
        catch (const sol::error& e) { 
            std::cerr << "[Lua Error] " << e.what() << std::endl; 
        }
        
        while (!needReload) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::cout << "[System] Reloading environment..." << std::endl;
        HotkeyManager::Clear();
    }

    return 0;
}