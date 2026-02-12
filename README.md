# MoonKey
![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus)
![Lua](https://img.shields.io/badge/Lua-5.4-2C2D72?logo=lua)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D4?logo=windows)
![License](https://img.shields.io/badge/License-GPL--3.0-blue)
![Build](https://img.shields.io/badge/Build-CMake-064F8C?logo=cmake)
[![Docs](https://img.shields.io/badge/Documentation-GitHub_Pages-blue?style=flat&logo=github)](https://jvnkoo.github.io/MoonKey/)

MoonKey is a lightweight automation engine that bridges Windows system calls with the Lua scripting environment. It enables global hotkeys, input simulation, and window management through flexible scripts that can be modified on the fly without recompiling the C++ core.

Unlike tools restricted by custom macro languages, MoonKey provides the full power of Lua 5.4. This allows for complex logic, conditional loops, and modular code to handle any task with the speed and flexibility of a real programming language.

## Development Status 

MoonKey's core engine is functional. Development is currently focused on expanding the **API surface** and adding **new features**.

**Contributions welcome** — open an issue or submit a PR on [GitHub](https://github.com/jvnkoo/MoonKey/issues).

## Documentation

Complete API reference, supported keys, and advanced examples:  
**https://jvnkoo.github.io/MoonKey/**

## Quick Start

1. Go to the **Releases** page and download the latest `MoonKey.exe`.
2. Create a folder named `scripts` in the same directory where you placed the exe.
3. Create a file named `main.lua` inside the `scripts` folder.
4. Run `MoonKey.exe`.

### Example Script (`scripts/main.lua`)

```lua
-- Register Alt+T to automate Notepad
bind(MOD.ALT, KEY.T, function()
    focus("Notepad")
    wait(0.2)
    write("This text was typed by Lua!")
    send(KEY.ENTER)
end)

log("Scripts loaded. Press Alt+T to test.")

```
> [!NOTE]
> The engine automatically loads `scripts/main.lua` on startup. Key codes and modifiers are globally available.

---

<img src="https://media1.tenor.com/m/RhnIylqIIIUAAAAd/asushin-las.gif" width="1000" height="300" alt="Demo">
