#include "TestItems.h"

void Check_Crc16(void);
int main(void)
{      
    
    System_Init();
    enableInterrupts();
    Rf1278_ModeSet(128);
//    Check_Crc16();
    
    RS485_PWR_ON();
    
    RS485_PWR_OFF();
    
    while(1)
    {
        if(LoraDataStruct.LoRaRXFlag == TRUE)        // �ж�Lora���ձ�־λ�Ƿ�仯
        { 
            LoraDataStruct.LoRaRXFlag = FALSE;
            RF1278_RecePacket(LoraDataStruct.LoRaReceArr, 20);      // ��������
                       
            if((LoraDataStruct.LoRaReceArr[0] == LORADATAHEAD) && \
                (LoraDataStruct.LoRaReceArr[LoraDataStruct.LoRaReceArr[1] -1] == LORADATATAIL))   // �ж����ݵ�֡ͷ��֡β
            {               
                LoRaDataManage();
                RF1278_ClearIrq();
            }
        
        }
    }
}



void Check_Crc16(void)
{
    u8 ConfTabNum[] = { 0X68, 0X11, 0XE1, 0XA1, 0XAA, 0XAA, 0XAA, 0XAA, 0XAA, 0XFB, 0X00, 0X00, 0X00, 0X00, 0x00, 0x00,0X16};
    u16 CreValve = GetCRC16(ConfTabNum, 14);
    printf("%d\r\n", CreValve);
}

//int main(void)
//{
//    SysClockInit();     // ʱ�ӳ�ʼ��
//    ValveCtrlInit();    // ���ų�ʼ��
//    KeyGpioInit();      // ������ʼ��
//    LED_Init();         // LED��ʼ��
//    enableInterrupts(); // ����ȫ���ж�
//    while(1)
//    {
//        if(FlagSturct.Key0 == TRUE)
//        {
//           FlagSturct.Key0 = FALSE;
//           LED0_FLIP();
//           ValveOpen(1);            
//        }
//        else if(FlagSturct.Key1 == TRUE)
//        {
//            FlagSturct.Key1 = FALSE;
//            LEDG_FLIP();
//            ValveClose(0,1);   
//        }   
//    }
//}