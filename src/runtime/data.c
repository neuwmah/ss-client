BOOL keyENTER = FALSE;
BOOL keyDEL   = FALSE;
BOOL hackON   = FALSE;

struct GameUnit {
    int targetId;
    uintptr_t hpAddr, mpAddr, maxHpAddr, maxMpAddr;
    uintptr_t flagAddr;
};

struct GameUnit gameUnits[4];

int potionsHP[500], countHP       = 0;
int hotbarHP[10],   countHotbarHP = 0;
int potionsMP[500], countMP       = 0;
int hotbarMP[10],   countHotbarMP = 0;

DWORD healDelay[10]    = {300, 300, 300, 300, 300, 300, 300, 300, 300, 300};
DWORD lastHealTime[10] = {0};
DWORD currentTime      = 0;

char lastCommand[256];

int connection = 0;
unsigned char* heroConnected = NULL;