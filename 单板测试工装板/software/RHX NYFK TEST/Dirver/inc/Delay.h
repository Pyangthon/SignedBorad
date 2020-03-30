#ifndef __DELAY_H
#define __DELAY_H
#include "stm8l15x.h"
extern void Delay_ms(uint16_t t);
extern void DelayMs(uint16_t t , bool clr);
extern void Delay100Ms(uint16_t t , bool clr, bool check_power, bool Dis);
extern void delay(uint16_t nCount);
extern void Delay_ms_T(u16 n_ms);
extern void delay_1us(u16 n_1us);
extern void delay_us(uint16_t tim);
#endif