-- Simple log test
log_info("MoonKey script initialized!")

-- Register Alt + H
-- We use MOD.ALT and KEY.H from our new tables
register_hotkey(MOD.ALT, KEY.H, function()
    log_info("Hotkey Alt+H pressed! Executing logic...")
end)

-- Register Ctrl + G
register_hotkey(MOD.CTRL, KEY.G, function()
    log_info("Hotkey Ctrl+G pressed! Hello from Lua!")
end)

-- To simulate Ctrl+G, we press them sequentially 
simulate_key_press(KEY.G)

-- Open Start Menu (Windows Key)
simulate_key_press(KEY.LWIN)

log_info("Setup complete. Waiting for hotkeys...")