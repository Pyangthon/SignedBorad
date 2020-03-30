#ifndef __SPI__H
#define __SPI__H

#include "stm8l15x.h"
#include "LoraSpiGpio.h"

#define SPI_CS_H    GPIO_SetBits(LORA_SPI_PORT, LORA_SPI_NSS)  
#define SPI_CS_L    GPIO_ResetBits(LORA_SPI_PORT, LORA_SPI_NSS)

#define SPI_CLK_H   GPIO_SetBits(LORA_SPI_PORT, LORA_SPI_CLK) 
#define SPI_CLK_L   GPIO_ResetBits(LORA_SPI_PORT, LORA_SPI_CLK)

#define SPI_MOSI_H  GPIO_SetBits(LORA_SPI_PORT, LORA_SPI_MOSI)
#define SPI_MOSI_L  GPIO_ResetBits(LORA_SPI_PORT, LORA_SPI_MOSI) 

#define SPI_MISO  (GPIO_ReadInputDataBit(LORA_SPI_PORT, LORA_SPI_MISO) == 0x10) ? 1:0


extern void SPIWrite8bit(unsigned char WrPara);
extern unsigned char SPIRead8bit(void);

extern void SPIWriteString(unsigned char adr, unsigned char *ptr, unsigned char length);
extern void SPIReadString (unsigned char adr, unsigned char *ptr, unsigned char length);

#endif

