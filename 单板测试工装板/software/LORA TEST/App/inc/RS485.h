
#ifndef __RS485_H_
#define __RS485_H_

#include "usart.h"
#include "stm8l15x_gpio.h"

// RS485使能端口定义(PE5)
#define RS485_EN_PORT   GPIOE
#define RS485_EN_PIN    GPIO_Pin_5
// RS485接收使能定义
#define RS_EN_RX()      GPIO_ResetBits(RS485_EN_PORT, RS485_EN_PIN)
// RS485发送使能定义
#define RS_EN_TX()      GPIO_SetBits(RS485_EN_PORT, RS485_EN_PIN)

extern unsigned char RSReceiveArr[30];  // 定义接收数据数组
extern unsigned char RSPointer;        // 数据指针

// RS485初始化函数; 初始化串口2，初始化使能接收
extern void RS485Init(void);





#endif