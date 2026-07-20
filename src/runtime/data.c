BOOL keyENTER = FALSE;
BOOL keyDEL   = FALSE;
BOOL hackON   = FALSE;

struct GameUnit {
    int targetId;
    uintptr_t hpAddr, mpAddr, maxHpAddr, maxMpAddr;
    uintptr_t flagAddr;
};

struct GameUnit gameUnits[4] = {
    { 0x3C, HERO_HP,    HERO_MP,    HERO_HP_MAX,    HERO_MP_MAX },
    { 0x38, HENCH_1_HP, HENCH_1_MP, HENCH_1_HP_MAX, HENCH_1_MP_MAX, HENCH_1_FLAG },
    { 0x34, HENCH_2_HP, HENCH_2_MP, HENCH_2_HP_MAX, HENCH_2_MP_MAX, HENCH_2_FLAG },
    { 0x30, HENCH_3_HP, HENCH_3_MP, HENCH_3_HP_MAX, HENCH_3_MP_MAX, HENCH_3_FLAG }
};

int potionsHP[500], countHP       = 0;
int hotbarHP[10],   countHotbarHP = 0;
int potionsMP[500], countMP       = 0;
int hotbarMP[10],   countHotbarMP = 0;

DWORD healDelay[10]    = {300, 300, 300, 300, 300, 300, 300, 300, 300, 300};
DWORD lastHealTime[10] = {0};
DWORD currentTime      = 0;

char lastCommand[256];