#pragma once
#include <string>
#include <winrt/Windows.Foundation.h>
#include <windows.h>
#include <iostream>
#include "../utils/EventDispatcher.hpp"

// Directory monitoring for hot-reload functionality
// Monitors a directory for file changes using Windows ReadDirectoryChangesW API
// Triggers reload events when Lua scripts are modified
struct Directory {
    // Monitor directory for changes
    // directoryPath: Directory to monitor (wide string)
    // eventDispatcher: Event dispatcher for change notifications
    // Runs in a dedicated thread to monitor file system changes without
    // blocking the main application thread
    static void DirectoryChangesLoop(winrt::hstring directoryPath, EventDispatcher& eventDispatcher);
};