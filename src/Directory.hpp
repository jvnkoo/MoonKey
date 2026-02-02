#pragma once
#include <string>
#include <winrt/Windows.Foundation.h>
#include <windows.h>
#include <iostream>
#include "EventDispatcher.hpp"

struct Directory {
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

        if (hDir == INVALID_HANDLE_VALUE) return;

        alignas(DWORD) BYTE buffer[1024];
        DWORD bytesReturned;

        while(true) {
            if (ReadDirectoryChangesW(
                hDir,
                buffer,
                sizeof(buffer),
                FALSE, 
                FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME,
                &bytesReturned,
                NULL,
                NULL
            )) {
                if (bytesReturned > 0) {
                    std::wcout << L"[Directory] Change detected in " << std::wstring(directoryPath) << std::endl;
                    eventDispatcher.dispatch("OnDirectoryChange");
                }
            } else {
                break; 
            }
        }
        CloseHandle(hDir);
    }
};