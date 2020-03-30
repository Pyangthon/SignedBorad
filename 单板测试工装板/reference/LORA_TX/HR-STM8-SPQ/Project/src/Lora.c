

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



//===================================定义变量===================================

__root const unsigned short  RFM96FreqTbl[] =
{
    0x0678,0x0786,0x0866,     //482100000 CH2 
   0x066c, 0x0740, 0x0812,  //433000000  CH0
    0x066c, 0x0780, 0x0800,  //434000000  CH1 
    0x066c, 0x07C0, 0x0812,  //435000000  CH2 
	
    0x066d, 0x0700, 0x0812,  //436000000  CH3 
    0x066d, 0x0740, 0x0812,  //437000000  CH4 
    0x066d, 0x077F, 0x0840,  //438000000  CH5
    0x066d, 0x07C0, 0x0812,  //439000000  CH6
	
    0x066e, 0x0700, 0x0812,  //440000000  CH7
    0x066e, 0x0740, 0x0812,  //4410000000  CH8 
    0x066e, 0x0780, 0x0812, //4420000000  CH9
    0x066e, 0x07C0, 0x0812, //4430000000  CH10
	
    0x066E, 0x0700, 0x0812, //4440000000  CH11
    0x066f, 0x0740, 0x0812, //4450000000  CH12 
    0x066f, 0x0780, 0x0812, //4460000000  CH13
    0x066f, 0x07C0, 0x0812, //4470000000  CH14
	
    0x0670, 0x0700, 0x0812, //4480000000  CH15
    0x0670, 0x0740, 0x0812, //4490000000  CH16
    0x0670, 0x0780, 0x0812, //4500000000  CH17
    0x0670, 0x07C0, 0x0812, //4510000000  CH18
	
    0x0671, 0x0700, 0x0812, //4520000000  CH19
    0x0671, 0x0740, 0x0813, //4530000000  CH20 
    0x0671, 0x0780, 0x0813, //4540000000  CH21
    0x0671, 0x07C0, 0x0813, //4550000000  CH22
		
    0x0672, 0x0700, 0x0813, //4560000000  CH23
    0x0672, 0x0740, 0x0813, //4570000000  CH24 
    0x0672, 0x0780, 0x0813, //4580000000  CH25
    0x0672, 0x07C0, 0x0813, //4590000000  CH26
		
    0x0673, 0x0700, 0x0813, //4600000000  CH27
    0x0673, 0x0740, 0x0813, //4610000000  CH28 
    0x0673, 0x0780, 0x0813, //4620000000  CH29
    0x0673, 0x07C0, 0x0813, //4630000000  CH30
		
    0x0674, 0x0700, 0x0813, //4640000000  CH31
    0x0674, 0x0740, 0x0813, //4650000000  CH32
    0x0674, 0x0780, 0x0813, //4660000000  CH33
    0x0674, 0x07C0, 0x0813, //4670000000  CH34
		
    0x0675, 0x0700, 0x0813, //4680000000  CH35  
    0x0675, 0x0740, 0x0813, //4690000000  CH36 
    0x0675, 0x0780, 0x0813, //4700000000  CH37
    0x0675, 0x07C0, 0x0813, //4710000000  CH38
		
    0x0676, 0x0700, 0x0813, //4720000000  CH39
    0x0676, 0x0740, 0x0813, //4730000000  CH40
    0x0676, 0x0780, 0x0813, //4740000000  CH41  
    0x0676, 0x07C0, 0x0813, //4750000000  CH42
		
    0x0677, 0x0700, 0x0813, //4760000000  CH43
    0x0677, 0x0740, 0x0813, //4770000000  CH44
    0x0677, 0x0780, 0x0813, //4780000000  CH45
    0x0677, 0x07C0, 0x0813, //4790000000  CH46
		
    0x0678, 0x0700, 0x0814, //4800000000  CH47
    0x0678, 0x0740, 0x0814, //4810000000  CH48
    0x0678, 0x0780, 0x0814, //4820000000  CH49
    0x0678, 0x07C0, 0x0814, //4830000000  CH50
		
    0x0679, 0x0700, 0x0814, //4840000000  CH51
    0x0679, 0x0740, 0x0814, //4850000000  CH52
    0x0679, 0x0780, 0x0814, //4860000000  CH53
    0x0679, 0x07C0, 0x0814, //4870000000  CH54 
		
    0x067A, 0x0700, 0x0814, //4880000000  CH55
    0x067A, 0x0740, 0x0814, //4890000000  CH56
    0x067A, 0x0780, 0x0814, //4900000000  CH57-------
    0x067A, 0x07C0, 0x0814, //4910000000  CH58
		
    0x067B, 0x0700, 0x0814, //4920000000  CH59
    0x067B, 0x0740, 0x0814, //4930000000  CH60
    0x067B, 0x0780, 0x0814, //4940000000  CH61
    0x067B, 0x07C0, 0x0814, //4950000000  CH62
		
    0x067C, 0x0700, 0x0814, //4960000000  CH63
    0x067C, 0x0740, 0x0814, //4970000000  CH64
    0x067C, 0x0780, 0x0814, //4980000000  CH65
    0x067C, 0x07C0, 0x0814, //4990000000  CH66
		
    0x067D, 0x0700, 0x0814, //5000000000  CH67
    0x067D, 0x0740, 0x0815, //5010000000  CH68
    0x067D, 0x0780, 0x0815, //5020000000  CH69
    0x067D, 0x07C0, 0x0815, //5030000000  CH70
		
    0x067E, 0x0700, 0x0815, //5040000000  CH71
    0x067E, 0x0740, 0x0815, //5050000000  CH72
    0x067E, 0x0780, 0x0815, //5060000000  CH73
    0x067E, 0x07C0, 0x0815, //5070000000  CH74
		
    0x067F, 0x0700, 0x0815, //5080000000  CH75
    0x067F, 0x0740, 0x0815, //5090000000  CH76
};



