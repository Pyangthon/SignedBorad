

#include "Lora.h"
#include "stm8l15x.h"

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
    0x067B, 0x0740, 0x0800, //493MHz    0
    0x067B, 0x0780, 0x0800, //494MHz    1
    0x067B, 0x07C0, 0x0800, //495MHz    2
    0x067C, 0x0700, 0x0800, //496MHz    3
    0x067C, 0x0740, 0x0800, //497MHz    4
    0x067C, 0x0780, 0x0800, //498MHz    5
    0x067C, 0x07C0, 0x0800, //499MHz    6
    0x067D, 0x0700, 0x0800, //500MHz    7
    0x067D, 0x0740, 0x0800, //501MHz    8
    0x067D, 0x0780, 0x0800, //502MHz    9
    
    0x0675, 0x07A4, 0x0806, //470,562,866   10
    0x0675, 0x07E0, 0x0806, //471,500,366   11
    0x0676, 0x071C, 0x0806, //472,437,866   12
    0x0676, 0x0758, 0x0806, //473,375,366   13
    0x0676, 0x0794, 0x0806, //474,312,866   14   
    0x0676, 0x07D0, 0x0806, //475,250,366   15  
    0x0677, 0x070C, 0x0806, //476,187,866   16
    0x0677, 0x0748, 0x0806, //477,125,366   17
    0x0677, 0x0784, 0x0806, //478,062,866   18
    0x0677, 0x07C0, 0x0806, //479,000,366   19
    0x0677, 0x07FC, 0x0806, //479,937,866   20
    0x0678, 0x0738, 0x0806, //480,875,366   21
    0x0678, 0x0774, 0x0806, //481,812,866   22
    0x0678, 0x07B0, 0x0806, //482,750,366   23
    0x0678, 0x07EC, 0x0806, //483,687,866   24 
    0x0679, 0x0728, 0x0806, //484,625,366   25
    0x0679, 0x0764, 0x0806, //485,562,866   26
    0x0679, 0x07A0, 0x0806, //486,500,366   27
    0x0679, 0x07DC, 0x0806, //487,437,866   28 
    0x067A, 0x0718, 0x0806, //488,375,366   29
    0x067A, 0x0754, 0x0806, //489,312,866   30
    0x067A, 0x0790, 0x0806, //490,250,366   31
    0x067A, 0x07CC, 0x0806, //491,187,866   32
    0x067B, 0x0708, 0x0806, //492,125,366   33
    0x067B, 0x0744, 0x0806, //493,062,866   34 
    0x067B, 0x0780, 0x0806, //494,000,366   35
    0x067B, 0x07BC, 0x0806, //494,937,866   36
    0x067B, 0x07F8, 0x0806, //495,875,366   37
    0x067C, 0x0734, 0x0806, //496,812,866   38
    0x067C, 0x0770, 0x0806, //497,750,366   39
    0x067C, 0x07AC, 0x0806, //498,687,866   40
    0x067C, 0x07E8, 0x0806, //499,625,366   41
    0x067D, 0x0724, 0x0806, //500,562,866   42
    0x067D, 0x0760, 0x0806, //501,500,366   43
    0x067D, 0x079C, 0x0806, //502,437,866   44 
    0x067D, 0x07D8, 0x0806, //503,375,366   45 
    0x067E, 0x0714, 0x0806, //504,312,866   46
    0x067E, 0x0750, 0x0806, //505,250,366   47
    0x067E, 0x078C, 0x0806, //506,187,866   48
    0x067E, 0x07C8, 0x0806, //507,125,366   49
    0x067F, 0x0704, 0x0806, //508,062,866   50
    0x067F, 0x0740, 0x0806, //509,000,366   51
    0x067F, 0x077C, 0x0806, //509,937,866   52     
    0x066c, 0x0744, 0x0806, //433,062,866   53  
    0x066c, 0x0780, 0x0806, //434,000,366   54
    0x066c, 0x07BC, 0x0806, //434,937,866   55 
    0x066c, 0x07F8, 0x0806, //435,875,366   56 
    0x066d, 0x0734, 0x0806, //436,812,866   57 
    0x066d, 0x0770, 0x0806, //437,750,366   58 
    0x066d, 0x07ac, 0x0806, //438,687,866   59
    0x066d, 0x07e8, 0x0806, //439,625,366   60
    0x066e, 0x0724, 0x0806, //440,562,866   61
    0x066e, 0x0760, 0x0806, //441,500,366   62  
    0x066e, 0x079c, 0x0806, //442,437,866   63
    0x066e, 0x07D8, 0x0806, //443,375,366   64
    0x066f, 0x0714, 0x0806, //444,312,866   65
    0x066f, 0x0750, 0x0806, //445,250,366   66 
    0x066f, 0x078c, 0x0806, //446,187,866   67
    0x066f, 0x07C8, 0x0806, //447,125,366   68
    0x0670, 0x0704, 0x0806, //448,062,866   69
    0x0670, 0x0740, 0x0806, //449,000,366   70 
    0x0670, 0x077C, 0x0806, //449,937,866   71
    0x0670, 0x07B8, 0x0806, //450,875,366   72
    0x0670, 0x07F4, 0x0806, //451,812,866   73
    0x0671, 0x0730, 0x0806, //452,750,366   74
    0x0671, 0x076C, 0x0806, //453,687,866   75 
    0x0671, 0x07A8, 0x0806, //454,625,366   76
    0x0671, 0x07E4, 0x0806, //455,562,866   77
    0x0672, 0x0720, 0x0806, //456,500,366   78
    0x0672, 0x075C, 0x0806, //457,437,866   79 
    0x0672, 0x0798, 0x0806, //458,375,366   80
    0x0672, 0x07D4, 0x0806, //459,312,866   81
    0x0673, 0x0710, 0x0806, //460,250,366   82
    0x0673, 0x074C, 0x0806, //461,187,866   83 
    0x0673, 0x0788, 0x0806, //462,125,366   84
    0x0673, 0x07C4, 0x0806, //463,062,866   85
    0x0674, 0x0700, 0x0806, //464,000,366   86
    0x0674, 0x073C, 0x0806, //464,937,866   87 
    0x0674, 0x0778, 0x0806, //465,875,366   88
    0x0674, 0x07B4, 0x0806, //466,812,866   89
    0x0674, 0x07F0, 0x0806, //467,750,366   90
    0x0675, 0x072C, 0x0806, //468,687,866   91  
    0x0675, 0x0768, 0x0806, //469,625,366   92  
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




