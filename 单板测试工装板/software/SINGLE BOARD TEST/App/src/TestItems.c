//����ͷ�ļ�
#include "TestItems.h"

// ����ȫ�ֱ���
Lora_TypeDef LoraDataStruct;
Valve_TypeDef ValveStruct;
u8 LoraDataArr[LORAARRSIZE] = {0};      // Lora���ݷ���
u8 DataCheckArr[2] = {0XAA, 0XAB};                  // Ĭ������У������
                      
u8 CmdAndAddArr[12] = {0X11, 0X22, 0X03, 0X44, 0X0A, 0X0B, 0X0C, 0X0D, 0XA0, 0XB0, 0XC0, 0XD0}
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
    // ������ʾ����
//    u8 LoRa_Str1[] = {"LoRa Initialization successful!\r\n"};
//    u8 LoRa_Str2[] = {"LoRa Startup failure!\r\n"};
    u8 LoraArr[LORADEFSIZE] = {0};
    if(FlagStruct.LoRaInitFlag == TRUE)       // �жϳ�ʼ���Ƿ�ɹ�
    {        
        LoraSendData(LORATEST,LoraArr, LORADEFSIZE);
        LEDFlicker(0, 1);
        Rf1278_ModeSet(100);     // ��������
//        UsartSend(USART3, LoRa_Send_DataArr, 5);             
        TIM3_Cmd(ENABLE);   // ������ʱ��3
        MsCount = 0;      // ��λ������
        
        while(MsCount < COUNTNUM)     // �ȴ����룬��������
        {
            if(LoraDataStruct.LoRaRXFlag == TRUE)
            {
                RF1278_RecePacket(LoraDataStruct.LoRaReceArr, 30);      // ��������
                Rece_DataCheck(LORACOM, LoraDataStruct.LoRaReceArr);    // 
                RF1278_ReadRssiSnr(&LoraDataStruct.LoRaRrsi);      // ��ȡ������ֵ
                if(LoraDataStruct.LoRaRrsi > LORADEFRRSI)   // ���յ����ݺ�,�ж�������ֵ�Ƿ���ڱ�׼ֵ
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
                ReturnTestDet(UpDataArr);   // �ϴ�LORA���ԵĽ��
                TIM3_Cmd(DISABLE);  // �رն�ʱ��3
                MsCount = 0;        // ����ʱ���־λ��0
                break;
            }
        } 
        if(MsCount >= COUNTNUM)
        {
            TIM3_Cmd(DISABLE);  // �رն�ʱ��3
            MsCount = 0;        // ��������0
            LoraDataStruct.LoRaRXFlag = FALSE;  // lora���ձ�־λ��λ
            UpDataArr[0] = LORAERRDET;  // �ϴ�����0λ����Ϊlora���Դ���ָ�� 
            ReturnTestDet(UpDataArr);   // �ϴ�LORA���ԵĽ��
            Rf1278_ModeSet(100);        // ��������
        }
    }   
    else
    {
        RF1278_Init(2, 2);  // û�г�ʼ��������¾ͽ��г�ʼ��
        FlagStruct.LoRaInitFlag = TRUE;
        LEDFlicker(0, 1);
    }
}
//*****************************************************************************/
//*������ :void _Rece_DataCheck(u8 Mode)
//*˵��   :��������У�麯��
//*����   :mode    ѡ�����ģʽ
//*����ֵ :DataVar У��ɹ�����(0-5֮��)
//*����   :
//*****************************************************************************/
void Rece_DataCheck(u8 Mode, u8 *Cbuf)
{
    u8 Local_DataArr[] = {0X68, 0X05, 0X31, 0X5F, 0X90};
    u8 DataVar;
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
    }
    else if(Mode == RSCOMDET)
    {
        for(DataVar = 0; DataVar < 5; DataVar++)
        {
            if(Cbuf[DataVar] != Local_DataArr[DataVar])
            {
                FlagStruct.ReceDataFlag = RSERRDET;
                break;
            }
        }
        if(FlagStruct.ReceDataFlag!= RSERRDET)
        {
            FlagStruct.ReceDataFlag = RSCOMDET;
        }
    }
    
}



