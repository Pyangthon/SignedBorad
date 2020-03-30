#ifndef __MCUCONFIG__H
#define __MCUCONFIG__H


#include "stm8l15x.h"
#include "Delay.h"

#define RELOAD_VALUE       254    //独立看门狗参数

typedef struct
{
  
  RTC_DateTypeDef Date;
  RTC_TimeTypeDef Time;
  
}RTC_T;

extern RTC_T Rtc;  //RTC初始化

extern void CLK_Configuration(void);
extern void GPIO_Config(void);
extern void RTC_Time_Init(void);
extern void Rtc_Configuration(void);
extern void RTC_WAKEINIT(void);
extern void TIM1_Configuration(void);
extern void Timer3_init(void);
extern void Timer2_init(void);
extern void IWDG_Config(void);
extern void Timer4_init(void);


#endif
