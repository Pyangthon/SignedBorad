

#include "Lora.h"


//RF Internal registers Address
#define LR_RegFifo                                  0x0000
// Common settings
#define LR_RegOpMode                                0x0100
#define LR_RegFrMsb                                 0x0600
#define LR_RegFrMid                                 0x0700
#define LR_RegFrLsb                                 0x0800
// Tx settings
#define LR_RegPaConfig                              0x0900
#define LR_RegPaRamp                                0x0A00
#define LR_RegOcp                                   0x0B00
// Rx settings
#define LR_RegLna                                   0x0C00
// LoRa registers
#define LR_RegFifoAddrPtr                           0x0D00
#define LR_RegFifoTxBaseAddr                        0x0E00
#define LR_RegFifoRxBaseAddr                        0x0F00
#define LR_RegFifoRxCurrentaddr                     0x1000
#define LR_RegIrqFlagsMask                          0x1100
#define LR_RegIrqFlags                              0x1200
#define LR_RegRxNbBytes                             0x1300
#define LR_RegRxHeaderCntValueMsb                   0x1400
#define LR_RegRxHeaderCntValueLsb                   0x1500
#define LR_RegRxPacketCntValueMsb                   0x1600
#define LR_RegRxPacketCntValueLsb                   0x1700
#define LR_RegModemStat                             0x1800
#define LR_RegPktSnrValue                           0x1900
#define LR_RegPktRssiValue                          0x1A00
#define LR_RegRssiValue                             0x1B00
#define LR_RegHopChannel                            0x1C00
#define LR_RegModemConfig1                          0x1D00
#define LR_RegModemConfig2                          0x1E00
#define LR_RegSymbTimeoutLsb                        0x1F00
#define LR_RegPreambleMsb                           0x2000
#define LR_RegPreambleLsb                           0x2100
#define LR_RegPayloadLength                         0x2200
#define LR_RegMaxPayloadLength                      0x2300
#define LR_RegHopPeriod                             0x2400
#define LR_RegFifoRxByteAddr                        0x2500
#define LR_RegModemConfig3                          0x2600

#define LR_RegFeiMsb                                0x2800
#define LR_RegFeiMid                                0x2900
#define LR_RegFeiLsb                                0x2A00

// I/O settings
#define REG_LR_DIOMAPPING1                          0x4000
#define REG_LR_DIOMAPPING2                          0x4100
// Version
#define REG_LR_VERSION                              0x4200
// Additional settings
#define REG_LR_PLLHOP                               0x4400
#define REG_LR_TCXO                                 0x4B00
#define REG_LR_PADAC                                0x4D00
#define REG_LR_FORMERTEMP                           0x5B00

#define REG_LR_AGCREF                               0x6100
#define REG_LR_AGCTHRESH1                           0x6200
#define REG_LR_AGCTHRESH2                           0x6300
#define REG_LR_AGCTHRESH3                           0x6400



//===================================�������===================================

