# MoonKey
![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus)
![Lua](https://img.shields.io/badge/Lua-5.4-2C2D72?logo=lua)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D4?logo=windows)
![License](https://img.shields.io/badge/License-GPL--3.0-blue)
![Build](https://img.shields.io/badge/Build-CMake-064F8C?logo=cmake)
[![Docs](https://img.shields.io/badge/Documentation-GitHub_Pages-blue?style=flat&logo=github)](https://zolofq.github.io/MoonKey/)

MoonKey is a lightweight automation engine that bridges Windows system calls with a Lua scripting environment. Unlike similar tools that rely on restricted, custom macro languages, MoonKey gives you the full power of real programming. You can write complex logic, use conditional statements, loops, and extend built-in functions with standard Lua code to handle any task. It allows you to register global hotkeys, simulate keyboard input, and manage window focus through flexible scripts that can be modified on the fly without ever touching C++ or recompiling the engine.

## Development Status 

**MoonKey is currently in early alpha.** The core engine is functional, but the API surface is still growing. 

**Contributions are highly welcome!** Whether it's adding new system bindings, improving the engine, or fixing bugs, feel free to open an Issue or submit a Pull Request.

> [!TIP]
> Complete API documentation, including a full list of supported keys and modifiers, is available on our [GitHub Pages](https://zolofq.github.io/MoonKey/).

## Lua API

| Function | Description | Example |
| --- | --- | --- |
| `log(msg)` | Prints message to console | `log("Action triggered")` |
| `bind(mod, key, fn)` | Registers a global hotkey | `bind(MOD.ALT, KEY.F1, function() ... end)` |
| `send(key)` | Simulates a single key tap | `send(KEY.ENTER)` |
| `focus(title)` | Brings window to foreground | `focus("Notepad")` |
| `write(text)` | Types a string of text | `write("Hello World")` |
| `wait(sec)` | Pauses execution (seconds) | `wait(1.5)` |
| `sleep(ms)` | Pauses execution (ms) | `sleep(500)` |

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

## Configuration

The engine automatically loads `scripts/main.lua` on startup. Key codes (`KEY`) and modifiers (`MOD`) are globally available within the Lua state.

---

<img src="https://media1.tenor.com/m/RhnIylqIIIUAAAAd/asushin-las.gif" width="1000" height="300" alt="Demo">
