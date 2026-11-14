typedef void (__stdcall *callUi)(int arg1, int arg2, int arg3);
callUi hookGameInterface = (callUi)CALL_GAME_INTERFACE;

void AutoPotionHP(int target, unsigned short currentHP, unsigned short maxHP) {
    if (currentHP == maxHP) return;

    for (int i = 0; i < countHotbarHP; i++) {
        char* pointerStatus = (char*)POINTER_STATUS;
        if (*pointerStatus == 8) return;

        int index = hotbarHP[i];
        
        DWORD indexDelay    = healDelay[index];
        DWORD indexLastHeal = lastHealTime[index];
        if (currentTime - indexLastHeal < indexDelay) continue;
        lastHealTime[index] = currentTime;

        int hotbarKey = 0x1D + index;
        hookGameInterface(hotbarKey, 1, 0x201);
        hookGameInterface(gameUnits[target].targetId, 1, 0x202);

        wchar_t* lastChatMessage = (wchar_t*)CHAT_LAST_MESSAGE;
        swprintf(lastChatMessage, 256, L"~ HP F%d", index + 1);
        *(DWORD*)CHAT_LAST_COLOR = CHAT_COLOR_PURPLE;

        Sleep(33);
    }
}

void AutoPotionMP(int target, unsigned short currentMP, unsigned short maxMP) {
    if (currentMP == maxMP) return;

    for (int i = 0; i < countHotbarMP; i++) {
        char* pointerStatus = (char*)POINTER_STATUS;
        if (*pointerStatus == 8) return;

        int index = hotbarMP[i];
        
        DWORD indexDelay    = healDelay[index];
        DWORD indexLastHeal = lastHealTime[index];
        if (currentTime - indexLastHeal < indexDelay) continue;
        lastHealTime[index] = currentTime;

        int hotbarKey = 0x1D + index;
        hookGameInterface(hotbarKey, 1, 0x201);
        hookGameInterface(gameUnits[target].targetId, 1, 0x202);

        wchar_t* lastChatMessage = (wchar_t*)CHAT_LAST_MESSAGE;
        swprintf(lastChatMessage, 256, L"~ MP F%d", index + 1);
        *(DWORD*)CHAT_LAST_COLOR = CHAT_COLOR_PURPLE;

        Sleep(33);
    }
}