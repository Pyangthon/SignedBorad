
/*******************************************
* @File   RS485.c  
* @brief  RS485相关配置文件   
* @author  
* @date     
* @version V0.1 
* @par Copyright (c)
* @par History
            None
*********************************************/
#include "RS485.h"
#include "led.h"


///***************************************************************************
//* 函数名称: void RS485Init(void)
//* 功能  	: RS485初始化
//* 入口参数: None
//* 返回值  : None
//* 作者  	:
//* 创建时间:
//* 修改时间:
//****************************************************************************
void RS485Init(void)
{
    Usart2_Module_Init(9600);     // 初始化串口2
    
    GPIO_Init(RS485_EN_PORT, RS485_EN_PIN, GPIO_Mode_Out_PP_High_Fast); // 初始化RS485发送使能脚
    
    GPIO_ResetBits(RS485_EN_PORT, RS485_EN_PIN);    // 使能脚置低，默认接收
}
///***************************************************************************
//* 函数名称: int putchar(int data) 
//* 功能  	: 重写putchar函数，让printf函数可用于串口打印
//* 入口参数: data 需要发送的数据
//* 返回值  : data 返回该数据
//* 作者  	:
//* 创建时间:
//* 修改时间:
//****************************************************************************
int putchar(int data) 
{ 
    USART_SendData8(USART2,(u8)data); //发送8位数据
//    LEDFlicker(3, 1);
    while(!USART_GetFlagStatus (USART2,USART_FLAG_TXE));//等待发送完毕
    return data; 
}