__root const unsigned short  RFM96FreqTbl[] =
{
#if 0
    0x066c, 0x0744, 0x0806, //433,062,866  CH0
    0x066c, 0x0780, 0x0806, //434,000,366  CH1
    0x066c, 0x07BC, 0x0806, //434,937,866  CH2 
    0x066c, 0x07F8, 0x0806, //435,875,366  CH3 
    0x066d, 0x0734, 0x0806, //436,812,866  CH4 
    0x066d, 0x0770, 0x0806, //437,750,366  CH5 
    0x066d, 0x07ac, 0x0806, //438,687,866  CH6
    0x066d, 0x07e8, 0x0806, //439,625,366  CH7
    0x066e, 0x0724, 0x0806, //440,562,866  CH8
    0x066e, 0x0760, 0x0806, //441,500,366  CH9  
    0x066e, 0x079c, 0x0806, //442,437,866  CH10
    0x066e, 0x07D8, 0x0806, //443,375,366  CH11
    0x066f, 0x0714, 0x0806, //444,312,866  CH12
    0x066f, 0x0750, 0x0806, //445,250,366  CH13 
    0x066f, 0x078c, 0x0806, //446,187,866  CH14
    0x066f, 0x07C8, 0x0806, //447,125,366  CH15
    0x0670, 0x0704, 0x0806, //448,062,866  CH16
    0x0670, 0x0740, 0x0806, //449,000,366  CH17 
    0x0670, 0x077C, 0x0806, //449,937,866  CH18
    0x0670, 0x07B8, 0x0806, //450,875,366  CH19
    0x0670, 0x07F4, 0x0806, //451,812,866  CH20
    0x0671, 0x0730, 0x0806, //452,750,366  CH21
    0x0671, 0x076C, 0x0806, //453,687,866  CH22 
    0x0671, 0x07A8, 0x0806, //454,625,366  CH23
    0x0671, 0x07E4, 0x0806, //455,562,866  CH24
    0x0672, 0x0720, 0x0806, //456,500,366  CH25
    0x0672, 0x075C, 0x0806, //457,437,866  CH26 
    0x0672, 0x0798, 0x0806, //458,375,366  CH27
    0x0672, 0x07D4, 0x0806, //459,312,866  CH28
    0x0673, 0x0710, 0x0806, //460,250,366  CH29
    0x0673, 0x074C, 0x0806, //461,187,866  CH30 
    0x0673, 0x0788, 0x0806, //462,125,366  CH31
    0x0673, 0x07C4, 0x0806, //463,062,866  CH32
    0x0674, 0x0700, 0x0806, //464,000,366  CH33
    0x0674, 0x073C, 0x0806, //464,937,866  CH34 
    0x0674, 0x0778, 0x0806, //465,875,366  CH35
    0x0674, 0x07B4, 0x0806, //466,812,866  CH36
    0x0674, 0x07F0, 0x0806, //467,750,366  CH37
    0x0675, 0x072C, 0x0806, //468,687,866  CH38  
    0x0675, 0x0768, 0x0806, //469,625,366  CH39 
    0x0675, 0x07A4, 0x0806, //470,562,866  CH40
    0x0675, 0x07E0, 0x0806, //471,500,366  CH41
    0x0676, 0x071C, 0x0806, //472,437,866  CH42
    0x0676, 0x0758, 0x0806, //473,375,366  CH43
    0x0676, 0x0794, 0x0806, //474,312,866  CH44   
    0x0676, 0x07D0, 0x0806, //475,250,366  CH45
    0x0677, 0x070C, 0x0806, //476,187,866  CH46
    0x0677, 0x0748, 0x0806, //477,125,366  CH47
    0x0677, 0x0784, 0x0806, //478,062,866  CH48
    0x0677, 0x07C0, 0x0806, //479,000,366  CH49
    0x0677, 0x07FC, 0x0806, //479,937,866  CH50
    0x0678, 0x0738, 0x0806, //480,875,366  CH51
    0x0678, 0x0774, 0x0806, //481,812,866  CH52
    0x0678, 0x07B0, 0x0806, //482,750,366  CH53
    0x0678, 0x07EC, 0x0806, //483,687,866  CH54
    0x0679, 0x0728, 0x0806, //484,625,366  CH55
    0x0679, 0x0764, 0x0806, //485,562,866  CH56
    0x0679, 0x07A0, 0x0806, //486,500,366  CH57
    0x0679, 0x07DC, 0x0806, //487,437,866  CH58 
    0x067A, 0x0718, 0x0806, //488,375,366  CH59
    0x067A, 0x0754, 0x0806, //489,312,866  CH60
    0x067A, 0x0790, 0x0806, //490,250,366  CH61
    0x067A, 0x07CC, 0x0806, //491,187,866  CH62
    0x067B, 0x0708, 0x0806, //492,125,366  CH63
    0x067B, 0x0744, 0x0806, //493,062,866  CH64
    0x067B, 0x0780, 0x0806, //494,000,366  CH65
    0x067B, 0x07BC, 0x0806, //494,937,866  CH66
    0x067B, 0x07F8, 0x0806, //495,875,366  CH67
    0x067C, 0x0734, 0x0806, //496,812,866  CH68
    0x067C, 0x0770, 0x0806, //497,750,366  CH69
    0x067C, 0x07AC, 0x0806, //498,687,866  CH70
    0x067C, 0x07E8, 0x0806, //499,625,366  CH71
    0x067D, 0x0724, 0x0806, //500,562,866  CH72
    0x067D, 0x0760, 0x0806, //501,500,366  CH73
    0x067D, 0x079C, 0x0806, //502,437,866  CH74
    0x067D, 0x07D8, 0x0806, //503,375,366  CH75
    0x067E, 0x0714, 0x0806, //504,312,866  CH76
    0x067E, 0x0750, 0x0806, //505,250,366  CH77
    0x067E, 0x078C, 0x0806, //506,187,866  CH78
    0x067E, 0x07C8, 0x0806, //507,125,366  CH79
    0x067F, 0x0704, 0x0806, //508,062,866  CH80
    0x067F, 0x0740, 0x0806, //509,000,366  CH81
    0x067F, 0x077C, 0x0806, //509,937,866  CH82
 #endif  
 #if 1
     //0x067C,0x07E6,0x0866,     //499600000 CH27
     0x0678,0x072C,0x08CD,     //480700000 CH0 
     0x0678,0x0759,0x089A,     //481400000 CH1 
     0x0678,0x0786,0x0866,     //482100000 CH2 
     0x0678,0x07B3,0x0833,     //482800000 CH3 
     0x0678,0x07E0,0x0800,     //483500000 CH4 
     0x0679,0x070C,0x08CD,     //484200000 CH5 
     0x0679,0x0739,0x089A,     //484900000 CH6 
     0x0679,0x0766,0x0866,     //485600000 CH7 
     0x0679,0x0793,0x0833,     //486300000 CH8 
     0x0679,0x07C0,0x0800,     //487000000 CH9 
     0x0679,0x07EC,0x08CD,     //487700000 CH10
     0x067A,0x0719,0x089A,     //488400000 CH11
     0x067A,0x0746,0x0866,     //489100000 CH12
     0x067A,0x0773,0x0833,     //489800000 CH13
     0x067A,0x07A0,0x0800,     //490500000 CH14
     0x067A,0x07CC,0x08CD,     //491200000 CH15
     0x067A,0x07F9,0x089A,     //491900000 CH16
     0x067B,0x0726,0x0866,     //492600000 CH17
     0x067B,0x0753,0x0833,     //493300000 CH18
     0x067B,0x0780,0x0800,     //494000000 CH19
     0x067B,0x07AC,0x08CD,     //494700000 CH20
     0x067B,0x07D9,0x089A,     //495400000 CH21
     0x067C,0x0706,0x0866,     //496100000 CH22
     0x067C,0x0733,0x0833,     //496800000 CH23
     0x067C,0x0760,0x0800,     //497500000 CH24
     0x067C,0x078C,0x08CD,     //498200000 CH25
     0x067C,0x07B9,0x089A,     //498900000 CH26
     0x067C,0x07E6,0x0866,     //499600000 CH27
 #endif    
};



