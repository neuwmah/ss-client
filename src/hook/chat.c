typedef void (__thiscall *callChat)(void* chat, LPCSTR text, int color, int xd);
callChat hookChatMessage = NULL;

void LogToChat(const char* message, int color) {
    void* mainChat = (void*)CHAT_BASE;
    if (mainChat == NULL || hookChatMessage == NULL) return;
    
    hookChatMessage(mainChat, message, color, 0);
}