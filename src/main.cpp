#include <sol/sol.hpp>
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include "HotkeyManager.hpp"
#include "KeyCodes.hpp" 

void SetupLuaEnvironment(sol::state& lua) {
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

    // Bind API
    lua.set_function("log", [](const std::string& m) { std::cout << "[Lua]: " << m << std::endl; });

    lua.set_function("bind", &HotkeyManager::Add);

    lua.set_function("send", &HotkeyManager::SimulateKeyPress);

    lua.set_function("focus", [](const std::string& windowTitle) {
        HotkeyManager::SetFocusToWindow(windowTitle);
    });

    lua.set_function("wait", [](float seconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(seconds * 1000)));
    });

    // Bind all keys and modifiers to Lua tables
    KeyCodes::Bind(lua);
}

int main() {
    // Start background thread for hotkeys
    std::thread(HotkeyManager::MessageLoop).detach();

    sol::state lua;
    SetupLuaEnvironment(lua);

    const std::string path = "scripts/main.lua";
    if (std::filesystem::exists(path)) {
        try {
            lua.script_file(path);
        } catch (const sol::error& e) {
            std::cerr << "[Lua Error] " << e.what() << std::endl;
        }
    }

    std::cout << "Engine active. Press Enter to stop." << std::endl;
    std::cin.get();
    return 0;
}