__root const unsigned short RFM96PowerTbl[4] =
{
    0x09FF,                   //20dbm
    0x09FC,                   //17dbm
    0x09F9,                   //14dbm
    0x09F6,                   //11dbm
};
__root const unsigned char RFM96SpreadFactorTbl[7] =
{
     7, 8, 9, 10, 11, 12
};

__root const unsigned char RFM96LoRaBwTbl[10] =
{
    // 0        1     2       3      4       5         6      7       8      9
    //7.8KHz,10.4KHz,15.6KHz,20.8KHz,31.2KHz,41.7KHz,62.5KHz,125KHz,250KHz,500KHz
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};




/******************LORA��ز���************************/
static unsigned char LoraPower = 0;  //����
static unsigned char LoraBw = 7;     //����
unsigned char        LoraSF = 2;             //SF ��Ƶ���� 
static unsigned char LoraFreq = 0;   //Ƶ��
static unsigned char LoraCR = 1;     //��������
static unsigned char LoraCRC = 1;    //��CRCУ��

static unsigned char RF1278_State = 0;  //1278״̬  0 Ϊ˯�� 1 Ϊ���� 2 Ϊ���� 3 Ϊ����



extern void RF1278_EntryLoRa(void);
/**********************************
*��������void SPIWrite8bit(unsigned char WrPara)
*���ܣ�SPI����д�� 8bit
*����: WrPara д����������
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void SPIWrite8bit(unsigned char WrPara)
{
    unsigned char bitcnt;
    SPI_CS_L();
    SPI_CLK_L();
    for(bitcnt = 8; bitcnt != 0; bitcnt--)
    {
        SPI_CLK_L();
        if(WrPara & 0x80)
            SPI_MOSI_H();
        else
            SPI_MOSI_L();
        asm("nop");
        asm("nop");
        SPI_CLK_H();
        asm("nop");
        WrPara <<= 1;
    }
    SPI_CLK_L();
    SPI_MOSI_H();
}

/**********************************
*��������unsigned char SPIRead8bit(void)
*���ܣ�SPI���ݶ�ȡ 8bit
*����: ���ض�ȡ����
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
unsigned char SPIRead8bit(void)
{
    unsigned char RdPara = 0;
    unsigned char bitcnt = 0;
    SPI_CS_L();
    SPI_MOSI_H();
    for(bitcnt = 8; bitcnt != 0; bitcnt--)
    {       
        SPI_CLK_L();
        asm("nop");
        asm("nop");
        RdPara <<= 1;
        SPI_CLK_H();
        if(SPI_MISO())
            RdPara |= 0x01;
        else
            RdPara |= 0x00;
    }
    SPI_CLK_L();
    return(RdPara);
}

/**********************************
*��������unsigned char SPIRead8bit(void)
*���ܣ��Ƕ���ַ��ȡ����
*����: ���ض�ȡ����
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
unsigned char SPIRead(unsigned char adr)
{
    unsigned char tmp;
    SPIWrite8bit(adr);  //Send address first
    tmp = SPIRead8bit();
    SPI_CS_H();
    return(tmp);
}

/*******************************************************************************
**Name:     SPIWrite
**Function: SPI Write CMD
**Input:    WrPara -> address & data
**Output:   None
*******************************************************************************/
void SPIWrite(unsigned short WrPara)
{
    unsigned char bitcnt;
    SPI_CLK_L(); 
    SPI_CS_L(); 
    WrPara |= 0x8000;                                  //MSB must be "1" for write
    for(bitcnt = 16; bitcnt != 0; bitcnt--)
    {
        SPI_CLK_L();
        asm("nop");
        asm("nop");
        if(WrPara & 0x8000)
            SPI_MOSI_H();
        else
            SPI_MOSI_L();
        SPI_CLK_H();
        WrPara <<= 1;
    }
    SPI_CLK_L();
    SPI_MOSI_H(); 
    SPI_CS_H();
}

