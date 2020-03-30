#ifndef __USART__H
#define __USART__H

#include "includes.h"
#include "stm8l15x_flash.h"
#include "lora.h"

#define BUFFER_LEN 256
#define UPDATAFLAG_FLAG  0X97FE  //APP升级标志位

#define RS485_SEND_MODE() GPIO_SetBits(GPIOC,GPIO_Pin_4)   //RS485发送数据
#define RS485_RECV_MODE() GPIO_ResetBits(GPIOC,GPIO_Pin_4)  //RS485接收数据

extern u8 u1_flag;
extern u8 RxBuffer[BUFFER_LEN];


extern void Usart_Init(u32 spend);
extern void UsartSend(USART_TypeDef* USARTx, u8 *str, u8 Len) ;
extern void u1_clear_rxbuffer(void);
void ReverStr(const u8* old_data,u8* new_data,u8 len);
u8 Link_Str(u8 *new_str,u8* new_len,const u8* old_str,u8 len);
u8 chack_Data(u8 *data);
void Response_Config(u8* data,u8 falg);
u8 SetKzq_Id(u8 *data);
u8 Set_Lora(u8 *data);
void GetKzq_Id(u8 *data);
void Rs485_Event(void);
#endif