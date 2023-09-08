#include "Disp.h"

void set_disp_para(menu_ctx_t *ctx, disp_para_t *T);
void disp_ui(menu_ctx_t *ctx, disp_para_t *T);
void key_in_menu(menu_ctx_t *ctx, disp_para_t *T);

menu_ctx_t menu_stack[MENU_STACK_DEEPTH];
u8 stack_index = 0;
s32 num = 0;
u8 edit_flg = 0;

// ����С����������С����
static s16 InsertDot(u8 *dir_buff, int int_size, u8 dot_size, s32 D, u8 flg)
{
    s16 i;
    if (D >= 0) // ��ֵΪ����
    {
        if (int_size > 0 && flg == 1) // ����ָ�����λ��,���ڱ༭ģʽ��,�� 0 ����������λ��
        {
            if (dot_size > 0) // ����С�����ֵ���ʾ
                i = sprintf((char *)dir_buff, "%0*d.%0*d", int_size, D / (int)pow(10, dot_size), dot_size, D % (int)pow(10, dot_size));
            else
                i = sprintf((char *)dir_buff, "%0*d", int_size, D);
        }
        else // δָ�����λ��,��Ԥ��0��λ��
        {
            if (dot_size > 0) // ����С�����ֵ���ʾ
                i = sprintf((char *)dir_buff, "%d.%0*d", D / (int)pow(10, dot_size), dot_size, D % (int)pow(10, dot_size));
            else
                i = sprintf((char *)dir_buff, "%d", D);
        }
    }
    else // ��ֵΪ����
    {
        D = -D;
        if (int_size > 0 && flg == 1)
        {
            if (dot_size > 0)
                i = sprintf((char *)dir_buff, "-%0*d.%0*d", int_size, D / (int)pow(10, dot_size), dot_size, D % (int)pow(10, dot_size));
            else
                i = sprintf((char *)dir_buff, "-%0*d", int_size, D);
        }
        else
        {
            if (dot_size > 0)
                i = sprintf((char *)dir_buff, "-%d.%0*d", D / (int)pow(10, dot_size), dot_size, D % (int)pow(10, dot_size));
            else
                i = sprintf((char *)dir_buff, "-%d", D);
        }
    }
    return i;
}

u8 GetItemsNumbers(str_one_line *pMenu)
{
    for (u8 num = 0; pMenu[num].end_flg != 1; num++) // ����˵�������
        ;
    return num + 1;
}

u8 Get_Page_Count(str_one_line *pMenu, u8 per_page_items)
{
    u8 items_cnt = Get_Items_Count(pMenu);
    u8 page_cnt = items_cnt % per_page_items ? items_cnt / per_page_items + 1 : items_cnt / per_page_items;
    return page_cnt;
}

u8 Get_Max_Pos(str_one_line *pMenu, u8 per_page_items)
{
    u8 retval;
    retval = (Get_Items_Count(pMenu) - 1) % per_page_items;
    return retval;
}

/**
 * @brief ����ѡ��
 *
 * @para ctx
 * @para T
 */
