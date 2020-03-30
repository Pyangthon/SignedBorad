
#ifndef __RS485_H_
#define __RS485_H_

#include "usart.h"
#include "stm8l15x_gpio.h"

// RS485ʹ�ܶ˿ڶ���(PE5)
#define RS485_EN_PORT   GPIOE
#define RS485_EN_PIN    GPIO_Pin_5
// RS485����ʹ�ܶ���
#define RS_EN_RX()      GPIO_ResetBits(RS485_EN_PORT, RS485_EN_PIN)
// RS485����ʹ�ܶ���
#define RS_EN_TX()      GPIO_SetBits(RS485_EN_PORT, RS485_EN_PIN)

extern unsigned char RSReceiveArr[30];  // ���������������
extern unsigned char RSPointer;        // ����ָ��

// RS485��ʼ������; ��ʼ������2����ʼ��ʹ�ܽ���
extern void RS485Init(void);





#endif