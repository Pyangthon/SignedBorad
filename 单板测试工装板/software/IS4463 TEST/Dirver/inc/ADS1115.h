

#ifndef ADS1115_H
#define ADS1115_H
#include "stm8l15x_gpio.h"

// ADS1115Ӳ���ӿں궨�� 
#define ADS_IIC_PORT    GPIOC
#define ADS_SCL_PIN     GPIO_Pin_1
#define ADS_SDA_PIN     GPIO_Pin_0 

#define SCL_1       GPIO_SetBits(ADS_IIC_PORT, ADS_SCL_PIN)
#define SCL_0       GPIO_ResetBits(ADS_IIC_PORT, ADS_SCL_PIN)

#define SDA_1       GPIO_SetBits(ADS_IIC_PORT, ADS_SDA_PIN)
#define SDA_0       GPIO_ResetBits(ADS_IIC_PORT, ADS_SDA_PIN)

#define READ_SDA    GPIO_ReadInputDataBit(ADS_IIC_PORT, ADS_SDA_PIN)

#define SDA_OUT()   GPIO_Init(ADS_IIC_PORT, ADS_SDA_PIN, GPIO_Mode_Out_PP_High_Fast)
#define SDA_IN()    GPIO_Init(ADS_IIC_PORT, ADS_SDA_PIN, GPIO_Mode_In_FL_No_IT)

// ��ȡADS1115��ֵ
unsigned int GetADS1115Adc(unsigned char Channel);
// ��ʼ��ADS1115iic����
void ADS1115_Init(void);

#endif






