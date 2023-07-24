#include "data.h"

/**
 *  NOTE:!!
 *  1.  �����ʾλ������max��λ��������������Ҫ��ʾС���㣬min �� max ��Ҫ��Ϊ 0;
 *      �����ʼ��max = 90000, D_dir_2DOT, ������ʾ5λ��,�ڵ���λ�͵���λ֮�������ʾС����,�ﵽ2λС������ʾЧ����
 *      ��Ҫ��ʾʵ������123.45���������10^2ת��������������ʾ,�����Ǵ���123.45����ʾ123.45��
 *  2.  С����λ������ͨ�� str_one_line.D_dir_f ����
 *  3.  �˵����ĩ��ͨ�� str_one_line.end_flg ��־λ�ж�,��ؽ����һ���ʼ��ΪEND;
 *  4.  ��������  str_one_line.D_danwei �г�ʼ��
 *  5.  str_one_line.D ��ȡֵ��ΧΪ[min, max]
 */

/* ���˵���ִ�к��� */
u8 MainMenuFunc(u16 index)
{
    u8 retval;
    switch (index)
    {
    case 1:
        // retval = check_pwd("1234"); // ��������
        break;
    }
    return retval;
}

/* �����Ӳ˵� - ��ѹ���� */
str_one_line menu_measure_voltage_para[] =
    {
        {"Ua:", &measure_voltage_para_s.Ua, {"V"}, 0, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
        {"Ub:", &measure_voltage_para_s.Ub, {"V"}, 0, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
        {"Uc:", &measure_voltage_para_s.Uc, {"V"}, END, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
};
/* �����Ӳ˵� - �������� */
str_one_line menu_measure_current_para[] =
    {
        {"Ia:", &measure_current_para_s.Ia, {"A"}, 0, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
        {"Ib:", &measure_current_para_s.Ib, {"A"}, 0, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},
        {"Ic:", &measure_current_para_s.Ic, {"A"}, END, 0, 0, NULL, NULL, D_dir_2DOT, NULL, NONE},

};

/* �����Ӳ˵� - ���� */

str_one_line menu_measure_sub[] =
    {
        {"��ѹ", NULL, {""}, 0, 0, 0, menu_measure_voltage_para, NULL, D_dir_STR, NULL, Para_Menu_UI_5x8},
        {"����", NULL, {""}, 0, 0, 0, menu_measure_current_para, NULL, D_dir_STR, NULL, Para_Menu_UI_5x8},
};

/* �����Ӳ˵� */
str_one_line menu_control_sub[] =
    {
        {"��һ", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"�ض�", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"����", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"����", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"����", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"����", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"����", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"�ذ�", NULL, {" "}, 0, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},
        {"�ؾ�", NULL, {" "}, END, 0, 0, NULL, ControlMenuFunc, D_dir_STR, NULL, NONE},

};

/**
 * @brief �����Ӳ˵���ִ�к���
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

/* ״̬�Ӳ˵� */
str_one_line menu_state_sub[] =
    {
        {"�ǵ�����һ    ", &state_para_s.FDL1, {"��", "��"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"�ǵ�������    ", &state_para_s.FDL2, {"��", "��"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"�ǵ�������    ", &state_para_s.FDL3, {"��", "��"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"�ǵ�������    ", &state_para_s.FDL4, {"��", "��"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"�ǵ�������    ", &state_para_s.FDL5, {"��", "��"}, 0, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"�ǵ�������    ", &state_para_s.FDL6, {"��", "��"}, END, 0, 1, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},

};

/* ���˵� */
str_one_line menu_main[] =
    {
        {"����", NULL, {" "}, 0, 0, 0, menu_measure_sub, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"����", NULL, {" "}, 0, 0, 0, menu_control_sub, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"״̬", NULL, {" "}, 0, 0, 0, menu_state_sub, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"ͨ��", NULL, {" "}, 0, 0, 0, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"�޸�", NULL, {" "}, 0, 0, 0, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"����", NULL, {" "}, 0, 0, 0, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
        {"����", NULL, {" "}, END, 0, 0, NULL, NULL, D_dir_STR, NULL, Para_Menu_UI_12x14},
};
