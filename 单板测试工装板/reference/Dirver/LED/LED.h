#ifndef __LED__H
#define __LED__H


#include "stm8l15x.h"

#define LED_PIN  GPIO_Pin_6
#define LED_GPIO GPIOC


extern void LED_ON(void);
extern void LED_OFF(void);
extern void LED_Flicker(void);


#endif
