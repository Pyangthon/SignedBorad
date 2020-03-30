#ifndef __USART__H
#define __USART__H

#include "stm8l15x.h"
#include "string.h"
#include "stdlib.h"

//������󻺴�����
#define Max_Lenght 200

typedef struct 
{
    unsigned char USART_Date[Max_Lenght];
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

