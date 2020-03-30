#include "Adc.h"

unsigned long ADC_VALUE = 0;  //ADC�ɼ�ֵ
///*******************************************************************************
//* ��    �ƣ�void Vadc_IOStar(void)
//* ��    �ܣ�����ADCǰ ��ʼ��IO ״̬ 
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����
//* ���÷�������
//*******************************************************************************/
void Vadc_IOStar(unsigned char sel)
{
  if(sel == 1)
  {
    ADC_EN_L;
    GPIO_Init(MADC_Pin_1, MADC_Pin_Io_1, GPIO_Mode_In_FL_No_IT);
  }
  else if(sel == 2)
  {
    ADC_EN_L;
    GPIO_Init(MADC_Pin_2, MADC_Pin_Io_2, GPIO_Mode_In_FL_No_IT);  
  }
}
///*******************************************************************************
//* ��    �ƣ�void Vadc_IOStop(void)
//* ��    �ܣ�ADC�ɼ���� �ر�IO 
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����
//* ���÷�������
//*******************************************************************************/
void Vadc_IOStop(unsigned char sel)
{
  if(sel == 1)
  {
    ADC_EN_H;
    GPIO_Init(MADC_Pin_1, MADC_Pin_Io_1, GPIO_Mode_Out_PP_Low_Slow);
    
  }
  else if(sel == 2)
  {
    ADC_EN_H;
    GPIO_Init(MADC_Pin_2, MADC_Pin_Io_2, GPIO_Mode_Out_PP_Low_Slow);    
  }

}
///*******************************************************************************
//* ��    �ƣ�void ADC_Config(void)
//* ��    �ܣ�ADC���ó�ʼ��
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����
//* ���÷�������
//*******************************************************************************/
void ADC_Config_Init()
{
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
    /* Initialise and configure ADC1 */
    ADC_Init(ADC1, ADC_ConversionMode_Continuous, ADC_Resolution_12Bit, ADC_Prescaler_2);
    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_384Cycles);
    ADC_VrefintCmd(ENABLE);
}
///*******************************************************************************
//* Function Name   : VADC_Init
//* Description     : ADC������ʼ��
//* Calls           :
//* Called By       :
//* Inputs          : None
//* Outputs         : None
//* Return          : None
//* Notes           : None
//*******************************************************************************/
void VADC_Init(unsigned char sel)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);   
    /* de-initialize ADC */
    ADC_DeInit(ADC1);
    /* Initialise and configure ADC1 */
    ADC_Init(ADC1, ADC_ConversionMode_Continuous, ADC_Resolution_12Bit, ADC_Prescaler_2);
    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_384Cycles);
    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);
    if(sel == 1)
    {
      /* Enable ADC_Channel_TempSensor */
      ADC_ChannelCmd(ADC1, MADC_Channel_1, ENABLE);//�˴�����ͨ��
    }
    else if(sel == 2)
    {
      /* Enable ADC_Channel_TempSensor */
      ADC_ChannelCmd(ADC1, MADC_Channel_2, ENABLE);//�˴�����ͨ��    
    }
      ADC_SoftwareStartConv(ADC1);
}

///*******************************************************************************
//* Function Name   : VREF_Init
//* Description     : �ڲ��ο���ѹ ADC��ʼ������
//* Calls           :
//* Called By       :
//* Inputs          : None
//* Outputs         : None
//* Return          : None
//* Notes           : None
//*******************************************************************************/
void VREF_Init(void)
{
    /* Enable ADC clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);

    /* de-initialize ADC */
    ADC_DeInit(ADC1);

    /*ADC configuration
      ADC configured as follow:
      - Channel VREF
      - Mode = Single ConversionMode(ContinuousConvMode disabled)
      - Resolution = 12Bit
      - Prescaler = /2
      - sampling time 384 */

    ADC_VrefintCmd(ENABLE);
    //delay_10us(3);
    ADC_Cmd(ADC1, ENABLE);
    ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit, ADC_Prescaler_2);
    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_384Cycles);
    ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, ENABLE);
}
///******************************************************************************
//*������:u16 VADC_Value(void)
//*����:ADC1����3��ȡ���һ��
//*����:��
//*���:����ֵ
//*��ע:��
//*******************************************************************************/
u16 VADC_Value(void)
{       
  uint16_t res = 0;
  u8 i = 0;
  for(i = 0; i < 3; i++){
    ADC_SoftwareStartConv(ADC1);
    while( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0 );
    ADC_ClearFlag(ADC1,ADC_FLAG_EOC);//�����Ӧ��־
    res = ADC_GetConversionValue(ADC1);
  }
  return res;
}
///*******************************************************************************
//*������:uint16_t VadcGet(void)
//*����:��ȡADCֵ
//*����:��
//*���:��ص�ѹ
//*��ע:��
//*******************************************************************************/
unsigned char VadcGet_1(void)
{
    unsigned long adcvref;
    unsigned long adc_vin_buff;
    unsigned int i = 0;
    Vadc_IOStar(1);
    VREF_Init();
    adcvref = VADC_Value();
    while(i++ < 500);
    VADC_Init(1);
    adc_vin_buff = VADC_Value();
    
    adc_vin_buff =(unsigned long)((1.225 * adc_vin_buff / adcvref ) * Decimal * Coefficient);  //������λ 
    ADC_Cmd(ADC1, DISABLE);
    Vadc_IOStop(1);
    ADC_VALUE = (unsigned int)adc_vin_buff;
    return ADC_VALUE;
}
///*******************************************************************************
//*������:uint16_t VadcGet_2(void)
//*����:��ȡADCֵ
//*����:��
//*���:��ص�ѹ
//*��ע:��
//*******************************************************************************/
unsigned char VadcGet_2(void)
{
    unsigned long adcvref;
    unsigned long adc_vin_buff;
    unsigned int i = 0;
    Vadc_IOStar(2);
    VREF_Init();
    adcvref = VADC_Value();
    while(i++ < 500);
    VADC_Init(2);
    adc_vin_buff = VADC_Value();
    
    adc_vin_buff =(unsigned long)((1.225 * adc_vin_buff / adcvref ) * Decimal * Coefficient );  //������λ 
    ADC_Cmd(ADC1, DISABLE);
    Vadc_IOStop(2);
    ADC_VALUE = (unsigned int)adc_vin_buff;
    return ADC_VALUE;
}





