#ifndef __COMMAND__H
#define __COMMAND__H


#include "includes.h"
#define RELOAD_VALUE 254

extern void IWDG_Config(void);
extern void CLK_Configuration(void) ;
extern void N_CRC16(u8 *updata,u16 len, u8* MSB, u8* LSB);
extern void Lora_Event(void);
extern void Text_Event(void);



#endif