#include "led.h"


///***************************************************************************
//* 函数名称: void LED_Init(void)
//* 功能  	: 初始化LED端口
//* 入口参数: None
//* 返回值  : None
//* 作者  	:
//* 创建时间:
//* 修改时间:
//****************************************************************************
void LED_Init(void)
{
    GPIO_Init(LED_PORT, LED0_PIN, GPIO_Mode_Out_PP_High_Fast);      // 初始化LED0为通用推挽高速输出
    GPIO_Init(LED_PORT, LED1_PIN, GPIO_Mode_Out_PP_High_Fast);      // LED1  
    GPIO_Init(LED_PORT, LED2_PIN, GPIO_Mode_Out_PP_High_Fast);      // LED2
    GPIO_Init(LED_PORT, LED3_PIN, GPIO_Mode_Out_PP_High_Fast);      // LED3
}

///***************************************************************************
//* 函数名称: void LED_Run(u8 mode) 
//* 功能  	: 开启LED灯
//* 入口参数: mode 需要开启的LED编号 0-3为对应LED， 4为所有LED
//* 返回值  : None
//* 作者  	:
//* 创建时间:
//* 修改时间:
//****************************************************************************
void LED_Run(u8 mode)
{
    switch(mode)
    {
        case 0:                 // 模式0 LED0亮
            GPIO_ResetBits(LED_PORT, LED0_PIN);
            break;          
        case 1:                 // 模式1 LED1亮
            GPIO_ResetBits(LED_PORT, LED1_PIN);
            break;              
        case 2:                 // 模式2 LED2亮
            GPIO_ResetBits(LED_PORT, LED2_PIN);
            break;
        case 3:                 // 模式3 LED3亮
            GPIO_ResetBits(LED_PORT, LED3_PIN);
            break;
        case 4:                 // 模式4 全亮
            GPIO_ResetBits(LED_PORT, LED0_PIN);      // 输出低电平，LED灯亮
            GPIO_ResetBits(LED_PORT, LED1_PIN);
            GPIO_ResetBits(LED_PORT, LED2_PIN);
            GPIO_ResetBits(LED_PORT, LED3_PIN);
            break;

        default:                // 默认无动作
            break;
    }
}

///***************************************************************************
//* 函数名称: void LED_Off(u8 mode)
//* 功能  	: 关闭对应的LED
//* 入口参数: mode 需要关闭的LED编号 0-3为对应LED， 4为所有LED
//* 返回值  : None
//* 作者  	:
//* 创建时间:
//* 修改时间:
//****************************************************************************
void LED_Off(u8 mode)
{
    switch(mode)
    {
        case 0:                 //  模式0 LED0灭
            GPIO_SetBits(LED_PORT, LED0_PIN);
            break;
        case 1:                 //  模式1 LED1灭
            GPIO_SetBits(LED_PORT, LED1_PIN);
            break;
        case 2:                 // 模式2 LED2灭
            GPIO_SetBits(LED_PORT, LED2_PIN);
            break;  
        case 3:                 // 模式3 LED3灭
            GPIO_SetBits(LED_PORT, LED3_PIN);
            break;
        case 4:                 // 模式4 LED全灭
            GPIO_SetBits(LED_PORT, LED0_PIN);
            GPIO_SetBits(LED_PORT, LED1_PIN);
            GPIO_SetBits(LED_PORT, LED2_PIN);
            GPIO_SetBits(LED_PORT, LED3_PIN);
            break;
            
        default:                // 默认无动作
            break;
    }
}


///***************************************************************************
//* 函数名称: void LEDFlicker(u8 LEDNum, u8 i) 
//* 功能  	: 指定LED闪烁和次数
//* 参数  	: u8 LEDNum  LED灯的编号
//*           u8 i       LED闪烁的次数
//* 作者  	:
//* 创建时间:
//* 修改时间:
//****************************************************************************

void LEDFlicker(u8 LEDNum, u8 i)
{
    if(i > 0)
    {
        while(i--)
        {
            LED_Run(LEDNum);
            Delay_ms(200);
            LED_Off(LEDNum);
            Delay_ms(200);
        }
    }
}