/* Includes ------------------------------------------------------------------*/
#include "ht24lc32.h"
#include <string.h>
/**
  * @brief  Write datum to EEPROM
  * @param  addr - EEPROM offset address
  *	    src - source datum address
  *	    len - write datum length
  * @retval error status
  * @note		Priority to page program
*/
uint8_t HT24LC32_WriteData(uint16_t addr, uint8_t *src, uint16_t len)
{
    I2C_DataBlock iic_data_blk;
    uint8_t DataBuffer[32];
    uint8_t err;
    uint16_t widx = 0, temp = 0;

    iic_data_blk.DeviceAddr = HT24LC32_ADDR;
    iic_data_blk.Option = I2C_OPT_MEM16;
    iic_data_blk.DataPtr = DataBuffer;

    while(widx < len)
    {
        iic_data_blk.DataLength = 0;
        while(1)
        {
            err = IIC_Write(iic_data_blk);
            if(!err) break;
        }
        temp = addr + widx;
        iic_data_blk.MemAddrH = temp / 256;
        iic_data_blk.MemAddrL = temp % 256;
        temp &= 0x001F;
        temp = 32 - temp;
        if(temp > (len - widx))
            iic_data_blk.DataLength = len - widx;
        else
            iic_data_blk.DataLength = temp;

        memcpy(DataBuffer, src + widx, iic_data_blk.DataLength);
        widx += iic_data_blk.DataLength;
        err = IIC_Write(iic_data_blk);
        if(err)
            return 1;
    }

    return 0;
}

/**
  * @brief  Read datum from EEPROM
  * @param  addr - EEPROM offset address
  *	    dst - destination datum address
  *	    len - read datum length
  * @retval None
  * @note		None
*/
uint8_t HT24LC32_ReadData(uint16_t addr, uint8_t *dst, uint16_t len)
{
    I2C_DataBlock iic_data_blk;
    uint8_t err;

    iic_data_blk.DeviceAddr = HT24LC32_ADDR;
    iic_data_blk.Option = I2C_OPT_MEM16;
    iic_data_blk.DataPtr = dst;
    iic_data_blk.DataLength = len;
    iic_data_blk.MemAddrH = addr / 256;
    iic_data_blk.MemAddrL = addr % 256;

    err = IIC_Read(iic_data_blk);

    return err;
}

/**********************************
*函数名：uint8_t DataChk(uint8_t *ptr, uint8_t size)
*功能：数据校验和
*参数: uint8_t *ptr 数据指针  uint8_t size 数据长度
       返回值: 校验和
*作者：wq
*创建时间：
*修改时间：
***********************************/
uint8_t DataChk(uint8_t *ptr, uint8_t size)
{
    uint8_t ii, i2;
    i2 = 0;
    for(ii = 0; ii < size; ii++)
    {
        i2 = i2 + ptr[ii];
    }
    return(i2);
}


/**********************************
*函数名：uint8_t EepromWriteData(uint16_t addr,uint8_t *dst,uint16_t len)
*功能：将数据存入EEPROM中
*参数: addr : 存储地址
       *dst : 存储数据指针
       len  : 存储数据长度
*返回值: 0 正确 1 存储错误
*备注:带校验和计算
*作者：wq
*创建时间：
*修改时间：
***********************************/
uint8_t EepromWriteData(uint16_t addr, uint8_t *dst, uint16_t len)
{
    uint8_t tmp = 0;
    IWDG_ReloadCounter();  //独立看门狗喂狗
    tmp = DataChk(dst, len - 1);
    *(dst + len - 1) = tmp;
   // if(VadcGet_2() >= 290)
    { //低压写保护
      tmp = HT24LC32_WriteData(addr, dst, len);
      return tmp;
    }
//    else
//    { 
//      return 0;
//    }
}

/**********************************
*函数名：uint8_t EepromReadData(uint16_t addr,uint8_t *dst,uint16_t len)
*功能：将数据从EEPROM中读出
*参数: addr : 读取地址
       *dst : 读取数据指针
       len  : 读取数据长度
*返回值: 0 正确 1 存储错误
*备注: 带校验和计算
*作者：wq
*创建时间：
*修改时间：
***********************************/
uint8_t EepromReadData(uint16_t addr, uint8_t *dst, uint16_t len)
{
    uint8_t tmp = 0;
    IWDG_ReloadCounter();  //喂狗函数
  
      tmp = HT24LC32_ReadData(addr, dst, len);
       DelayMs(100,TRUE);
    if(tmp)
        return 1;
    tmp = DataChk(dst, len - 1);
    if(tmp == *(dst + len - 1))
        return 0;
    else
        return 1;
}