/**********************************
*��������void SPIReadString(unsigned char adr, unsigned char *ptr, unsigned char length)
*���ܣ���ָ����ַ��ȡָ����������
*����: unsigned char adr �׵�ַ
       unsigned char *ptr �������ݻ�����ָ��
       unsigned char length ��ȡ���ݳ���
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void SPIReadString(unsigned char adr, unsigned char *ptr, unsigned char length)
{
    unsigned char i;
    if(length <= 1)                                    //length must more than one
        return;
    else
    {
        SPI_CLK_L();
        SPI_CS_L();
        SPIWrite8bit(adr);
        for(i = 0; i < length; i++)
            ptr[i] = SPIRead8bit();
        SPI_CS_H();
    }
}

/**********************************
*��������void SPIWriteString(unsigned char adr, unsigned char *ptr, unsigned char length)
*���ܣ���ָ����ַд��ָ����������
*����: unsigned char adr �׵�ַ
       unsigned char *ptr ��д�����ݻ�����ָ��
       unsigned char length д�����ݳ���
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void SPIWriteString(unsigned char adr, unsigned char *ptr, unsigned char length)
{
    unsigned char i;
    if(length <= 1)                                    //length must more than one
        return;
    else
    {
        SPI_CLK_L();
        SPI_CS_L();
        SPIWrite8bit(adr | 0x80);
        for(i = 0; i < length; i++)
            SPIWrite8bit(ptr[i]);
        SPI_CS_H();
    }
}

/**********************************
*��������unsigned char RF_FreqSet(unsigned char ch)
*���ܣ��趨��Ƶͨ��Ƶ��
*����: unsigned char ch �ŵ��� 0~82
       ���� 1 �ɹ��� 0 ʧ��
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
unsigned char RF1278_FreqSet(unsigned char ch)
{
    unsigned char test_FRFMSB = 0, test_FRFMID = 0, test_FRFLSB = 0;

    if(ch > 27)
        return 0;
    LoraFreq = ch;
    RF1278_EntryLoRa(); //�����ģʽ������������Ƶ�β���

    SPIWrite(RFM96FreqTbl[3 * ch]);
    SPIWrite(RFM96FreqTbl[3 * ch + 1]);
    SPIWrite(RFM96FreqTbl[3 * ch + 2]);
    test_FRFMSB = SPIRead(0x06);
    test_FRFMID = SPIRead(0x07);
    test_FRFLSB = SPIRead(0x08);
    if(test_FRFMSB != ((RFM96FreqTbl[3 * ch] & 0x00FF)))
        return 0;
    if(test_FRFMID != ((RFM96FreqTbl[3 * ch + 1] & 0x00FF)))
        return 0;
    if(test_FRFLSB != ((RFM96FreqTbl[3 * ch + 2] & 0x00FF)))
        return 0;
    return 1;
}

/**********************************
*��������void RF_TxRxEN( unsigned char txEnable)
*���ܣ��շ�ʹ��,������Ƶ����
*����: txEnable: 0 RX  1 TX 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void RF1278_TxRxEN( unsigned char txEnable)
{
    if( txEnable != 0 )       //���Ϊ�棬ΪTX
    {
        RF_RX_EN_L();
        RF_TX_EN_H();
    }
    else  //Ϊ�٣�ΪRX
    {
        RF_RX_EN_H();
        RF_TX_EN_L();        
    }
}

/**********************************
*��������void RF1278_Sleep(void)
*���ܣ���Ƶ˯��ģʽ
*����: 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void RF1278_Sleep(void)
{
    SPIWrite(LR_RegOpMode + 0x00 + 0x80);                          //Sleep
    RF_RX_EN_L();//˯��ģʽ�ϵ͹���
    RF_TX_EN_L();//˯��ģʽ�ϵ͹���  
    RF1278_State = 0; //˯��״̬
}

/**********************************
*��������void RF1278_EntryLoRa(void)
*���ܣ���Ƶ����LORAģʽ
*����: 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void RF1278_EntryLoRa(void)
{
    SPIWrite(LR_RegOpMode + 0x80 + 0x08);
}

/**********************************
*��������void RF1278_ClearIrq(void)
*���ܣ���1278�ڲ��жϱ�־λ
*����: 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void RF1278_ClearIrq(void)
{
    SPIWrite(LR_RegIrqFlags + 0xFF);
}


/**********************************
*��������void RF1278_Standby(void)
*���ܣ�1278�������״̬
*����: 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void RF1278_Standby(void)
{
    SPIWrite(LR_RegOpMode + 0x01 + 0x80);                                //Standby
    RF1278_State = 3;   //����״̬
}

/**********************************
*��������unsigned char GetRF1278_State(void)
*���ܣ���ȡRF1278״̬
*����: ����ֵ: 0 ˯�� ��1 ���� ��2 ���� ��3 ���� 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
unsigned char GetRF1278_State(void)
{
    if(RF1278_State < 4)
        return RF1278_State;
    else
        return 0xFF;
}


static void delayms(unsigned int t)
{
    unsigned int i;
    unsigned short j;
    for(i = 0; i < t; i++)
        for(j = 0; j < 3207; j++);
}
/**********************************
*��������unsigned char RF1278_Init(unsigned char ch)
*���ܣ�1278��ʼ��
*����: ch Ƶ�� 
       ����ֵ  1 �ɹ� 0 ʧ��
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
unsigned char RF1278_Init(unsigned char ch,unsigned char SpreadFactor)
{
    unsigned char tmp;
    if(SpreadFactor > 5)
       // SpreadFactor = 2;  //Ĭ��ֵ
       return 0;
    if(ch > 27)
       // ch = 0;     //Ĭ��ֵ
        return 0;
    LoraFreq = ch;
    LoraSF = SpreadFactor;
    RF_RST_L();
    delayms(1);   //Delay >100us
    RF_RST_H();
    delayms(10);   //Delay > 5ms
    RF1278_Sleep(); //Change modem mode Must in Sleep mode
    delayms(10);   //Delay > 5ms
    RF1278_EntryLoRa();//Set RFM69 entry LoRa(LongRange) mode

    if(RF1278_FreqSet(LoraFreq) == 0)
        return(0);//setting frequency parameter
        
    //setting base parameter
    SPIWrite(RFM96PowerTbl[LoraPower]);     //Setting output power parameter
    SPIWrite(LR_RegOcp + 0x1f);          //RegOcp,Close Ocp
    SPIWrite(LR_RegLna + 0x23);          //RegLNA,High & LNA Enable
   //2015-10-23 ���ӵ�20dbm����
    SPIWrite(REG_LR_PADAC +0x87);
   
    if(RFM96SpreadFactorTbl[LoraSF] == 6) //SFactor=6
    {
        
        SPIWrite(LR_RegModemConfig1 + (RFM96LoRaBwTbl[LoraBw] << 4) + (LoraCR<< 1) + 0x01); //Implicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
        SPIWrite(LR_RegModemConfig2 + (RFM96SpreadFactorTbl[LoraSF] << 4) + (LoraCRC<< 2) + 0x03);

        tmp = SPIRead(0x31);
        tmp &= 0xF8;
        tmp |= 0x05;
        SPIWrite(0x3100 + tmp);
        SPIWrite(0x3700 + 0x0C);
    }
    else
    {
        SPIWrite(LR_RegModemConfig1 + (RFM96LoRaBwTbl[LoraBw] << 4) + (LoraCR << 1) + 0x00); //Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
        SPIWrite(LR_RegModemConfig2 + (RFM96SpreadFactorTbl[LoraSF] << 4) + (LoraCRC << 2) + 0x03); //SFactor &  LNA gain set by the internal AGC loop
    }
    if(RFM96SpreadFactorTbl[LoraSF] > 10)    //���ų��ȴ���16ms ��Ҫ���øò���
    {
        SPIWrite(LR_RegModemConfig3+ 0x08); 
    }
   
    SPIWrite(LR_RegSymbTimeoutLsb + 0xFF); //RegSymbTimeoutLsb Timeout = 0x3FF(Max)

    SPIWrite(LR_RegPreambleMsb + 0x00);         //RegPreambleMsb
    SPIWrite(LR_RegPreambleLsb + 0x14);        //RegPreambleLsb 8+4=12byte Preamble
    //�˴��Ĺ� ��֮ǰΪ 80
    SPIWrite(REG_LR_DIOMAPPING2 + 0x01);    //RegDioMapping2 DIO5=00, DIO4=01
    RF1278_Standby();
    return(1);
}


/**********************************
*��������void Rf1278_ModeSet(unsigned char clen)
*���ܣ�����Ϊ����ģʽ
*����: unsigned char clen �������ݳ��ȣ���ֵֻ������ģʽ����Ч����ʾģʽ��Ч
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: 
***********************************/
void Rf1278_ModeSet(unsigned char clen)
{
    unsigned char addr;
    RF1278_TxRxEN(0);
    SPIWrite(0x4D00 + 0x84);                                 //Normal and Rx
    SPIWrite(LR_RegHopPeriod + 0xFF);                        //RegHopPeriod NO FHSS
    SPIWrite(REG_LR_DIOMAPPING1 + 0x01);                     //DIO0=00, DIO1=00, DIO2=00, DIO3=01
                                                             //DIO0 - RXDONE DIO1 - RXTIMEOUT                                                             //DIO3 - VALIDHEADER
    SPIWrite(LR_RegIrqFlagsMask + 0x3F);                     //Open RxDone interrupt & Timeout
    RF1278_ClearIrq();

    SPIWrite(LR_RegPreambleMsb + 0x7F);        //RegPreambleMsb
    SPIWrite(LR_RegPreambleLsb + 0xFF);        //RegPreambleLsb 8+4=12byte Preamble


    SPIWrite(LR_RegPayloadLength + clen);                     //RegPayloadLength clen byte(this register must difine when the data long of one byte in SF is 6)
    addr = SPIRead((unsigned char)(LR_RegFifoRxBaseAddr >> 8));  //Read RxBaseAddr
    SPIWrite(LR_RegFifoAddrPtr + addr);                      //RxBaseAddr -> FiFoAddrPtr��
    SPIWrite(LR_RegOpMode + 0x0D);                      //Continuous Rx Mode
    RF1278_State = 1; //����״̬
    RF1278_ClearIrq();
}


