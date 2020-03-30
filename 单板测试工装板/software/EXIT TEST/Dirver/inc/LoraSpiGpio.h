#ifndef __LoraSpiGpio__H
#define __LoraSpiGpio__H

#include "stm8l15x.h"

#define LORA_SPI_PORT   GPIOD
#define LORA_SPI_NSS    GPIO_Pin_6
#define LORA_SPI_MOSI   GPIO_Pin_5
#define LORA_SPI_MISO   GPIO_Pin_4

#define LORA_CLK_PORT   GPIOF
#define LORA_SPI_CLK    GPIO_Pin_7

#define LORA_DI0_PORT   GPIOG
#define LORA_DI0_PIN    GPIO_Pin_5

#define LORA_DI12_PORT  GPIOC
#define LORA_DI1_PIN    GPIO_Pin_2
#define LORA_DI2_PIN    GPIO_Pin_3

#define LORA_DI345_PORT GPIOF
#define LORA_DI3_PIN    GPIO_Pin_4
#define LORA_DI4_PIN    GPIO_Pin_5
#define LORA_DI5_PIN    GPIO_Pin_6

#define LORA_RX_PORT    GPIOD
#define LORA_RXEN_PIN   GPIO_Pin_7

#define LORA_TX_PORT    GPIOG
#define LORA_TXEN_PIN   GPIO_Pin_4

#define LORA_RST_PORT   GPIOC
#define LORA_RST_PIN    GPIO_Pin_4

extern void SPI_CS_H(void);    
extern void SPI_CS_L(void);   

extern void SPI_CLK_H(void);    
extern void SPI_CLK_L(void);   

extern void SPI_MOSI_H(void);  
extern void SPI_MOSI_L(void);   

extern unsigned char SPI_MISO(void);    

extern void RF_TX_EN_H(void);  
extern void RF_TX_EN_L(void);  

extern void RF_RX_EN_H(void);   
extern void RF_RX_EN_L(void);  

extern void RF_RST_H(void);   
extern void RF_RST_L(void);    

extern unsigned char RF_DIO0(void);     
extern unsigned char RF_DIO1(void);
extern unsigned char RF_DIO3(void);

extern void Watchdog_Reload(void);

extern void Lora_Gpio_Init(void);





#endif