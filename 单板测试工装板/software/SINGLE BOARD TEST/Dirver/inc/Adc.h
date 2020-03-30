#ifndef ADC_H
#define ADC_H

#include "stm8l15x.h"
#include "stm8l15x_adc.h"

//С��λ
#define Decimal     100
//ϵ��
#define Coefficient 1.91

// ADC_1 ����
#define  MADC_Channel_1  ADC_Channel_7 //ADC����ͨ��
#define  MADC_Pin_1      GPIOD         //ADC�����˿�
#define  MADC_Pin_Io_1   GPIO_Pin_7    //ADC�����˿�  

// ADC_2 ����
#define  MADC_Channel_2  ADC_Channel_15 //ADC����ͨ��
#define  MADC_Pin_2      GPIOB          //ADC�����˿�
#define  MADC_Pin_Io_2   GPIO_Pin_3     //ADC�����˿�  

//ADC EN
#define ADC_EN_H  GPIO_SetBits(GPIOF,GPIO_Pin_0)   
#define ADC_EN_L  GPIO_ResetBits(GPIOF,GPIO_Pin_0) 

extern unsigned long ADC_VALUE;  //ADC�ɼ�ֵ
extern void ADC_Config_Init();
extern u16 VadcGet_1(void);
extern u16 VadcGet_2(void);

#endif



