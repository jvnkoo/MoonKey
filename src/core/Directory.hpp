#pragma once
/**
 * @brief Directory monitoring for hot-reload functionality
 * @ingroup internal
 * * Monitors a directory for file changes using Windows ReadDirectoryChangesW API.
 * Triggers reload events when Lua scripts are modified.
 */

#include <string>
#include <winrt/Windows.Foundation.h>
#include <windows.h>
#include <iostream>
#include "../utils/EventDispatcher.hpp"

/**
 * @struct Directory
 * @brief Static class for directory change monitoring
 * * Runs in a dedicated thread to monitor file system changes without
 * blocking the main application thread.
 */
struct Directory {
    /**
     * @brief Monitor directory for changes
     * @param directoryPath Directory to monitor (wide string)
     * @param eventDispatcher Event dispatcher for change notifications
     */
    static void DirectoryChangesLoop(winrt::hstring directoryPath, EventDispatcher& eventDispatcher);
};