void key_in_menu(menu_ctx_t *ctx, disp_para_t *T)
{
    get_key(5);
    if (edit_flg == 0)
    {
        switch (mkvalue)
        {
        case KEY_UP:
            ctx->currentPos -= T->col;
            if (ctx->currentPos < 0) // ��ҳ
            {
                if (ctx->currentPage == 0) // ��ǰ�ڵ�0ҳ,���Ϸ��������һҳ,posָ�����һ��
                {
                    ctx->currentPos += T->last_page_max_pos + 1;
                    ctx->currentPage = T->page_cnt - 1;
                }
                else // ��ǰ������ҳ,������ҳ
                {
                    ctx->currentPage -= 1;
                    ctx->currentPos += T->per_page_items;
                }
            }
            break;
        case KEY_DOWN:
            ctx->currentPos += T->col;
            if (ctx->currentPage == T->page_cnt - 1) // ��ǰ��ĩҳ
            {
                if (ctx->currentPos > T->last_page_max_pos) // ��ҳ,���·�������0ҳ,posָ��0
                {
                    ctx->currentPage = 0;
                    ctx->currentPos -= T->last_page_max_pos + 1;
                }
            }
            else // ����ĩҳ,������ҳ
            {
                if (ctx->currentPos >= T->per_page_items)
                {
                    ctx->currentPage += 1;
                    ctx->currentPos -= T->per_page_items;
                    if (ctx->currentPage == T->page_cnt - 1)
                    {
                        if (T->last_page_max_pos == 0)
                            ctx->currentPos = 0; // ������һҳֻ��һ��,��ҳ��ָ����һ��
                    }
                }
            }
            break;
        case KEY_LEFT:
            ctx->currentPos -= 1;
            if (ctx->currentPos < 0)
            {
                ctx->currentPos += T->per_page_items;
                if (ctx->currentPage == T->page_cnt - 1)
                    ctx->currentPos = T->last_page_max_pos;
            }
            break;
        case KEY_RIGHT:
            ctx->currentPos += 1;
            if (ctx->currentPage == T->page_cnt - 1) // ��ǰ�����һҳ,ָ��������ָ����ָ��0
            {
                if (ctx->currentPos > T->last_page_max_pos)
                    ctx->currentPos = 0;
            }
            else if (ctx->currentPos >= T->per_page_items)
                ctx->currentPos -= T->per_page_items;
            break;
        case KEY_SET:
            if (ctx->pMenu[ctx->currentIndex].Edit_Flg == EDIT && (ctx->pMenu[ctx->currentIndex].func == NULL))
            {
                edit_flg = 1;
                num = *ctx->pMenu[ctx->currentIndex].D;
                if (num < ctx->pMenu[ctx->currentIndex].min)
                    num = ctx->pMenu[ctx->currentIndex].min;
                else if (num > ctx->pMenu[ctx->currentIndex].max)
                    num = ctx->pMenu[ctx->currentIndex].max;
                break;
            }
            else if (ctx->pMenu[ctx->currentIndex].func != NULL && ctx->pMenu[ctx->currentIndex].Edit_Flg == NULL)
            {
                if (ctx->pMenu[ctx->currentIndex].func(ctx->currentIndex) == 0) // ����ֵΪ0����ִ�гɹ�
                {
                    if (ctx->pMenu[ctx->currentIndex].next_level != NULL)
                        if (stack_index < MENU_STACK_DEEPTH - 1)
                        {
                            (ctx + 1)->pMenu = ctx->pMenu[ctx->currentIndex].next_level;     // �滻�˵���ʾ����
                            (ctx + 1)->ui_type = ctx->pMenu[ctx->currentIndex].next_ui_type; // �滻ҳ������
                            stack_index++;
                        }
                }
                break;
            }
            else if (ctx->pMenu[ctx->currentIndex].next_ui_type != NONE)
            {
                if (stack_index < MENU_STACK_DEEPTH - 1)
                {
                    (ctx + 1)->pMenu = ctx->pMenu[ctx->currentIndex].next_level;     // �滻�˵���ʾ����
                    (ctx + 1)->ui_type = ctx->pMenu[ctx->currentIndex].next_ui_type; // �滻ҳ������
                    stack_index++;
                    break;
                }
            }
            else
                break;
        case KEY_QUIT:
            if (edit_flg == 1)
            {
                edit_flg = 0;
                break;
            }
            else if (stack_index > 0)
            {
                ctx->currentPage = ctx->currentPos = 0;
                stack_index--;
                break;
            }
            else
                break;
        case KEY_ADD: // ��ǰ��ҳ
            ctx->currentPage -= 1;
            if (ctx->currentPage < 0) // �������һҳʱ
            {
                ctx->currentPage += T->page_cnt;
                if (ctx->currentPos > T->last_page_max_pos)
                    ctx->currentPos = T->last_page_max_pos;
            }
            break;
        case KEY_CUT: // ����ҳ
            ctx->currentPage += 1;
            if (ctx->currentPage == T->page_cnt - 1) // ��һҳ��ĩҳ
            {
                if (ctx->currentPos > T->last_page_max_pos)
                    ctx->currentPos = T->last_page_max_pos;
            }
            else
            {
                if (ctx->currentPage >= T->page_cnt) // ��ǰ��ĩҳ,���󷭷�����0ҳ
                    ctx->currentPage -= T->page_cnt;
            }
            break;
        case KEY_RESET:
            ctx->currentPage = 0;
            ctx->currentPos = 0;
            break;
        default:
            break;
        }
    }
}
/**
 * @brief �����޸���ֵ
 *
 * @para ctx
 * @para T
 */
