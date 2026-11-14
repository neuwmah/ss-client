#include <windows.h>
#include <tlhelp32.h>
#include "resource.h"

#define PROCESS_NAME "MixMaster.exe"

static int Inject(DWORD pid, const char *dllPath) {
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProc) return 0;

    size_t len = lstrlenA(dllPath) + 1;
    LPVOID remote = VirtualAllocEx(hProc, NULL, len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!remote) {
        CloseHandle(hProc);
        return 0;
    }

    WriteProcessMemory(hProc, remote, dllPath, len, NULL);

    HANDLE hThread = CreateRemoteThread(
        hProc, NULL, 0,
        (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"),
        remote, 0, NULL
    );

    if (hThread) {
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);
    }

    VirtualFreeEx(hProc, remote, 0, MEM_RELEASE);
    CloseHandle(hProc);
    return hThread != NULL;
}

static int ExtractDll(char *outPath, DWORD outPathSize) {
    HRSRC hRes = FindResourceA(NULL, MAKEINTRESOURCEA(IDR_SS_DLL), RT_RCDATA);
    if (!hRes) return 0;

    HGLOBAL hData = LoadResource(NULL, hRes);
    if (!hData) return 0;

    void *pData = LockResource(hData);
    DWORD size = SizeofResource(NULL, hRes);
    if (!pData || !size) return 0;

    char tempDir[MAX_PATH];
    GetTempPathA(MAX_PATH, tempDir);
    if ((DWORD)(lstrlenA(tempDir) + 6) >= outPathSize) return 0;
    lstrcpyA(outPath, tempDir);
    lstrcatA(outPath, "ss.dll");

    HANDLE hFile = CreateFileA(outPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return 0;

    DWORD written;
    BOOL ok = WriteFile(hFile, pData, size, &written, NULL);
    CloseHandle(hFile);
    return ok && written == size;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    char dllPath[MAX_PATH];
    if (!ExtractDll(dllPath, sizeof(dllPath))) {
        MessageBoxW(NULL, L"SS Client already injected.", L".dll", MB_OK | MB_ICONERROR);
        return 1;
    }

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Process error.", L".dll", MB_OK | MB_ICONERROR);
        return 1;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);
    int found = 0;
    int ok = 0;

    if (Process32First(snap, &pe)) {
        do {
            if (lstrcmpiA(pe.szExeFile, PROCESS_NAME) == 0) {
                found++;
                if (Inject(pe.th32ProcessID, dllPath))
                    ok++;
            }
        } while (Process32Next(snap, &pe));
    }

    CloseHandle(snap);

    if (found == 0)  MessageBoxW(NULL, L"MixMaster.exe not found.", L".dll", MB_OK | MB_ICONWARNING);
    else if (ok > 0) MessageBoxW(NULL, L"SS Client by 2014\nPress DEL key to toggle ON/OFF", L".dll", MB_OK | MB_ICONINFORMATION);
    else             MessageBoxW(NULL, L"Internal error.", L".dll", MB_OK | MB_ICONERROR);

    return ok > 0 ? 0 : 1;
}