/**********************************
*��������void RF1278_CadInit(void)
*���ܣ�1278Cad��ʼ������
*����: 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void RF1278_CadInit(void)
{
    RF1278_Standby();
    SPIWrite( LR_RegPreambleMsb + 0x7F); //set preamble length
    SPIWrite( LR_RegPreambleLsb + 0xFF); //set preamble length
    //SPIWrite( LR_RegPreambleMsb,0xF0);//set preamble length
    //SPIWrite( LR_RegPreambleLsb,0xFF);//set preamble length
    SPIWrite( LR_RegIrqFlagsMask + 0xFA);  //���CAD��־
    SPIWrite( REG_LR_DIOMAPPING1 + 0x20); // Mapping of oins DIO1 CadDetect
                                         //  DIO3 Cad Done
    RF1278_TxRxEN(0);   //set RF switch to RX path
    RF1278_ClearIrq(); //Clear irq

}

/**********************************
*��������void RF1278_CadSample(void)
*���ܣ�����1278cad ����
*����: 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: ����ʱ��ԼΪ(2^SF+32)/BW
***********************************/
void RF1278_CadSample(void)
{
    RF1278_TxRxEN(0);     //set RF switch to RX path
    RF1278_Standby();            //Standby
    SPIWrite(LR_RegOpMode + 0x80 + 0x07); //CAD MODE
}

