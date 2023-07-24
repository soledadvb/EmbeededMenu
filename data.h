#ifndef __DATA_H__
#define __DATA_H__

/* �������ʾ��˴����ֵ��Χ�����޸ĳ�ռ�ÿռ��С��s16,��������str_one_line�ṹ�嶨����ͬ���޸� */
typedef struct
{
    s32 Ua;
    s32 Ub;
    s32 Uc;
} measure_voltage_para_s;

typedef struct
{
    s32 Ia;
    s32 Ib;
    s32 Ic;
} measure_current_para_s;

typedef struct
{
    s32 FDL1;
    s32 FDL2;
    s32 FDL3;
    s32 FDL4;
    s32 FDL5;
    s32 FDL6;

} state_para_t;
extern state_para_t state_para_s;

#endif
