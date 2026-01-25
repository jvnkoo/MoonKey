-- Simple log test
log_info("MoonKey script initialized!")

-- Register Alt + H
register_hotkey(MOD_ALT, KEY_H, function()
    log_info("Hotkey Alt+H pressed! Executing logic...")
end)

simulate_key_press(KEY_CONTROL, KEY_G)

-- Register Ctrl + G
register_hotkey(MOD_CTRL, KEY_G, function()
    log_info("Hotkey Ctrl+G pressed! Hello from Lua!")
end)

simulate_key_press(KEY_LWIN)