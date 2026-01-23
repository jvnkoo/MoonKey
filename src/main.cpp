#include <sol/sol.hpp>
#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <thread>
#include <map>

void RegisterHotKeys();
std::map<int, sol::function> luaCallbacks;
int nextHotKeyId = 1;
void AddHotkey();

/**
 * MoonKey Engine Entry Point
 * Manages C++/Lua interoperability and script execution.
 */
int main() {
    std::thread hotkeyThread(RegisterHotKeys);
    hotkeyThread.detach();

    // Initialize Lua state with essential sandboxed libraries
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

    std::cout << "[System] MoonKey Core initialized" << std::endl;

    // Bridge C++ logic to Lua environment
    // Note: We use lambda captures to expose host-side functionality to scripts
    lua.set_function("log_from_cpp", [](const std::string &message) {
        std::cout << "[Script Runtime]: " << message << std::endl;
    });

    lua.set_function("register_hotkey", &AddHotkey);

    lua["MOD_ALT"] = MOD_ALT;
    lua["MOD_CTRL"] = MOD_CONTROL;
    lua["MOD_SHIFT"] = MOD_SHIFT;
    lua["KEY_H"] = 0x48;

    // Resolve script location relative to the working directory
    const std::string scriptPath = "scripts/main.lua";

    // Validate filesystem integrity before attempting execution
    if (std::filesystem::exists(scriptPath)) {
        try {
            // Execute the script within a protected call (pcall) context
            lua.script_file(scriptPath);
            std::cout << "[System] Script lifecycle completed successfully" << std::endl;
        } catch (const sol::error &e) {
            // Log script-level exceptions (syntax errors, runtime panics)
            std::cerr << "[Critical] Script execution failed: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "[Critical] Resource missing: " << scriptPath << std::endl;
    }

    // Keep console alive for debugging purposes
    std::cout << "Engine suspended. Press Enter to terminate..." << std::endl;
    std::cin.get();

    return 0;
}

void AddHotKey(int modifiers, int vkCode, sol::function callback, sol::state &lua) {
    int hotkeyId = nextHotKeyId++;

    if (RegisterHotKey(NULL, hotkeyId, modifiers | MOD_NOREPEAT, vkCode)) {
        luaCallbacks[hotkeyId] = callback;
        std::cout << "[System] Hotkey registered: ID " << hotkeyId << std::endl;
    } else {
        std::cerr << "[Warning] Failed to register hotkey: ID " << hotkeyId << std::endl;
    }
}

void RegisterHotKeys() {
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            int id = (int)msg.wParam;
            if (luaCallbacks.count(id)) {
                luaCallbacks[id]();
            }
        }
    }
}