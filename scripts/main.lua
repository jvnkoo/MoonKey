-- log test
log("MoonKey script initialized!")

-- Alt + H
bind(MOD.ALT, KEY.H, function()
    log("Hotkey Alt+H pressed! Executing logic...")
end)

-- Ctrl + G
bind(MOD.CTRL, KEY.G, function()
    log("Hotkey Ctrl+G pressed! Hello from Lua!")
end)

send(KEY.G)

log("Start waiting")

wait (8.0)

log("end waiting")
-- Open Start Menu
send(KEY.LWIN)

log("Setup complete. Waiting for hotkeys...")