/**********************************
*��������unsigned char RF1278_CAD(void)
*���ܣ�1278 ����һ��CAD��⣬��⵽ ����1 δ��⵽ ����0
*����: 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: ����ʱ��ԼΪ(2^SF+32)/BW
***********************************/
unsigned char RF1278_CAD(void)
{
    unsigned long int i = 2777215;//CAD��ⳬʱ�� ms
    RF1278_CadInit(); //����ִ��WOR
    RF1278_CadSample();// CAD ����һ��
    while((i != 0) && (RF_DIO3() == 0) && (RF_DIO1() == 0))
    {
         i--;
         delayms(2);
         IWDG_ReloadCounter();//ι��
        
    }
    if(RF_DIO1() == 1)//CAD ��⵽����
    {
        //RF1278_ClearIrq();
        Rf1278_ModeSet(128);
        RF1278_State = 1; //����״̬
        RF1278_ClearIrq();
        return 1;
    }
    else
    {
       RF1278_Sleep();//Change modem Must in Sleep mode
       RF1278_State = 0; //˯��״̬
       return 0;
    }
}

/**********************************
*��������void RF1278_AwakeSend(unsigned char *cbuf, unsigned char csize)
*���ܣ����ͻ������ݰ�
*����: unsigned char *cbuf ���������ݻ����ַָ��
       unsigned char csize ���������ݳ���
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: �ȷ��ͻ���ǰ���룬��������ٷ�������
***********************************/
void RF1278_AwakeSend(unsigned char *cbuf, unsigned char csize)
{
  
    unsigned long int j = 1777215;  //���ͳ�ʱ�ã���Ҫ����ʵ�����������
    unsigned char IrqFlags = 0;
    
    RF1278_Standby();
    SPIWrite(REG_LR_PADAC +0x87);//max 17db ���ӵ� 20db
    SPIWrite( LR_RegPayloadLength + csize ); //���س���
    RF1278_TxRxEN(1);
    SPIWrite( LR_RegFifoAddrPtr + 0x80 );  //Turns on the mechanism restarting
    //the receiver automatically if it gets saturated or a packet collision is detected
    SPIWriteString(0x00, cbuf, csize); 			 // �������ݵ�RFģ��
    RF1278_ClearIrq();
    SPIWrite( LR_RegIrqFlagsMask + 0xF7 );     //���������ɱ�־

    SPIWrite( REG_LR_DIOMAPPING1 + 0x40 );  //
    //����ǰ��ʱ�� (T)/(2 ^ S F / B W) ת��Ϊ16����
    switch(LoraSF) //��Ƶ����
    {
    case 0:
        SPIWrite( LR_RegPreambleMsb + 0x26);//set preamble length
        SPIWrite( LR_RegPreambleLsb + 0xF6);//set preamble length
        break;
    case 1:
        SPIWrite( LR_RegPreambleMsb + 0x13);//set preamble length
        SPIWrite( LR_RegPreambleLsb + 0x7C);//set preamble length
        break;
    case 2:
        SPIWrite( LR_RegPreambleMsb + 0x09);//set preamble length
        SPIWrite( LR_RegPreambleLsb + 0xBF);//set preamble length
        break;
    case 3:
        SPIWrite( LR_RegPreambleMsb + 0x04);//set preamble length
        SPIWrite( LR_RegPreambleLsb + 0xE0);//set preamble length
        break;
    case 4:
        SPIWrite( LR_RegPreambleMsb + 0x02);//set preamble length
        SPIWrite( LR_RegPreambleLsb + 0x71);//set preamble length
        break;
    case 5:
        SPIWrite( LR_RegPreambleMsb + 0x01);//set preamble length
        SPIWrite( LR_RegPreambleLsb + 0x39);//set preamble length
        break;
    case 6:
        SPIWrite( LR_RegPreambleMsb + 0x00);//set preamble length
        SPIWrite( LR_RegPreambleLsb + 0x9D);//set preamble length
        break;
    default:
        break;

    }
    SPIWrite(LR_RegOpMode + 0x03 + 0x08); //Tx Mode
    RF1278_State = 2; //����״̬
    IrqFlags = SPIRead((unsigned char)(LR_RegIrqFlags >> 8));
    while(((IrqFlags&0x08) != 0x08) && j != 0) //�ȴ�GDIO0��ƽΪ�߻�ʱ
    {    
        SPIRead((unsigned char)(LR_RegIrqFlags >> 8));
        Watchdog_Reload();      //�������Ź�ι��
        delayms(1);
        j--;                                         //�ȴ�GDIO0��ƽΪ��
    }

  
    RF1278_ClearIrq();		// Clear irq
    RF1278_Standby();	       // Entry Standby mode

    //�����껽�����ݰ��󣬽�ǰ��ʱ��Ļ�����Ĭ��ֵ��
    //SPIWrite(LR_RegPreambleMsb + 0x00); //set preamble length
    //SPIWrite(LR_RegPreambleLsb + 0x10); //set preamble length
}


