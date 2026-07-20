// SS Client by 2014 🐰
// 13/03/2026

#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>

#define CHAR_HP 0x00891A68
#define CHAR_HP_MAX 0x00891A6C
#define CHAR_MP 0x00891A6A
#define CHAR_MP_MAX 0x00891A6E

#define HENCH_1_HP 0x00896F4C
#define HENCH_1_HP_MAX 0x00896F50
#define HENCH_1_MP 0x00896F4E
#define HENCH_1_MP_MAX 0x00896F52
#define HENCH_1_FLAG 0x00896DF4

#define HENCH_2_HP 0x00897144
#define HENCH_2_HP_MAX 0x00897148
#define HENCH_2_MP 0x00897146
#define HENCH_2_MP_MAX 0x0089714A
#define HENCH_2_FLAG 0x00896FEC

#define HENCH_3_HP 0x0089733C
#define HENCH_3_HP_MAX 0x00897340
#define HENCH_3_MP 0x0089733E
#define HENCH_3_MP_MAX 0x00897342
#define HENCH_3_FLAG 0x008971E4

struct GameUnit {
    int targetId;
    uintptr_t hpAddr;
    uintptr_t mpAddr;
    uintptr_t maxHpAddr;
    uintptr_t maxMpAddr;
    uintptr_t flagAddr;
};

struct GameUnit gameUnits[4] = {
    { 0x3c, CHAR_HP,    CHAR_MP,    CHAR_HP_MAX,    CHAR_MP_MAX },
    { 0x38, HENCH_1_HP, HENCH_1_MP, HENCH_1_HP_MAX, HENCH_1_MP_MAX, HENCH_1_FLAG },
    { 0x34, HENCH_2_HP, HENCH_2_MP, HENCH_2_HP_MAX, HENCH_2_MP_MAX, HENCH_2_FLAG },
    { 0x30, HENCH_3_HP, HENCH_3_MP, HENCH_3_HP_MAX, HENCH_3_MP_MAX, HENCH_3_FLAG }
};

typedef void (__stdcall *MMAPI)(int arg1, int arg2, int arg3);
MMAPI gamePotion = (MMAPI)0x004925f0;

typedef void (__thiscall *tChat)(void* pChatStruct, LPCSTR text, int color, int type);
tChat Chat = (tChat)0x00432880;
void* pChat = (void*)0x005D40D0; 

int potionsHP[500];
int countHP = 0;
int hotbarHP[10];
int countHotbarHP = 0;

int potionsMP[500];
int countMP = 0;
int hotbarMP[10];
int countHotbarMP = 0;

DWORD lastHealTime[10] = {0};
DWORD healDelay[10] = {300, 300, 300, 300, 300, 300, 300, 300, 300, 300};

char shadowChat[256] = "";
BOOL keyENTER = FALSE;
BOOL keyDEL = FALSE;
BOOL hackON = FALSE;

int GetPotionById(int id, int* list, int count) {
    for (int i = 0; i < count; i++)
        if (list[i] == id) return 1;
    return 0;
}

void LogToChat(const char* message, int color) {
    if (pChat != NULL) Chat(pChat, message, color, 0);
}

void ReadItemsTable() {
    countHP = 0;
    countMP = 0;
    
    uintptr_t itemTableBase = 0x00d2e5c8; 
    for (int id = 1; id < 10000; id++) {
        int iVar9 = id * 0x538;
        
        short itemIDMemory = *(short*)(itemTableBase + 0x02 + iVar9); 
        if (itemIDMemory > 0) {
            unsigned char itemTarget = *(unsigned char*)(itemTableBase + 0x112 + iVar9);
            unsigned char itemType = *(unsigned char*)(itemTableBase + 0x113 + iVar9);

            if (itemTarget == 1 && itemType == 2) {
                char* itemName = (char*)(itemTableBase + 0x04 + iVar9);
                char* shuxing = (char*)(itemTableBase + 0x12C + iVar9);
                char* shuoming = (char*)(itemTableBase + 0x22C + iVar9);
                
                if (StrStrIA(shuxing, "hp") != NULL || StrStrIA(shuoming, "hp") != NULL) {
                    if (countHP < 500) {
                        potionsHP[countHP] = id;
                        countHP++;
                    }
                }
                else if (StrStrIA(shuxing, "mp") != NULL || StrStrIA(shuoming, "mp") != NULL) {
                    if (countMP < 500) {
                        potionsMP[countMP] = id;
                        countMP++;
                    }
                }
            }
        }
    }
}

void ReadItemsHotbar() {
    for (int i = 0; i < 10; i++) {
        hotbarHP[i] = 0;
        hotbarMP[i] = 0;
    }
    countHotbarHP = 0;
    countHotbarMP = 0;

    for (int slot = 0; slot < 10; slot++) {
        uintptr_t baseAddress = 0x00637000 + (slot * 8);
        unsigned char hasItem = *(unsigned char*)(baseAddress + 4);
        
        if (hasItem == 1) {
            unsigned short itemID = *(unsigned short*)baseAddress;

            if (GetPotionById(itemID, potionsHP, countHP)) {
                hotbarHP[countHotbarHP] = slot;
                countHotbarHP++;
            }
            else if (GetPotionById(itemID, potionsMP, countMP)) {
                hotbarMP[countHotbarMP] = slot;
                countHotbarMP++;
            }
        }
    }
}

