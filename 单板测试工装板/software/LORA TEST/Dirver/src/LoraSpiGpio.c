
#include "LoraSpiGpio.h"

//#define RF_RST        PD_ODR_ODR5
//#define SCK           PB_ODR_ODR5
//#define MISO          PB_IDR_IDR7 //INPUT
//#define MOSI          PB_ODR_ODR6
//#define nCS           PB_ODR_ODR4
//#define RF_RX         PB_ODR_ODR3
//#define RF_TX         PD_ODR_ODR6


//#define RF_IRQ_DIO0       PD_IDR_IDR4 //�������� ƽʱ0  �յ�����1
//#define RF_IRQ_DIO1       PF_IDR_IDR1 //�������  ƽʱ0  �յ�����1
//#define RF_IRQ_DIO3       PF_IDR_IDR0 //CAD ��ʱ

u8 RXFlag = 0;

/************Loraģ��ܽų�ʼ��*************/
void Lora_Gpio_Init(void)
{
    GPIO_Init(LORA_SPI_PORT, LORA_SPI_NSS,  GPIO_Mode_Out_PP_Low_Fast);  //PG4--CS--OUTPUT
    GPIO_Init(LORA_SPI_PORT, LORA_SPI_CLK,  GPIO_Mode_Out_PP_Low_Fast);  //PG5--CLK--OUTPUT
    GPIO_Init(LORA_SPI_PORT, LORA_SPI_MOSI, GPIO_Mode_Out_PP_Low_Fast);  //PG6--MOSI--OUTPUT
    GPIO_Init(LORA_DI_PORT,  LORA_TXEN_PIN, GPIO_Mode_Out_PP_Low_Fast);  //PE7--TXEN--OUTPUT
    GPIO_Init(LORA_DI_PORT,  LORA_RXEN_PIN, GPIO_Mode_Out_PP_Low_Fast);  //PE6--RXEN--OUTPUT
    GPIO_Init(LORA_RST_PORT, LORA_RST_PIN,  GPIO_Mode_Out_PP_Low_Fast);  //PF0--RSET--OUTPUT

    GPIO_Init(LORA_SPI_PORT, LORA_SPI_MISO, GPIO_Mode_In_FL_No_IT);  //PG7--MISO--INPUT

    GPIO_Init(LORA_DI_PORT,  LORA_DI0_PIN, GPIO_Mode_In_FL_IT);     //PE0--DIO--INPUT Interrupt 
    EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Rising); 

    GPIO_Init(LORA_DI_PORT, LORA_DI1_PIN, GPIO_Mode_In_FL_No_IT);  //PE1--DI1--INPUT NO Interrupt
    GPIO_Init(LORA_DI_PORT, LORA_DI2_PIN, GPIO_Mode_In_FL_No_IT);  //PE2--DI2--INPUT NO Interrupt
    GPIO_Init(LORA_DI_PORT, LORA_DI3_PIN, GPIO_Mode_In_FL_No_IT);  //PE3--DI3--INPUT NO Interrupt
    GPIO_Init(LORA_DI_PORT, LORA_DI4_PIN, GPIO_Mode_In_FL_No_IT);  //PE4--DI4--INPUT NO Interrupt
    GPIO_Init(LORA_DI_PORT, LORA_DI5_PIN, GPIO_Mode_In_FL_No_IT);  //PE5--DI5--INPUT NO Interrupt

}

/******************SPI�ܽŽӿ�ӳ��**************************/
void SPI_CS_H(void)
{
     GPIO_WriteBit(LORA_SPI_PORT, LORA_SPI_NSS, SET);    //PG4
}
void SPI_CS_L(void)
{
     GPIO_WriteBit(LORA_SPI_PORT, LORA_SPI_NSS, RESET);   
}

void SPI_CLK_H(void)
{
    GPIO_WriteBit(LORA_SPI_PORT, LORA_SPI_CLK, SET);    //PG5
}
void SPI_CLK_L(void)
{
    GPIO_WriteBit(LORA_SPI_PORT, LORA_SPI_CLK,RESET); 
}

void SPI_MOSI_H(void)
{
    GPIO_WriteBit(LORA_SPI_PORT,LORA_SPI_MOSI,SET);     //PG6
}
void SPI_MOSI_L(void)
{
    GPIO_WriteBit(LORA_SPI_PORT,LORA_SPI_MOSI,RESET); 
}

unsigned char SPI_MISO(void)    //PG7
{   
    GPIO_Init(LORA_SPI_PORT,LORA_SPI_MISO,GPIO_Mode_In_FL_No_IT);  //PG7--MISO--INPUT
    if(GPIO_ReadInputDataBit(LORA_SPI_PORT,LORA_SPI_MISO))
        return 1;
    else
        return 0;
}
/*****************��Ƶ��ʹ�ܽ�ӳ��************************/
void RF_TX_EN_H(void)
{
     GPIO_WriteBit(LORA_DI_PORT, LORA_TXEN_PIN,SET);    //PE7
}
void RF_TX_EN_L(void)
{
     GPIO_WriteBit(LORA_DI_PORT, LORA_TXEN_PIN,RESET);     
}
/*****************��Ƶ��ʹ�ܽ�ӳ��************************/
void RF_RX_EN_H(void)
{ 
     GPIO_WriteBit(LORA_DI_PORT,LORA_RXEN_PIN,SET); //PE6
}
void RF_RX_EN_L(void)
{
     GPIO_WriteBit(LORA_DI_PORT,LORA_RXEN_PIN,RESET); 
}
/*****************��Ƶ��λ��ӳ��************************/
void RF_RST_H(void)
{
    GPIO_WriteBit(LORA_RST_PORT, LORA_RST_PIN,SET);   //PF0
}
void RF_RST_L(void)
{
    GPIO_WriteBit(LORA_RST_PORT, LORA_RST_PIN,RESET); 
}
/*****************��Ƶ���IO��ӳ��************************/
unsigned char RF_DIO0(void)    //PE0
{
    if(GPIO_ReadInputDataBit(LORA_DI_PORT, LORA_DI0_PIN))
        return 1;
    else
        return 0;
}
unsigned char RF_DIO1(void)     //PE1
{
    if(GPIO_ReadInputDataBit(LORA_DI_PORT, LORA_DI1_PIN))
        return 1;
    else 
        return 0;
}
unsigned char RF_DIO3(void)     //PE3
{
    if(GPIO_ReadInputDataBit(LORA_DI_PORT,LORA_DI3_PIN))
        return 1;
    else
        return 0;
}
/*******************���Ź�ι��ӳ��************************/
void Watchdog_Reload(void)
{
    //IWDG_ReloadCounter(); //�������Ź�ι��
}





