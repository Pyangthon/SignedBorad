#include "TestItems.h"
Lora_TypeDef LoraDataStruct;

const u8 CmdSerNumArr[4] = {0x11, 0x22, 0x03, 0x44};      // 命令序列数组
const u8 TargetAddArr[4] = {0XA0, 0XB0, 0XC0, 0XD0};      // 目标地址数组
const u8 SourceAddArr[4] = {0X0A, 0X0B, 0X0C, 0X0D};      // 源地址数组
const u8 DataCheckArr[2] = {0XAA, 0XAB};                  // 默认数据校验数组

//*****************************************************************************/
//*函数名 :
//*说明   :
//*参数   :
//*返回值 :
//*作者   :
//*****************************************************************************/
void System_Init(void)
{
    SysClockInit();     // 时钟初始化
    LED_Init();         // LED初始化
    Lora_Gpio_Init();   // LORA初始化
    Usart2_Module_Init(115200); // 串口2初始化
    RS485_Init(9600);
    if(RF1278_Init(2,2))
    {
        LED0_ON();
        Delay_ms(500);
        LED0_OFF();   
    }
    Rf1278_ModeSet(128);
}

//*****************************************************************************/
//*函数名 :
//*说明   :
//*参数   :
//*返回值 :
//*作者   :
//*****************************************************************************/

void LoRaDataManage(void)
{ 
    u8 ReturnData[LORAARRSIZE] = {0};      // 该数组用于存储上传数据内容
    
    switch(LoraDataStruct.LoRaReceArr[14])       // 选择需要进行的模式
    {
    case LORATEST:
        ReturnData[0] = ~(LoraDataStruct.LoRaReceArr[14]);
        Delay_ms(500);
        LoraSendData(LORATEST ,ReturnData, LORAARRSIZE);               // 然后再进行回复
//        RS485_Send("AAA", 3);
        LED_RGB_Fli(3, LED_R_PIN);
        break;
    case OPENVALVE:
        if(LoraDataStruct.LoRaReceArr[15] == VALVEA)
            ValveOpen(1);
        else if(LoraDataStruct.LoRaReceArr[15] == VALVEB)
            ValveOpen(2);
        break;
    case CLOSEVALVE:
        if(LoraDataStruct.LoRaReceArr[15] == VALVEA)
            ValveClose(1, 1);
        else if(LoraDataStruct.LoRaReceArr[15] == VALVEB)
            ValveClose(1, 2);
        break;
    case RSCOMDET:
        RS485Test();
        break;
    default:
        ReturnData[0] = LORADATAERR;
        LoraSendData(LORATEST,ReturnData, LORAARRSIZE);      // 上传指令错误码              
        break;
    }

    
}
//*****************************************************************************/
//*函数名 :
//*说明   :
//*参数   :
//*返回值 :
//*作者   :
//*****************************************************************************/

void LoraSendData(u8 Det, u8 *Cbuf, u8 Buflen)
{

    u8 temp;
    for(temp = 0; temp < 4; temp++) //
    {
        LoraDataStruct.LoRaSendArr[temp+2] = CmdSerNumArr[temp];        // 将命令序列数组写入发送数组中   2-5位
        LoraDataStruct.LoRaSendArr[temp+6] = TargetAddArr[temp];        // 将目标地址数组写入发送数组     6-9
        LoraDataStruct.LoRaSendArr[temp+10] = SourceAddArr[temp];       // 将源地址数组写入发送数组       10-13
    }
    LoraDataStruct.LoRaSendArr[0] = LORADATAHEAD;       // 帧头
    LoraDataStruct.LoRaSendArr[1] = LORADATALENGTH+Buflen;     // 数据长度
    LoraDataStruct.LoRaSendArr[14] = Det;
    for(temp = 0; temp < Buflen; temp++)
    {
        LoraDataStruct.LoRaSendArr[temp+15] = Cbuf[temp];
    }
    LoraDataStruct.LoRaSendArr[LORADATALENGTH+Buflen-3] = DataCheckArr[0];
    LoraDataStruct.LoRaSendArr[LORADATALENGTH+Buflen-2] = DataCheckArr[1];
    LoraDataStruct.LoRaSendArr[LORADATALENGTH+Buflen-1] = LORADATATAIL;       // 帧尾 
    RF1278_SendPacket(LoraDataStruct.LoRaSendArr, LORADATALENGTH+Buflen);   // 通过LORA模块进行发送
    LED_RGB_Fli(1, LED_B_PIN);
    memset(LoraDataStruct.LoRaSendArr, 0, sizeof(LoraDataStruct.LoRaSendArr));
    Rf1278_ModeSet(128);
}

//*****************************************************************************/
//*函数名 :
//*说明   :
//*参数   :
//*返回值 :
//*作者   :
//*****************************************************************************/
void RS485Test(void)
{
    u8 RS485SendArr[5] = {0};
    RS485SendArr[0] = 0XAF;
    RS485SendArr[1] = RSCOMDET;
    RS485SendArr[2] = RSCOMDET & 0XF0;
    RS485SendArr[3] = 0X00;
    RS485SendArr[4] = 0X68;
    RS485_Send(RS485SendArr, 5);
}