u8 key_in_para_edit(menu_ctx_t *ctx, disp_para_t *T)
{
    get_key(5);
    s32 tmp = 0;
    if (ctx->pMenu[ctx->currentIndex].D_dir_f == D_dir_STR) // ������
    {
        switch (mkvalue)
        {
        case KEY_UP:
            num--;
            if (num < ctx->pMenu[ctx->currentIndex].min)
                num = 0;
            break;
        case KEY_DOWN:
            num++;
            if (num > ctx->pMenu[ctx->currentIndex].max)
                num = ctx->pMenu[ctx->currentIndex].max;
            break;
        case KEY_LEFT:

            break;
        case KEY_RIGHT:
            break;
        case KEY_SET:
            *ctx->pMenu[ctx->currentIndex].D = num;
            edit_flg = 0;

            return 0;

        case KEY_QUIT:
            num = 0;
            edit_flg = 0;
            return 1;
        default:
            break;
        }
    }
    else // ��ֵ
    {
        switch (mkvalue)
        {
        case KEY_UP:
            tmp = pow(10, T->crtIndex_cnt - 1 - T->pos);
            if ((num + tmp) > ctx->pMenu[ctx->currentIndex].max)
            {
                num = ctx->pMenu[ctx->currentIndex].max;
                break;
            }
            num += tmp;
            break;
        case KEY_DOWN:
            tmp = pow(10, T->crtIndex_cnt - 1 - T->pos);
            if ((num - tmp) < ctx->pMenu[ctx->currentIndex].min)
            {
                num = ctx->pMenu[ctx->currentIndex].min;
                break;
            }
            num -= tmp;
            break;
        case KEY_LEFT:
            T->pos--;
            if (T->pos < 0)
                T->pos = T->crtIndex_cnt - 1;
            if (T->i == 0)
                T->_pos = T->pos + 2;
            else
            {
                if (T->pos >= T->i)
                    T->_pos = T->pos + 1;
                else
                    T->_pos = T->pos;
            }
            break;
        case KEY_RIGHT:
            T->pos++;
            if (T->pos > T->crtIndex_cnt - 1)
                T->pos = 0;
            if (T->i == 0)
                T->_pos = T->pos + 2;
            else
            {

                if (T->pos >= T->i)
                    T->_pos = T->pos + 1;
                else
                    T->_pos = T->pos;
            }
            break;
        case KEY_SET:
            *ctx->pMenu[ctx->currentIndex].D = num;
            T->pos = T->_pos = 0;
            num = 0;
            edit_flg = 0;
            return 0;

        case KEY_QUIT:
            T->pos = T->_pos = 0;
            num = 0;
            edit_flg = 0;
            return 1;
        default:
            break;
        }
    }
    return 1;
}

