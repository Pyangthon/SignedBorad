/*******************************************************************************
  * @file
  * @author
  * @version
  * @date
  * @brief
  */

/* Includes ------------------------------------------------------------------*/

#include "mcu_i2c.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void DELAY(uint8_t dly);
void IIC_START(void);
void IIC_STOP(void);
uint8_t IIC_SENDBYTE(uint8_t dat);
uint8_t IIC_RECVBYTE(uint8_t ack);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  I2C SCL clock delay
  * @param  dly - delay time
  * @retval None
  * @note		None
*/
void DELAY(uint8_t dly)
{
    dly *= 5;
    while(dly--);
}

/**
  * @brief  Generate IIC Start condition
  * @param  None
  * @retval None
  * @note		None
*/
void IIC_START(void)
{
    SDA_1;
    SCL_1;
    DELAY(10);
    SDA_0;
    DELAY(10);
    SCL_0;
    DELAY(10);
}

/**
  * @brief  Generate IIC Stop condition
  * @param  None
  * @retval None
  * @note		None
*/
void IIC_STOP(void)
{
    SDA_0;
    SCL_1;
    DELAY(10);
    SDA_1;
    DELAY(10);
}

/**
  * @brief  IIC Send a byte data
  * @param  dat - send data
  * @retval 0 - No ACK signal
  *					1 - Detect ACK signal
  * @note		None
*/
uint8_t IIC_SENDBYTE(uint8_t dat)
{
    uint8_t idx = 0;
    uint8_t ack = 0;

    SET_SDA_OUT();

    for(; idx < 8; idx ++)						// Send byte data MSB
    {
        if(dat & 0x80)
            SDA_1;
        else
            SDA_0;
        DELAY(5);
        SCL_1;
        DELAY(5);
        SCL_0;
        dat <<= 1;
    }
    SET_SDA_IN();
    SCL_1;
    DELAY(5);													// Detect ACK signal
    if(!SDAM) ack = 1;
    SCL_0;
    DELAY(5);
    SET_SDA_OUT();

    return ack;
}

/**
  * @brief  IIC Receive a byte data
  * @param  ack  0/1 -> Dont sned/Send ACK signal
  * @retval receive data
  * @note		None
*/
uint8_t IIC_RECVBYTE(uint8_t ack)
{
    uint8_t idx = 0;
    uint8_t ret = 0;

    SET_SDA_IN();

    for(; idx < 8; idx ++)						// Receive byte data MSB
    {
        ret <<= 1;
        SCL_1;
        DELAY(5);
        if(SDAM) ret |= 0x01;
        SCL_0;
        DELAY(5);
    }

    SET_SDA_OUT();
    if(ack) 													// Send ACK Signal
        SDA_0;
    else
        SDA_1;
    SCL_1;
    DELAY(5);
    SCL_0;
    DELAY(5);

    return ret;

}

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Initilization I2C Interface
  * @param  None
  * @retval None
  * @note		None
*/
void IIC_Init(void)
{
   SET_SCL_OUT();
   SET_SDA_OUT();
}

/**
  * @brief  IIC Write device register
  * @param  blk : I2C Transmit Data Block
  * @retval 0 - success
  *					other - fail
  * @note		None
*/
uint8_t IIC_Write(I2C_DataBlock blk)
{
    uint8_t ack = 0;
    uint16_t idx = 0;

    IIC_Init();

    IIC_START();
    ack = IIC_SENDBYTE(blk.DeviceAddr & 0xFE);
    if(!ack) return 1;
    if(blk.Option & I2C_OPT_MEM16)
        ack = IIC_SENDBYTE(blk.MemAddrH);
    if(!ack) return 1;
      ack = IIC_SENDBYTE(blk.MemAddrL);
    if(!ack) return 1;
    for(; idx < blk.DataLength; idx++)
    {
        ack = IIC_SENDBYTE(*(blk.DataPtr++));
        if(!ack) 
          return 1;
    }
    IIC_STOP();

    return 0;
}

/**
  * @brief  IIC Read device register
  * @param  blk : I2C Receive Data Block
  * @retval 0 - success
  *	@other - fail
  * @note		None
*/
uint8_t IIC_Read(I2C_DataBlock blk)
{
    uint8_t ack = 0;
    uint16_t idx = 0;

    IIC_Init();

    IIC_START();
    ack = IIC_SENDBYTE(blk.DeviceAddr & 0xFE);
    if(!ack) return 1;
    if(blk.Option & I2C_OPT_MEM16)
        ack = IIC_SENDBYTE(blk.MemAddrH);
    if(!ack) return 1;
    ack = IIC_SENDBYTE(blk.MemAddrL);
    if(!ack)
        return 1;
    IIC_START();
    ack = IIC_SENDBYTE(blk.DeviceAddr | 0x01);
    if(!ack) return 1;
    idx = 1;
    for(; idx <= blk.DataLength; idx++)
    {
        *blk.DataPtr++ = IIC_RECVBYTE(idx < blk.DataLength);
    }
    IIC_STOP();

    return 0;
}

/******************************* END OF FILE **********************************/
