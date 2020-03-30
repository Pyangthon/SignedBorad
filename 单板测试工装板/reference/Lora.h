

#ifndef LORA_H
#define LORA_H


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



/**********************************
*��������unsigned char RF1278_Init(unsigned char ch,unsigned char SpreadFactor)
*���ܣ�1278��ʼ��
*����: ch Ƶ�� 0~27
       SpreadFactor ��Ƶ���� 7~12 
       ����ֵ  1 �ɹ� 0 ʧ��
*���ߣ�
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
extern unsigned char RF1278_Init(unsigned char ch,unsigned char SpreadFactor);

/**********************************
*��������void RF1278_Sleep(void)
*���ܣ���Ƶ����˯��ģʽ
*����: 
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
extern void RF1278_Sleep(void);

/**********************************
*��������unsigned char RF_FreqSet(unsigned char ch)
*���ܣ��趨��Ƶͨ��Ƶ��
*����: unsigned char ch �ŵ��� 0~82
       ���� 1 �ɹ��� 0 ʧ��  0xFF �ŵ��ų����������ֵ 
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
extern unsigned char RF1278_FreqSet(unsigned char ch);

/**********************************
*��������unsigned char RF1278_CAD(void)
*���ܣ�1278 ����һ��CAD��⣬��⵽ ����1 δ��⵽ ����0
*����: 
*���ߣ�
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: ����ʱ��ԼΪ(2^SF+32)/BW
***********************************/
extern unsigned char RF1278_CAD(void);

/**********************************
*��������void RF1278_AwakeSend(unsigned char *cbuf, unsigned char csize)
*���ܣ����ͻ������ݰ�
*����: unsigned char *cbuf ���������ݻ����ַָ��
       unsigned char csize ���������ݳ���
*���ߣ�
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: �ȷ��ͻ���ǰ���룬��������ٷ�������
***********************************/
extern void RF1278_AwakeSend(unsigned char *cbuf, unsigned char csize);


/**********************************
*��������void RF1278_SendPacket(unsigned char *cbuf, unsigned char csize)
*���ܣ��������ݰ�
*����: unsigned char *cbuf ���������ݻ����ַָ��
       unsigned char csize ���������ݳ���
*���ߣ�
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: 
***********************************/
extern void RF1278_SendPacket(unsigned char *cbuf, unsigned char csize);

/**********************************
*��������void RF1278_ReadRssiSnr(char *snr,short* rssi)
*���ܣ���ȡRSSI �� SNR ֵ
*����: 
*���ߣ�
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: 
***********************************/
extern void RF1278_ReadRssiSnr(short* rssi);
extern void RF1278_ClearIrq(void);
/**********************************
*��������void Rf1278_ModeSet(unsigned char clen)
*���ܣ�����Ϊ����ģʽ
*����: unsigned char clen �������ݳ��ȣ���ֵֻ������ģʽ����Ч����ʾģʽ��Ч
*���ߣ�
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: 
***********************************/
extern void Rf1278_ModeSet(unsigned char clen);


/**********************************
*��������unsigned char RF1278_RecePacket(unsigned char *cbuf)
*���ܣ�������Ƶ���ݰ�
*����: unsigned char *cbuf �������ݻ����ַָ��
       unsigned *Crc LoraӲ��CrcУ�� 
*���ߣ�
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
extern unsigned char RF1278_RecePacket(unsigned char *cbuf,unsigned char *Crc);

/**********************************
*��������unsigned char GetRF1278_State(void)
*���ܣ���ȡRF1278״̬
*����: ����ֵ: 0 ˯�� ��1 ���� ��2 ���� ��3 ���� 
*���ߣ�
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
extern unsigned char GetRF1278_State(void);


extern unsigned char RF1278_ReceDetect(void);

#endif



