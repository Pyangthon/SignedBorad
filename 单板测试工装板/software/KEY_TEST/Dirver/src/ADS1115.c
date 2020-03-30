
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
    //SDA_IN();
    //  Delayus(10);
    //	SDA_1;
    //SCL_1;
    //  Delayus(10);
    // SCL_0;
}

uint8_t IIC_Read_Byte(void)
{
    uint8_t i, receive = 0;
    SDA_IN();	//
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
//*������ :void ADS1115_Confige(uint8_t Channel)
//*˵��   :ADS1115 оƬ���ú���
//*����   :��
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
void ADS1115_Confige(uint8_t Channel)
{
    uint8_t i;
    uint8_t table[4] = {0};
    uint8_t ChannelTab[4] = {0xC2, 0xD2, 0xE2, 0xF2}; //������FS=+-4.096������ת��ģʽ
    if(Channel > 3)
        return;
    table[0] = 0x90; //CMD_Write;
    table[1] = 0x01; //ָ�����üĴ���
    table[2] = ChannelTab[Channel]; //�������üĴ����ĸ߰�λ1100 0101����AINp=AIN0��AINn=GND;������FS=+-4.096������ת��ģʽ
    table[3] = 0xe3; //�������üĴ����ĵͰ�λ1100 0101����
    IIC_Start(); //������ʼ�ź�
    for(i = 0; i < 4; i++)
    {
        IIC_Send_Byte(table[i]); //��table�������д��ads1115
        //Delayus(20);
        ADS1115_Delayms(1);
        IIC_Wait_Ack();
    }
    IIC_Stop(); //����ֹͣ�ź�
}


///******************************************************************************************************
//*������ :void ADS1115_PointRegister (void)
//*˵��   :ADS1115 ָ�����üĴ���
//*����   :��
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
void ADS1115_PointRegister (void)
{
    uint8_t i;
    uint8_t table[4] = {0};
    table[0] = 0x90;
    table[1] = 0x00;
    IIC_Start(); //������ʼ�ź�
    for(i = 0; i < 2; i++)
    {
        IIC_Send_Byte(table[i]); //��table�������д��ads1115
        //Delayus(20);
        ADS1115_Delayms(1);
        IIC_Wait_Ack();
    }
    IIC_Stop();  /////ֹͣI2C
}
///******************************************************************************************************
//*������ :void ADS1115_ReadData (void)
//*˵��   :ADS1115 ��ȡ����
//*����   :��
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
uint16_t ADS1115_ReadData (void)
{
    uint16_t  data;
    uint8_t table[4] = {0};
    IIC_Start();     /////����I2C
    IIC_Send_Byte(0x91);   /////���Ͷ�����
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
///******************************************************************************************************
//*������ :void ADS1115_ReadData (void)
//*˵��   :ADS1115 ��ȡADCֵ
//*����   :��
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
unsigned int GetADS1115Adc(uint8_t Channel)
{
    uint16_t GetDatHex = 0;
    float Voltage = 0;
    ADS1115_Confige(Channel);
    ADS1115_Delayms(10);
    ADS1115_PointRegister();
    ADS1115_Delayms(10);
    GetDatHex = ADS1115_ReadData();
    ADS1115_Delayms(10);
    Voltage = GetDatHex * 409.6 / 0xFFFF;

    return (u16)Voltage;
}
//*****************************************************************************/
//*������ :void ADS1115_Init(void)
//*˵��   :��ʼ��ADS1115����SDA��SCL��ʼ��Ϊ����������������������
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void ADS1115_Init(void)
{
    GPIO_Init(ADS_IIC_PORT, ADS_SCL_PIN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(ADS_IIC_PORT, ADS_SDA_PIN, GPIO_Mode_Out_PP_High_Fast);
    
    SCL_1;
    SDA_1;
    
    ADS1115_Delayms(5);
}
