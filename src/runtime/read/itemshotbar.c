static int GetPotionById(int id, int* list, int count) {
    for (int i = 0; i < count; i++)
        if (list[i] == id) return 1;
    return 0;
}

void ReadItemsHotbar() {
    countHotbarHP = 0;
    countHotbarMP = 0;
    for (int i = 0; i < 10; i++) {
        hotbarHP[i] = 0;
        hotbarMP[i] = 0;
    }

    for (int slot = 0; slot < 10; slot++) {
        uintptr_t baseAddress = BASE_ITEMS_HOTBAR + (slot * 0x08);
        char hasItem = *(char*)(baseAddress + 0x04);
        if (hasItem != 1) continue;
        
        short itemID = *(short*)baseAddress;

        if (GetPotionById(itemID, potionsHP, countHP)) {
            hotbarHP[countHotbarHP] = slot;
            countHotbarHP++;
            continue;
        }
        
        if (GetPotionById(itemID, potionsMP, countMP)) {
            hotbarMP[countHotbarMP] = slot;
            countHotbarMP++;
            continue;
        }
    }
}