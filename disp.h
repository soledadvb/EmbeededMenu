#ifndef __DISP_H__
#define __DISP_H__

#define D_dir_INT 0
#define D_dir_1DOT 1
#define D_dir_2DOT 2
#define D_dir_3DOT 3
#define D_dir_4DOT 4
#define D_dir_0x 5
#define D_dir_STR 10

#define DISP_1DOT 10
#define DISP_2DOT 100
#define DISP_3DOT 1000
#define DISP_4DOT 10000

// LCD��Ļ��С(pixel)
#define X 128
#define Y 64
#define MENU_STACK_DEEPTH 5
#define EDIT 1
#define END 1
/* key */

void get_key(u16 dly_200ms);

typedef enum
{
    KEY_SET = 0x100,
    KEY_QUIT = 0x10,
    KEY_UP = 0x08,
    KEY_DOWN = 0x40,
    KEY_LEFT = 0x80,
    KEY_RIGHT = 0x01,
    KEY_ADD = 0x04,
    KEY_CUT = 0x02,
    KEY_RESET = 0x20
} key_list_e;

typedef enum
{
    Main_Menu_UI,
    Para_Menu_UI_5x8,
    Para_Menu_UI_12x14,
    TIME_MENU_UI,
    Alarm_Menu_UI,
    UI_Type_Num,
    NONE,
} menu_ui_type_e;

typedef struct
{
    u8 row; // ����
    u8 col; // ����
    u8 height;
    u16 x0, y0;
} UI_Info_t;

typedef struct str_one_line_s
{
    char const *text;        // ����ı�
    s32 *value;              // ʵ����ֵ
    char const *appendix[2]; // ��λ or ������
    u8 is_last_item;         // 1:���һ�� 0:�����һ��
    s32 min_value;
    s32 max_value;
    struct str_one_line_s *next_menu_level; // ��һ��������ʾ
    u8 (*func)(u16 index);                  // ����ȷ�Ϻ�ִ�еĺ���
    u8 const display_format;                // ��ʾ��ʽ
    u8 edit_flag;                           // ���������༭����
    menu_ui_type_e next_ui_type;            // ��һ����������
} str_one_line;

typedef struct menu_ctx_s
{
    struct str_one_line_s *p;
    s8 current_page; // ��ǰ�ڼ�ҳ,���ڷ�ҳ
    s8 current_pos;  // ��ǰ��Ŀλ��,����ѡ�з���
    s16 current_index;
    u8 start_item;
    u8 end_item;
    menu_ui_type_e ui_type; // ��ǰҳ������
} menu_ctx_t;

typedef struct
{
    u8 col;
    u8 per_page_items;
    u8 last_page_max_pos;
    u8 page_cnt;
    u8 items_cnt;
    u8 crtIndex_cnt; // �޸���ֵ����
} disp_para_t;

u8 i;
s8 pos;
s8 _pos;

extern menu_ctx_t menu_stack[MENU_STACK_DEEPTH];
extern u8 stack_index;
u8 check_pwd(u8 pwd[]);
u8 DispConfirmPrompt(void);
u8 DispConfirmResultPrompt(u8 *result);
#endif
