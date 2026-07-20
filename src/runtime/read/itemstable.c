void ReadItemsTable() {
    countHP = 0;
    countMP = 0;
    
    uintptr_t itemTableBase = BASE_ITEMS_TABLE; 
    for (int id = 1; id < 10000; id++) {
        int iVar9 = id * 0x538;
        
        short itemIDMemory = *(short*)(itemTableBase + 0x02 + iVar9); 
        if (itemIDMemory < 1) continue;
        
        char itemTarget = *(char*)(itemTableBase + 0x112 + iVar9);
        char itemType   = *(char*)(itemTableBase + 0x113 + iVar9);
        if (itemTarget != 1) continue;
        if (itemType != 2) continue;

        char* itemName = (char*)(itemTableBase + 0x04  + iVar9);
        char* shuxing  = (char*)(itemTableBase + 0x12C + iVar9);
        char* shuoming = (char*)(itemTableBase + 0x22C + iVar9);
        
        BOOL isHP = StrStrIA(shuxing, "hp") != NULL || StrStrIA(shuoming, "hp") != NULL;
        if (isHP) {
            if (countHP >= 500) continue;
            potionsHP[countHP] = id;
            countHP++;
            continue;
        }

        BOOL isMP = StrStrIA(shuxing, "mp") != NULL || StrStrIA(shuoming, "mp") != NULL;
        if (isMP) {
            if (countMP >= 500) continue;
            potionsMP[countMP] = id;
            countMP++;
            continue;
        }
    }
}