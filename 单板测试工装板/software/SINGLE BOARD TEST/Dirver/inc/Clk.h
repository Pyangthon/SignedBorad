#ifndef __CLK_H_
#define __CLK_H_
//Include-------------------------------------------------------------
#include "stm8l15x_clk.h"
#include "stm8l15x_tim4.h"

extern u16 MsCounts;

// 初始化系统时钟，内部高速时钟，16MHz
extern void SysClockInit(void);
// TIM4配置函数，16分频，每0.001s(1ms)中断一次
extern void TIM4_Config(void);
// TIM2配置函数, 128分频， 每0.1s中断一次
//extern void Timer2_Config(void);
extern void TIM1_Config(void);

#endif
