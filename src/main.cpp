#include <sol/sol.hpp>
#include <iostream>
#include <filesystem>
#include <thread>
#include "HotkeyManager.hpp"

void SetupLuaEnvironment(sol::state& lua) {
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

    // Bind API
    lua.set_function("log_info", [](const std::string& m) { std::cout << "[Lua]: " << m << std::endl; });
    lua.set_function("register_hotkey", &HotkeyManager::Add);
    lua.set_function("simulate_key_press", &HotkeyManager::SimulateKeyPress);

    // Bind Constants
    lua["MOD_ALT"]   = 0x0001;
    lua["MOD_CTRL"]  = 0x0002;
    lua["MOD_SHIFT"] = 0x0004;
    lua["MOD_WIN"]   = 0x0008; 
    
    // --- simulate_key_press ---
    lua["KEY_H"]      = 0x48;
    lua["KEY_G"]      = 0x47;
    lua["KEY_LWIN"]   = VK_LWIN;   // 0x5B 
    lua["KEY_RWIN"]   = VK_RWIN;   // 0x5C
    lua["KEY_CONTROL"] = VK_CONTROL;
    lua["KEY_SHIFT"]   = VK_SHIFT;
    lua["KEY_ESCAPE"]  = VK_ESCAPE;
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