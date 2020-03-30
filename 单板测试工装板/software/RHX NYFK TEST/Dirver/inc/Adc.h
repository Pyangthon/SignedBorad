#ifndef ADC_H
#define ADC_H

#include "Stm8l15x.h"

//小数位
#define Decimal     100
//系数
#define Coefficient 1.91

// ADC_1 配置
#define  MADC_Channel_1  ADC_Channel_7 //ADC采样通道
#define  MADC_Pin_1      GPIOD         //ADC采样端口
#define  MADC_Pin_Io_1   GPIO_Pin_7    //ADC采样端口  

// ADC_2 配置
#define  MADC_Channel_2  ADC_Channel_25 //ADC采样通道
#define  MADC_Pin_2      GPIOF          //ADC采样端口
#define  MADC_Pin_Io_2   GPIO_Pin_1     //ADC采样端口  

//ADC EN
#define ADC_EN_H  GPIO_SetBits(GPIOF,GPIO_Pin_0)   
#define ADC_EN_L  GPIO_ResetBits(GPIOF,GPIO_Pin_0) 

extern unsigned long ADC_VALUE;  //ADC采集值

extern unsigned char VadcGet_1(void);
extern unsigned char VadcGet_2(void);

#endif



