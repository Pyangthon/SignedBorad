#include "TestItems.h"
Lora_TypeDef LoraDataStruct;

const u8 CmdSerNumArr[4] = {0x11, 0x22, 0x03, 0x44};      // ������������
const u8 TargetAddArr[4] = {0XA0, 0XB0, 0XC0, 0XD0};      // Ŀ���ַ����
const u8 SourceAddArr[4] = {0X0A, 0X0B, 0X0C, 0X0D};      // Դ��ַ����
const u8 DataCheckArr[2] = {0XAA, 0XAB};                  // Ĭ������У������

//*****************************************************************************/
//*������ :
//*˵��   :
//*����   :
//*����ֵ :
//*����   :
//*****************************************************************************/
void System_Init(void)
{
    SysClockInit();     // ʱ�ӳ�ʼ��
    LED_Init();         // LED��ʼ��
    Lora_Gpio_Init();   // LORA��ʼ��
    Usart2_Module_Init(115200); // ����2��ʼ��
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
//*������ :
//*˵��   :
//*����   :
//*����ֵ :
//*����   :
//*****************************************************************************/

void LoRaDataManage(void)
{ 
    u8 ReturnData[LORAARRSIZE] = {0};      // ���������ڴ洢�ϴ���������
    
    switch(LoraDataStruct.LoRaReceArr[14])       // ѡ����Ҫ���е�ģʽ
    {
    case LORATEST:
        ReturnData[0] = ~(LoraDataStruct.LoRaReceArr[14]);
        Delay_ms(500);
        LoraSendData(LORATEST ,ReturnData, LORAARRSIZE);               // Ȼ���ٽ��лظ�
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
        LoraSendData(LORATEST,ReturnData, LORAARRSIZE);      // �ϴ�ָ�������              
        break;
    }

    
}
//*****************************************************************************/
//*������ :
//*˵��   :
//*����   :
//*����ֵ :
//*����   :
//*****************************************************************************/

void LoraSendData(u8 Det, u8 *Cbuf, u8 Buflen)
{

    u8 temp;
    for(temp = 0; temp < 4; temp++) //
    {
        LoraDataStruct.LoRaSendArr[temp+2] = CmdSerNumArr[temp];        // ��������������д�뷢��������   2-5λ
        LoraDataStruct.LoRaSendArr[temp+6] = TargetAddArr[temp];        // ��Ŀ���ַ����д�뷢������     6-9
        LoraDataStruct.LoRaSendArr[temp+10] = SourceAddArr[temp];       // ��Դ��ַ����д�뷢������       10-13
    }
    LoraDataStruct.LoRaSendArr[0] = LORADATAHEAD;       // ֡ͷ
    LoraDataStruct.LoRaSendArr[1] = LORADATALENGTH+Buflen;     // ���ݳ���
    LoraDataStruct.LoRaSendArr[14] = Det;
    for(temp = 0; temp < Buflen; temp++)
    {
        LoraDataStruct.LoRaSendArr[temp+15] = Cbuf[temp];
    }
    LoraDataStruct.LoRaSendArr[LORADATALENGTH+Buflen-3] = DataCheckArr[0];
    LoraDataStruct.LoRaSendArr[LORADATALENGTH+Buflen-2] = DataCheckArr[1];
    LoraDataStruct.LoRaSendArr[LORADATALENGTH+Buflen-1] = LORADATATAIL;       // ֡β 
    RF1278_SendPacket(LoraDataStruct.LoRaSendArr, LORADATALENGTH+Buflen);   // ͨ��LORAģ����з���
    LED_RGB_Fli(1, LED_B_PIN);
    memset(LoraDataStruct.LoRaSendArr, 0, sizeof(LoraDataStruct.LoRaSendArr));
    Rf1278_ModeSet(128);
}

//*****************************************************************************/
//*������ :
//*˵��   :
//*����   :
//*����ֵ :
//*����   :
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



