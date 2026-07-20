#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>

#include "address.h"
#include "include.h"

#include "runtime/data.c"

#include "hook/chat.c"
#include "hook/potion.c"

#include "runtime/setup.c"

#include "runtime/check/loginmessage.c"
#include "runtime/check/chatcommands.c"
#include "runtime/check/gamewindow.c"
#include "runtime/check/hackon.c"

#include "runtime/command/f1f9.c"
#include "runtime/command/f10.c"
#include "runtime/command/delay.c"

#include "runtime/read/itemstable.c"
#include "runtime/read/itemshotbar.c"

DWORD WINAPI by2014(LPVOID lpParam) {
    while (TRUE) {
        CheckLoginMessage();
        CheckChatCommands();
        CheckGameWindow();
        CheckHack();
        Sleep(33); 
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(NULL, 0, by2014, NULL, 0, NULL);
    return TRUE;
}