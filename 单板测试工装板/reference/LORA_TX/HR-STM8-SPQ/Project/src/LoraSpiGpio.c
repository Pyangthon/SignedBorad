
#include "LoraSpiGpio.h"

u8 lora_falg=0;
//#define RF_RST        F0
//#define SCK           G5
//#define MISO          G7
//#define MOSI          G6
//#define nCS           G4
//#define RF_RX         E6
//#define RF_TX         E7

//#define RF_IRQ_DIO0       E0 //接收数据 平时0  收到数据1
//#define RF_IRQ_DIO1       PF_IDR_IDR1 //检测序言  平时0  收到语言1
//#define RF_IRQ_DIO3       PF_IDR_IDR0 //CAD 超时

/************Lora模块管脚初始化*************/
void  Lora_Gpio_Init(void){
     GPIO_Init(GPIOF,GPIO_Pin_0,GPIO_Mode_Out_PP_Low_Fast);   //PD4--RSET--OUTPUT
      GPIO_Init(GPIOG,GPIO_Pin_5,GPIO_Mode_Out_PP_Low_Fast);  //PD2--CLK--OUTPUT
      GPIO_Init(GPIOG,GPIO_Pin_4,GPIO_Mode_Out_PP_Low_Fast);  //PB1--CS--OUTPUT
      
      GPIO_Init(GPIOG,GPIO_Pin_6,GPIO_Mode_Out_PP_Low_Fast);  //PB0--MOSI--OUTPUT
      GPIO_Init(GPIOE,GPIO_Pin_7,GPIO_Mode_Out_PP_Low_Fast);  //PC0--TXEN--OUTPUT
      GPIO_Init(GPIOE,GPIO_Pin_6,GPIO_Mode_Out_PP_Low_Fast);  //PB2--RXEN--OUTPUT
      
      
      GPIO_Init(GPIOG,GPIO_Pin_7,GPIO_Mode_In_PU_No_IT);  //PD3--MISO--INPUT
      
      GPIO_Init(GPIOE,GPIO_Pin_0,GPIO_Mode_In_FL_IT);  //PA2--DIO--INPUT Interrupt 
      EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Rising); //
      
      //GPIO_Init(GPIOA,GPIO_Pin_3,GPIO_Mode_In_FL_No_IT);  //PA3--DI1--INPUT Interrupt
      
     // GPIO_Init(GPIOA,GPIO_Pin_5,GPIO_Mode_In_FL_No_IT);  //PA5--DI3--INPUT Interrupt

}

/******************SPI管脚接口映射**************************/
void SPI_CS_H(void)
{
     GPIO_WriteBit(GPIOG,GPIO_Pin_4,SET);    //PG4
}
void SPI_CS_L(void)
{
     GPIO_WriteBit(GPIOG,GPIO_Pin_4,RESET);   
}

void SPI_CLK_H(void)
{
    GPIO_WriteBit(GPIOG,GPIO_Pin_5,SET);  //PG5
}
void SPI_CLK_L(void)
{
    GPIO_WriteBit(GPIOG,GPIO_Pin_5,RESET); 
}

void SPI_MOSI_H(void)
{
    GPIO_WriteBit(GPIOG,GPIO_Pin_6,SET);  //PG6
}
void SPI_MOSI_L(void)
{
    GPIO_WriteBit(GPIOG,GPIO_Pin_6,RESET); 
}

unsigned char SPI_MISO(void)    //PG7
{   
   if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7))
    return 1;
   else
    return 0;
}
/*****************射频发使能脚映射************************/
void RF_TX_EN_H(void)
{
     GPIO_WriteBit(GPIOE,GPIO_Pin_7,SET);    //s6   PE7
}
void RF_TX_EN_L(void)
{
     GPIO_WriteBit(GPIOE,GPIO_Pin_7,RESET);    //s6    
}
/*****************射频收使能脚映射************************/
void RF_RX_EN_H(void)
{ 
     GPIO_WriteBit(GPIOE,GPIO_Pin_6,SET); //PE6
}
void RF_RX_EN_L(void)
{
     GPIO_WriteBit(GPIOE,GPIO_Pin_6,RESET);    //RX  
}
/*****************射频复位脚映射************************/
void RF_RST_H(void)
{
    GPIO_WriteBit(GPIOF,GPIO_Pin_0,SET);   //PF0
}
void RF_RST_L(void)
{
    GPIO_WriteBit(GPIOF,GPIO_Pin_0,RESET); 
}
/*****************射频输出IO脚映射************************/
unsigned char RF_DIO0(void)    //PE0
{
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0))
        return 1;
    else
        return 0;
}
unsigned char RF_DIO1(void)  //PA3
{
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
        return 1;
    else 
        return 0;
}
unsigned char RF_DIO3(void)  //PA5
{
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5))
        return 1;
    else
        return 0;
}
/*******************看门狗喂狗映射************************/
void Watchdog_Reload(void)
{
    IWDG_ReloadCounter(); //独立看门狗喂狗
}





