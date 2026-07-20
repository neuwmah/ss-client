void Setup() {
    hackON = !hackON;
    if (!hackON) {
        LogToChat("2014 OFF", CHAT_COLOR_PURPLE);
        return;
    } else LogToChat("2014 ON", CHAT_COLOR_PURPLE);
    
    ReadItemsHotbar();
    if (countHotbarHP == 0 && countHotbarMP == 0) {
        LogToChat("[Auto Potion] Please set potions and try again.", CHAT_COLOR_PINK);
        return;
    }

    if (countHotbarHP > 0) {
        char msgHP[256] = "[Auto Potion] HP";
        for (int i = 0; i < countHotbarHP; i++) {
            int index = hotbarHP[i] + 1;
            char keyStr[16];
            sprintf(keyStr, " F%d", index);
            strcat(msgHP, keyStr);
        }
        LogToChat(msgHP, CHAT_COLOR_PINK);
    }

    if (countHotbarMP > 0) {
        char msgMP[256] = "[Auto Potion] MP";
        for (int i = 0; i < countHotbarMP; i++) {
            int index = hotbarMP[i] + 1;
            char keyStr[16];
            sprintf(keyStr, " F%d", index);
            strcat(msgMP, keyStr);
        }
        LogToChat(msgMP, CHAT_COLOR_PINK);
    }
}