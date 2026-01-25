#include <sol/sol.hpp>
#include <iostream>
#include <filesystem>
#include <thread>
#include "HotkeyManager.hpp"
#include "KeyCodes.hpp" // Include the new file

void SetupLuaEnvironment(sol::state& lua) {
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

    // Bind API
    lua.set_function("log_info", [](const std::string& m) { std::cout << "[Lua]: " << m << std::endl; });
    lua.set_function("register_hotkey", &HotkeyManager::Add);
    lua.set_function("simulate_key_press", &HotkeyManager::SimulateKeyPress);

    // Bind all keys and modifiers from our new file
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