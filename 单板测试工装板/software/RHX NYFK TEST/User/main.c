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
        if(LoraDataStruct.LoRaRXFlag == TRUE)        // 判断Lora接收标志位是否变化
        { 
            LoraDataStruct.LoRaRXFlag = FALSE;
            RF1278_RecePacket(LoraDataStruct.LoRaReceArr, 20);      // 接收数据
                       
            if((LoraDataStruct.LoRaReceArr[0] == LORADATAHEAD) && \
                (LoraDataStruct.LoRaReceArr[LoraDataStruct.LoRaReceArr[1] -1] == LORADATATAIL))   // 判断数据的帧头和帧尾
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
//    SysClockInit();     // 时钟初始化
//    ValveCtrlInit();    // 阀门初始化
//    KeyGpioInit();      // 按键初始化
//    LED_Init();         // LED初始化
//    enableInterrupts(); // 开启全局中断
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