/**********************************
*��������void RF1278_SendPacket(unsigned char *cbuf, unsigned char csize)
*���ܣ��������ݰ�
*����: unsigned char *cbuf ���������ݻ����ַָ��
       unsigned char csize ���������ݳ���
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: 
***********************************/
void RF1278_SendPacket(unsigned char *cbuf, unsigned char csize)
{
    unsigned char IrqFlags = 0;
    unsigned long int j = 1777215;  //���ͳ�ʱ�ã���Ҫ����ʵ�����������
    RF1278_Standby();
    SPIWrite(REG_LR_PADAC +0x87);//max 17db ���ӵ� 20db
    SPIWrite( LR_RegPayloadLength + csize ); //���س���
    RF1278_TxRxEN(1);
    SPIWrite(LR_RegFifoAddrPtr + 0x00 );  //Turns on the mechanism restarting    
	SPIWrite(LR_RegFifoTxBaseAddr+0x00);		// Base address in FIFO data buffer for TX modulator
    //the receiver automatically if it gets saturated or a packet collision is detected
    SPIWriteString(0x00, cbuf, csize); 			 // �������ݵ�RFģ��
    RF1278_ClearIrq();
    SPIWrite( LR_RegIrqFlagsMask + 0xF7 );     //���������ɱ�־

    SPIWrite( REG_LR_DIOMAPPING1 + 0x40 );  //
    SPIWrite(LR_RegPreambleMsb + 0x00); //set preamble length
    SPIWrite(LR_RegPreambleLsb + 0x14); //set preamble length
    SPIWrite(LR_RegOpMode + 0x03 + 0x08); //Tx Mode
    RF1278_State = 2; //����״̬
    IrqFlags = SPIRead((unsigned char)(LR_RegIrqFlags >> 8));
    while(((IrqFlags&0x08) != 0x08) && j != 0) //�ȴ�GDIO0��ƽΪ�߻�ʱ
    {
       IrqFlags = SPIRead((unsigned char)(LR_RegIrqFlags >> 8)); 
       Watchdog_Reload();      //�������Ź�ι��
        delayms(1);
        j--;
    }
    RF1278_ClearIrq();					  // Clear irq
    RF1278_Standby();					 // Entry Standby mode
}
unsigned char RF1278_RF1278_ReadRssiOld(void)
{
  //      unsigned char RegRssiValue;
  //      // Reads the RSSI value
   ////     RegRssiValue = SPIRead((unsigned char)(LR_RegPktRssiValue >> 8));
   //     RegRssiValue = RegRssiValue - 164 + 127;//127:Max RSSI,137:RSSI offset+ 127
    //    RegRssiValue = (unsigned char)RegRssiValue;
    //    if(RegRssiValue > 164)
    //    {
    //        RegRssiValue = 0;
   //     }
   //     return RegRssiValue;
       unsigned char RegRssiValue;
    // Reads the RSSI value
       RegRssiValue = SPIRead((unsigned char)(LR_RegPktRssiValue>>8));
       RegRssiValue = RegRssiValue - 164 + 127;//127:Max RSSI,137:RSSI offset+ 127
       return ( (unsigned char)RegRssiValue);//-137 +
		
}

