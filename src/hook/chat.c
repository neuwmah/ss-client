typedef void (__thiscall *callChat)(void* chat, LPCSTR text, int color, int xd);
callChat hookChatMessage = (callChat)CALL_CHAT_MESSAGE;

void LogToChat(const char* message, int color) {
    void* mainChat = (void*)CHAT_BASE;
    if (mainChat == NULL) return;
    
    hookChatMessage(mainChat, message, color, 0);
}