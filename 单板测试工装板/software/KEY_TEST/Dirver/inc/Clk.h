#ifndef __CLK_H_
#define __CLK_H_
//Include-------------------------------------------------------------
#include "stm8l15x_clk.h"
#include "stm8l15x_tim4.h"

extern u16 MsCounts;

// ��ʼ��ϵͳʱ�ӣ��ڲ�����ʱ�ӣ�16MHz
extern void SysClockInit(void);
// TIM4���ú�����16��Ƶ��ÿ0.001s(1ms)�ж�һ��
extern void TIM4_Config(void);
// TIM2���ú���, 128��Ƶ�� ÿ0.1s�ж�һ��
//extern void Timer2_Config(void);

#endif
