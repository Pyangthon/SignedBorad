
#include "Clk.h"

///***************************************************************************
//* 函数名称: void SysClockInit(void)
//* 功能  	: 初始化时钟，选择内部高速时钟
//* 参数  	: None
//* 作者  	:
//* 创建时间: 2020年1月14日
//* 修改时间:
//****************************************************************************

void SysClockInit(void)
{

    CLK_DeInit();
    /* High speed internal clock prescaler: 1 */
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

    /* Select HSI as system clock source */
    CLK_SYSCLKSourceSwitchCmd(ENABLE);
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);

    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);
}