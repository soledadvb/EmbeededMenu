#include "data.h"

/**
 *  NOTE:!!
 *  1.  最大显示位数根据max的位数决定，若不需要显示小数点，min 和 max 需要设为 0;
 *      例如初始化max = 90000, D_dir_2DOT, 最大可显示5位数,在第三位和第四位之间插入显示小数点,达到2位小数的显示效果。
 *      故要显示实际数据123.45，必须乘以10^2转换成整数进行显示,而不是传入123.45就显示123.45。
 *  2.  小数点位数可以通过 str_one_line.D_dir_f 调整
 *  3.  菜单项的末项通过 str_one_line.end_flg 标志位判断,务必将最后一项初始化为END;
 *  4.  控制字在  str_one_line.D_danwei 中初始化
 *  5.  str_one_line.D 的取值范围为[min, max]
 */

/* 主菜单可执行函数 */
u8 MainMenuFunc(u16 index)
{
    u8 retval;
    switch (index)
    {
    case 1:
        // retval = check_pwd("1234"); // 传动密码
        break;
    }
    return retval;
}

/* 测量子菜单 - 电压参数 */
str_one_line menu_measure_voltage_para[] =
    {
        {"Ua:", &measure_voltage_para_s.Ua, {"V"}, 0, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
        {"Ub:", &measure_voltage_para_s.Ub, {"V"}, 0, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
        {"Uc:", &measure_voltage_para_s.Uc, {"V"}, END, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
};
/* 测量子菜单 - 电流参数 */
str_one_line menu_measure_current_para[] =
    {
        {"Ia:", &measure_current_para_s.Ia, {"A"}, 0, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
        {"Ib:", &measure_current_para_s.Ib, {"A"}, 0, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
        {"Ic:", &measure_current_para_s.Ic, {"A"}, END, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},

};

/* 测量子菜单 - 标题 */

str_one_line menu_measure_sub[] =
    {
        {"电压", NULL, {""}, 0, 0, 0, menu_measure_voltage_para, NULL, D_dir_STR, NULL, Para_Menu_UI_5x8},
        {"电流", NULL, {""}, 0, 0, 0, menu_measure_current_para, NULL, D_dir_STR, NULL, Para_Menu_UI_5x8},
};

/* 控制子菜单 */
str_one_line menu_control_sub[] =
    {
        {"控一", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"控二", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"控三", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"控四", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"控五", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"控六", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"控七", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"控八", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"控九", NULL, {" "}, END, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},

};

/**
 * @brief 控制子菜单可执行函数
 *
 * @para index
 * @return u8
 */

u8 ControlMenuFunc(u16 index)
{
    u8 retval = 0;
    switch (index)
    {
    case 0:
        // if (DispConfirmPrompt() == 0)
        // {
        //     retval = KC_Set(0, 200);
        //     DispConfirmResultPrompt(&retval);
        // }
        break;
    case 1:
        // if (DispConfirmPrompt() == 0)
        // {
        //     retval = KC_Set(1, 200);
        //     DispConfirmResultPrompt(&retval);
        // }
        break;
    case 2:
        // if (DispConfirmPrompt() == 0)
        // {
        //     retval = KC_Set(2, 200);
        //     DispConfirmResultPrompt(&retval);
        // }
        break;
    case 3:
        // if (DispConfirmPrompt() == 0)
        // {
        //     retval = KC_Set(3, 200);
        //     DispConfirmResultPrompt(&retval);
        // }
        break;
    case 4:
        // if (DispConfirmPrompt() == 0)
        // {
        //     retval = KC_Set(4, 200);
        //     DispConfirmResultPrompt(&retval);
        // }
        break;
    case 5:
        // if (DispConfirmPrompt() == 0)
        // {
        //     retval = KC_Set(5, 200);
        //     DispConfirmResultPrompt(&retval);
        // }
        break;
    case 6:
        // if (DispConfirmPrompt() == 0)
        // {
        //     retval = KC_Set(6, 200);
        //     DispConfirmResultPrompt(&retval);
        // }
        break;
    case 7:
        // if (DispConfirmPrompt() == 0)
        // {
        //     retval = KC_Set(7, 200);
        //     DispConfirmResultPrompt(&retval);
        // }
        break;
    case 8:
        // if (DispConfirmPrompt() == 0)
        // {
        //     retval = KC_Set(8, 200);
        //     DispConfirmResultPrompt(&retval);
        // }
        break;
    default:
        break;
    }
    return 0;
}

/* 状态子菜单 */
str_one_line menu_state_sub[] =
    {
        {"非电气量一    ", &state_para_s.FDL1, {"分", "合"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"非电气量二    ", &state_para_s.FDL2, {"分", "合"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"非电气量三    ", &state_para_s.FDL3, {"分", "合"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"非电气量四    ", &state_para_s.FDL4, {"分", "合"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"非电气量五    ", &state_para_s.FDL5, {"分", "合"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"非电气量六    ", &state_para_s.FDL6, {"分", "合"}, END, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},

};

/* 主菜单 */
str_one_line menu_main[] =
    {
        {"测量", NULL, {" "}, 0, 0, 0, menu_measure_sub, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"传动", NULL, {" "}, 0, 0, 0, menu_control_sub, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"状态", NULL, {" "}, 0, 0, 0, menu_state_sub, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"通信", NULL, {" "}, 0, 0, 0, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"修改", NULL, {" "}, 0, 0, 0, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"调试", NULL, {" "}, 0, 0, 0, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"关于", NULL, {" "}, END, 0, 0, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
};
