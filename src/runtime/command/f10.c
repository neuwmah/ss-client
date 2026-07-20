void CommandF10() {
    if (strlen(lastCommand) <= 5) return;

    char cmd[32];
    sprintf(cmd, "> %s", lastCommand);
    LogToChat(cmd, CHAT_COLOR_PURPLE);

    char* delay = lastCommand + 5;
    DWORD delayValue = atoi(delay);
    healDelay[9] = delayValue;

    char msg[32];
    sprintf(msg, "~ F10 key delay set to %dms.", healDelay[9]);
    LogToChat(msg, CHAT_COLOR_PINK);
}