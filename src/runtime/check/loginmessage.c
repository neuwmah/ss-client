void CheckLoginMessage() {
    wchar_t* lastChatMessage = (wchar_t*)CHAT_LAST_MESSAGE;
    if (wcscmp(lastChatMessage, L"Help : /h, /help") != 0) return;
    wcscpy(lastChatMessage, L"");
    
    LogToChat("SS Client by 2014", CHAT_COLOR_PURPLE);
    LogToChat("discord.gg/mixmaster", CHAT_COLOR_PINK);
}