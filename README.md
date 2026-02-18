<div align="center">

<img src="https://github.com/user-attachments/assets/87d8b1f3-1fae-4603-a03d-85bac3175122" width="400" alt="MoonKey Logo">

**Automate Windows with Lua. No custom macro language. No limits.**

![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus)
![Lua](https://img.shields.io/badge/Lua-5.4-2C2D72?logo=lua)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D4?logo=windows)
![License](https://img.shields.io/badge/License-GPL--3.0-blue)
![Build](https://img.shields.io/badge/Build-CMake-064F8C?logo=cmake)
[![Docs](https://img.shields.io/badge/Documentation-GitHub_Pages-blue?style=flat&logo=github)](https://jvnkoo.github.io/MoonKey/)

</div>

---

## Why MoonKey?

Most automation tools on Windows either use clunky custom scripting languages or require you to recompile C++ every time you change a macro. MoonKey fixes both problems.

You write real **Lua 5.4** — a proper programming language with loops, functions, tables, and modules. The C++ engine underneath handles all Windows API calls. Change your script, save the file, and MoonKey **hot-reloads instantly** — no restart, no recompile.

| | MoonKey | AutoHotkey | Custom C++ |
|---|---|---|---|
| Scripting language | Lua 5.4 | AHK syntax | C++ |
| Hot-reload | ✅ | ❌ | ❌ |
| Real programming language | ✅ | Partial | ✅ |
| Easy to embed / extend | ✅ | ❌ | ✅ |
| Setup time | ~1 min | ~5 min | Hours |

---

## What you can build

- **Gaming macros** — complex key sequences, conditional logic, timed inputs
- **Window automation** — focus, switch, and control any application
- **Text expanders** — type a shortcut, get a full text block
- **Productivity scripts** — automate repetitive workflows across any app
- **Dev tools** — bind build/run/deploy commands to hotkeys in any IDE

---

## Quick Start

**1.** Download `MoonKey.exe` from the [Releases](https://github.com/jvnkoo/MoonKey/releases) page.

**2.** Create a `scripts` folder next to the exe, and inside it create `main.lua`.

**3.** Paste this example and run `MoonKey.exe`:

```lua
-- Alt+T: focus Notepad and type a message
bind(MOD.ALT, KEY.T, function()
    focus("Notepad")
    wait(0.2)
    write("Automated by MoonKey!")
    send(KEY.ENTER)
end)

-- Ctrl+Shift+M: move mouse and click
bind(MOD.CTRL + MOD.SHIFT, KEY.M, function()
    mouse_move(960, 540)
    wait(0.1)
    mouse_click(0)
end)

log("MoonKey ready.")
```

**4.** Edit and save `main.lua` — the engine reloads automatically.

---

## Real-world example: auto-reply macro

```lua
-- Press Alt+R to paste a canned response in any chat app
local reply = "Thanks for reaching out! I'll get back to you within 24 hours."

bind(MOD.ALT, KEY.R, function()
    write(reply)
    send(KEY.ENTER)
end)
```

---

## API at a glance

| Function | Description |
|:---------|:------------|
| `bind(mods, key, fn, [window])` | Register a global hotkey, optionally scoped to one window |
| `send(key)` | Simulate a key press |
| `write(text)` | Type a string with proper shift handling |
| `focus(title)` | Bring a window to the foreground |
| `wait(seconds)` | Pause execution |
| `sleep(ms)` | Pause execution (milliseconds) |
| `mouse_move(x, y)` | Move cursor to absolute screen coordinates |
| `mouse_click(button)` | Click left (0), right (1), or middle (2) |
| `mouse_pos()` | Get current cursor position as `{x, y}` |
| `set_interval(ms, fn, [window])` | Run a function on a repeating timer |
| `log(message)` | Print to console |

Full reference → **[jvnkoo.github.io/MoonKey](https://jvnkoo.github.io/MoonKey/)**

---

## Building from source

```bash
git clone https://github.com/jvnkoo/MoonKey.git
cd MoonKey
cmake -B build
cmake --build build --config Release
```

**Requirements:** CMake 3.20+, MSVC or MinGW with C++20 support, Windows 10+

---

## Contributing

MoonKey's core engine is stable. The focus right now is expanding the API — more window introspection, process management, clipboard access, and screen reading.

If you have a use case that's not covered, **open an issue** describing what you're trying to automate. PRs are welcome.

→ [Open an issue](https://github.com/jvnkoo/MoonKey/issues) · [Read the docs](https://jvnkoo.github.io/MoonKey/)

---

## License

GPL-3.0 — see [LICENSE](LICENSE) for details.

---

<img src="https://media1.tenor.com/m/RhnIylqIIIUAAAAd/asushin-las.gif" width="1000" height="300" alt="banner">
