#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
// STM32开发板
//LED驱动代码	   
  
//技术论坛: 
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
// 
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PEout(2)// PE2
#define LED1 PEout(0)// PE0	

void LED_Init(void);//初始化

		 				    
#endif
