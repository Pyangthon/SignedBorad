//����ͷ�ļ�
#include "LoraTest.h"

// ����ȫ�ֱ���
Lora_TypeDef LoraDataStruct;
Valve_TypeDef ValveStruct;
u8 LoraDataArr[LORADEFSIZE] = {0};      // Lora���ݷ���
u8 DataCheckArr[2] = {0XAA, 0XAB};                  // Ĭ������У������
                      
u8 CmdAndAddArr[12] = {0X11, 0X22, 0X03, 0X44, 0X0A, 0X0B, 0X0C, 0X0D, 0XA0, 0XB0, 0XC0, 0XD0};
                       // ������������         // Ŀ���ַ����           // ԭ��ַ����

//*****************************************************************************/
//*������ :void LoRa_Test(void)
//*˵��   :LoRaģ����Ժ���
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void LoRa_Test(void)
{ 
    u8 LoraDataArr[LORADEFSIZE] = {0};
    if(FlagStruct.LoRaInitFlag == TRUE)       // �жϳ�ʼ���Ƿ�ɹ�
    {        
        LoraSendData(LORATEST,LoraDataArr, LORADEFSIZE);
        
        Rf1278_ModeSet(128);    // ��������
        RF1278_ClearIrq();	            
        MsCount = 0;            // ��λ������
        TIM3_Cmd(ENABLE);       // ������ʱ��3
        while(MsCount < COUNTNUM)     // �ȴ����룬��������
        {
            if(LoraDataStruct.LoRaRXFlag == TRUE)
            {
                RF1278_RecePacket(LoraDataStruct.LoRaReceArr, 30);      // ��������
                Rece_DataCheck(LORACOM, LoraDataStruct.LoRaReceArr);    // У������
                RF1278_ReadRssiSnr(&LoraDataStruct.LoRaRrsi);           // ��ȡ������ֵ
                printf("Lora������ֵΪ: %d\r\n", LoraDataStruct.LoRaRrsi);
                if(LoraDataStruct.LoRaRrsi > LORADEFRRSI)               // ���յ����ݺ�,�ж�������ֵ�Ƿ���ڱ�׼ֵ
                {
                    FlagStruct.LoRaTestFlag = LORACOM;                       
                    LED0_L();    // ��ʾ������                       
                }
                else
                {
                    FlagStruct.LoRaTestFlag = LORAERRDET;   
                }
                UpDataArr[0] = FlagStruct.LoRaTestFlag;     // ����lora���Խ��
                LoraDataStruct.LoRaRXFlag = FALSE;          // ���ձ�־λ��λ
                ReturnTestDet(UpDataArr, 2);                // �ϴ�LORA���ԵĽ��
                break;
            }
        } 
        if(MsCount >= COUNTNUM)
        {
            LoraDataStruct.LoRaRXFlag = FALSE;  // lora���ձ�־λ��λ
            UpDataArr[0] = LORAERRDET;          // �ϴ�����0λ����Ϊlora���Դ���ָ�� 
            ReturnTestDet(UpDataArr, 2);        // �ϴ�LORA���ԵĽ��            
        }
    }   
    else
    {
        RF1278_Init(2, 2);  // û�г�ʼ��������¾ͽ��г�ʼ��
        FlagStruct.LoRaInitFlag = TRUE;
        LEDFlicker(0, 1);
    }
    memset(UpDataArr, 0, sizeof(UpDataArr));
    TIM3_Cmd(DISABLE);  // �رն�ʱ��3
}
//*****************************************************************************/
//*������ :void _Rece_DataCheck(u8 Mode)
//*˵��   :��������У�麯��
//*����   :mode    ѡ�����ģʽ
//*        *Cbuf   ��Ҫ��У�鵽������
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Rece_DataCheck(u8 Mode, u8 *Cbuf)
{
    u8 temp;    // ��ʱ�������ڴ洢����ָ��λ��ȡ��ֵ
    if(Mode == LORACOM)
    {
        if((LoraDataStruct.LoRaReceArr[0] == LORADATAHEAD) && \
            (LoraDataStruct.LoRaReceArr[LoraDataStruct.LoRaReceArr[1]-1] == LORADATATAIL)) 
        {
            temp = ~LORATEST; 
            if(LoraDataStruct.LoRaReceArr[15] == temp)
            {
                FlagStruct.ReceDataFlag = LORACOM;
            }
            else
            {
                FlagStruct.ReceDataFlag = LORAERRDET;
            }
        }
        memset(LoraDataStruct.LoRaReceArr, 0, sizeof(LoraDataStruct.LoRaReceArr));
    }
    else if(Mode == RSCOMDET)
    {
        if(USART_2.USART_Date[2] == RSCOMDET & 0XF0)
        {
            FlagStruct.RS485TestFlag = RSCOMDET;
        }
        else
        {
            FlagStruct.RS485TestFlag = RSERRDET;
        }
    }
    
}

