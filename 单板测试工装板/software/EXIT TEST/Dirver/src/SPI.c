#include "SPI.h"



//unsigned char SPI_MISO(void)
//{   
//   if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4))
//    return 1;
//   else
//    return 0;
//}

//******************************************************************************************************
//*��������void SPIWrite8bit(unsigned char WrPara)
//*���ܣ�SPI����д�� 8bit
//*����: WrPara д����������
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
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
//*��������unsigned char SPIRead8bit(void)
//*���ܣ�SPI���ݶ�ȡ 8bit
//*����: ���ض�ȡ����
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
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
////*��������unsigned char SPIRead8bit(void)
////*���ܣ��Ƕ���ַ��ȡ����
////*����: ���ض�ȡ����
////*���ߣ�wq
////*����ʱ�䣺
////*�޸�ʱ�䣺
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
//*��������void SPIReadString(unsigned char adr, unsigned char *ptr, unsigned char length)
//*���ܣ���ָ����ַ��ȡָ����������
//*����: unsigned char adr �׵�ַ
//       unsigned char *ptr �������ݻ�����ָ��
//       unsigned char length ��ȡ���ݳ���
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
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
//*��������void SPIWriteString(unsigned char adr, unsigned char *ptr, unsigned char length)
//*���ܣ���ָ����ַд��ָ����������
//*����: unsigned char adr �׵�ַ
//       unsigned char *ptr ��д�����ݻ�����ָ��
//       unsigned char length д�����ݳ���
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
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




