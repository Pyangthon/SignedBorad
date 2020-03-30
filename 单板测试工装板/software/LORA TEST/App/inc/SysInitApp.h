#ifndef __SYS_INIT_APP_H_
#define __SYS_INIT_APP_H_

#include "stm8l15x_gpio.h"



// 定义继电器控制脚
#define SPDT_PORT       GPIOC
#define SPDT_EN_PIN     GPIO_Pin_7
// 宏定义继电器控制函数
// 继电器关闭
#define SPDT_EN_L()     GPIO_ResetBits(SPDT_PORT, SPDT_EN_PIN)
// 继电器开启
#define SPDT_EN_H()     GPIO_SetBits(SPDT_PORT, SPDT_EN_PIN)
// 继电器初始化


#endif

