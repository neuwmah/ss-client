void CheckGameWindow() {
    HWND foregroundWnd = GetForegroundWindow();
    DWORD foregroundProcID;

    GetWindowThreadProcessId(foregroundWnd, &foregroundProcID);
    if (foregroundProcID != GetCurrentProcessId()) return;
    
    if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
        if (keyDEL) return;
        keyDEL = TRUE;
        
        Setup();

    } else keyDEL = FALSE;
}