static void set_disp_para(menu_ctx_t *ctx, disp_para_t *T) // UI ����
{
    T->per_page_items = UI_Info[ctx->ui_type].row * UI_Info[ctx->ui_type].col;
    T->col = UI_Info[ctx->ui_type].col;
    T->last_page_max_pos = (Get_Items_Count(ctx->pMenu) - 1) % T->per_page_items;
    T->page_cnt = Get_Page_Count(ctx->pMenu, T->per_page_items);
    ctx->currentIndex = ctx->currentPage * T->per_page_items + ctx->currentPos;
    ctx->start_item = ctx->currentPage * T->per_page_items;
    ctx->end_item = (ctx->currentPage + 1) * T->per_page_items;
    if (ctx->end_item > Get_Items_Count(ctx->pMenu))
        ctx->end_item = Get_Items_Count(ctx->pMenu);
}
/****************************** ���˵���� ****************************************/
static void disp_ui_main(menu_ctx_t *ctx, disp_para_t *T)
{
    u8 i, ii, x, y, word_length, col_interval;

    GET_DGUS_Sb_P();
    PackFrame_to_send1(0, 0x7F, 0xffff, 0x02, 0xff); // ����
    // -------------------------------
    col_interval = X / UI_Info[Main_Menu_UI].col;
    // -------------------------------
    // д��˵���Ŀ��������
    for (ii = ctx->start_item; ii < ctx->end_item; ii++)
    {
        for (i = 0; ctx->pMenu[ii].text[i] != 0; i++)
            DGUS_Sb_P[DGUS_FRAME_BUF + i] = ctx->pMenu[ii].text[i];
        x = UI_Info[Main_Menu_UI].x0 + (ii - ctx->start_item) % 2 * col_interval;
        y = UI_Info[Main_Menu_UI].y0 + UI_Info[Main_Menu_UI].height * ((ii - ctx->start_item) / UI_Info[Main_Menu_UI].col);
        PackFrame_to_send1(i, (x << 8) + y, 0xffff, 0x0a, 0x00);

        // ѡ�з�����
        word_length = i * 7; // 1��Ӣ���ַ�ռ1������ 1������ռ2������ ���ȵ�λΪ7px
        if (ii - ctx->start_item == ctx->currentPos)
            PackFrame_to_send1(0x00, ((x - 2) << 8) | (y - 1), ((x + word_length + 2) << 8) | (y + 14), 0x04, 0xff); // ����������,����x���������2px,����y���������1px
    }
    // Draw_Scroll_Bar(ctx->currentPage, Get_Page_Count(ctx->pMenu, T->per_page_items));
    PackFrame_to_send1(0x00, 0xffff, 0xffff, 0x01, 0xff); // ˢ��
    Write_LCD_Data();
    Disp_OSTimeDly(ms200);
}

void Main_Menu(menu_ctx_t *ctx)
{
    // ��������
    static disp_para_t T;
    set_disp_para(ctx, &T);
    disp_ui_main(ctx, &T);
    key_in_menu(ctx, &T);
}

/**********************************************************************/
static inline u8 Disp_CountDigitNumber(s32 num)
{
    u8 digit_num = 0;
    while (num)
    {
        num /= 10;
        digit_num++;
    }
    return digit_num;
}

static inline void Disp_ReflashScreen(s32 dly)
{
    PackFrame_to_send1(0x00, 0xffff, 0xffff, 0x01, 0xff);
    Write_LCD_Data();
    Disp_OSTimeDly(dly);
}

static inline void Disp_PromptWindow(u8 x0, u8 y0, u8 x1, u8 y1)
{
    PackFrame_to_send1(0, x0 << 8 | y0, x1 << 8 | y1, 0x03, 0xff);
}
/**
 * @brief
 * @param {menu_ctx_t} *ctx
 * @param {disp_para_t} *T
 * @return {*}
 */
