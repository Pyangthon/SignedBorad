
#ifndef __KEY_H_
#define __KEY_H_

#include "stm8l15x_gpio.h"
#include "led.h"
#include "TestItems.h"

// �궨�尴���˿�
#define KEY_PORT        GPIOD
#define KEY1_PIN        GPIO_Pin_4
#define KEY2_PIN        GPIO_Pin_5
#define KEY3_PIN        GPIO_Pin_6
#define KEY4_PIN        GPIO_Pin_7

// ��ȡ����״̬�����궨��
#define READ_KEY1()     GPIO_ReadInputDataBit(KEY_PORT, KEY1_PIN)
#define READ_KEY2()     GPIO_ReadInputDataBit(KEY_PORT, KEY2_PIN)
#define READ_KEY3()     GPIO_ReadInputDataBit(KEY_PORT, KEY3_PIN)
#define READ_KEY4()     GPIO_ReadInputDataBit(KEY_PORT, KEY4_PIN)

#define READ_FUN_KEY()  GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)



// ������غ���
// �����˿ڳ�ʼ��
extern void Key_Init(u8 Mode);
// ��ȡ�˿ڵĵ�ƽ״̬
extern BitStatus IO_Read(u8 IO_No);
#endif