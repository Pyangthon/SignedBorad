#ifndef __SYS_INIT_APP_H_
#define __SYS_INIT_APP_H_

#include "led.h"

#include "Lora.h"

#include "SPI.h"

#include "stm8l15x_spi.h"

#include "stm8l15x_gpio.h"

#include "LoraSpiGpio.h"

#include "usart.h"

#include "stm8l15x_clk.h"

#include "Delay.h"

#include "ADS1115.h"

#define RS485_EN_PORT GPIOE
#define RS485_EN_PIN  GPIO_Pin_5

#define SPDT_PORT       GPIOC
#define SPDT_EN_PIN     GPIO_Pin_7

extern void SPDT_Init(void);
extern void SysClockInit(void);
#endif