/******************LORA相关参数************************/
static unsigned char LoraPower = 0;  //功率
static unsigned char LoraBw = 7;     //带宽
unsigned char LoraSF = 2;     //SF 扩频因子 
//static unsigned char LoraFreq = 0;   //频率
static unsigned char LoraCR = 1;     //纠错码率
static unsigned char LoraCRC = 1;    //带CRC校验

static unsigned char RF1278_State = 0;  //1278状态  0 为睡眠 1 为接收 2 为发送 3 为待机







    

extern void RF1278_EntryLoRa(void);

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

    if(ch > 92)
        return 0;
    //LoraFreq = ch;
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
    SPI_MOSI_L();
    SPI_CLK_L();
    SPI_CS_L();
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
    if(SpreadFactor > 5)
       // SpreadFactor = 2;  //默认值
       return 0;
    if(ch > 92)
       // ch = 0;     //默认值
        return 0;
    //LoraFreq = ch;
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
    if(RFM96SpreadFactorTbl[LoraSF] > 9)    //符号长度大于16ms 需要设置该参数
    {
   //     SPIWrite(LR_RegModemConfig3+ 0x08); 
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

    SPIWrite(LR_RegPreambleMsb + 0x0F);         //RegPreambleMsb
    SPIWrite(LR_RegPreambleLsb + 0xFB);        //RegPreambleLsb 8+4=12byte Preamble


    SPIWrite(LR_RegPayloadLength + clen);                     //RegPayloadLength clen byte(this register must difine when the data long of one byte in SF is 6)
    addr = SPIRead((unsigned char)(LR_RegFifoRxBaseAddr >> 8));         //Read RxBaseAddr
    SPIWrite(LR_RegFifoAddrPtr + addr);                      //RxBaseAddr -> FiFoAddrPtr　
    SPIWrite(LR_RegOpMode + 0x0D);                      //Continuous Rx Mode
    RF1278_State = 1; //接收状态
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
    SPIWrite( LR_RegPreambleMsb + 0x04); //set preamble length
    SPIWrite( LR_RegPreambleLsb + 0xE0); //set preamble length
    //SPIWrite( LR_RegPreambleMsb,0xF0);//set preamble length
    //SPIWrite( LR_RegPreambleLsb,0xFF);//set preamble length
    SPIWrite( LR_RegIrqFlagsMask + 0xFA );//清除CAD标志
    SPIWrite( REG_LR_DIOMAPPING1 + 0x20); // Mapping of oins DIO1 CadDetect
                                          //                 DIO3 Cad Done
    RF1278_TxRxEN(0);     //set RF switch to RX path
    RF1278_ClearIrq();       //Clear irq

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
    unsigned long int i = 1777215;//CAD检测超时用 ms
    RF1278_CadInit(); //启动执行WOR
    RF1278_CadSample();// CAD 采样一次
    while((i != 0) && (RF_DIO3() == 0) && (RF_DIO1() == 0))
    {
        i--;
        //delayms(1);
        Watchdog_Reload();      //独立看门狗喂狗
    }
    if(RF_DIO1() == 1)//CAD 检测到数据
    {
        Rf1278_ModeSet(100);
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
    disableInterrupts();
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
    while((!RF_DIO0()) && j != 0)
    {        
        Watchdog_Reload();      //独立看门狗喂狗
        delayms(1);
        j--;                                         //等待GDIO0电平为高
    }

    SPIRead((unsigned char)(LR_RegIrqFlags >> 8));
    RF1278_ClearIrq();					  // Clear irq
    RF1278_Standby();						  // Entry Standby mode

    //发送完唤醒数据包后，将前导时间改回正常默认值。
    SPIWrite(LR_RegPreambleMsb + 0x00); //set preamble length
    SPIWrite(LR_RegPreambleLsb + 0x10); //set preamble length
    enableInterrupts();
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
    unsigned long int j = 2000;  //发送超时用，需要根据实际情况来调整
    disableInterrupts();
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
    RF1278_Standby();						  // Entry Standby mode
    enableInterrupts();
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
void RF1278_ReadRssiSnr(short* rssi)
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
*函数名：unsigned char RF1278_RecePacket(unsigned char *cbuf)
*功能：接收射频数据包
*参数: unsigned char *cbuf 接收数据缓存地址指针
*作者：wq
*创建时间：
*修改时间：
***********************************/
unsigned char RF1278_RecePacket(unsigned char *cbuf,unsigned char *Crc)
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




