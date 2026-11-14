void AutoPotionHP(int index, unsigned short currentHP, unsigned short maxHP);
void AutoPotionMP(int index, unsigned short currentMP, unsigned short maxMP);
void LogToChat(const char* message, int color);

void ReadItemsTable();
void ReadItemsHotbar();

void CheckLoginMessage();
void CheckChatCommands();
void CheckGameWindow();
void CheckHack();
void CheckHeroLogin();

void CommandF1F9();
void CommandF10();
void CommandDelay();

void Setup();
int DetectServer(void);