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

// Initializes the Lua environment with all API functions
// Sets up all exposed C++ functions and constants
void SetupLuaEnvironment(sol::state& lua) {
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

    // Lua API functions
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

// Cleans and reinitializes the Lua environment
// Called during hot-reload to reset the scripting environment
void ResetLuaEnvironment(sol::state& lua) {
    lua.collect_garbage();
    SetupLuaEnvironment(lua);
}

// Main application entry point
// Initializes all subsystems and runs the main loop with hot-reload capability
int main() {
    EventDispatcher dispatcher;

    // Subscribe for hot-reload events
    dispatcher.subscribe("OnDirectoryChange", [&]() {
        needReload = true;
    });
    
    // Start hotkey message loop in separate thread
    std::thread msgThread(HotkeyManager::MessageLoop);
    msgThread.detach();

    // Start directory monitoring thread
    std::thread dirThread(Directory::DirectoryChangesLoop, L"scripts", std::ref(dispatcher));
    dirThread.detach();

    const std::string path = "scripts/main.lua";

    // Main loop with hot-reload support
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
        
        // Wait for reload signal
        while (!needReload) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::cout << "[System] Reloading environment..." << std::endl;
        HotkeyManager::Clear();
    }

    return 0;
}