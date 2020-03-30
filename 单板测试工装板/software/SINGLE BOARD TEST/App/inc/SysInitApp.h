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
#include "SerialData.h"
#include "Adc.h"



// ����PB0-3��ʼ���˿�ģʽ, SET �����������ģʽ�� RESET ��������ģʽ
#define PB_LSB_MODE     1

// ����̵������ƽ�
#define SPDT_PORT        GPIOC
#define SPDT_EN_PIN      GPIO_Pin_7

// �궨��̵������ƺ���
// �̵����ر�
#define SPDT_EN_OFF()     GPIO_ResetBits(SPDT_PORT, SPDT_EN_PIN)
// �̵�������
#define SPDT_EN_ON()      GPIO_SetBits(SPDT_PORT, SPDT_EN_PIN)

extern u16 MsCount;
extern u16 SceCount;
extern u16 CountDown;
extern bool HaltState;
// �̵�����ʼ��
extern void SPDT_Init(void);
// �̵������ƶ˿ڳ�ʼ��
extern void SPDT_Ctrl_Port_Init(void);
// ����Ӳ����ʼ������
extern void System_Init(void);
// GPIO���ú���
extern void GPIO_Init_Config(void);
// д��LoraĬ�ϲ���
extern void WriteLoraDef(void);
// ����ϵͳ���ڲ���λ��
extern void ResetDefault(void);
// ������ƫ��ѹ
extern bool ZeroBisVoltTset(u8 State);
// ��ӡ����
extern void PrintArr(u8 *Arr,int Length);
// ��������
extern void Dormancy(void);
// ����GPIOΪ����״̬
extern void DisableGPIO(void);
// �ر�����ʱ��
extern void DisableCLK(void);
// ������ƫ��ѹ��ز���
extern void ZeroBiaVoltConfig(void);
#endif