static void Disp_WriteEditDispContent(menu_ctx_t *ctx, disp_para_t *T)
{
    u16 x, y, len;
    s32 min = ctx->pMenu[ctx->currentIndex].min;
    s32 max = ctx->pMenu[ctx->currentIndex].max;
    if (ctx->pMenu[ctx->currentIndex].D_dir_f == D_dir_STR)
    {
        for (u8 i = min; i <= max; i++)
        {
            const char *danwei = ctx->pMenu[ctx->currentIndex].D_danwei[i];
            u8 len = strlen(danwei);
            x = (X - len * 6) / 2;
            y = 7 + (48 - 16 * (max + 1)) / 2 + 16 * i;
            memcpy(&DGUS_Sb_P[DGUS_FRAME_BUF], danwei, len);
            PackFrame_to_send1(len, (x << 8) + y, 0xffff, 0x0a, 0x00);
        }
        // ��ѡѡ��λ
        len = strlen((ctx->pMenu[ctx->currentIndex].D_danwei[num]));
        y = 7 + (48 - 16 * (ctx->pMenu[ctx->currentIndex].max + 1)) / 2 + 16 * num;
        PackFrame_to_send1(0x00, ((x - 1) << 8) | (y - 1),
                           ((x + len * 6 + 1) << 8) | (y + 14), 0x04, 0xff);
    }
    else
    {
        // ��ֵ��Χ��ʾ
        u8 digit_num_of_max = 0;

        u8 dot_num = ctx->pMenu[ctx->currentIndex].D_dir_f;
        char max_format[20], min_to_max_range[50], edit_num_temp[20];

        digit_num_of_max = Disp_CountDigitNumber(max);
        T->crtIndex_cnt = digit_num_of_max;
        Data_dir((u8 *)min_to_max_range, digit_num_of_max - dot_num, dot_num, min, 1);
        strcat(min_to_max_range, "-");
        Data_dir((u8 *)max_format, digit_num_of_max - dot_num, dot_num, max, 1);
        strcat(min_to_max_range, max_format);
        len = strlen(min_to_max_range);
        memcpy(&DGUS_Sb_P[DGUS_FRAME_BUF], min_to_max_range, len);
        x = (X - len * 8) / 2;
        y = 20;
        PackFrame_to_send1(len, (x << 8) | y, 0xffff, 0x0b, 0x00);
        len = Data_dir((u8 *)edit_num_temp, digit_num_of_max - dot_num, dot_num, num, 1);
        memcpy(&DGUS_Sb_P[DGUS_FRAME_BUF], edit_num_temp, len);
        x = (X - len * 8) / 2;
        y = 35;
        PackFrame_to_send1(len, (x << 8) | y, 0xffff, 0x0b, 0x00);
        if (T->i == 0 && T->_pos == 0)
            T->_pos = 2;
        // ����ѡ����

        PackFrame_to_send1(0x00, ((x + (8 * T->_pos)) << 8) | (y - 1),
                           ((x + (8 * (T->_pos + 1)) - 3) << 8) | (y + 7), 0x04, 0xff);
    }
}
/****************************** ��������1��� ****************************************/

