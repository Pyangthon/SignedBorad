#include "led.h"
#include "key.h"
#include "Clk.h"
#include "LoraSpiGpio.h"
#include "Lora.h"
#include "Delay.h"
#include "stm8l15x_it.h"

void LoRaReveive(u8 *buf);
// ��������          
void main(void)
{   

//    u8 Key1Sta = 0;
//    u8 Key2Sta = 0;
//    unsigned char RFInit_Flag = 0;  // RF��ʼ����־λ�������ж�RF�Ƿ񱻳�ʼ��
    unsigned char Arry[5] = {0};
    unsigned char send_arry[5] = {0x01, 0x89, 0x87,0xAA,0xCC};
//    unsigned char i;
    SysClockInit();
    LED_Init();
    KeyGpioInit();
    Lora_Gpio_Init();
    enableInterrupts(); // �����ж� 
    if(RF1278_Init(0, 2))
    {
         LEDFlicker(3);
    }
    Delay_ms(5);
//    Rf1278_ModeSet(5);
    if(GetRF1278_State() == 1)
    {
        LEDFlicker(1);
    }
    while(1)
    {
        // ����ʹ��
        RF1278_TxRxEN(0);
        // �����жϺ���
        if(RXFlag == 1)
        {
            Rf1278_ModeSet(5);
            
            RF1278_RecePacket(Arry, 5);
            Delay_ms(1000);
            LoRaReveive(Arry);
            enableInterrupts();
            RXFlag = 0;
            
        }
//          ���û�����ݽ��յ�����ÿ��1s����һ������
        if(RXFlag == 0)
        {
//              RF1278_TxRxEN(1);
              Delay_ms(2000);
              RF1278_SendPacket(send_arry, 5);
              LED_RGB_Fli(1, LEDG);
              LED_RGB_Fli(1, LEDB);
              Rf1278_ModeSet(5);
              Delay_ms(300);

        }
        
       
    }
}

void LoRaReveive(u8 *buf)
{
    u8 i;       // ����ѭ��
    u8 Re_arry[]  = {0x02,0x12,0x45, 0xAC, 0xDB} ;
    for(i = 0; i < 5; i++)
    {
        if(buf[i] == Re_arry[i] )
        {
            LED_RGB_Fli(1, LEDG);
            
        }
        
        else
        {
            LEDFlicker(1);
//            Delay_ms(100);
        }
    }
}