const unsigned short RFM96PowerTbl[4] =
{
    0x09FF,                   //20dbm
    0x09FC,                   //17dbm
    0x09F9,                   //14dbm
    0x09F6,                   //11dbm
};
const unsigned char RFM96SpreadFactorTbl[13] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
};

const unsigned char RFM96LoRaBwTbl[10] =
{
    // 0        1     2       3      4       5         6      7       8      9
    //7.8KHz,10.4KHz,15.6KHz,20.8KHz,31.2KHz,41.7KHz,62.5KHz,125KHz,250KHz,500KHz
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};





/******************LORA相关参数************************/

static unsigned char LoraPower = 0;  //功率
static unsigned char LoraBw = 7;     //带宽
static unsigned char LoraSF = 2;     //SF 扩频因子 
static unsigned char LoraFreq = 0;   //频率
static unsigned char LoraCR = 1;     //纠错码率

static unsigned char LoraCRC = 1;    //带CRC校验
static unsigned char RF1278_State = 0;  //1278状态  0 为睡眠 1 为接收 2 为发送 3 为待机



extern void RF1278_EntryLoRa(void);

//设置LORa 相关参数
void Set_LoraConfig(u8 Freq,u8 Power,u8 Bw,u8 SF,u8 CR)
{
	LoraFreq = Freq;
	LoraPower = Power;
	LoraBw = Bw;
	LoraSF = SF;
	LoraCR = CR;
    RF1278_Init(LoraFreq,LoraSF);
    Rf1278_ModeSet(100);
}
//获取LORa 相关阐述 
void Get_LoraConfig(u8* Freq,u8* Power,u8* Bw,u8* SF,u8* CR)
{
	*Freq = LoraFreq;
	*Power = LoraPower;
	*Bw = LoraBw;
	*SF = LoraSF;
	*CR = LoraCR;
}
/**********************************
*函数名：void SPIWrite8bit(unsigned char WrPara)
*功能：SPI数据写入 8bit
*参数: WrPara 写入数据内容
*作者：wq
*创建时间：
*修改时间：
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
*函数名：unsigned char SPIRead8bit(void)
*功能：SPI数据读取 8bit
*参数: 返回读取数据
*作者：wq
*创建时间：
*修改时间：
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
*函数名：unsigned char SPIRead8bit(void)
*功能：是定地址读取数据
*参数: 返回读取数据
*作者：wq
*创建时间：
*修改时间：
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
*函数名：void SPIReadString(unsigned char adr, unsigned char *ptr, unsigned char length)
*功能：从指定地址读取指定长度数据
*参数: unsigned char adr 首地址
       unsigned char *ptr 读出数据缓存区指针
       unsigned char length 读取数据长度
*作者：wq
*创建时间：
*修改时间：
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
*函数名：void SPIWriteString(unsigned char adr, unsigned char *ptr, unsigned char length)
*功能：从指定地址写入指定长度数据
*参数: unsigned char adr 首地址
       unsigned char *ptr 待写入数据缓存区指针
       unsigned char length 写入数据长度
*作者：wq
*创建时间：
*修改时间：
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
*函数名：unsigned char RF_FreqSet(unsigned char ch)
*功能：设定射频通信频率
*参数: unsigned char ch 信道号 0~82
       返回 1 成功； 0 失败
*作者：wq
*创建时间：
*修改时间：
***********************************/
unsigned char RF1278_FreqSet(unsigned char ch)
{
    unsigned char test_FRFMSB = 0, test_FRFMID = 0, test_FRFLSB = 0;

    if(ch > 77)
        return 0;
    RF1278_EntryLoRa(); //进入该模式才能设置下面频段参数

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
*函数名：void RF_TxRxEN( unsigned char txEnable)
*功能：收发使能,控制射频开关
*参数: txEnable: 0 RX  1 TX 
*作者：wq
*创建时间：
*修改时间：
***********************************/
void RF1278_TxRxEN( unsigned char txEnable)
{
    if( txEnable != 0 )       //如果为真，为TX
    {
        RF_RX_EN_L();
        RF_TX_EN_H();
    }
    else  //为假，为RX
    {
        RF_RX_EN_H();
        RF_TX_EN_L();        
    }
}

/**********************************
*函数名：void RF1278_Sleep(void)
*功能：射频睡眠模式
*参数: 
*作者：wq
*创建时间：
*修改时间：
***********************************/
void RF1278_Sleep(void)
{
    SPIWrite(LR_RegOpMode + 0x00 + 0x80);                          //Sleep
    RF_RX_EN_L();//睡眠模式较低功耗
    RF_TX_EN_L();//睡眠模式较低功耗  
    RF1278_State = 0; //睡眠状态
}

/**********************************
*函数名：void RF1278_EntryLoRa(void)
*功能：射频进入LORA模式
*参数: 
*作者：wq
*创建时间：
*修改时间：
***********************************/
void RF1278_EntryLoRa(void)
{
    SPIWrite(LR_RegOpMode + 0x80 + 0x08);
}

/**********************************
*函数名：void RF1278_ClearIrq(void)
*功能：清1278内部中断标志位
*参数: 
*作者：wq
*创建时间：
*修改时间：
***********************************/
void RF1278_ClearIrq(void)
{
    SPIWrite(LR_RegIrqFlags + 0xFF);
}


/**********************************
*函数名：void RF1278_Standby(void)
*功能：1278进入待命状态
*参数: 
*作者：wq
*创建时间：
*修改时间：
***********************************/
void RF1278_Standby(void)
{
    SPIWrite(LR_RegOpMode + 0x01 + 0x80);                                //Standby
    RF1278_State = 3;   //待机状态
}

/**********************************
*函数名：unsigned char GetRF1278_State(void)
*功能：获取RF1278状态
*参数: 返回值: 0 睡眠 ，1 接收 ，2 发送 ，3 待机 
*作者：wq
*创建时间：
*修改时间：
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
*函数名：unsigned char RF1278_Init(unsigned char ch)
*功能：1278初始化
*参数: ch 频道 
       返回值  1 成功 0 失败
*作者：wq
*创建时间：
*修改时间：
***********************************/
unsigned char RF1278_Init(unsigned char ch,unsigned char SpreadFactor)
{
    unsigned char tmp;
    if(LoraSF >= 13)
       return 0;
    if(ch >= 77)
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

    if(RF1278_FreqSet(ch) == 0)
        return(0);//setting frequency parameter
        
    //setting base parameter
    SPIWrite(RFM96PowerTbl[LoraPower]);     //Setting output power parameter
    SPIWrite(LR_RegOcp + 0x1f);          //RegOcp,Close Ocp
    SPIWrite(LR_RegLna + 0x23);          //RegLNA,High & LNA Enable
   //2015-10-23 增加到20dbm功率
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
    if(RFM96SpreadFactorTbl[LoraSF] >= 10)    //符号长度大于16ms 需要设置该参数
    {
        SPIWrite(LR_RegModemConfig3+ 0x08); 
    }
   
    SPIWrite(LR_RegSymbTimeoutLsb + 0xFF); //RegSymbTimeoutLsb Timeout = 0x3FF(Max)

    SPIWrite(LR_RegPreambleMsb + 0x00);         //RegPreambleMsb
    SPIWrite(LR_RegPreambleLsb + 0x14);        //RegPreambleLsb 8+4=12byte Preamble
    //此处改过 ，之前为 80
    SPIWrite(REG_LR_DIOMAPPING2 + 0x01);    //RegDioMapping2 DIO5=00, DIO4=01
    RF1278_Standby();
    return(1);
}


/**********************************
*函数名：void Rf1278_ModeSet(unsigned char clen)
*功能：设置为接收模式
*参数: unsigned char clen 接收数据长度，该值只对隐试模式下有效，显示模式无效
*作者：wq
*创建时间：
*修改时间：
*说明: 
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

    SPIWrite(LR_RegPreambleMsb + 0xF0);         //RegPreambleMsb
    SPIWrite(LR_RegPreambleLsb + 0x00);         //RegPreambleLsb 8+4=12byte Preamble

    SPIWrite(LR_RegPayloadLength + clen);                     //RegPayloadLength clen byte(this register must difine when the data long of one byte in SF is 6)
    addr = SPIRead((unsigned char)(LR_RegFifoRxBaseAddr >> 8));         //Read RxBaseAddr
    SPIWrite(LR_RegFifoAddrPtr + addr);                      //RxBaseAddr -> FiFoAddrPtr??
    SPIWrite(LR_RegOpMode + 0x0D);                      //Continuous Rx Mode
    RF1278_State = 1; 
}


/**********************************
*函数名：void RF1278_CadInit(void)
*功能：1278Cad初始化配置
*参数: 
*作者：wq
*创建时间：
*修改时间：
***********************************/
void RF1278_CadInit(void)
{
    RF1278_Standby();
    SPIWrite( LR_RegPreambleMsb + 0x7F); //set preamble length
    SPIWrite( LR_RegPreambleLsb + 0xFF); //set preamble length
    //SPIWrite( LR_RegPreambleMsb,0xF0);//set preamble length
    //SPIWrite( LR_RegPreambleLsb,0xFF);//set preamble length
    SPIWrite( LR_RegIrqFlagsMask + 0xFA);  //清除CAD标志
    SPIWrite( REG_LR_DIOMAPPING1 + 0x20); // Mapping of oins DIO1 CadDetect
                                         //  DIO3 Cad Done
    RF1278_TxRxEN(0);   //set RF switch to RX path
    RF1278_ClearIrq(); //Clear irq

}

/**********************************
*函数名：void RF1278_CadSample(void)
*功能：启动1278cad 采样
*参数: 
*作者：wq
*创建时间：
*修改时间：
*说明: 采样时间约为(2^SF+32)/BW
***********************************/
void RF1278_CadSample(void)
{
    RF1278_TxRxEN(0);     //set RF switch to RX path
    RF1278_Standby();            //Standby
    SPIWrite(LR_RegOpMode + 0x80 + 0x07); //CAD MODE
}

/**********************************
*函数名：unsigned char RF1278_CAD(void)
*功能：1278 进行一次CAD检测，检测到 返回1 未检测到 返回0
*参数: 
*作者：wq
*创建时间：
*修改时间：
*说明: 采样时间约为(2^SF+32)/BW
***********************************/
unsigned char RF1278_CAD(void)
{
    unsigned long int i = 2777215;//CAD检测超时用 ms
    RF1278_CadInit(); //启动执行WOR
    RF1278_CadSample();// CAD 采样一次
    while((i != 0) && (RF_DIO3() == 0) && (RF_DIO1() == 0))
    {
         i--;
         delayms(2);
         IWDG_ReloadCounter();//喂狗
        
    }
    if(RF_DIO1() == 1)//CAD 检测到数据
    {
        //RF1278_ClearIrq();
        Rf1278_ModeSet(128);
        RF1278_State = 1; //接收状态
        RF1278_ClearIrq();
        return 1;
    }
    else
    {
       RF1278_Sleep();//Change modem Must in Sleep mode
       RF1278_State = 0; //睡眠状态
       return 0;
    }
}

/**********************************
*函数名：void RF1278_AwakeSend(unsigned char *cbuf, unsigned char csize)
*功能：发送唤醒数据包
*参数: unsigned char *cbuf 待发送数据缓存地址指针
       unsigned char csize 待发送数据长度
*作者：wq
*创建时间：
*修改时间：
*说明: 先发送唤醒前导码，发送完后再发送数据
***********************************/
void RF1278_AwakeSend(unsigned char *cbuf, unsigned char csize)
{
  
    unsigned long int j = 1777215;  //发送超时用，需要根据实际情况来调整
    unsigned char IrqFlags = 0;
    
    RF1278_Standby();
    SPIWrite(REG_LR_PADAC +0x87);//max 17db 增加到 20db
    SPIWrite( LR_RegPayloadLength + csize ); //负载长度
    RF1278_TxRxEN(1);
    SPIWrite( LR_RegFifoAddrPtr + 0x80 );  //Turns on the mechanism restarting
    //the receiver automatically if it gets saturated or a packet collision is detected
    SPIWriteString(0x00, cbuf, csize); 			 // 发送数据到RF模块
    RF1278_ClearIrq();
    SPIWrite( LR_RegIrqFlagsMask + 0xF7 );     //清除接收完成标志

    SPIWrite( REG_LR_DIOMAPPING1 + 0x40 );  //
    //设置前导时间 (T)/(2 ^ S F / B W) 转换为16进制
    switch(LoraSF) //扩频因子
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
    RF1278_State = 2; //发送状态
    IrqFlags = SPIRead((unsigned char)(LR_RegIrqFlags >> 8));
    while(((IrqFlags&0x08) != 0x08) && j != 0) //等待GDIO0电平为高或超时
    {    
        SPIRead((unsigned char)(LR_RegIrqFlags >> 8));
        Watchdog_Reload();      //独立看门狗喂狗
        delayms(1);
        j--;                                         //等待GDIO0电平为高
    }

  
    RF1278_ClearIrq();		// Clear irq
    RF1278_Standby();	       // Entry Standby mode

    //发送完唤醒数据包后，将前导时间改回正常默认值。
    //SPIWrite(LR_RegPreambleMsb + 0x00); //set preamble length
    //SPIWrite(LR_RegPreambleLsb + 0x10); //set preamble length
}


/**********************************
*函数名：void RF1278_SendPacket(unsigned char *cbuf, unsigned char csize)
*功能：发送数据包
*参数: unsigned char *cbuf 待发送数据缓存地址指针
       unsigned char csize 待发送数据长度
*作者：wq
*创建时间：
*修改时间：
*说明: 
***********************************/
void RF1278_SendPacket(unsigned char *cbuf, unsigned char csize)
{
    unsigned char IrqFlags = 0;
    unsigned long int j = 1777215;  //发送超时用，需要根据实际情况来调整
    RF1278_Standby();
    SPIWrite(REG_LR_PADAC +0x87);//max 17db 增加到 20db
    SPIWrite( LR_RegPayloadLength + csize ); //负载长度
    RF1278_TxRxEN(1);
    SPIWrite(LR_RegFifoAddrPtr + 0x00 );  //Turns on the mechanism restarting    
	SPIWrite(LR_RegFifoTxBaseAddr+0x00);		// Base address in FIFO data buffer for TX modulator
    //the receiver automatically if it gets saturated or a packet collision is detected
    SPIWriteString(0x00, cbuf, csize); 			 // 发送数据到RF模块
    RF1278_ClearIrq();
    SPIWrite( LR_RegIrqFlagsMask + 0xF7 );     //清除接收完成标志

    SPIWrite( REG_LR_DIOMAPPING1 + 0x40 );  //
    SPIWrite(LR_RegPreambleMsb + 0x00); //set preamble length
    SPIWrite(LR_RegPreambleLsb + 0x14); //set preamble length
    SPIWrite(LR_RegOpMode + 0x03 + 0x08); //Tx Mode
    RF1278_State = 2; //发送状态
    IrqFlags = SPIRead((unsigned char)(LR_RegIrqFlags >> 8));
    while(((IrqFlags&0x08) != 0x08) && j != 0) //等待GDIO0电平为高或超时
    {
       IrqFlags = SPIRead((unsigned char)(LR_RegIrqFlags >> 8)); 
       Watchdog_Reload();      //独立看门狗喂狗
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
*函数名：void RF1278_ReadRssiSnr(char *snr,short* rssi)
*功能：读取RSSI 和 SNR 值
*参数: 
*作者：wq
*创建时间：
*修改时间：
*说明: 
***********************************/
void RF1278_ReadRssiSnr(unsigned char* rssi)
{
#if 0
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
#if 1
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
*函数名：void RF1278_RecePacket(unsigned char *cbuf,unsigned char len)
*功能：接收射频数据包
*参数: unsigned char *cbuf 接收数据缓存地址指针
*作者：wq
*创建时间：
*修改时间：
***********************************/
void RF1278_RecePacket(unsigned char *cbuf,unsigned char len)
{
  
    SPIReadString(0x00, cbuf, len);
  
}

/**********************************
*函数名：unsigned char RF1278_RecePacket(unsigned char *cbuf)
*功能：接收射频数据包
*参数: unsigned char *cbuf 接收数据缓存地址指针
*作者：wq
*创建时间：
*修改时间：
***********************************/
unsigned char RF1278_RecePacketDate(unsigned char *cbuf,unsigned char *Crc)
{
    unsigned char addr;
    unsigned char packet_size;    
    unsigned char IrqFlag = 0;
   
    IrqFlag = SPIRead((unsigned char)(LR_RegIrqFlags>>8));
    if((IrqFlag&0x20) == 0x20)      //CRC判断
    {
        *Crc = 0;           //CRC错误
        SPIWrite( LR_RegIrqFlags+0x20);
    }
    else
        *Crc = 1;           //CRC正确
    addr = SPIRead((unsigned char)(LR_RegFifoRxCurrentaddr >> 8));    //last packet addr 数据包的最后地址(数据的尾地址)
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




