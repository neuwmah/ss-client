ServerAddrs ADDR;

static const ServerAddrs addrs_au =
#include "../address/au.h"
;

static const ServerAddrs addrs_pv =
#include "../address/pv.h"
;

static const ServerAddrs addrs_fr =
#include "../address/fr.h"
;

static int ServerMarkerSet(uintptr_t marker) {
    char *s = (char *)(uintptr_t)marker;
    return s != NULL && s[0] != '\0';
}

static void NopHotbarClickLog(void) {
    DWORD oldProtect;
    BYTE *p = (BYTE *)NOP_CHAT_MSG;
    if (!VirtualProtect(p, 33, PAGE_EXECUTE_READWRITE, &oldProtect))
        return;
    for (int i = 0; i < 33; i++)
        p[i] = 0x90;
    VirtualProtect(p, 33, oldProtect, &oldProtect);
}

static void ApplyServer(const ServerAddrs *src) {
    ADDR = *src;

    hookGameInterface = (callUi)CALL_GAME_INTERFACE;
    hookChatMessage   = (callChat)CALL_CHAT_MESSAGE;
    heroConnected     = (unsigned char *)HERO_ON;

    gameUnits[0] = (struct GameUnit){ 0x3C, HERO_HP,    HERO_MP,    HERO_HP_MAX,    HERO_MP_MAX, 0 };
    gameUnits[1] = (struct GameUnit){ 0x38, HENCH_1_HP, HENCH_1_MP, HENCH_1_HP_MAX, HENCH_1_MP_MAX, HENCH_1_FLAG };
    gameUnits[2] = (struct GameUnit){ 0x34, HENCH_2_HP, HENCH_2_MP, HENCH_2_HP_MAX, HENCH_2_MP_MAX, HENCH_2_FLAG };
    gameUnits[3] = (struct GameUnit){ 0x30, HENCH_3_HP, HENCH_3_MP, HENCH_3_HP_MAX, HENCH_3_MP_MAX, HENCH_3_FLAG };

    NopHotbarClickLog();
}

int DetectServer(void) {
    if (ServerMarkerSet(AU_ADDRESS)) {
        ApplyServer(&addrs_au);
        return 1;
    }
    if (ServerMarkerSet(PV_ADDRESS)) {
        ApplyServer(&addrs_pv);
        return 1;
    }
    if (ServerMarkerSet(FR_ADDRESS)) {
        ApplyServer(&addrs_fr);
        return 1;
    }
    return 0;
}