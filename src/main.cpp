#include <sol/sol.hpp>
#include <iostream>
#include <string>
#include <filesystem>

/**
 * MoonKey Engine Entry Point
 * Manages C++/Lua interoperability and script execution.
 */
int main() {
    // Initialize Lua state with essential sandboxed libraries
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

    std::cout << "[System] MoonKey Core initialized" << std::endl;

    // Bridge C++ logic to Lua environment
    // Note: We use lambda captures to expose host-side functionality to scripts
    lua.set_function("log_from_cpp", [](const std::string& message) {
        std::cout << "[Script Runtime]: " << message << std::endl;
    });

    // Resolve script location relative to the working directory
    const std::string scriptPath = "scripts/main.lua";

    // Validate filesystem integrity before attempting execution
    if (std::filesystem::exists(scriptPath)) {
        try {
            // Execute the script within a protected call (pcall) context
            lua.script_file(scriptPath);
            std::cout << "[System] Script lifecycle completed successfully" << std::endl;
        } 
        catch (const sol::error& e) {
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