

#ifndef LORA_H
#define LORA_H

#include "LoraSpiGpio.h"

/**********************************
*函数名：unsigned char RF1278_Init(unsigned char ch,unsigned char SpreadFactor)
*功能：1278初始化
*参数: ch 频道 0~27
       SpreadFactor 扩频因子 7~12 
       返回值  1 成功 0 失败
*作者：
*创建时间：
*修改时间：
***********************************/
extern unsigned char RF1278_Init(unsigned char ch,unsigned char SpreadFactor);

/**********************************
*函数名：void RF1278_Sleep(void)
*功能：射频进入睡眠模式
*参数: 
*创建时间：
*修改时间：
***********************************/
extern void RF1278_Sleep(void);

/**********************************
*函数名：unsigned char RF_FreqSet(unsigned char ch)
*功能：设定射频通信频率
*参数: unsigned char ch 信道号 0~82
       返回 1 成功； 0 失败  0xFF 信道号超出最大设置值 
*创建时间：
*修改时间：
***********************************/
extern unsigned char RF1278_FreqSet(unsigned char ch);

/**********************************
*函数名：unsigned char RF1278_CAD(void)
*功能：1278 进行一次CAD检测，检测到 返回1 未检测到 返回0
*参数: 
*作者：
*创建时间：
*修改时间：
*说明: 采样时间约为(2^SF+32)/BW
***********************************/
extern unsigned char RF1278_CAD(void);

/**********************************
*函数名：void RF1278_AwakeSend(unsigned char *cbuf, unsigned char csize)
*功能：发送唤醒数据包
*参数: unsigned char *cbuf 待发送数据缓存地址指针
       unsigned char csize 待发送数据长度
*作者：
*创建时间：
*修改时间：
*说明: 先发送唤醒前导码，发送完后再发送数据
***********************************/
extern void RF1278_AwakeSend(unsigned char *cbuf, unsigned char csize);


/**********************************
*函数名：void RF1278_SendPacket(unsigned char *cbuf, unsigned char csize)
*功能：发送数据包
*参数: unsigned char *cbuf 待发送数据缓存地址指针
       unsigned char csize 待发送数据长度
*作者：
*创建时间：
*修改时间：
*说明: 
***********************************/
extern void RF1278_SendPacket(unsigned char *cbuf, unsigned char csize);

/**********************************
*函数名：void RF1278_ReadRssiSnr(char *snr,short* rssi)
*功能：读取RSSI 和 SNR 值
*参数: 
*作者：
*创建时间：
*修改时间：
*说明: 
***********************************/
extern void RF1278_ReadRssiSnr(unsigned char* rssi);

/**********************************
*函数名：void Rf1278_ModeSet(unsigned char clen)
*功能：设置为接收模式
*参数: unsigned char clen 接收数据长度，该值只对隐试模式下有效，显示模式无效
*作者：
*创建时间：
*修改时间：
*说明: 
***********************************/
extern void Rf1278_ModeSet(unsigned char clen);


/**********************************
*函数名：unsigned char RF1278_RecePacket(unsigned char *cbuf)
*功能：接收射频数据包
*参数: unsigned char *cbuf 接收数据缓存地址指针
       unsigned *Crc Lora硬件Crc校验 
*作者：
*创建时间：
*修改时间：
***********************************/
extern void RF1278_RecePacket(unsigned char *cbuf,unsigned char len);

/**********************************
*函数名：unsigned char GetRF1278_State(void)
*功能：获取RF1278状态
*参数: 返回值: 0 睡眠 ，1 接收 ，2 发送 ，3 待机 
*作者：
*创建时间：
*修改时间：
***********************************/
extern unsigned char GetRF1278_State(void);
extern unsigned char RF1278_ReceDetect(void);
extern void RF1278_ClearIrq(void);
extern unsigned char RF1278_RF1278_ReadRssiOld(void);
extern unsigned char RF1278_RecePacketLenht(unsigned char *Crc);
extern unsigned char RF1278_RecePacketDate(unsigned char *cbuf,unsigned char *Crc);
extern void RF1278_Standby(void);
extern void SPIWrite8bit(unsigned char WrPara);
extern unsigned char SPIRead8bit(void);
extern void SPIWriteString(unsigned char adr, unsigned char *ptr, unsigned char length);
extern void RF1278_EntryLoRa(void);
extern void RF1278_CadSample(void);
extern void RF1278_CadInit(void); 
extern unsigned char RF1278_Init(unsigned char ch,unsigned char SpreadFactor);
extern void RF1278_TxRxEN( unsigned char txEnable);


#endif



