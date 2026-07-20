void CommandF1F9() {
    if (strlen(lastCommand) <= 4) return;

    char cmd[32];
    sprintf(cmd, "> %s", lastCommand);
    LogToChat(cmd, CHAT_COLOR_PURPLE);

    char* delay = lastCommand + 4;
    DWORD delayValue = atoi(delay);
    int idx = lastCommand[2] - '0' - 1;
    healDelay[idx] = delayValue;

    char msg[32];
    sprintf(msg, "~ F%d key delay set to %dms.", idx + 1, healDelay[idx]);
    LogToChat(msg, CHAT_COLOR_PINK);
}