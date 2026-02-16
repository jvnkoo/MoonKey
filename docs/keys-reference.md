# Key & Modifier Reference

## Modifiers (MOD)

Available in Lua as `MOD`. Used as the first argument in `bind()`.
Modifiers can be combined using `+` operator.

| Constant | Value | Description |
|:---------|:------|:------------|
| `MOD.NONE` | 0 | No modifier |
| `MOD.ALT` | MOD_ALT | Alt key |
| `MOD.CTRL` | MOD_CONTROL | Control key |
| `MOD.SHIFT` | MOD_SHIFT | Shift key |
| `MOD.WIN` | MOD_WIN | Windows key |
| `MOD.NOREPEAT` | 0x4000 | Prevents repeated hotkey triggers |

### Usage Examples:

```lua
bind(MOD.ALT, KEY.F1, function() end)           -- Alt + F1
bind(MOD.CTRL + MOD.SHIFT, KEY.T, function() end) -- Ctrl + Shift + T
bind(MOD.WIN, KEY.R, function() end)             -- Windows + R
```

---

## Virtual Keys (KEY)

Available in Lua as `KEY`. Used in `send()` and as the second argument in `bind()`.

### Letters and Numbers

- **Letters:** `KEY.A` through `KEY.Z`
- **Numbers:** `KEY.N0` through `KEY.N9` (top row)
- **Numpad:** `KEY.NUM0` through `KEY.NUM9`

### Function Keys

- `KEY.F1` through `KEY.F24`

### Navigation Keys

| Key | Description |
|:----|:------------|
| `KEY.UP`, `KEY.DOWN` | Arrow keys |
| `KEY.LEFT`, `KEY.RIGHT` | Arrow keys |
| `KEY.HOME`, `KEY.END` | Home/End |
| `KEY.PAGEUP`, `KEY.PAGEDOWN` | Page Up/Down |

### Special Keys

| Key | Description |
|:----|:------------|
| `KEY.ENTER`, `KEY.SPACE` | Enter and Space |
| `KEY.ESCAPE`, `KEY.TAB` | Escape and Tab |
| `KEY.BACKSPACE`, `KEY.DELETE` | Backspace and Delete |
| `KEY.INSERT` | Insert key |

### Mouse Buttons

| Key | Description |
|:----|:------------|
| `KEY.LBUTTON` | Left mouse button |
| `KEY.RBUTTON` | Right mouse button |
| `KEY.MBUTTON` | Middle mouse button |

### Modifier Keys (Individual)

| Key | Description |
|:----|:------------|
| `KEY.LSHIFT`, `KEY.RSHIFT` | Left/Right Shift |
| `KEY.LCTRL`, `KEY.RCTRL` | Left/Right Control |
| `KEY.LALT`, `KEY.RALT` | Left/Right Alt |
| `KEY.LWIN`, `KEY.RWIN` | Left/Right Windows |

### Numpad Operations

| Key | Description |
|:----|:------------|
| `KEY.MULTIPLY`, `KEY.DIVIDE` | * and / |
| `KEY.ADD`, `KEY.SUBTRACT` | + and - |
| `KEY.DECIMAL` | Decimal point |

### Lock Keys

| Key | Description |
|:----|:------------|
| `KEY.CAPSLOCK` | Caps Lock |
| `KEY.NUMLOCK` | Num Lock |
| `KEY.SCROLLLOCK` | Scroll Lock |
