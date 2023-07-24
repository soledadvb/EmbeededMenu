#ifndef __DATA_H__
#define __DATA_H__

/* 若无需表示如此大的数值范围可以修改成占用空间更小的s16,但必须在str_one_line结构体定义中同步修改 */
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
