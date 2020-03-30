#ifndef __SYS_INIT_APP_H_
#define __SYS_INIT_APP_H_

#include "stm8l15x_gpio.h"
#include "usart.h"
#include "Lora.h"
#include "LoraSpiGpio.h"
#include "Clk.h"
#include "Delay.h"
#include "led.h"
#include "RS485.h"
#include "ADS1115.h"
#include "key.h"
#include "stm8l15x_tim2.h"
#include "Mcuconfig.h"



// ����PB0-3��ʼ���˿�ģʽ, SET �����������ģʽ�� RESET ��������ģʽ
#define PB_LSB_MODE     1

// ����̵������ƽ�
#define SPDT_PORT        GPIOC
#define SPDT_EN_PIN      GPIO_Pin_7

// �궨��̵������ƺ���
// �̵����ر�
#define SPDT_EN_ON()     GPIO_ResetBits(SPDT_PORT, SPDT_EN_PIN)
// �̵�������
#define SPDT_EN_OFF()    GPIO_SetBits(SPDT_PORT, SPDT_EN_PIN)

#define READ_KEY()       GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)

extern u16 MsCount;

// �̵�����ʼ��
extern void SPDT_Init(void);
// �̵������ƶ˿ڳ�ʼ��
extern void SPDT_Ctrl_Port_Init(void);
// ����Ӳ����ʼ������
extern void System_Init(void);
extern void GPIO_Init_Config(void);
#endif

