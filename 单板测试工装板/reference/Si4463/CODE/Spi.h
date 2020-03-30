/*
 * spi.h
 *
 *  Created on: 2016-9-6
 *      Author: lenovo
 */

#ifndef SPI_H_
#define SPI_H_
#include "Main.h"


#define SPI_CS_H    P1OUT |= BIT0
#define SPI_CS_L    P1OUT &= ~BIT0

#define SPI_CLK_H   P1OUT |= BIT6
#define SPI_CLK_L   P1OUT &= ~BIT6

#define SPI_MOSI_H  P1OUT |= BIT2
#define SPI_MOSI_L  P1OUT &= ~BIT2

#define SI_SDN_HIGH P2OUT |= BIT4
#define SI_SDN_LOW  P2OUT &= ~BIT4

#define SPI_MISO_DATE P1IN & BIT7

//void SI_SDN_HIGH(void);
//oid SI_SDN_LOW(void);

//extern void SI_CSN_HIGH(void);
//extern void SI_CSN_LOW(void);
extern void vSpi_WriteData(uint8_t Length, uint8_t *pData);
extern void vSpi_ReadData(uint8_t Length, uint8_t *pData);
extern uint8_t SpiReadWrite(uint8_t datain);
extern uint8_t SPI_ExchangeByte(uint8_t datain);


extern uint8_t SPI_Read(void);
extern void SPI_Write(uint8_t tempdata);
//#define IWDG_ReloadCounter()  {;}

#endif /* SPI_H_ */
