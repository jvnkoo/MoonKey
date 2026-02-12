#pragma once
/**
 * @brief Directory monitoring for hot-reload functionality
 * @ingroup internal
 * 
 * Monitors a directory for file changes using Windows ReadDirectoryChangesW API.
 * Triggers reload events when Lua scripts are modified.
 */

#include <string>
#include <winrt/Windows.Foundation.h>
#include <windows.h>
#include <iostream>
#include "EventDispatcher.hpp"

/**
 * @struct Directory
 * @brief Static class for directory change monitoring
 * 
 * Runs in a dedicated thread to monitor file system changes without
 * blocking the main application thread.
 */
struct Directory {
    /**
     * @brief Monitor directory for changes
     * @param directoryPath Directory to monitor (wide string)
     * @param eventDispatcher Event dispatcher for change notifications
     * 
     * Continuously monitors the specified directory for file modifications
     * and creation/deletion events. When changes are detected, dispatches
     * "OnDirectoryChange" event.
     * 
     * @note Runs in an infinite loop - should be executed in a separate thread
     * @note Only monitors for FILE_NOTIFY_CHANGE_LAST_WRITE and FILE_NOTIFY_CHANGE_FILE_NAME events
     * 
     * @warning Uses blocking I/O - ensure directory path is valid
     * @warning High-frequency file changes may cause event storms
     */
    static void DirectoryChangesLoop(winrt::hstring directoryPath, EventDispatcher& eventDispatcher) {
        HANDLE hDir = CreateFileW(
            directoryPath.c_str(),
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS,
            NULL
        );

        if (hDir == INVALID_HANDLE_VALUE) {
            std::wcerr << L"[Directory] Failed to open directory: " << directoryPath << std::endl;
            return;
        }

        // Buffer for change notifications (aligned for DWORD access)
        alignas(DWORD) BYTE buffer[1024];
        DWORD bytesReturned;

        std::wcout << L"[Directory] Monitoring: " << directoryPath << std::endl;

        // Main monitoring loop
        while(true) {
            if (ReadDirectoryChangesW(
                hDir,                   // Directory handle
                buffer,                 // Output buffer
                sizeof(buffer),         // Buffer size
                FALSE,                  // Watch subdirectory (FALSE = only this directory)
                FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME,
                &bytesReturned,         // Bytes returned
                NULL,                   // Overlapped (NULL = synchronous)
                NULL                    // Completion routine
            )) {
                if (bytesReturned > 0) {
                    std::wcout << L"[Directory] Change detected in " 
                              << std::wstring(directoryPath) << std::endl;
                    eventDispatcher.dispatch("OnDirectoryChange");
                }
            } else {
                DWORD error = GetLastError();
                std::wcerr << L"[Directory] Monitoring error: " << error 
                          << L" for path: " << directoryPath << std::endl;
                break; 
            }
        }
        
        CloseHandle(hDir);
        std::wcout << L"[Directory] Stopped monitoring: " << directoryPath << std::endl;
    }
};