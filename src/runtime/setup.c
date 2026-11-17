void Setup() {
    hackON = !hackON;
    if (!hackON) {
        LogToChat("2014 OFF", CHAT_COLOR_PINK);
        return;
    }
    
    ReadItemsHotbar();
    if (countHotbarHP == 0 && countHotbarMP == 0) {
        LogToChat("Please set potions and try again.", CHAT_COLOR_PURPLE);
        hackON = !hackON;
        return;
    }
    
    LogToChat("2014 ON", CHAT_COLOR_PURPLE);
}