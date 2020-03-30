#ifndef __KEY_H_
#define __KEY_H_

#include "stm8l15x_gpio.h"
#include "stm8l15x_exti.h"
#include "Delay.h"

#define KEY_PORT        GPIOE
#define KEY_PIN1        GPIO_Pin_1
#define KEY_PIN0        GPIO_Pin_0
#define READ_KEY1()     GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN1)
#define READ_KEY0()     GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN0)

typedef struct
{   
    bool Key1;
    bool Key0;
}Global_Flag_TypeDef;

extern Global_Flag_TypeDef FlagSturct;
extern void KeyGpioInit(void);
extern BitStatus GetKeySta(GPIO_TypeDef *GPIOx, GPIO_Pin_TypeDef GPIO_Pin);

#endif