static void disp_ui_para_5x8(menu_ctx_t *ctx, disp_para_t *T) // 5x8
{
    // ��ʾ
    GET_DGUS_Sb_P();

    u16 x, y;
    if (edit_flg == 1)
    {
        Disp_PromptWindow(15, 7, 111, 55);
        Disp_WriteEditDispContent(ctx, T);
    }
    else
    {
        // ����
        PackFrame_to_send1(0, 0x7F, 0xffff, 0x02, 0xff);
        /* д�뵱ǰҳ��Ĳ˵������� */
        for (u8 ii = ctx->start_item; ii < ctx->end_item; ii++)
        {
            char buff[50];
            u8 len = 0, cnt = 0;
            s32 tmp = ctx->pMenu[ii].max;

            // ����max��cntλ��
            while (tmp)
            {
                tmp /= 10;
                cnt++;
            }
            // ����ÿ�������ʾ����ʱ,��Ϊ��������Ա�֤��Խ��
            if (ctx->currentIndex == ii && ctx->pMenu[ctx->currentIndex].Edit_Flg == EDIT)
            {
                T->crtIndex_cnt = cnt;
                T->i = T->crtIndex_cnt - ctx->pMenu[ctx->currentIndex].D_dir_f;
            }
            // д�����
            memcpy(&DGUS_Sb_P[DGUS_FRAME_BUF], ctx->pMenu[ii].text, strlen(ctx->pMenu[ii].text));
            len += strlen(ctx->pMenu[ii].text);
            memset(buff, 0x00, sizeof(buff));
            // ������
            if (ctx->pMenu[ii].D_dir_f == D_dir_STR)
            {
                memcpy(buff, (ctx->pMenu[ii].D_danwei[*ctx->pMenu[ii].D]), strlen((ctx->pMenu[ii].D_danwei[*ctx->pMenu[ii].D])));
            }
            // ��ֵ + ��λ
            else
            {
                Data_dir((u8 *)buff, cnt - ctx->pMenu[ii].D_dir_f, ctx->pMenu[ii].D_dir_f, *ctx->pMenu[ii].D, 0); // ��ֵת��
                strcat(buff, *ctx->pMenu[ii].D_danwei);
            }
            memcpy(&DGUS_Sb_P[DGUS_FRAME_BUF + len], buff, strlen(buff));
            len += strlen(buff);
            x = UI_Info[Para_Menu_UI_5x8].x0;
            y = UI_Info[Para_Menu_UI_5x8].y0 + 10 * ((ii - ctx->start_item));
            PackFrame_to_send1(len, (x << 8) + y, 0xffff, 0x0b, 0x00);
        }
        // ���Ե�ǰ�˵���
        PackFrame_to_send1(0x00, (x - 1 << 8) | (UI_Info[Para_Menu_UI_5x8].y0 - 1 + UI_Info[Para_Menu_UI_5x8].height * ctx->currentPos),
                           (120 << 8) | (UI_Info[Para_Menu_UI_5x8].y0 - 2 + UI_Info[Para_Menu_UI_5x8].height * (ctx->currentPos + 1)), 0x04, 0xff); // ����������,����x���������2px,����y���������1px
        Draw_Scroll_Bar(X - 4, 0, X - 1, Y - 1, ctx->currentPage, T->page_cnt);
    }
    // ˢ����Ļ
    Disp_ReflashScreen(ms200);
}

void Para_Menu_5x8(menu_ctx_t *ctx) // 5x8
{
    static disp_para_t T;
    set_disp_para(ctx, &T);
    disp_ui_para_5x8(ctx, &T);
    if (edit_flg == 0)
        key_in_menu(ctx, &T);
    else
        key_in_para_edit(ctx, &T);
}

