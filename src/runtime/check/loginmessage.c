void CheckLoginMessage() {
    wchar_t* lastChatMessage = (wchar_t*)CHAT_LAST_MESSAGE;
    if (wcscmp(lastChatMessage, L"Help : /h, /help") != 0) return;
    wcscpy(lastChatMessage, L"");
    
    LogToChat("SS Client by 2014", 0xEB7AEB);
    LogToChat("Help: !delay", 0xED88ED);
    LogToChat("Usage: !key value", 0xEF93EF);
    LogToChat("Discord: discord.gg/mixmaster", 0xF4AEF2);
    LogToChat("Press DEL key to enable.", 0xF6B9F6);
    
    ReadItemsTable();
}