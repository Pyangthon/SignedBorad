

#ifndef __LED_H_
#define __LED_H_

// ͷ�ļ�
#include "stm8l15x_gpio.h"
#include "Delay.h"

// LED�˿ں궨��
#define LED_PORT        GPIOD				// LED �˿� PD
#define LED0_PIN        GPIO_Pin_0			// led0 PD0	
#define LED1_PIN        GPIO_Pin_1			// led1 PD1
#define LED2_PIN        GPIO_Pin_2			// led2 PD2
#define LED3_PIN        GPIO_Pin_3			// led3 PD3

// �궨�嵥��LED���øߵ͵�ƽ����
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


// ��������
// LED�˿ڳ�ʼ��
extern void LED_Init(void);         

// LED��
// ����LED��ż���������Ӧ��LED
// ����0-3�򿪶�Ӧ��LED������4����ȫ��LED
// mode Ϊ��� 0-3
extern void LED_Run(u8 mode);       // LED����
// LED��
// ����LED��ż��ɹرն�Ӧ��LED
// ����0-3�رն�Ӧ��LED������4�ر�ȫ��LED
// mode Ϊ��� 0-3
extern void LED_Off(u8 mode);       // LED�ر�
//LED��˸
// LEDNum LED�ı�ſ�����0-3
// i      LED��˸�Ĵ�������СΪ1
extern void LEDFlicker(u8 LEDNum, u8 i);


#endif