void CommandDelay() {
    LogToChat("> !delay", CHAT_COLOR_PURPLE);
    
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