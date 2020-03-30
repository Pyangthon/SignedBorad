/*
 * spi.c
 *
 *  Created on: 2016-9-6
 *      Author: lenovo
 */
#include "Spi.h"
#include "main.h"
#include <msp430G2955.h>

/******************SPI�ܽŽӿ�ӳ��**************************/
/*void SPI_CS_H(void)
{
	P1OUT |= BIT0;
}
void SPI_CS_L(void)
{
	P1OUT &= ~BIT0;
}

void SPI_CLK_H(void)////////////////
{
	P1OUT |= BIT6;
}
void SPI_CLK_L(void)
{
    P1OUT &= ~BIT6;
}

void SPI_MOSI_H(void)
{
    P1OUT |= BIT2;
}
void SPI_MOSI_L(void)
{
    P1OUT &= ~BIT2;
}

unsigned char SPI_MISO(void)
{
  if(P1IN & BIT7)
    return 1;
   else
    return 0;
}*/
/*Ƭѡ�ź�*/
/*
void SI_CSN_HIGH(void)
{
    P1OUT |= BIT0;
}

void SI_CSN_LOW(void)
{
    P1OUT &= ~BIT0;
}*/

/*��λ�ź�*/
/*void SI_SDN_HIGH(void)
{
    P2OUT |= BIT4;
}

void SI_SDN_LOW(void)
{
   P2OUT &= ~BIT4;
}*/

void nop(void)
{
    ;
}

/*****************��Ƶ���IO��ӳ��************************/

/*******************���Ź�ι��ӳ��************************/
void Watchdog_Reload(void)
{
    // IWDG_ReloadCounter(); //�������Ź�ι��
}

#if 0
uint8_t SPI_FLASH_SendByte(u8 byte)
{
    /* Loop while DR register in not emplty */
    while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);
    /* Send byte through the SPI1 peripheral */
    SPI_SendData(SPI1, byte);
    /* Wait to receive a byte */
    while (SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);
    /* Return the byte read from the SPI bus */
    return SPI_ReceiveData(SPI1);
}
#endif

/*===========================================================================
* ���� bSpiReadWrite() => ͨ��SPI�������ݽ���                          *
* ���� ����Ҫд��SPI��ֵ                                                    *
* ��� ��ͨ��SPI������ֵ                                                    *
============================================================================*/
uint8_t bSpiReadWrite(uint8_t tempdata )
{
#if 0
    //	Test1 = 1;
    /* Loop while DR register in not emplty */
    while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);
    /* Send byte through the SPI1 peripheral */
    SPI_SendData(SPI1, tempdata);
    /* Wait to receive a byte */
    while (SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);
    /* Return the byte read from the SPI bus */
    //  Test1 = 0;
    return SPI_ReceiveData(SPI1);
#endif
#if 1
    //CPHA=0 CPOL=0 ;ע:1.���ֽ��ȷ���2.Ҫȷ��Ƭѡ�ź���ЧʱSCK=0
    uint8_t i, ret = 0;
    //SPI_CLK_L();
    SPI_CLK_L;
    //nop();
    for(i = 0; i < 8; i++)
    {

        if(tempdata & 0x80)
            SPI_MOSI_H;
        else
            SPI_MOSI_L;

        tempdata <<= 1;

        ret <<= 1;
        if(SPI_MISO_DATE)
            ret |= 1;
        SPI_CLK_H;

        //nop();
        // nop();
        // nop();
        //  nop();
        SPI_CLK_L;
        // nop();
    }
    // nop();
    return ret;
#endif
}




void vSpi_WriteData(uint8_t Length, uint8_t *pData)
{
    while (Length--)
    {
        bSpiReadWrite(*pData++);
    }
}

void vSpi_ReadData(uint8_t Length, uint8_t *pData)
{
    // send command and get response from the radio IC
    while (Length--)
    {
        *pData++ = bSpiReadWrite(0xFF);
    }
}

uint8_t SpiReadWrite(uint8_t datain)
{
    return bSpiReadWrite(datain);
}


uint8_t SPI_ExchangeByte(uint8_t datain)
{
    return bSpiReadWrite(datain);
}

uint8_t SpiInOut(uint8_t datain)
{
    return bSpiReadWrite(datain);
}


uint8_t SPI_Read(void)
{
    uint8_t i, ret = 0;

    SPI_CLK_L;
    nop();
    for(i = 0; i < 8; i++)
    {

        ret <<= 1;
        if(SPI_MISO_DATE)
            ret |= 1;
        SPI_CLK_H;
        nop();
        SPI_CLK_L;
        nop();
    }
    return ret;
}

void SPI_Write(uint8_t tempdata)
{
    uint8_t i;
    SPI_CLK_L;
    nop();
    for(i = 0; i < 8; i++)
    {

        if(tempdata & 0x80)
            SPI_MOSI_H;
        else
            SPI_MOSI_L;

        tempdata <<= 1;

        SPI_CLK_H;
        nop();
        SPI_CLK_L;
        nop();
    }
}
