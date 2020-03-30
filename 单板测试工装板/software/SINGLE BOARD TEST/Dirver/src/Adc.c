#include "Adc.h"

unsigned long ADC_VALUE = 0;  //ADC采集值
///*******************************************************************************
//* 名    称：void Vadc_IOStar(void)
//* 功    能：配置ADC前 初始化IO 状态 
//* 入口参数：
//* 出口参数：
//* 说    明：
//* 调用方法：无
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
//* 名    称：void Vadc_IOStop(void)
//* 功    能：ADC采集完成 关闭IO 
//* 入口参数：
//* 出口参数：
//* 说    明：
//* 调用方法：无
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
//* 名    称：void ADC_Config(void)
//* 功    能：ADC配置初始化
//* 入口参数：
//* 出口参数：
//* 说    明：
//* 调用方法：无
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
//* Description     : ADC采样初始化
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
      ADC_ChannelCmd(ADC1, MADC_Channel_1, ENABLE);//此处配置通道
    }
    else if(sel == 2)
    {
      /* Enable ADC_Channel_TempSensor */
      ADC_ChannelCmd(ADC1, MADC_Channel_2, ENABLE);//此处配置通道    
    }
      ADC_SoftwareStartConv(ADC1);
}

///*******************************************************************************
//* Function Name   : VREF_Init
//* Description     : 内部参考电压 ADC初始化配置
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
//*函数名:u16 VADC_Value(void)
//*功能:ADC1采样3次取最后一次
//*输入:无
//*输出:采样值
//*备注:无
//*******************************************************************************/
u16 VADC_Value(void)
{       
  uint16_t res = 0;
  u8 i = 0;
  for(i = 0; i < 3; i++){
    ADC_SoftwareStartConv(ADC1);
    while( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0 );
    ADC_ClearFlag(ADC1,ADC_FLAG_EOC);//清除对应标志
    res = ADC_GetConversionValue(ADC1);
  }
  return res;
}
///*******************************************************************************
//*函数名:uint16_t VadcGet(void)
//*功能:获取ADC值
//*输入:无
//*输出:电池电压
//*备注:无
//*******************************************************************************/
u16 VadcGet_1(void)
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
    
    adc_vin_buff =(unsigned long)((1.225 * adc_vin_buff / adcvref ) * Decimal * Coefficient);  //保留两位 
    ADC_Cmd(ADC1, DISABLE);
    Vadc_IOStop(1);
    ADC_VALUE = (unsigned int)adc_vin_buff;
    return ADC_VALUE - 5;
}
///*******************************************************************************
//*函数名:uint16_t VadcGet_2(void)
//*功能:获取ADC值
//*输入:无
//*输出:电池电压
//*备注:无
//*******************************************************************************/
u16 VadcGet_2(void)
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
    
    adc_vin_buff =(unsigned long)((1.225 * adc_vin_buff / adcvref ) * Decimal * Coefficient );  //保留两位 
    ADC_Cmd(ADC1, DISABLE);
    Vadc_IOStop(2);
    ADC_VALUE = (unsigned int)adc_vin_buff;
    return ADC_VALUE;
}