void AutoPotionHP(int index, unsigned short currentHP, unsigned short maxHP, DWORD currentTime) {
    if (currentHP < maxHP) {
        for (int i = 0; i < countHotbarHP; i++) {
            int idx = hotbarHP[i];
            DWORD idxDelay = healDelay[idx];
            DWORD idxLastHeal = lastHealTime[idx];

            if (currentTime - idxLastHeal >= idxDelay) {
                lastHealTime[idx] = currentTime;

                int key = 0x1D + idx;
                gamePotion(key, 1, 0x201);
                gamePotion(gameUnits[index].targetId, 1, 0x202);

                wchar_t* lastChatMessage = (wchar_t*)0x005D84D0;
                swprintf(lastChatMessage, 256, L"~ HP F%d", idx + 1);
                *(DWORD*)0x005D87E0 = 0xEB7AEB;

                Sleep(33);
            }
        }
    }
}

void AutoPotionMP(int index, unsigned short currentMP, unsigned short maxMP, DWORD currentTime) {
    if (currentMP < maxMP) {
        for (int i = 0; i < countHotbarMP; i++) {
            int idx = hotbarMP[i];
            DWORD idxDelay = healDelay[idx];
            DWORD idxLastHeal = lastHealTime[idx];

            if (currentTime - idxLastHeal >= idxDelay) {
                lastHealTime[idx] = currentTime;

                int key = 0x1D + idx;
                gamePotion(key, 1, 0x201);
                gamePotion(gameUnits[index].targetId, 1, 0x202);

                wchar_t* lastChatMessage = (wchar_t*)0x005D84D0;
                swprintf(lastChatMessage, 256, L"~ MP F%d", idx + 1);
                *(DWORD*)0x005D87E0 = 0xEB7AEB;

                Sleep(33);
            }
        }
    }
}

void Setup() {
    hackON = !hackON;  
    if (hackON) {
        LogToChat("2014 ON", 0xEB7AEB);

        ReadItemsHotbar();
        if (countHotbarHP > 0 || countHotbarMP > 0) {
            if (countHotbarHP > 0) {
                char msgHP[256] = "[Auto Potion] HP";
                for (int i = 0; i < countHotbarHP; i++) {
                    int idx = hotbarHP[i] + 1;
                    char keyStr[16];
                    sprintf(keyStr, " F%d", idx);
                    strcat(msgHP, keyStr);
                }
                LogToChat(msgHP, 0xF099F0);
            }
            if (countHotbarMP > 0) {
                char msgMP[256] = "[Auto Potion] MP";
                for (int i = 0; i < countHotbarMP; i++) {
                    int idx = hotbarMP[i] + 1;
                    char keyStr[16];
                    sprintf(keyStr, " F%d", idx);
                    strcat(msgMP, keyStr);
                }
                LogToChat(msgMP, 0xF099F0);
            }
        } else LogToChat("[Auto Potion] Please set potions and try again.", 0xF099F0);
    } else LogToChat("2014 OFF", 0xEB7AEB);
}

void CheckLoginMessage() {
    wchar_t* lastChatMessage = (wchar_t*)0x005D84D0;
    if (wcscmp(lastChatMessage, L"Help : /h, /help") == 0) {
        wcscpy(lastChatMessage, L"");
        LogToChat("SS Client by 2014", 0xEB7AEB);
        LogToChat("Help: !delay", 0xED88ED);
        LogToChat("Usage: !key value", 0xEF93EF);
        LogToChat("Discord: discord.gg/mixmaster", 0xF4AEF2);
        LogToChat("Press DEL key to enable.", 0xF6B9F6);
        ReadItemsTable();
    }
}

