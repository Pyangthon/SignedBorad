#include "SysInitApp.h"
#include "RS485.h"
#include "Clk.h"
#include "Delay.h"
#include "led.h"
#include "stm8l15x_it.h"
#include "Lora.h"
#include "LoraSpiGpio.h"

u8 JudgeData();

// ���԰����
void main(void)
{
    u8 send_array[3] = {0x11, 0x22, 0x33};      // ��������
    u8 retChe = 0;                              // ���������жϱ�־λ
    SysClockInit();                             
    LED_Init();
    LED_Run(4);                                 // ��ʾϵͳ�������
    Delay_ms(300);          
    LED_Off(4);                 
    Delay_ms(100);
    RS485Init();                                // ��ʼ��RS485ͨ��
    Lora_Gpio_Init();                           // LoRaģ��GPIO��ʼ��
    if(RF1278_Init(2, 2))                       // ��ʼ����Ƶģ��Ƶ��Ϊ2����Ƶ����Ϊ2�����ж��Ƿ��ʼ���ɹ�
    {
        LEDFlicker(0, 3);                       // ��ʾ��ʼ���ɹ�
    }
    enableInterrupts(); // �����ж� 
    while(1)
    {
        
        if(retChe == 0)                         // ��һ�μ�������򱻲�巢�Ͳ�������
        {
            RF1278_SendPacket(send_array, 3);
            Delay_ms(1500);
            Rf1278_ModeSet(5);                  // ����Ϊ����ģʽ
        }
        if(RXFlag == 1)                         // ���������յ����ݺ󷵻�һ�����ݣ���ʱ�жϽ��ձ�־λ�Ƿ���1
        {
            retChe = JudgeData();               // �����ձ�־λ��1ʱ���������ݽ����жϺ���
            if(retChe)                          // �ж����ݽ��ձ�־λ
            {
                LEDFlicker(1, 4);               // ��1����˸��ʾ(LED1��˸4��)
                printf("���ݽ��ճɹ���");       // ����485ͨ����дprintf������ӡ��ʾ��Ϣ 
            }
            else
            {
                LEDFlicker(2,1);                // ������LED2��˸1��
            }
        }
        
    }      
}

u8 JudgeData()
{
    u8 ChackArray[] = {0x00, 0x10, 0xAA};       // ��������
    u8 RecArray[3] = {0};                       // ������������
    u8 chackFre;                                // 
    RF1278_RecePacket(RecArray, 3);
    Delay_ms(300);
    for(chackFre = 0; chackFre < 3; chackFre++) // �жϽ��������Ƿ�����
    {
        if(ChackArray[chackFre] != RecArray[chackFre])  // �����в�ͬ����������
        {
            break;
        }
    }
    return (chackFre == 3?1:0);     // �жϼ���־λ�Ƿ����3������3�򷵻�1�����򷵻�0
}

