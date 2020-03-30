#ifndef __USART__H
#define __USART__H

#include "stm8l15x.h"
#include "string.h"
#include "stdlib.h"
#include <stdio.h>
// 默认串口波特率
#define BAUDRATE    115200
// 默认最大缓存数据
#define SIZE        128

//串口最大缓存数据
#define Max_Lenght 200
//计算数组内的成员个数
#define COUNTOF(a) (sizeof(a) / sizeof(*(a)))
typedef struct 
{
    unsigned char USART_Date[Max_Lenght];
    unsigned char Length;
    unsigned char Falg;
    unsigned char USART_Halt_Falg;
}USART_STU;


/*定义一个结构体，存放串口相关变量*/
typedef struct uart_rxbuf_s
{
  unsigned char buf[SIZE];  /* 串口接收数据的buffer*/
  unsigned char len;      /* 数据的长度 */
}uart_rxbuf_t;
 
extern uart_rxbuf_t  g_uart_rxbuf;
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



extern unsigned char uart_getchar(void);
extern void uart_send(unsigned char *buf, int len);

#endif

