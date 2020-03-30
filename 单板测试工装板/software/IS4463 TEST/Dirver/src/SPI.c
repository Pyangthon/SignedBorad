#include "SPI.h"



//unsigned char SPI_MISO(void)
//{   
//   if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4))
//    return 1;
//   else
//    return 0;
//}

//******************************************************************************************************
//*函数名：void SPIWrite8bit(unsigned char WrPara)
//*功能：SPI数据写入 8bit
//*参数: WrPara 写入数据内容
//*作者：wq
//*创建时间：
//*修改时间：
//*******************************************************************************************************/
void SPIWrite8bit(unsigned char WrPara)
{
    unsigned char bitcnt;
    SPI_CS_L;
    SPI_CLK_L;
    for(bitcnt = 8; bitcnt != 0; bitcnt--)
    {
        SPI_CLK_L;
        if(WrPara & 0x80)
            SPI_MOSI_H;
        else
            SPI_MOSI_L;
        asm("nop");
        asm("nop");
        SPI_CLK_H;
        asm("nop");
        WrPara <<= 1;
    }
    SPI_CLK_L;
    SPI_MOSI_H;
   // SPI_CS_H;
}

///******************************************************************************************************
//*函数名：unsigned char SPIRead8bit(void)
//*功能：SPI数据读取 8bit
//*参数: 返回读取数据
//*作者：wq
//*创建时间：
//*修改时间：
//*******************************************************************************************************/
unsigned char SPIRead8bit(void)
{
    unsigned char RdPara = 0;
    unsigned char bitcnt = 0;
    SPI_CS_L;
    SPI_MOSI_H;
    for(bitcnt = 8; bitcnt != 0; bitcnt--)
    {       
        SPI_CLK_L;
        asm("nop");
        asm("nop");
        RdPara <<= 1;
        SPI_CLK_H;
        if(SPI_MISO)
            RdPara |= 0x01;
        else
            RdPara |= 0x00;
    }
    SPI_CLK_L;
    //SPI_CS_H;
    return(RdPara);
}

/////******************************************************************************************************
////*函数名：unsigned char SPIRead8bit(void)
////*功能：是定地址读取数据
////*参数: 返回读取数据
////*作者：wq
////*创建时间：
////*修改时间：
////*******************************************************************************************************/
//unsigned char SPIRead(unsigned char adr)
//{
//    unsigned char tmp;
//      SPIWrite8bit(adr);  //Send address first
//    tmp = SPIRead8bit();
//    SPI_CS_H;
//    return(tmp);
//}
//
/////*******************************************************************************
////**Name:     SPIWrite
////**Function: SPI Write CMD
////**Input:    WrPara -> address & data
////**Output:   None
////*******************************************************************************/
//void SPIWrite(unsigned short WrPara)
//{
//    unsigned char bitcnt;
//    SPI_CLK_L; 
//    SPI_CS_L; 
//    WrPara |= 0x8000;                                  //MSB must be "1" for write
//    for(bitcnt = 16; bitcnt != 0; bitcnt--)
//    {
//        SPI_CLK_L;
//        asm("nop");
//        asm("nop");
//        if(WrPara & 0x8000)
//            SPI_MOSI_H;
//        else
//            SPI_MOSI_L;
//        SPI_CLK_H;
//        WrPara <<= 1;
//    }
//    SPI_CLK_L;
//    SPI_MOSI_H; 
//    SPI_CS_H;
//}

///******************************************************************************************************
//*函数名：void SPIReadString(unsigned char adr, unsigned char *ptr, unsigned char length)
//*功能：从指定地址读取指定长度数据
//*参数: unsigned char adr 首地址
//       unsigned char *ptr 读出数据缓存区指针
//       unsigned char length 读取数据长度
//*作者：wq
//*创建时间：
//*修改时间：
//*******************************************************************************************************/
void SPIReadString(unsigned char adr, unsigned char *ptr, unsigned char length)
{
    unsigned char i;
    if(length <= 1)                                    //length must more than one
        return;
    else
    {
        SPI_CLK_L;
        SPI_CS_L;
        SPIWrite8bit(adr);
        for(i = 0; i < length; i++)
            ptr[i] = SPIRead8bit();
        SPI_CS_H;
    }
}

///******************************************************************************************************
//*函数名：void SPIWriteString(unsigned char adr, unsigned char *ptr, unsigned char length)
//*功能：从指定地址写入指定长度数据
//*参数: unsigned char adr 首地址
//       unsigned char *ptr 待写入数据缓存区指针
//       unsigned char length 写入数据长度
//*作者：wq
//*创建时间：
//*修改时间：
//*******************************************************************************************************/
void SPIWriteString(unsigned char adr, unsigned char *ptr, unsigned char length)
{
    unsigned char i;
    if(length <= 1)                                    //length must more than one
        return;
    else
    {
        SPI_CLK_L;
        SPI_CS_L;
        SPIWrite8bit(adr | 0x80);
        for(i = 0; i < length; i++)
            SPIWrite8bit(ptr[i]);
        SPI_CS_H;
    }
}




