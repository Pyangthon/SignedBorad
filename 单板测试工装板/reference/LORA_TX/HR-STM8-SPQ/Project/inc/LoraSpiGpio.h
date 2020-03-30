#ifndef __LoraSpiGpio__H
#define __LoraSpiGpio__H

#include "includes.h"

extern u8 lora_falg;//lora±êÖ¾Î»
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