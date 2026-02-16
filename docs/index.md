# User Documentation

## Overview

MoonKey provides automation capabilities through Lua scripting. 
Scripts execute in a managed environment with hot-reload functionality.

## Quick Start

1. Create a `scripts` folder in the same directory as the executable
2. Create `main.lua` inside that folder
3. Write your automation script using the API below
4. Run the executable - it will automatically reload when you save your script

## Core Functions

| Function | Description | Example |
|:---------|:------------|:--------|
| **log** | Prints a message to console | `log("System ready")` |
| **bind** | Registers a global hotkey | `bind(MOD.ALT, KEY.F1, function() end, "Notepad")` |
| **send** | Simulates a key press | `send(KEY.ENTER)` |
| **focus** | Brings window to foreground | `focus("Notepad")` |
| **write** | Types text | `write("Hello, World!")` |
| **wait** | Pauses script (seconds) | `wait(1.5)` |
| **sleep** | Pauses script (milliseconds) | `sleep(500)` |
| **mouse_move** | Moves cursor to X, Y coordinates | `mouse_move(1920, 1080)` |
| **mouse_click** | Clicks mouse button | `mouse_click(0)` |
| **mouse_pos** | Returns current mouse position | `local p = mouse_pos()` |
| **set_interval** | Sets a repeating timer | `set_interval(1000, function() log("Tick") end, "Notepad")` |

!!! note
    Window title in the last parameter is optional

## Example Script

```lua
-- Simple automation example
bind(MOD.ALT, KEY.T, function()
    focus("Notepad")
    write("Automation complete!")
    send(KEY.ENTER)
end)

-- Wait and click
bind(MOD.CTRL + MOD.SHIFT, KEY.M, function()
    mouse_move(100, 100)
    wait(0.5)
    mouse_click(0)
end)
```

## Key Reference

See [Keys & Modifiers Reference](keys-reference.md) for complete list of available keys and modifiers.
