#ifndef __USART__H
#define __USART__H

#include "stm8l15x.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

// 默认串口波特率
#define BAUDRATE        115200

// 默认最大缓存数据
#define BUFFER_LEN      128

// 计算数组长度
#define ARRLEN(ARRAY)   ((sizeof(ARRAY)) / (sizeof(ARRAY[0])))     

typedef struct 
{
    unsigned char USART_Date[BUFFER_LEN];
    unsigned char Length;
    unsigned char Falg;
    unsigned char USART_Halt_Falg;
}USART_STU;
 

extern USART_STU USART_3;
extern USART_STU USART_1;
extern USART_STU USART_2;



extern void Usart1_Module_Init(unsigned long Baud);
extern void Usart3_Module_Init(unsigned long Baud);
extern void Usart2_Module_Init(unsigned long Baud);

extern void Usart3_Module_Disable(void);
extern void Usart1_Module_Disable(void);
extern void Usart2_Module_Disable(void);

extern void UsartSend(USART_TypeDef* USARTx, unsigned char *str, int Len) ;




#endif

