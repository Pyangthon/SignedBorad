
#include "ADS1115.h"




//static void SDA_OUT(void)
//{
//	GPIO_Init(ADS_IIC_PORT, ADS_SDA_PIN,GPIO_Mode_Out_PP_High_Fast);
//}
//
//static void SDA_IN(void)
//{
//	GPIO_Init(ADS_IIC_PORT, ADS_SDA_PIN,GPIO_Mode_In_FL_No_IT);
//}

static void Delayus(unsigned int us)  
{  
	unsigned int i;  
	for(i=0;i<us;i++)
	{
		asm("nop");  
		asm("nop"); 
		asm("nop"); 
		asm("nop"); 
		asm("nop"); 
	}
} 

void ADS1115_Delayms(unsigned int time)
{
	unsigned int i,j;
	for(i = 0;i < time;i++)
		for(j = 0; j < 100;j++);
}

static void IIC_Start(void)  
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

static void IIC_Stop(void)  
{  
    uint8_t i;  
    SDA_OUT();//
    SDA_0;  
    Delayus(10);  
    SCL_1;  
    Delayus(10);  
    SDA_1;  
    for(i=0;i<5;i++)  
    {  
        Delayus(10);  
    }             
}  
  
static uint8_t IIC_Wait_Ack(void)  
{  
    uint8_t ucErrTime=0; 
//	SDA_1;
	Delayus(10); 
	SCL_1;
    SDA_IN();      //   
    Delayus(10);  
    Delayus(10);  
    while(READ_SDA)  
    {  
        ucErrTime++;  
        if(ucErrTime>250)  
        {  
            IIC_Stop();  
            return 1;  
        }  
          
    }  
    SCL_0;  //       
    return 0;    
}   
  
static void IIC_Ack(void)  
{       
    SDA_OUT();  
    SDA_0;  
    Delayus(10);  
    SCL_1;  
    Delayus(10);  
    SCL_0;  
    Delayus(10);  
}  
          
static void IIC_NAck(void)  
{  
    SDA_OUT();  
    SDA_1;  
    Delayus(10);  
    SCL_1;  
    Delayus(10);  
    SCL_0;  
    Delayus(10);  
}                                          
            
static void IIC_Send_Byte(uint8_t txd)  
{   
    uint8_t i;  
    SDA_OUT();  
    for(i=0;i<8;i++)  
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
  
static uint8_t IIC_Read_Byte(void)  
{  
    uint8_t i,receive=0;  
    SDA_IN();	//    
    for(i=0;i<8;i++)  
    {  
        SCL_1;  
        Delayus(10);  
        receive <<=1;  
        if(READ_SDA) 
		receive |= 0x01;  
          
        SCL_0;  
        Delayus(10);  
    }  
    SDA_OUT();  
    return receive;          
}  

void ADS1115_Confige(uint8_t Channel)
{
	uint8_t i;
	uint8_t table[4] = {0};
	uint8_t ChannelTab[4] = {0xC6,0xD4,0xE2,0xF2}; //������FS=+-4.096������ת��ģʽ
	if(Channel > 3)
           return;
	table[0] = 0x90; //CMD_Write;
	table[1] = 0x01; //ָ�����üĴ���
	table[2] = ChannelTab[Channel]; //�������üĴ����ĸ߰�λ1100 0101����AINp=AIN0��AINn=GND;������FS=+-4.096������ת��ģʽ
	table[3] = 0x03; //�������üĴ����ĵͰ�λ1110 0011����
	IIC_Start(); //������ʼ�ź�
	for(i=0; i<4; i++)
	{
            IIC_Send_Byte(table[i]); //��table�������д��ads1115
            ADS1115_Delayms(10);
            IIC_Wait_Ack();		
	}
	IIC_Stop(); //����ֹͣ�ź�
}



void ADS1115_PointRegister (void)
{
	uint8_t i;
	uint8_t table[4] = {0};
	table[0] = 0x90;
	table[1] = 0x00;
	IIC_Start(); //������ʼ�ź�
	for(i=0;i<2;i++)
	{
		IIC_Send_Byte(table[i]); //��table�������д��ads1115
		//Delayus(20);	
		ADS1115_Delayms(1);
		IIC_Wait_Ack();			
	}
	IIC_Stop();  /////ֹͣI2C
}

unsigned int ADS1115_ReadData (void)
{  
	unsigned int  data;
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



unsigned int GetADS1115Adc(uint8_t Channel)
{
	unsigned int GetDatHex = 0;
	float Voltage = 0;
	ADS1115_Confige(Channel);
	ADS1115_Delayms(10);
	ADS1115_PointRegister();
	ADS1115_Delayms(10);
	GetDatHex = ADS1115_ReadData();
	ADS1115_Delayms(10);
        if(Channel == 0){
            Voltage = GetDatHex/32768.f*1.024 ; 
        }else if(Channel == 1){
	    Voltage = GetDatHex/32768.f*2.048;
        }else{
            Voltage = GetDatHex/32768.f*4.096;
        }
	
	return (unsigned int)((Channel == 0) ? (Voltage*200):(Voltage*50));
//    return (unsigned int)((Channel == 0) ? (Voltage*1000):(Voltage*100));
}


///***************************************************************************
//* ��������: void ADS_GPIO_Init(void) 
//* ����  	: ��ʼ��ADS_IIC�˿�
//* ����  	: None
//* ����  	:
//* ����ʱ��: 2020��1��13��
//* �޸�ʱ��:
//****************************************************************************
void ADS_GPIO_Init(void)
{
    GPIO_Init(ADS_IIC_PORT, ADS_SDA_PIN, GPIO_Mode_Out_OD_Low_Fast);
    GPIO_Init(ADS_IIC_PORT, ADS_SCL_PIN, GPIO_Mode_Out_OD_Low_Fast);
    SDA_1;
    SCL_1;
    ADS1115_Delayms(5);
    
}
///***************************************************************************
//* ��������: 
//* ����  	:
//* ����  	:
//* ����  	:
//* ����ʱ��:
//* �޸�ʱ��:
//****************************************************************************
float VoltAverage(unsigned char Channel)        //���ѹƽ��ֵ
{
	unsigned int k;                           // ����ѭ������
    unsigned int EVAL_NUM = 300;              // ��ֵ����      
	float VoltCount=0,temp;                     
	
	// ��ƽ��ֵ 
	for(k=0;k<EVAL_NUM;k++)
	{
		VoltCount += GetADS1115Adc(Channel);	
	}
	temp=VoltCount;
	VoltCount = 0;
	return (temp/500);	
}

///***************************************************************************
//* ��������: 
//* ����  	:
//* ����  	:
//* ����  	:
//* ����ʱ��:
//* �޸�ʱ��:
//****************************************************************************
float GetCurrent(unsigned char Channel)
{
    float MeaCurrent;       // ��������ֵ
    float Gain = (unsigned int)(Channel == 0)?200:50;  
    MeaCurrent = VoltAverage(Channel) / (Gain * 1000);
    return MeaCurrent;
}
