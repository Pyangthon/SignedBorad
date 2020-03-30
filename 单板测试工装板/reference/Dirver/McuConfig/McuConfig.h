#ifndef __MCUCONFIG__H
#define __MCUCONFIG__H

#include "Stm8l15x.h"
#include "Display.h"

typedef struct
{  
  unsigned int Time;   //显示时间
  unsigned char Flag;   //显示标志位  
  
}Dispaly_T;

typedef struct
{
  
  RTC_DateTypeDef Date;
  RTC_TimeTypeDef Time;
  
}RTC_T;
extern RTC_T  Rtc;

extern void Stm8l15xConfig(void);

#endif