void CheckChatCommands() {
    char* currentChat = (char*)0x01A1AD40;
    if (strlen(currentChat) > 0) strncpy(shadowChat, currentChat, sizeof(shadowChat) - 1);
    if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
        if (!keyENTER) {
            if (strlen(shadowChat) > 0) {

                if (strncmp(shadowChat, "!f1 ", 4) == 0
                 || strncmp(shadowChat, "!f2 ", 4) == 0
                 || strncmp(shadowChat, "!f3 ", 4) == 0
                 || strncmp(shadowChat, "!f4 ", 4) == 0
                 || strncmp(shadowChat, "!f5 ", 4) == 0
                 || strncmp(shadowChat, "!f6 ", 4) == 0
                 || strncmp(shadowChat, "!f7 ", 4) == 0
                 || strncmp(shadowChat, "!f8 ", 4) == 0
                 || strncmp(shadowChat, "!f9 ", 4) == 0
                ) {
                    if (strlen(shadowChat) > 4) {
                        char cmd[32];
                        sprintf(cmd, "> %s", shadowChat);
                        LogToChat(cmd, 0xEB7AEB);

                        char* delay = shadowChat + 4;
                        DWORD delayValue = atoi(delay);
                        int idx = shadowChat[2] - '0' - 1;
                        healDelay[idx] = delayValue;

                        char msg[32];
                        sprintf(msg, "~ F%d key delay set to %dms.", idx + 1, healDelay[idx]);
                        LogToChat(msg, 0xF099F0);
                    }
                }

                if (strncmp(shadowChat, "!f10 ", 5) == 0) {
                    if (strlen(shadowChat) > 5) {
                        char cmd[32];
                        sprintf(cmd, "> %s", shadowChat);
                        LogToChat(cmd, 0xEB7AEB);

                        char* delay = shadowChat + 5;
                        DWORD delayValue = atoi(delay);
                        healDelay[9] = delayValue;

                        char msg[32];
                        sprintf(msg, "~ F10 key delay set to %dms.", healDelay[9]);
                        LogToChat(msg, 0xF099F0);
                    }
                }

                if (strcmp(shadowChat, "!delay") == 0) {
                    LogToChat("> !delay", 0xEB7AEB);
                    
                    DWORD fadeColors[10] = { 
                        0xEC84EC, 0xED88ED, 0xEE8FEE, 0xEF93EF, 0xF099F0, 
                        0xF2A4F2, 0xF4AEF4, 0xF6B9F6, 0xF8C3F8, 0xFACDFA
                    };

                    for (int i = 0; i < 10; i++) {
                        char msg[32];
                        DWORD color = fadeColors[i];
                        if (i < 9) {
                            sprintf(msg, "~ F%d %dms", i + 1, healDelay[i]);
                            LogToChat(msg, color);
                        } else {
                            sprintf(msg, "~ F10 %dms", healDelay[9]);
                            LogToChat(msg, color);
                        }
                    }
                }

                memset(shadowChat, 0, sizeof(shadowChat));
            }
            keyENTER = TRUE;
        }
    } 
    else keyENTER = FALSE;
    if (strlen(currentChat) == 0 && !keyENTER) shadowChat[0] = '\0';
}

void CheckGameWindow() {
    HWND foregroundWnd = GetForegroundWindow();
    DWORD foregroundProcID;
    GetWindowThreadProcessId(foregroundWnd, &foregroundProcID);
    if (foregroundProcID == GetCurrentProcessId()) {
        if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
            if (!keyDEL) {
                Setup();
                keyDEL = TRUE;
            }
        } else keyDEL = FALSE;
    }
}

void CheckHack() {
    unsigned char* pointerStatus = (unsigned char*)0x0062DBEC;
    if (hackON && *pointerStatus != 8) {
        DWORD currentTime = GetTickCount();
        int lowerHPindex = -1;
        int lowerMPindex = -1;
        unsigned short lowerHPcurrent = 0;
        unsigned short lowerHPmax = 0;
        unsigned short lowerMPcurrent = 0;
        unsigned short lowerMPmax = 0;

        for (int index = 0; index < 4; index++) {
            int isHench = index > 0;
            int idxHench = isHench ? index - 1 : -1;
            uintptr_t henchFlag = isHench ? *(uintptr_t*)gameUnits[index].flagAddr : 0;
            if (isHench && henchFlag != 1) continue;

            unsigned short currentHP = *(unsigned short*)gameUnits[index].hpAddr;
            unsigned short maxHP = *(unsigned short*)gameUnits[index].maxHpAddr;
            unsigned short currentMP = *(unsigned short*)gameUnits[index].mpAddr;
            unsigned short maxMP = *(unsigned short*)gameUnits[index].maxMpAddr;
            
            if (currentHP > 0) {
                BOOL needHealHP = currentHP < maxHP;
                BOOL needHealMP = currentMP < maxMP;

                if (needHealHP) {
                    if (lowerHPindex == -1 || currentHP < lowerHPcurrent) {
                        lowerHPindex = index;
                        lowerHPcurrent = currentHP;
                        lowerHPmax = maxHP;
                    }
                }
                if (needHealMP) {
                    if (lowerMPindex == -1 || currentMP < lowerMPcurrent) {
                        lowerMPindex = index;
                        lowerMPcurrent = currentMP;
                        lowerMPmax = maxMP;
                    }
                }
            }
            else if (index == 0) {
                hackON = FALSE;
                LogToChat("2014 OFF", 0xEB7AEB);
            }
        }

        if (lowerHPindex != -1) 
            AutoPotionHP(lowerHPindex, lowerHPcurrent, lowerHPmax, currentTime);
        if (lowerMPindex != -1) 
            AutoPotionMP(lowerMPindex, lowerMPcurrent, lowerMPmax, currentTime);
    }
}

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
