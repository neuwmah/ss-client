void CheckLoginMessage() {
    wchar_t* lastChatMessage4 = (wchar_t*)CHAT_LAST_MESSAGE_4;
    wchar_t* lastChatMessage3 = (wchar_t*)CHAT_LAST_MESSAGE_3;
    wchar_t* lastChatMessage2 = (wchar_t*)CHAT_LAST_MESSAGE_2;
    wchar_t* lastChatMessage1 = (wchar_t*)CHAT_LAST_MESSAGE;

    if (
        wcsstr(lastChatMessage1, L"Une Question ou un") != NULL ||
        wcsstr(lastChatMessage1, L"MixMaster vous souhaite un bon jeu") != NULL ||
        wcscmp(lastChatMessage1, L"Bon jeu !") == 0 ||
        wcscmp(lastChatMessage1, L"Help: /h, /help") == 0 ||
        wcscmp(lastChatMessage1, L"Help : /h, /help") == 0 ||
        wcscmp(lastChatMessage1, L"Ajuda : /h, /Ajuda") == 0 ||
        wcscmp(lastChatMessage1, L"Ajuda : /h, /help") == 0 ||
        wcscmp(lastChatMessage2, L"Help : /h, /help") == 0 ||
        wcscmp(lastChatMessage4, L"Help : /h, /help") == 0
    ) {
        wcscpy(lastChatMessage4, L"");
        wcscpy(lastChatMessage3, L"");
        wcscpy(lastChatMessage2, L"");
        wcscpy(lastChatMessage1, L"");
    } else return;

    LogToChat("SS Client by 2014", CHAT_COLOR_PURPLE);
    LogToChat("discord.gg/mixmaster", CHAT_COLOR_PINK);
}