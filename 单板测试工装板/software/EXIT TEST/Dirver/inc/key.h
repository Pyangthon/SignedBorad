#ifndef __KEY_H_
#define __KEY_H_

#include "stm8l15x_gpio.h"
#include "stm8l15x_exti.h"
#include "Delay.h"

#define KEY_PORT    GPIOE
#define KEY_PIN1    GPIO_Pin_1
#define KEY_PIN2    GPIO_Pin_0

extern void KeyGpioInit(void);
extern BitStatus GetKeySta(GPIO_TypeDef *GPIOx, GPIO_Pin_TypeDef GPIO_Pin);

#endif
