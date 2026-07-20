void CheckChatCommands() {
    char* currentChat = (char*)CHAT_LAST_COMMAND;
    if (strlen(currentChat) > 0)
        strncpy(lastCommand, currentChat, sizeof(lastCommand) - 1);

    if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
        if (keyENTER) return;
        keyENTER = TRUE;
        
        if (strlen(lastCommand) == 0) return;

        BOOL cmdf1f9 = strncmp(lastCommand, "!f1 ", 4) == 0 || strncmp(lastCommand, "!f2 ", 4) == 0 || strncmp(lastCommand, "!f3 ", 4) == 0 || 
                       strncmp(lastCommand, "!f4 ", 4) == 0 || strncmp(lastCommand, "!f5 ", 4) == 0 || strncmp(lastCommand, "!f6 ", 4) == 0 || 
                       strncmp(lastCommand, "!f7 ", 4) == 0 || strncmp(lastCommand, "!f8 ", 4) == 0 || strncmp(lastCommand, "!f9 ", 4) == 0;
        if (cmdf1f9)
            CommandF1F9();

        BOOL cmdf10 = strncmp(lastCommand, "!f10 ", 5) == 0;
        if (cmdf10)
            CommandF10();

        BOOL cmddelay = strcmp(lastCommand, "!delay") == 0;
        if (cmddelay)
            CommandDelay();

        memset(lastCommand, 0, sizeof(lastCommand));
        lastCommand[0] = '\0';

    } else keyENTER = FALSE;
}