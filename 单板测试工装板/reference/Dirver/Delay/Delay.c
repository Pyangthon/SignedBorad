/************************************************************
*文件名:通用系统延时函数
*文件描述:
*创建人:上海瑞臻信息电子研发部
*版本号:V1.0.0
*修改记录:

************************************************************/
#include "stm8l15x.h"
#include "Delay.h"

extern uint8_t dis_num;
extern bool GprsLoadFlag;

#define SYS_CLK_HSI_DIV1

void Delay_ms(uint16_t t)
{
    uint16_t i = 0, j = 0;
    for(i = 0; i < t; i++)
    {
        for(j = 0; j < 3207; j++)
        {
           ; //IWDG_ReloadCounter(); //喂狗  
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 延时豪秒
// 输入参数 : unsigned int: t 时间  < 65535 ms  clr 是否清看门狗
// 返回参数 : 无
// 说明     : STM8 16MHZ
////////////////////////////////////////////////////////////////////////////////
void DelayMs(uint16_t t , bool clr)
{
    uint16_t i = 0;// j = 0;
    for(i = 0; i < t; i++)
    {
        Delay_ms(1);
        if(clr)
            IWDG_ReloadCounter();  //独立看门狗喂狗
    }
}

/*******************************************************************************
* Function Name   : Delay
* Description     : 延时函数
* Calls           :
* Called By       :
* Inputs          : nCount: 延迟时间的长度
* Outputs         : None
* Return          : None
* Notes           : None
*******************************************************************************/
void delay(uint16_t nCount)
{
    for (; nCount != 0; nCount--);
}
/*******************************************************************************
* Function Name   : Delay_ms_T
* Description     : 定时器延时函数
* Calls           :
* Called By       :
* Inputs          : n_ms: how many ms of time to delay
* Outputs         : None
* Return          : None
* Notes           : None
*******************************************************************************/
void Delay_ms_T(u16 n_ms)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
    // Init TIMER 4 //
    // prescaler: / (2^6) = /64
    TIM4->PSCR = 6;
#ifdef SYS_CLK_HSE_DIV1
    // Auto-Reload value: 16M / 64 = 1/4M, 1/4M / 1k = 250
    TIM4->ARR = 250;
#else
#ifdef SYS_CLK_HSE_DIV2
    // Auto-Reload value: 16M/2 / 64 = 1/8M, 1/8M / 1k = 125
    TIM4->ARR = 125;
#else
#ifdef SYS_CLK_HSI_DIV1
    // Auto-Reload value: 16M / 64 = 1/4M, 1/4M / 1k = 250
    TIM4->ARR = 250;
#else
#ifdef SYS_CLK_HSI_DIV2
    // Auto-Reload value: 16M/2 / 64 = 1/8M, 1/8M / 1k = 125
    TIM4->ARR = 125;
#else
#error "either SYS_CLK_HSE_DIV1/DIV2 or SYS_CLK_HSI_DIV1/DIV2 should be defined"
#endif
#endif
#endif
#endif
    // Counter value: 2, to compensate the initialization of TIMER
    TIM4->CNTR = 2;

    // clear update flag
    TIM4->SR1 &= ~TIM4_SR1_UIF;
    // Enable Counter
    TIM4->CR1 |= TIM4_CR1_CEN;

    while (n_ms--)
    {
        while ((TIM4->SR1 & TIM4_SR1_UIF) == 0) ;
        TIM4->SR1 &= ~TIM4_SR1_UIF;
    }

    // Disable Counter
    TIM4->CR1 &= ~TIM4_CR1_CEN;
}
/*******************************************************************************
* Function Name   : delay_1us
* Description     : 延时函数
* Calls           :
* Called By       :
* Inputs          : n_10us: how many 10us of time to delay
* Outputs         : None
* Return          : None
* Notes           : None
*******************************************************************************/
void delay_1us(u16 n_1us)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
    // Init TIMER 4 //
    // prescaler: / (2^0) = /1
    TIM4->PSCR = 0;
#ifdef SYS_CLK_HSE_DIV1
    // Auto-Reload value: 16M / 1 = 16M, 16M / 100k = 160
    TIM4->ARR = 160;
#else
#ifdef SYS_CLK_HSE_DIV2
    // Auto-Reload value: 16M/2 / 1 = 8M, 8M / 100k = 80
    TIM4->ARR = 80;
#else
#ifdef SYS_CLK_HSI_DIV1
    // Auto-Reload value: 16M / 1 = 16M, 16M / 100k = 160
    TIM4->ARR = 16;
#else
#ifdef SYS_CLK_HSI_DIV2
    // Auto-Reload value: 16M/2 / 1 = 8M, 8M / 100k = 80
    TIM4->ARR = 80;
#else
#error "either SYS_CLK_HSE_DIV1/DIV2 or SYS_CLK_HSI_DIV1/DIV2 should be defined"
#endif
#endif
#endif
#endif
    // Counter value: 10, to compensate the initialization of TIMER
    TIM4->CNTR = 10;

    // clear update flag
    TIM4->SR1 &= ~TIM4_SR1_UIF;
    // Enable Counter
    TIM4->CR1 |= TIM4_CR1_CEN;

    while (n_1us--)
    {
        while ((TIM4->SR1 & TIM4_SR1_UIF) == 0) ;
        TIM4->SR1 &= ~TIM4_SR1_UIF;
    }

    // Disable Counter
    TIM4->CR1 &= ~TIM4_CR1_CEN;
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);

}



void delay_us(uint16_t tim)
{
    for(; tim > 0 ; tim--);
}

