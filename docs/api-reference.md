# API Reference

Complete reference for all functions available in MoonKey Lua scripts.

---

## Logging

### log(message)

Prints a message to console.

**Parameters:**

- `message` (string) - Text to print

**Example:**

```lua
log("System ready")
```

---

## Hotkey Management

### bind(modifiers, key, callback, [windowTitle])

Registers a global hotkey.

**Parameters:**

- `modifiers` (number) - Modifier keys (use `MOD` constants)
- `key` (number) - Virtual key code (use `KEY` constants)
- `callback` (function) - Function to execute when hotkey is pressed
- `windowTitle` (string, optional) - Only trigger when this window is active

**Examples:**

```lua
bind(MOD.ALT, KEY.F1, function() end)           -- Alt + F1
bind(MOD.CTRL + MOD.SHIFT, KEY.T, function() end) -- Ctrl + Shift + T
bind(MOD.WIN, KEY.R, function() end)             -- Windows + R
```

---

## Input Simulation

### send(key)

Simulates a key press.

**Parameters:**

- `key` (number) - Virtual key code (use `KEY` constants)

**Example:**

```lua
send(KEY.ENTER)
```

**Notes:**

- Simulates pressing and immediately releasing a key
- Equivalent to a quick tap on the keyboard
- Uses Windows SendInput() with KEYDOWN and KEYUP events
- For modifier keys, consider holding them with multiple calls

---

### write(text)

Types text as if from keyboard.

**Parameters:**

- `text` (string) - String to type

**Example:**

```lua
write("Hello, World!")
```

**Notes:**

- Simulates typing complete strings with proper shift key handling for uppercase and special characters
- Includes small delays between keystrokes for reliability with some applications
- Handles shift states for characters like @, !, %, etc.
- Includes 15ms delay between keystrokes
- Not suitable for extremely fast typing simulation

---

## Window Management

### focus(windowTitle)

Brings window to foreground and gives it focus.

**Parameters:**

- `windowTitle` (string) - Window title or class name to find

**Example:**

```lua
focus("Notepad")
```

**Notes:**

- Searches for a window with the specified title or class name and attempts to bring it to the foreground
- Tries two search methods:
    1. By window title (caption)
    2. By window class name
- Uses FindWindow() with NULL class name, then with NULL window name
- Shows window with SW_RESTORE if minimized
- May fail due to Windows security restrictions on foreground changes

!!! warning
    - Some applications block foreground window changes for security
    - UWP/Store apps may not be accessible with this method

---

## Timing Functions

### wait(seconds)

Pauses script execution (seconds).

**Parameters:**

- `seconds` (number) - Time to wait in seconds (can be fractional)

**Example:**

```lua
wait(1.5)
```

---

### sleep(milliseconds)

Pauses script execution (milliseconds).

**Parameters:**

- `milliseconds` (number) - Time to wait in milliseconds

**Example:**

```lua
sleep(500)
```

---

### set_interval(ms, callback, [targetWindow])

Sets a repeating timer.

**Parameters:**

- `ms` (number) - Interval in milliseconds between callback executions
- `callback` (function) - Lua function to call when timer ticks
- `targetWindow` (string, optional) - Optional window title for context-sensitive timers

**Example:**

```lua
set_interval(1000, function() 
    log("Tick") 
end, "Notepad")
```

**Notes:**

- If targetWindow is specified, the callback will only execute when that window is active
- If empty, the timer will execute regardless of active window

---

## Mouse Control

### mouse_move(x, y)

Moves cursor to X, Y coordinates.

**Parameters:**

- `x` (number) - X coordinate (0 = left edge, screen width = right edge)
- `y` (number) - Y coordinate (0 = top edge, screen height = bottom edge)

**Example:**

```lua
mouse_move(1920, 1080)
```

**Notes:**

- Moves cursor instantly to specified position using absolute coordinates
- Coordinates are transformed to Windows' virtual screen space (0-65535)
- Uses MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE flags
- Coordinates outside screen bounds are clamped by Windows

---

### mouse_click(button)

Clicks mouse button.

**Parameters:**

- `button` (number) - Button to click
    - `0` = left
    - `1` = right
    - `2` = middle

**Example:**

```lua
mouse_click(0)  -- Left click
mouse_click(1)  -- Right click
mouse_click(2)  -- Middle click
```

**Notes:**

- Simulates pressing and immediately releasing the specified mouse button
- Includes both down and up events for complete click simulation

---

### mouse_pos()

Returns current mouse position.

**Returns:**

- Lua table with `{x = number, y = number}`

**Example:**

```lua
local p = mouse_pos()
```

**Notes:**

- Returns the current cursor position in screen coordinates
- Position is relative to the primary monitor
