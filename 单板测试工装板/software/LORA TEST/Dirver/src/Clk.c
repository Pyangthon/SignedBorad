/*******************************************
* @File   Clk.c  
* @brief  初始化时钟   
* @author  
* @date     
* @version V0.1 
* @par Copyright (c)
* @par History
            None
*********************************************/
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

    CLK_DeInit();  // 时钟恢复默认状态                                 
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);   // 1分频 16M

    CLK_SYSCLKSourceSwitchCmd(ENABLE);      // 使能时钟源开关    
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);   // 选择片内高速时钟

    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);  // 等到时钟的开启
}