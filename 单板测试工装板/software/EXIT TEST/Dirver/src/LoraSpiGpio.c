
#include "LoraSpiGpio.h"

//#define RF_RST        PD_ODR_ODR5
//#define SCK           PB_ODR_ODR5
//#define MISO          PB_IDR_IDR7 //INPUT
//#define MOSI          PB_ODR_ODR6
//#define nCS           PB_ODR_ODR4
//#define RF_RX         PB_ODR_ODR3
//#define RF_TX         PD_ODR_ODR6


//#define RF_IRQ_DIO0       PD_IDR_IDR4 //接收数据 平时0  收到数据1
//#define RF_IRQ_DIO1       PF_IDR_IDR1 //检测序言  平时0  收到语言1
//#define RF_IRQ_DIO3       PF_IDR_IDR0 //CAD 超时

/************Lora模块管脚初始化*************/
void Lora_Gpio_Init(void)
{
    GPIO_Init(LORA_SPI_PORT, LORA_SPI_NSS,  GPIO_Mode_Out_PP_Low_Fast);  //PD6--CS--OUTPUT
    GPIO_Init(LORA_CLK_PORT, LORA_SPI_CLK,  GPIO_Mode_Out_PP_Low_Fast);  //PF7--CLK--OUTPUT
    GPIO_Init(LORA_SPI_PORT, LORA_SPI_MOSI, GPIO_Mode_Out_PP_Low_Fast);  //PD5--MOSI--OUTPUT
    GPIO_Init(LORA_TX_PORT,  LORA_TXEN_PIN, GPIO_Mode_Out_PP_Low_Fast);  //PG4--TXEN--OUTPUT
    GPIO_Init(LORA_RX_PORT,  LORA_RXEN_PIN, GPIO_Mode_Out_PP_Low_Fast);  //PD7--RXEN--OUTPUT
    GPIO_Init(LORA_RST_PORT, LORA_RST_PIN,  GPIO_Mode_Out_PP_Low_Fast);  //PC4--RSET--OUTPUT

    GPIO_Init(LORA_SPI_PORT, LORA_SPI_MISO, GPIO_Mode_In_FL_No_IT);      //PD4--MISO--INPUT

    GPIO_Init(LORA_DI0_PORT,  LORA_DI0_PIN, GPIO_Mode_In_FL_IT);         //PG5--DIO--INPUT Interrupt 
    EXTI_SetPinSensitivity(EXTI_Pin_5,EXTI_Trigger_Falling); 

    GPIO_Init(LORA_DI12_PORT, LORA_DI1_PIN, GPIO_Mode_In_FL_No_IT);      //PC2--DI1--INPUT NO Interrupt
    GPIO_Init(LORA_DI12_PORT, LORA_DI2_PIN, GPIO_Mode_In_FL_No_IT);      //PC3--DI2--INPUT NO Interrupt
    GPIO_Init(LORA_DI345_PORT, LORA_DI3_PIN, GPIO_Mode_In_FL_No_IT);     //PF4--DI3--INPUT NO Interrupt
    GPIO_Init(LORA_DI345_PORT, LORA_DI4_PIN, GPIO_Mode_In_FL_No_IT);     //PF5--DI4--INPUT NO Interrupt
    GPIO_Init(LORA_DI345_PORT, LORA_DI5_PIN, GPIO_Mode_In_FL_No_IT);     //PF6--DI5--INPUT NO Interrupt

}

/******************SPI管脚接口映射**************************/
void SPI_CS_H(void)
{
     GPIO_WriteBit(LORA_SPI_PORT, LORA_SPI_NSS, SET);    //PD6
}
void SPI_CS_L(void)
{
     GPIO_WriteBit(LORA_SPI_PORT, LORA_SPI_NSS, RESET);   
}

void SPI_CLK_H(void)
{
    GPIO_WriteBit(LORA_CLK_PORT, LORA_SPI_CLK, SET);    //PF7
}
void SPI_CLK_L(void)
{
    GPIO_WriteBit(LORA_CLK_PORT, LORA_SPI_CLK,RESET); 
}

void SPI_MOSI_H(void)
{
    GPIO_WriteBit(LORA_SPI_PORT,LORA_SPI_MOSI,SET);     //PD5
}
void SPI_MOSI_L(void)
{
    GPIO_WriteBit(LORA_SPI_PORT,LORA_SPI_MOSI,RESET); 
}

unsigned char SPI_MISO(void)    //PD4
{   
    GPIO_Init(LORA_SPI_PORT,LORA_SPI_MISO,GPIO_Mode_In_FL_No_IT);  //PG7--MISO--INPUT
    if(GPIO_ReadInputDataBit(LORA_SPI_PORT,LORA_SPI_MISO))
        return 1;
    else
        return 0;
}
/*****************射频发使能脚映射************************/
void RF_TX_EN_H(void)
{
     GPIO_WriteBit(LORA_TX_PORT, LORA_TXEN_PIN,SET);    //PD7
}
void RF_TX_EN_L(void)
{
     GPIO_WriteBit(LORA_TX_PORT, LORA_TXEN_PIN,RESET);     
}
/*****************射频收使能脚映射************************/
void RF_RX_EN_H(void)
{ 
     GPIO_WriteBit(LORA_RX_PORT,LORA_RXEN_PIN,SET); //PG4
}
void RF_RX_EN_L(void)
{
     GPIO_WriteBit(LORA_RX_PORT,LORA_RXEN_PIN,RESET); 
}
/*****************射频复位脚映射************************/
void RF_RST_H(void)
{
    GPIO_WriteBit(LORA_RST_PORT, LORA_RST_PIN,SET);   //PC4
}
void RF_RST_L(void)
{
    GPIO_WriteBit(LORA_RST_PORT, LORA_RST_PIN,RESET); 
}
/*****************射频输出IO脚映射************************/
unsigned char RF_DIO0(void)    //PG5
{
    if(GPIO_ReadInputDataBit(LORA_DI0_PORT, LORA_DI0_PIN))
        return 1;
    else
        return 0;
}
unsigned char RF_DIO1(void)     //PC2
{
    if(GPIO_ReadInputDataBit(LORA_DI12_PORT, LORA_DI1_PIN))
        return 1;
    else 
        return 0;
}
unsigned char RF_DIO3(void)     //PF4
{
    if(GPIO_ReadInputDataBit(LORA_DI345_PORT,LORA_DI3_PIN))
        return 1;
    else
        return 0;
}
/*******************看门狗喂狗映射************************/
void Watchdog_Reload(void)
{
    //IWDG_ReloadCounter(); //独立看门狗喂狗
}





