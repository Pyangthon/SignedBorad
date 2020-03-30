#ifndef __LED_H_
#define __LED_H_

// 头文件
#include "stm8l15x_gpio.h"
#include "Delay.h"

// LED端口宏定义
#define LED_PORT    GPIOA				// LED 端口 PD
#define LED_1_PIN    GPIO_Pin_2			// led0 PD0	
#define LED_R_PIN    GPIO_Pin_5      
#define LED_G_PIN    GPIO_Pin_4
#define LED_B_PIN    GPIO_Pin_3
#define LEDR        LED_R_PIN
#define LEDG        LED_G_PIN
#define LEDB        LED_B_PIN

// 函数声明
extern void LED_Init(void);         // LED端口初始化
/*使用某一个LED时，输入其编号即可，共有四个LED灯，编号为0-3，输入4为开启全部LED灯*/
extern void LED_Run(u8 mode);       // LED运行

/*关闭某一个LED时，同样也是输入编号，输入4为关闭全部LED灯*/
extern void LED_Off(u8 mode);       // LED关闭
extern void LED_Flicker(GPIO_TypeDef *GPIOx, GPIO_Pin_TypeDef GPIO_Pin); // led闪烁
extern void LEDFlicker( u8 i);
extern void LED_RGB_Fli(u8 i, GPIO_Pin_TypeDef led);
#endif