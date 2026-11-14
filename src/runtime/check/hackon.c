void CheckHack() {
    if (!hackON) return;

    char* pointerStatus = (char*)POINTER_STATUS;
    if (*pointerStatus == 8) return;
    
    int lowerHPindex     = -1;
    int lowerMPindex     = -1;
    unsigned short lowerHPcurrent =  0;
    unsigned short lowerHPmax     =  0;
    unsigned short lowerMPcurrent =  0;
    unsigned short lowerMPmax     =  0;
    for (int index = 0; index < 4; index++) {

        int isHench       = index > 0;
        int henchEquipped = isHench ? *(uintptr_t*)gameUnits[index].flagAddr : 0;
        if (isHench && !henchEquipped) continue;

        unsigned short currentHP = *(unsigned short*)gameUnits[index].hpAddr;
        unsigned short maxHP     = *(unsigned short*)gameUnits[index].maxHpAddr;
        unsigned short currentMP = *(unsigned short*)gameUnits[index].mpAddr;
        unsigned short maxMP     = *(unsigned short*)gameUnits[index].maxMpAddr;
        
        if (currentHP == 0) {
            if (index == 0) Setup();
            continue;
        }

        if (currentHP < maxHP) {
            if (lowerHPindex != -1 && currentHP > lowerHPcurrent) continue;
            lowerHPindex = index;
            lowerHPcurrent = currentHP;
            lowerHPmax = maxHP;
        }

        if (currentMP < maxMP) {
            if (lowerMPindex != -1 && currentMP > lowerMPcurrent) continue;
            lowerMPindex = index;
            lowerMPcurrent = currentMP;
            lowerMPmax = maxMP;
        }
    }

    currentTime = GetTickCount();
    if (lowerHPindex != -1) 
        AutoPotionHP(lowerHPindex, lowerHPcurrent, lowerHPmax);
    if (lowerMPindex != -1) 
        AutoPotionMP(lowerMPindex, lowerMPcurrent, lowerMPmax);
}