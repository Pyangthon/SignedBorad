#ifndef __RS485_H_
#define __RS485_h_

#include "usart.h"
#include "stm8l15x_gpio.h"

#define RS485_PORT          GPIOG
#define RS485_EN_PIN        GPIO_Pin_2

#define RS485_PWR_PORT      GPIOB
#define RS485_PWR_EN_PIN    GPIO_Pin_1

#define RS485_EN_TX()       GPIO_SetBits(RS485_PORT, RS485_EN_PIN)
#define RS485_EN_RX()       GPIO_ResetBits(RS485_PORT, RS485_EN_PIN)

#define RS485_PWR_ON()      GPIO_ResetBits(RS485_PWR_PORT, RS485_PWR_EN_PIN)
#define RS485_PWR_OFF()     GPIO_SetBits(RS485_PWR_PORT, RS485_PWR_EN_PIN)

void RS485_Init(u16 Baud);
void RS485_Send(u8 *Arr, u8 Len);

#endif