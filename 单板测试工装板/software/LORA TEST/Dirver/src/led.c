#include "led.h"


///***************************************************************************
//* ��������: void LED_Init(void)
//* ����  	: ��ʼ��LED�˿�
//* ��ڲ���: None
//* ����ֵ  : None
//* ����  	:
//* ����ʱ��:
//* �޸�ʱ��:
//****************************************************************************
void LED_Init(void)
{
    GPIO_Init(LED_PORT, LED0_PIN, GPIO_Mode_Out_PP_High_Fast);      // ��ʼ��LED0Ϊͨ������������
    GPIO_Init(LED_PORT, LED1_PIN, GPIO_Mode_Out_PP_High_Fast);      // LED1  
    GPIO_Init(LED_PORT, LED2_PIN, GPIO_Mode_Out_PP_High_Fast);      // LED2
    GPIO_Init(LED_PORT, LED3_PIN, GPIO_Mode_Out_PP_High_Fast);      // LED3
}

///***************************************************************************
//* ��������: void LED_Run(u8 mode) 
//* ����  	: ����LED��
//* ��ڲ���: mode ��Ҫ������LED��� 0-3Ϊ��ӦLED�� 4Ϊ����LED
//* ����ֵ  : None
//* ����  	:
//* ����ʱ��:
//* �޸�ʱ��:
//****************************************************************************
void LED_Run(u8 mode)
{
    switch(mode)
    {
        case 0:                 // ģʽ0 LED0��
            GPIO_ResetBits(LED_PORT, LED0_PIN);
            break;          
        case 1:                 // ģʽ1 LED1��
            GPIO_ResetBits(LED_PORT, LED1_PIN);
            break;              
        case 2:                 // ģʽ2 LED2��
            GPIO_ResetBits(LED_PORT, LED2_PIN);
            break;
        case 3:                 // ģʽ3 LED3��
            GPIO_ResetBits(LED_PORT, LED3_PIN);
            break;
        case 4:                 // ģʽ4 ȫ��
            GPIO_ResetBits(LED_PORT, LED0_PIN);      // ����͵�ƽ��LED����
            GPIO_ResetBits(LED_PORT, LED1_PIN);
            GPIO_ResetBits(LED_PORT, LED2_PIN);
            GPIO_ResetBits(LED_PORT, LED3_PIN);
            break;

        default:                // Ĭ���޶���
            break;
    }
}

///***************************************************************************
//* ��������: void LED_Off(u8 mode)
//* ����  	: �رն�Ӧ��LED
//* ��ڲ���: mode ��Ҫ�رյ�LED��� 0-3Ϊ��ӦLED�� 4Ϊ����LED
//* ����ֵ  : None
//* ����  	:
//* ����ʱ��:
//* �޸�ʱ��:
//****************************************************************************
void LED_Off(u8 mode)
{
    switch(mode)
    {
        case 0:                 //  ģʽ0 LED0��
            GPIO_SetBits(LED_PORT, LED0_PIN);
            break;
        case 1:                 //  ģʽ1 LED1��
            GPIO_SetBits(LED_PORT, LED1_PIN);
            break;
        case 2:                 // ģʽ2 LED2��
            GPIO_SetBits(LED_PORT, LED2_PIN);
            break;  
        case 3:                 // ģʽ3 LED3��
            GPIO_SetBits(LED_PORT, LED3_PIN);
            break;
        case 4:                 // ģʽ4 LEDȫ��
            GPIO_SetBits(LED_PORT, LED0_PIN);
            GPIO_SetBits(LED_PORT, LED1_PIN);
            GPIO_SetBits(LED_PORT, LED2_PIN);
            GPIO_SetBits(LED_PORT, LED3_PIN);
            break;
            
        default:                // Ĭ���޶���
            break;
    }
}


///***************************************************************************
//* ��������: void LEDFlicker(u8 LEDNum, u8 i) 
//* ����  	: ָ��LED��˸�ʹ���
//* ����  	: u8 LEDNum  LED�Ƶı��
//*           u8 i       LED��˸�Ĵ���
//* ����  	:
//* ����ʱ��:
//* �޸�ʱ��:
//****************************************************************************

void LEDFlicker(u8 LEDNum, u8 i)
{
    if(i > 0)
    {
        while(i--)
        {
            LED_Run(LEDNum);
            Delay_ms(200);
            LED_Off(LEDNum);
            Delay_ms(200);
        }
    }
}