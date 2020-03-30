#ifndef __LED_H_
#define __LED_H_

// ͷ�ļ�
#include "stm8l15x_gpio.h"
#include "Delay.h"

// LED�˿ں궨��
#define LED_PORT        GPIOA				// LED �˿� PD
#define LED_0_PIN       GPIO_Pin_2			// led0 PD0	
#define LED_R_PIN       GPIO_Pin_5      
#define LED_G_PIN       GPIO_Pin_4
#define LED_B_PIN       GPIO_Pin_3
#define LEDR            LED_R_PIN
#define LEDG            LED_G_PIN
#define LEDB            LED_B_PIN

#define LED0_ON()       GPIO_WriteBit(LED_PORT, LED_0_PIN, RESET)
#define LED0_OFF()      GPIO_WriteBit(LED_PORT, LED_0_PIN, SET)
#define LED0_FLIP()     GPIO_ToggleBits(LED_PORT, LED_0_PIN)

#define LEDR_ON()       GPIO_WriteBit(LED_PORT, LED_R_PIN, RESET)
#define LEDR_OFF()      GPIO_WriteBit(LED_PORT, LED_R_PIN, SET)
#define LEDR_FLIP()     GPIO_ToggleBits(LED_PORT, LED_R_PIN)

#define LEDB_ON()       GPIO_WriteBit(LED_PORT, LED_B_PIN, RESET)
#define LEDB_OFF()      GPIO_WriteBit(LED_PORT, LED_B_PIN, SET)
#define LEDB_FLIP()     GPIO_ToggleBits(LED_PORT, LED_B_PIN)

#define LEDG_ON()       GPIO_WriteBit(LED_PORT, LED_G_PIN, RESET)
#define LEDG_OFF()      GPIO_WriteBit(LED_PORT, LED_G_PIN, SET)
#define LEDG_FLIP()     GPIO_ToggleBits(LED_PORT, LED_G_PIN)

#define ADC_IOSTART()   GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_In_FL_No_IT);
#define ADC_IOSTOP()    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);


// ��������
extern void LED_Init(void);         // LED�˿ڳ�ʼ��
extern void LED0Flicker( u8 i);
extern void LED_RGB_Fli(u8 i, GPIO_Pin_TypeDef led);
#endif