/**********************************
*��������void RF1278_ReadRssiSnr(char *snr,short* rssi)
*���ܣ���ȡRSSI �� SNR ֵ
*����: 
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
*˵��: 
***********************************/
void RF1278_ReadRssiSnr(unsigned char* rssi)
{
#if 1
        signed char snrval;
        int rssival;
        
        snrval = (char)SPIRead((unsigned char)(LR_RegPktSnrValue >> 8));
        snrval /= 4;
        rssival = SPIRead((unsigned char)(LR_RegPktRssiValue >> 8));
        rssival -= 164;
        if(snrval < 0) rssival += snrval;
        
        *rssi = rssival;
 //       *snr = snrval;
#endif
#if 0
        unsigned char RegRssiValue;
        // Reads the RSSI value
        RegRssiValue = SPIRead((unsigned char)(LR_RegPktRssiValue >> 8));
        RegRssiValue = RegRssiValue - 164 + 127;//127:Max RSSI,137:RSSI offset+ 127
        RegRssiValue = (unsigned char)RegRssiValue;
        if(RegRssiValue > 164)
        {
            RegRssiValue = 0;
        }
        *rssi = RegRssiValue;
#endif

}


/**********************************
*��������void RF1278_RecePacket(unsigned char *cbuf,unsigned char len)
*���ܣ�������Ƶ���ݰ�
*����: unsigned char *cbuf �������ݻ����ַָ��
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
void RF1278_RecePacket(unsigned char *cbuf,unsigned char len)
{
  
    SPIReadString(0x00, cbuf, len);
  
}
/**********************************
*��������unsigned char RF1278_RecePacketLenht(unsigned char *Crc)
*���ܣ�������Ƶ���ݰ����Ⱥ���
*����: Crc У�麯��
*���ߣ�Mr.He
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
unsigned char RF1278_RecePacketLenht(unsigned char *Crc){

    unsigned char addr;
    unsigned char packet_size;    
    unsigned char IrqFlag = 0;
   
    IrqFlag = SPIRead((unsigned char)(LR_RegIrqFlags>>8));
    if((IrqFlag&0x20) == 0x20)      //CRC�ж�
    {
        *Crc = 0;           //CRC����
        SPIWrite( LR_RegIrqFlags+0x20);
    }
    else
        *Crc = 1;           //CRC��ȷ
    addr = SPIRead((unsigned char)(LR_RegFifoRxCurrentaddr >> 8));    //last packet addr ���ݰ�������ַ(���ݵ�β��ַ)
    SPIWrite(LR_RegFifoAddrPtr + addr);                    //RxBaseAddr -> FiFoAddrPtr
    packet_size = SPIRead((unsigned char)(LR_RegRxNbBytes >> 8));   //Number for received bytes
    
    return packet_size;

}

/**********************************
*��������unsigned char RF1278_RecePacket(unsigned char *cbuf)
*���ܣ�������Ƶ���ݰ�
*����: unsigned char *cbuf �������ݻ����ַָ��
*���ߣ�wq
*����ʱ�䣺
*�޸�ʱ�䣺
***********************************/
unsigned char RF1278_RecePacketDate(unsigned char *cbuf,unsigned char *Crc)
{
    unsigned char addr;
    unsigned char packet_size;    
    unsigned char IrqFlag = 0;
   
    IrqFlag = SPIRead((unsigned char)(LR_RegIrqFlags>>8));
    if((IrqFlag&0x20) == 0x20)      //CRC�ж�
    {
        *Crc = 0;           //CRC����
        SPIWrite( LR_RegIrqFlags+0x20);
    }
    else
        *Crc = 1;           //CRC��ȷ
    addr = SPIRead((unsigned char)(LR_RegFifoRxCurrentaddr >> 8));    //last packet addr ���ݰ�������ַ(���ݵ�β��ַ)
    SPIWrite(LR_RegFifoAddrPtr + addr);                    //RxBaseAddr -> FiFoAddrPtr
    packet_size = SPIRead((unsigned char)(LR_RegRxNbBytes >> 8));   //Number for received bytes
    SPIReadString(0x00, cbuf, packet_size);

    RF1278_ClearIrq();
    return packet_size;
}


unsigned char RF1278_ReceDetect(void)
{   unsigned char IrqFlags = 0;
    IrqFlags = SPIRead((unsigned char)(LR_RegIrqFlags >> 8));
    if((IrqFlags&0x40) == 0x40)
        return 1;
    else
        return 0;
}