//*****************************************************************************/
//*������ :void Valve_Test(u8 Det)
//*˵��   :���Ų��Բ���
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Valve_Test(u8 Det)
{
    // ���Ϳ��ط�ָ��,��һor����
    LoraDataArr[0] = USART_3.USART_Date[2];
    LoraSendData(Det, LoraDataArr, LORAARRSIZE);

    // ���IOͨ��
    // �ȴ�10s����ѯIO�Ƿ�����ж�
    MsCount = 0;
    TIM3_Cmd(ENABLE);
    while(MsCount < 50)
    {
        // ��ⷧ��״̬
       if((FlagStruct.Key1Flag == TRUE) || (FlagStruct.Key2Flag == TRUE) ||       // �жϵ�ǰ�Ƿ��з�����Ӧ
           (FlagStruct.Key3Flag == TRUE) || (FlagStruct.Key4Flag == TRUE))
       {
           if((FlagStruct.Key1Count == 1) && (FlagStruct.Key2Count == 1))
           {
                ValveStruct.Valve1State = TRUE;     // ��1״̬��
                UpDataArr[1] = OPVALCONA;
           }
           else if((FlagStruct.Key2Count == 1) && (FlagStruct.Key1Count == 1))
           {
                ValveStruct.Valve1State = FALSE;    // ��1״̬��
                UpDataArr[1] = CLVALCONA;
           }
           else if((FlagStruct.Key3Count == 1) && (FlagStruct.Key4Count == 1))
           {
               ValveStruct.Valve2State = TRUE;      // ��2״̬��
               UpDataArr[1] = OPVALCONB;
           }
           else if((FlagStruct.Key4Count == 1) && (FlagStruct.Key3Count == 1))
           {
               ValveStruct.Valve2State = FALSE;     // ��2״̬��
               UpDataArr[1] = CLVALCONB;
           }
           if(UpDataArr[1] != 0X00)
           {
               UpDataArr[0] = USART_3.USART_Date[2];
               ReturnTestDet(UpDataArr);
               TIM3_Cmd(DISABLE);  // �رն�ʱ��3
               MsCount = 0;      // ����ʱ���־λ��0
               break;
           }
       }

    }
    if(MsCount <= 50)
    {
        TIM3_Cmd(DISABLE);  // �رն�ʱ��2
        MsCount = 0;
        UpDataArr[0] = USART_3.USART_Date[2];
        UpDataArr[1] = CTRVALERR;
        ReturnTestDet(UpDataArr);
    }
        
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
    LoraDataStruct.LoRaSendArr[14] = Det;       // ��Ҫ���͵�ָ��
    for(temp = 0; temp < Buflen; temp++)
    {
        LoraDataStruct.LoRaSendArr[temp+15] = Cbuf[temp];   // ����λ
    }
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 3] = DataCheckArr[0];  // У��λ
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 2] = DataCheckArr[1];
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 1] = LORADATATAIL;     // ֡β   
    
    RF1278_SendPacket(LoraDataStruct.LoRaSendArr, LORADATALENGTH+Buflen);       // ͨ��LORAģ����з���
  
}


//*****************************************************************************/
//*������ :void WriteLoraDef(void)
//*˵��   :д��lora���������Ĭ��ֵ
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void WriteLoraDef(void)
{
    u8 temp;
    for(temp = 0; temp < 12; temp++) // д���������У�ԭ��ַ��Ŀ���ַ
    {
        LoraDataStruct.LoRaSendArr[temp+2] = CmdAndAddArr[temp];
    }
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
        USART_Cmd(USART1,ENABLE);  //ʹ��
        Delay_ms(50);
    }
    if(USART_1.USART_Date[0] == 0X00)
    {
        UsartSend(USART1, "R", 1);
        Delay_ms(20);
    }
    if(USART_1.Falg == 1)
    {
        LEDFlicker(1, 3);
        UpDataArr[0] = METERDET;
        UpDataArr[1] = USART_1.USART_Date[3];
        ReturnTestDet(UpDataArr);
        USART_1.Length = 0;
    }    
}