
#ifndef __KEY_H_
#define __KEY_H_

#include "stm8l15x_gpio.h"
#include "led.h"
#include "SerialData.h"

// 宏定义按键端口
#define KEY_PORT        GPIOD
#define KEY1_PIN        GPIO_Pin_4
#define KEY2_PIN        GPIO_Pin_5
#define KEY3_PIN        GPIO_Pin_6
#define KEY4_PIN        GPIO_Pin_7

// 读取按键状态函数宏定义
#define READ_KEY1()     GPIO_ReadInputDataBit(KEY_PORT, KEY1_PIN)
#define READ_KEY2()     GPIO_ReadInputDataBit(KEY_PORT, KEY2_PIN)
#define READ_KEY3()     GPIO_ReadInputDataBit(KEY_PORT, KEY3_PIN)
#define READ_KEY4()     GPIO_ReadInputDataBit(KEY_PORT, KEY4_PIN)

#define READ_FUN_KEY()  GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)



// 按键相关函数
// 按键端口初始化
extern void Key_Init(void);
// 初始化阀门检测端口为浮空输入，上升沿触发
extern void ValveTest_Init(void);
// 重置阀门检测端口
extern void DeInitValve(void);
// 获取端口的电平状态
extern BitStatus IO_Read(u8 IO_No);
#endif