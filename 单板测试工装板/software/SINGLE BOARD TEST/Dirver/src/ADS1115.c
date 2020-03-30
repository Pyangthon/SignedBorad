
#include "ADS1115.h"


static void Delayus(uint16_t us)
{
    uint16_t i;
    for(i = 0; i < us; i++)
    {
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    }
}

void ADS1115_Delayms(uint16_t time)
{
    uint16_t i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 100; j++);
}

void IIC_Start(void)
{
    SDA_OUT();
    SCL_1;
    SDA_1;
    Delayus(10);
    SDA_0;
    Delayus(10);
    SCL_0;
    Delayus(10);
}

void IIC_Stop(void)
{
    uint8_t i;
    SDA_OUT();//
    SDA_0;
    Delayus(10);
    SCL_1;
    Delayus(10);
    SDA_1;
    for(i = 0; i < 5; i++)
    {
        Delayus(10);
    }
}

uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    //	SDA_1;
    Delayus(10);
    SCL_1;
    SDA_IN();      //
    Delayus(10);
    Delayus(10);
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }

    }
    SCL_0;  //
    return 0;
}

void IIC_Ack(void)
{
    SDA_OUT();
    SDA_0;
    Delayus(10);
    SCL_1;
    Delayus(10);
    SCL_0;
    Delayus(10);
}

void IIC_NAck(void)
{
    SDA_OUT();
    SDA_1;
    Delayus(10);
    SCL_1;
    Delayus(10);
    SCL_0;
    Delayus(10);
}

void IIC_Send_Byte(uint8_t txd)
{
    uint8_t i;
    SDA_OUT();
    for(i = 0; i < 8; i++)
    {
        if(txd & 0x80)
        {
            SDA_1;
        }
        else
        {
            SDA_0;
        }
        txd <<= 1;
        Delayus(10);
        SCL_1;
        Delayus(10);
        SCL_0;
    }
}

uint8_t IIC_Read_Byte(void)
{
    uint8_t i, receive = 0;
    SDA_IN();	
    for(i = 0; i < 8; i++)
    {
        SCL_1;
        Delayus(10);
        receive <<= 1;
        if(READ_SDA)
            receive |= 0x01;

        SCL_0;
        Delayus(10);
    }
    SDA_OUT();
    return receive;
}
///******************************************************************************************************
//*函数名 :void ADS1115_Confige(uint8_t Channel)
//*说明   :ADS1115 芯片配置函数
//*参数   :无
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
void ADS1115_Confige(uint8_t Channel)
{
    uint8_t i;
    uint8_t table[4] = {0};
    uint8_t ChannelTab[4] = {0xC2, 0xD2, 0xE2, 0xF2}; //满量程FS=+-4.096；连续转换模式
    if(Channel > 3)
        return;
    table[0] = 0x90; //CMD_Write;
    table[1] = 0x01; //指向配置寄存器
    table[2] = ChannelTab[Channel]; //设置配置寄存器的高八位1100 0101，即AINp=AIN0，AINn=GND;满量程FS=+-4.096；连续转换模式
    table[3] = 0xe3; //设置配置寄存器的低八位11100101
    IIC_Start(); //发送起始信号
    for(i = 0; i < 4; i++)
    {
        IIC_Send_Byte(table[i]); //将table里面的数写入ads1115
        ADS1115_Delayms(1);
        IIC_Wait_Ack();
    }
    IIC_Stop(); //发送停止信号
}


///******************************************************************************************************
//*函数名 :void ADS1115_PointRegister (void)
//*说明   :ADS1115 指向配置寄存器
//*参数   :无
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
void ADS1115_PointRegister (void)
{
    uint8_t i;
    uint8_t table[4] = {0};
    table[0] = 0x90;
    table[1] = 0x00;
    IIC_Start(); //发送起始信号
    for(i = 0; i < 2; i++)
    {
        IIC_Send_Byte(table[i]); //将table里面的数写入ads1115
        ADS1115_Delayms(1);
        IIC_Wait_Ack();
    }
    IIC_Stop();  //停止I2C
}
///******************************************************************************************************
//*函数名 :void ADS1115_ReadData (void)
//*说明   :ADS1115 读取数据
//*参数   :无
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
uint16_t ADS1115_ReadData (void)
{
    uint16_t  data;
    uint8_t table[4] = {0};
    IIC_Start();            //开启I2C
    IIC_Send_Byte(0x91);    //发送读命令
    IIC_Wait_Ack();
    Delayus(20);
    table[0] = IIC_Read_Byte();
    Delayus(10);
    IIC_Ack();
    ADS1115_Delayms(1);

    table[1] = IIC_Read_Byte();
    Delayus(10);
    IIC_NAck();
    ADS1115_Delayms(1);
    IIC_Stop();

    data = table[0];
    data <<= 8;
    data |= table[1];

    return data;
}
//*****************************************************************************/
//*函数名 :uint16_t GetADS1115Adc(uint8_t Channel)
//*说明   :获取ADC采样值
//*参数   :Channel 采样通道
//*返回值 :GetDetHex 采样值
//*作者   :
//*****************************************************************************/
uint16_t GetADS1115Adc(uint8_t Channel)
{
    uint16_t GetDatHex = 0;
//    float Voltage = 0;
    ADS1115_Confige(Channel);
    ADS1115_Delayms(10);
    ADS1115_PointRegister();
    ADS1115_Delayms(3);
    GetDatHex = ADS1115_ReadData();
    return GetDatHex;
}
//*****************************************************************************/
//*函数名 :void ADS1115_Init(void)
//*说明   :初始化ADS1115，将SDA和SCL初始化为高速推挽输出，并拉高输出
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void ADS1115_Init(void)
{
    GPIO_Init(ADS_IIC_PORT, ADS_SCL_PIN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(ADS_IIC_PORT, ADS_SDA_PIN, GPIO_Mode_Out_PP_High_Fast);
    SCL_1;
    SDA_1;
    ADS1115_Delayms(5);
}

//*****************************************************************************/
//*函数名 :int avg(unsigned char x,unsigned char ch )
//*说明   :获取采样平均值
//*参数   :ch 采样通道
//*返回值 :sum/x 采样平均值结果
//*作者   :
//*****************************************************************************/
int GetAdcAvg(u8 ch )
{
    u8 x = 50;
    unsigned char temp;
    long sum = 0;
    u16 buff[256];
    
    for(temp=0;temp<2*x;temp++)//采样100次
    {
        buff[temp]=GetADS1115Adc(ch);
    }
    
    BubblingSort(buff,2*x);//冒泡排序

    for(temp=x/2;temp<1.5*x;temp++)//取中间50个求平均
    {
        sum+=buff[temp];
    }
    return sum/x;
}

//*****************************************************************************/
//*函数名 :void BubblingSort(int *arr, int n);
//*说明   :冒泡排序
//*参数   :*arr 需要排序的数组
//*        n  排序次数
//*返回值 :
//*作者   :
//*****************************************************************************/
void BubblingSort(u16 *arr, int n) 
{
    int i, j, temp;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n - i - 1; ++j) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}