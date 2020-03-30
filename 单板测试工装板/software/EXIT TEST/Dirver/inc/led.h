#ifndef __LED_H_
#define __LED_H_

// ͷ�ļ�
#include "stm8l15x_gpio.h"
#include "Delay.h"

// LED�˿ں궨��
#define LED_PORT    GPIOA				// LED �˿� PD
#define LED_1_PIN    GPIO_Pin_2			// led0 PD0	
#define LED_R_PIN    GPIO_Pin_5      
#define LED_G_PIN    GPIO_Pin_4
#define LED_B_PIN    GPIO_Pin_3
#define LEDR        LED_R_PIN
#define LEDG        LED_G_PIN
#define LEDB        LED_B_PIN

// ��������
extern void LED_Init(void);         // LED�˿ڳ�ʼ��
/*ʹ��ĳһ��LEDʱ���������ż��ɣ������ĸ�LED�ƣ����Ϊ0-3������4Ϊ����ȫ��LED��*/
extern void LED_Run(u8 mode);       // LED����

/*�ر�ĳһ��LEDʱ��ͬ��Ҳ�������ţ�����4Ϊ�ر�ȫ��LED��*/
extern void LED_Off(u8 mode);       // LED�ر�
extern void LED_Flicker(GPIO_TypeDef *GPIOx, GPIO_Pin_TypeDef GPIO_Pin); // led��˸
extern void LEDFlicker( u8 i);
extern void LED_RGB_Fli(u8 i, GPIO_Pin_TypeDef led);
#endif