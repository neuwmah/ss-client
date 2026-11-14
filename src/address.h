// Server
#define PV_ADDRESS 0x019EC1B9
#define FR_ADDRESS 0x00AA0891
#define AU_ADDRESS 0x00AAF6D1

// Colors
#define CHAT_COLOR_PURPLE 0xEB7AEB
#define CHAT_COLOR_PINK   0xF099F0

typedef struct {
    uintptr_t call_game_interface;
    uintptr_t call_chat_message;
    uintptr_t hero_hp, hero_hp_max, hero_mp, hero_mp_max;
    uintptr_t hero_on;
    uintptr_t hench_1_hp, hench_1_hp_max, hench_1_mp, hench_1_mp_max, hench_1_flag;
    uintptr_t hench_2_hp, hench_2_hp_max, hench_2_mp, hench_2_mp_max, hench_2_flag;
    uintptr_t hench_3_hp, hench_3_hp_max, hench_3_mp, hench_3_mp_max, hench_3_flag;
    uintptr_t base_items_table, base_items_hotbar;
    uintptr_t chat_base, chat_last_command, chat_last_message, chat_last_color;
    uintptr_t pointer_status;
    uintptr_t nop_chat_msg;
} ServerAddrs;

extern ServerAddrs ADDR;

#define CALL_GAME_INTERFACE (ADDR.call_game_interface)
#define CALL_CHAT_MESSAGE   (ADDR.call_chat_message)

#define HERO_HP     (ADDR.hero_hp)
#define HERO_HP_MAX (ADDR.hero_hp_max)
#define HERO_MP     (ADDR.hero_mp)
#define HERO_MP_MAX (ADDR.hero_mp_max)
#define HERO_ON     (ADDR.hero_on)

#define HENCH_1_HP     (ADDR.hench_1_hp)
#define HENCH_1_HP_MAX (ADDR.hench_1_hp_max)
#define HENCH_1_MP     (ADDR.hench_1_mp)
#define HENCH_1_MP_MAX (ADDR.hench_1_mp_max)
#define HENCH_1_FLAG   (ADDR.hench_1_flag)

#define HENCH_2_HP     (ADDR.hench_2_hp)
#define HENCH_2_HP_MAX (ADDR.hench_2_hp_max)
#define HENCH_2_MP     (ADDR.hench_2_mp)
#define HENCH_2_MP_MAX (ADDR.hench_2_mp_max)
#define HENCH_2_FLAG   (ADDR.hench_2_flag)

#define HENCH_3_HP     (ADDR.hench_3_hp)
#define HENCH_3_HP_MAX (ADDR.hench_3_hp_max)
#define HENCH_3_MP     (ADDR.hench_3_mp)
#define HENCH_3_MP_MAX (ADDR.hench_3_mp_max)
#define HENCH_3_FLAG   (ADDR.hench_3_flag)

#define BASE_ITEMS_TABLE  (ADDR.base_items_table)
#define BASE_ITEMS_HOTBAR (ADDR.base_items_hotbar)

#define CHAT_BASE         (ADDR.chat_base)
#define CHAT_LAST_COMMAND (ADDR.chat_last_command)
#define CHAT_LAST_MESSAGE (ADDR.chat_last_message)
#define CHAT_LAST_COLOR   (ADDR.chat_last_color)

#define POINTER_STATUS (ADDR.pointer_status)
#define NOP_CHAT_MSG   (ADDR.nop_chat_msg)