//*****************************************************************************/
//*������ :void Valve_Test(u8 Det)
//*˵��   :���Ų��Բ���
//*����   :Det        ����ָ��������߹ط�
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Valve_Test(u8 Det)
{
    // ���Ϳ��ط�ָ��
    FlagStruct.Key3Flag = FALSE;
    FlagStruct.Key4Flag = FALSE;
    LoraDataArr[0] = 0X01;
    LoraDataArr[1] = 0X00;
    LoraSendData(Det, LoraDataArr, 2);
    Rf1278_ModeSet(128);     // ��������
    // ������ʱ����ʼ���
    MsCount = 0;
    TIM3_Cmd(ENABLE);
    while(MsCount < COUNTNUM)     
    {
        if(FlagStruct.Key3Flag == TRUE || FlagStruct.Key4Flag == TRUE)
        {
            if(FlagStruct.ValveCount == 0X01)
            {
                printf("�����ɹ�\r\n");
                LEDFlicker(1,2);
                break;
            }
            else if(FlagStruct.ValveCount == 0X02)
            {
                printf("�ط��ɹ�\r\n");
                LEDFlicker(2,2);
                break;
            }
        }
    }
    if(MsCount >= 60)   // �ж������ʱ��ᷴ��ʧ����Ϣ
    {
        
        printf("δ��⵽����״̬\r\n");
            
    }
    TIM3_Cmd(DISABLE);          // �رն�ʱ��
    FlagStruct.ValveCount = 0;
//    memset(UpDataArr, 0, sizeof(UpDataArr));    
}

//*****************************************************************************/
//*������ :void LoraSendData(u8 Det, u8 *Cbuf, u8 Buflen)
//*˵��   :Lora���ͷ�װ���ݺ��� 
//*����   :Det        ��Ҫ���͵�ָ��
//*        *Cbuf      ��Ҫ���͵�����
//*        Buflen     ���ݵĳ���
//*����ֵ :
//*����   :
//*****************************************************************************/
void LoraSendData(u8 Det, u8 *Cbuf, u8 Buflen)
{
    u8 temp;
    LoraDataStruct.LoRaSendArr[0] = LORADATAHEAD;           // ֡ͷ
    LoraDataStruct.LoRaSendArr[1] = LORADATALENGTH+Buflen;  // ���ݳ���
    for(temp = 0; temp < 12; temp++) // д���������У�ԭ��ַ��Ŀ���ַ
    {
        LoraDataStruct.LoRaSendArr[temp+2] = CmdAndAddArr[temp];
    }
    LoraDataStruct.LoRaSendArr[14] = Det;       // ��Ҫ���͵�ָ��
    for(temp = 0; temp < Buflen; temp++)
    {
        LoraDataStruct.LoRaSendArr[temp+15] = Cbuf[temp];   // ����λ
    }
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 3] = DataCheckArr[0];  // У��λ
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 2] = DataCheckArr[1];
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 1] = LORADATATAIL;     // ֡β   
    RF1278_SendPacket(LoraDataStruct.LoRaSendArr, LORADATALENGTH+Buflen);       // ͨ��LORAģ����з���
    LEDFlicker(0, 1);
    printf("LoRa��������Ϊ: ");
    PrintArr(LoraDataStruct.LoRaSendArr, LORADATALENGTH+Buflen);
}


//*****************************************************************************/
//*������ :void Meter_Test(void)
//*˵��   :ֱ�������������
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Meter_Test(void)
{
    if(FlagStruct.SPDTIEnFlag == FALSE)
    {
        SPDT_EN_ON();
        FlagStruct.SPDTIEnFlag = TRUE;
        Delay_ms(50);
        USART_Cmd(USART1,ENABLE);       //ʹ�ܴ���1
        Delay_ms(50);
    }
    if((USART_1.USART_Date[0] == 0X59) || (USART_1.USART_Date[0] == 0x00))   // ����������1�����ݻ������Ƿ�������
    {   
        UsartSend(USART1, "R", 1);      // ���û�оͷ���R��ȡ��������ֵ
        Delay_ms(20);
    }
    Delay_ms(100);
    if(USART_1.Falg == TRUE)   // �����ݽ�����ɺ�
    {
        USART_1.Falg = FALSE;
        LEDFlicker(1, 3);   // LED��ʾ
        UpDataArr[0] = METERDET;    // �ϴ�����0λΪ����ָ��
        UpDataArr[1] = USART_1.USART_Date[3];   //1λΪ����ֵ����ֵ��Ϊ0-255 
        ReturnTestDet(UpDataArr, 2);   // �ϴ�����(����3)
        USART_1.Length = 0; // ����1���ȸ�λ
        memset(USART_1.USART_Date, 0, sizeof(USART_1.USART_Date));
    }
    else
    {
        UpDataArr[0] = METERERRDET; // û�յ��������ϴ�0���ò���ʧ��ָ��
        UpDataArr[1] = 0X00;    
        ReturnTestDet(UpDataArr, 2);
    }
}

//*****************************************************************************/
//*������ :void RS485_Test(void)
//*˵��   :RS485����
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void RS485_Test(void)
{
    LoraDataArr[0] = 0X00;
    LoraDataArr[1] = 0X00;
    LoraSendData(RSCOMDET, LoraDataArr, 2);
    Rf1278_ModeSet(128);     // ��������
    MsCount = 0;
    TIM3_Cmd(ENABLE);
    while(MsCount < COUNTNUM)
    {
        if(USART_2.Falg == 1)
        {
            USART_2.Falg = 0;
            Rece_DataCheck(RSCOMDET, USART_2.USART_Date);
            UpDataArr[0] = FlagStruct.RS485TestFlag;
            UpDataArr[1] = 0X01;
            ReturnTestDet(UpDataArr, 2);
            break;
        }
    }
    if(MsCount >= COUNTNUM)
    {
        UpDataArr[0] = FlagStruct.RS485TestFlag;
        UpDataArr[1] = 0X01;
        ReturnTestDet(UpDataArr, 2);
    }
    TIM3_Cmd(DISABLE);
    MsCount = 0;
    memset(USART_2.USART_Date, 0, sizeof(USART_2.USART_Date));
    USART_2.Length = 0;
}
