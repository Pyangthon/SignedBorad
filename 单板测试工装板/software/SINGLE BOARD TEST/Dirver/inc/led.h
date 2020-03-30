

#ifndef __LED_H_
#define __LED_H_

// 头文件
#include "stm8l15x_gpio.h"
#include "Delay.h"

// LED端口宏定义
#define LED_PORT        GPIOD				// LED 端口 PD
#define LED0_PIN        GPIO_Pin_0			// led0 PD0	
#define LED1_PIN        GPIO_Pin_1			// led1 PD1
#define LED2_PIN        GPIO_Pin_2			// led2 PD2
#define LED3_PIN        GPIO_Pin_3			// led3 PD3

// 宏定义单独LED设置高低电平函数
#define LED0_H()        GPIO_SetBits(LED_PORT, LED0_PIN)        // LED0
#define LED0_L()        GPIO_ResetBits(LED_PORT, LED0_PIN)
#define LED0_FLIP()     GPIO_ToggleBits(LED_PORT, LED0_PIN);

#define LED1_H()        GPIO_SetBits(LED_PORT, LED1_PIN)        // LED1
#define LED1_L()        GPIO_ResetBits(LED_PORT, LED1_PIN)
#define LED1_FLIP()     GPIO_ToggleBits(LED_PORT, LED1_PIN);

#define LED2_H()        GPIO_SetBits(LED_PORT, LED2_PIN)        // LED2
#define LED2_L()        GPIO_ResetBits(LED_PORT, LED2_PIN)
#define LED2_FLIP()     GPIO_ToggleBits(LED_PORT, LED2_PIN);

#define LED3_H()        GPIO_SetBits(LED_PORT, LED3_PIN)        // LED3
#define LED3_L()        GPIO_ResetBits(LED_PORT, LED3_PIN)
#define LED3_FLIP()     GPIO_ToggleBits(LED_PORT, LED3_PIN);


// 函数声明
// LED端口初始化
extern void LED_Init(void);         

// LED亮
// 输入LED编号即可启动对应的LED
// 输入0-3打开对应的LED，输入4开启全部LED
// mode 为编号 0-3
extern void LED_Run(u8 mode);       // LED运行
// LED灭
// 输入LED编号即可关闭对应的LED
// 输入0-3关闭对应的LED，输入4关闭全部LED
// mode 为编号 0-3
extern void LED_Off(u8 mode);       // LED关闭
//LED闪烁
// LEDNum LED的编号可输入0-3
// i      LED闪烁的次数，最小为1
extern void LEDFlicker(u8 LEDNum, u8 i);


#endif