/**********************************************************************/
static void disp_ui_para_12x14(menu_ctx_t *ctx, disp_para_t *T)
{
    // ��ʾ
    GET_DGUS_Sb_P();
    u16 x, y;
    if (edit_flg == 1)
    {
        Disp_PromptWindow(15, 7, 111, 55);
        Disp_WriteEditDispContent(ctx, T);
    }

    else
    {
        // ����
        PackFrame_to_send1(0, 0x7F, 0xffff, 0x02, 0xff);
        for (u8 ii = ctx->start_item; ii < ctx->end_item; ii++)
        {
            char buff[50];
            u8 len = 0, cnt = 0;
            s32 tmp = ctx->pMenu[ctx->currentIndex].max;
            // ����max��cntλ��
            while (tmp)
            {
                tmp /= 10;
                cnt++;
            }
            // ����ÿ�������ʾ����ʱ,��Ϊ��������Ա�֤��Խ��
            if (ctx->currentIndex == ii && ctx->pMenu[ctx->currentIndex].Edit_Flg == EDIT)
            {
                T->crtIndex_cnt = cnt;
                T->i = T->crtIndex_cnt - ctx->pMenu[ctx->currentIndex].D_dir_f;
            }
            // д�����
            memcpy(&DGUS_Sb_P[DGUS_FRAME_BUF], ctx->pMenu[ii].text, strlen(ctx->pMenu[ii].text));
            len += strlen(ctx->pMenu[ii].text);
            memset(buff, 0x00, sizeof(buff));

            /* �����ֵ�Ƿ�Խ�� */
            if (*ctx->pMenu[ctx->currentIndex].D < ctx->pMenu[ctx->currentIndex].min)
                *ctx->pMenu[ctx->currentIndex].D = ctx->pMenu[ctx->currentIndex].min;
            else if (*ctx->pMenu[ctx->currentIndex].D > ctx->pMenu[ctx->currentIndex].max)
                *ctx->pMenu[ctx->currentIndex].D = ctx->pMenu[ctx->currentIndex].max;
            // ������
            if (ctx->pMenu[ii].D_dir_f == D_dir_STR)
            {
                if (edit_flg == 1 && ii == ctx->currentIndex)
                {
                    memcpy(buff, (ctx->pMenu[ii].D_danwei[num]), strlen((ctx->pMenu[ii].D_danwei[num])));
                }
                else
                {
                    memcpy(buff, (ctx->pMenu[ii].D_danwei[*ctx->pMenu[ii].D]), strlen((ctx->pMenu[ii].D_danwei[*ctx->pMenu[ii].D])));
                }
            }
            // ��ֵ + ��λ
            else
            {
                if (edit_flg == 1 && ii == ctx->currentIndex)
                {
                    Data_dir((u8 *)buff, cnt - ctx->pMenu[ii].D_dir_f, ctx->pMenu[ii].D_dir_f, num, 1); // ��ֵת��
                }
                else
                    Data_dir((u8 *)buff, cnt - ctx->pMenu[ii].D_dir_f, ctx->pMenu[ii].D_dir_f, *ctx->pMenu[ii].D, 0); // ��ֵת��
                strcat(buff, *ctx->pMenu[ii].D_danwei);
            }
            memcpy(&DGUS_Sb_P[DGUS_FRAME_BUF + len], buff, strlen(buff));
            len += strlen(buff);
            x = UI_Info[Para_Menu_UI_12x14].x0;
            y = UI_Info[Para_Menu_UI_12x14].y0 + 16 * ((ii - ctx->start_item));
            PackFrame_to_send1(len, (x << 8) + y, 0xffff, 0x0a, 0x00);
        }
        // ���Ե�ǰ�˵���
        PackFrame_to_send1(0x00, (x - 1 << 8) | (UI_Info[Para_Menu_UI_12x14].y0 - 1 + UI_Info[Para_Menu_UI_12x14].height * ctx->currentPos),
                           (120 << 8) | (UI_Info[Para_Menu_UI_12x14].y0 - 2 + UI_Info[Para_Menu_UI_12x14].height * (ctx->currentPos + 1)), 0x04, 0xff); // ����������,����x���������2px,����y���������1px
        Draw_Scroll_Bar(X - 4, 0, X - 1, Y - 1, ctx->currentPage, T->page_cnt);
    }

    // ˢ����Ļ
    Disp_ReflashScreen(ms200);
}

/****************************** ��������2�޸�****************************************/
void Para_Menu_12x14(menu_ctx_t *ctx)
{
    static disp_para_t T;
    set_disp_para(ctx, &T);
    disp_ui_para_12x14(ctx, &T);
    if (edit_flg == 0)
        key_in_menu(ctx, &T);
    else
        key_in_para_edit(ctx, &T);
}

/**
 * @brief
 * @para	void * argument:
 * @return	void:
 **/
void TASK_FUNC_DISP(void *argument)
{
    // ��ʼ���˵�
    menu_stack[0].pMenu = menu_main;
    menu_stack[0].ui_type = Main_Menu_UI;
    while (1)
    {
        switch (menu_stack[stack_index].ui_type)
        {
        case Main_Menu_UI:
            Main_Menu(&menu_stack[stack_index]);
            break;
        case Para_Menu_UI_5x8:
            Para_Menu_5x8(&menu_stack[stack_index]); // 5x8
            break;
        case Para_Menu_UI_12x14:
            Para_Menu_12x14(&menu_stack[stack_index]); // 12x14
            break;
        default:
            break;
        }
    }
}
