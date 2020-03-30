#include "SerialData.h"

u8 UpDataArr[2] = {0};  // ָ�����������
Global_Flag_TypeDef FlagStruct;     // ȫ�ֱ�־λ�ṹ��
ADSZeroBiaData_TypeDef ADSZBStruct; // ADS��ʼ���ݽṹ��

//*****************************************************************************/
//*������ :void Wait_Implement(void)
//*˵��   :�ȴ���λ���·������ݣ��ж�ָ��λ�����ݣ�����ָ���ĺ���ִ��
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Wait_Implement(void)
{       
    switch(USART_3.USART_Date[1])   // ѡ����Ҫִ�еĺ���
    {   
    case LORACOM:
        LoRa_Test();                // LoRa���Ժ���
        break;                
    case CURRENTDET:                
        Current_Test();             // �������Ժ���
        break;
    case OPENVALVE:
        Valve_Test(OPENVALVE);     // �������Ժ���
        break;
    case CLOSEVALVE:
        Valve_Test(CLOSEVALVE);     // �ط����Ժ���
        break;
    case RSCOMDET:
        RS485_Test();               // RS485ͨ�Ų��Ժ���
        break;                                
    case RESETDET:      
        ResetDefault();             // ��λָ��
        break;               
    case METERDET:
        Meter_Test();               // �������
        break;
    case VOLTDET:
        Volt_Test();                // ��ѹ���
        break;
    case KEYDET:
        Key_Test();                 // ��������
    case INFRAREDDET:
        InfraredTest();
        break;
    case MODCONDET:
        ModifyConfig();             // ϵͳ���ú������޸�ϵͳ����
        break;
    default:      
        UpDataArr[0] = ERRORCOM;    // ����ָ��
        ReturnTestDet(UpDataArr, 2); // ���Ѷ���Ĳ���ָ��
        break;                   
    } 
    CountDown = DEFCOUNTDOWN;
    USART_3.Falg = 0;
    memset(USART_3.USART_Date, 0, sizeof(USART_3.USART_Date));
    USART_3.Length = 0;
}

//*****************************************************************************/
//*������ :void ReturnTestDet(u8 *det, u8 Len)
//*˵��   :�ϴ����Խ��
//*����   :Det    ���Խ��ָ��
//*        Len    �ϴ�ָ���
//*����ֵ :��
//*����   :
//*****************************************************************************/
void ReturnTestDet(u8 *Det, u8 Len)
{
    u8 temp;
    u8 UploadDetArr[10] = {0};                  // �ϴ�����
    UploadDetArr[0] = UPDATACOM;                // �ϴ����ݿ�ʼλ
    for(temp = 0; temp < Len; temp++)           // д������λ
    {
        UploadDetArr[temp+1] = Det[temp];
    }
    UploadDetArr[Len + 1] = UPCHECKDET;         // У��λ
    UploadDetArr[Len + 2] = UPCONFIR;           // ���ݽ���λ
    printf("���μ����Ϊ: ");
    PrintArr(UploadDetArr, Len+3);
    USART_3.Length = 0; 
    memset(USART_3.USART_Date,0,sizeof(USART_3.USART_Date));  // �������3���ݻ�����             
}

//*****************************************************************************/
//*������ :void Current_Test(void)
//*˵��   :�������
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Current_Test(void)
{
    int temp = 0;    
    ADSDATA_TypeDef ADSDataStruct;      // ADS���ݴ洢�ṹ��
    if(FlagStruct.SPDTIEnFlag == TRUE)
    {
        SPDT_EN_OFF();                      // �ڼ�����ǰ�ȹرռ̵�������֤�޵�������
        FlagStruct.SPDTIEnFlag = FALSE;
    }
    if((ADSZBStruct.ZeroBiaVolt0 * 1000 > ADSZBStruct.ZeroBiaVoltThre0)     // �ж�ͨ��0��1����ƫ��ѹ�Ƿ񳬹���ֵ
        || (ADSZBStruct.ZeroBiaVolt1 * 1000 > ADSZBStruct.ZeroBiaVoltThre1) 
            || (FlagStruct.ZeroBiaVoltFlag == FALSE))           // �ж���ƫ��ѹ�Ƿ�ɼ��ɹ�
    {
        printf("��ƫ��ѹ��������ȥ�����������»�ȡ��ƫ��ѹ!!!!\r\n");
        return;
    }
    temp = GetAdcAvg(0);                // ��ȡͨ��0����ֵ
    ADSDataStruct.Chan0Volt = temp * 4.096 / 0X7fff;    // ����ͨ��0�ĵ�ѹֵ
    ADSDataStruct.Chan0Curr = (ADSDataStruct.Chan0Volt - ADSZBStruct.ZeroBiaVolt0) / 50;    // ��ȡͨ��0�ĵ���ֵ
    if(ADSDataStruct.Chan0Curr*1000 >= 1)     // ���ͨ��0�ĵ�������1mA���ӡ����ֵ     mA������
    {
        printf("ͨ�� a ���� %f mA\r\n", ADSDataStruct.Chan0Curr * 1000);  // ��ӡ����ֵ
    }
    else if(ADSDataStruct.Chan0Curr * 1000 < 1)   // ���ͨ��0�ĵ���ֵС�ڻ����1mA�����ͨ��1��uA������
    {
        temp = GetAdcAvg(1);            // ��ȡͨ��1�Ĳ���ֵ
        ADSDataStruct.Chan1Volt = temp * 4.096 / 0X7fff;        // ����ͨ��1�ĵ�ѹֵ
        ADSDataStruct.Chan1Curr = (ADSDataStruct.Chan1Volt - ADSZBStruct.ZeroBiaVolt1) / 200;   // ����ͨ��1�ĵ���ֵ
        if(ADSDataStruct.Chan1Curr * 1000 >= 1)
        {
            printf("ͨ�� a ���� %f mA\r\n", ADSDataStruct.Chan1Curr * 1000);  // ��ӡ����ֵ��������Ϊ���Թ����з�����ʱ�ᷢ�ֵ������Ǹպû��ѻ�ͻ�䣬
                                                                              // Ӧ������ֵ������λ�����д���ͨ��b�ɼ�����ֵ��ͨ��a���������Ϸ���
        }
        else
        {
            printf("ͨ�� b ���� %f uA\r\n", ADSDataStruct.Chan1Curr*1000000);  // ��ӡͨ��1����ֵ
        }
    }
}
//*****************************************************************************/
//*������ :void Volt_Test(void)
//*˵��   :��ѹ���
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Volt_Test(void)
{
    u16 VoltValve_Int = 0;      // �����ȡ�ĵ�ѹֵ
    if(FlagStruct.FristVoltTest == TRUE && FlagStruct.SPDTIEnFlag == FALSE)    // �ж��Ƿ��ǵ�һ�λ�ȡ��ѹ
    {
        FlagStruct.FristVoltTest = FALSE;   // �ı��ȡ��ѹ��־λ  
        SPDT_EN_ON();                       // �򿪼̵���
        FlagStruct.SPDTIEnFlag = TRUE;      // ���̵�����־λ��Ϊ��
        VoltValve_Int = VadcGet_2();        // ��ȡ��ѹ����ֵ
        Delay_ms(100);                      // ��ʱ100ms
        Volt_Test();                        // ��һ�βɼ�ʵ�����ǲ�׼ȷ�ģ�����ʹ�õݹ��ٴβɼ���ѹ���õ�һ�βɼ���ֵ�����ǣ���֤�ɼ���׼ȷ��
    }
    else
    {
        VoltValve_Int = VadcGet_2();        // ��ȡ��ѹ����ֵ
        printf("���β��Ե�ѹֵΪ %.2f V\r\n", VoltValve_Int / 100.0);
    }
}

//*****************************************************************************/
//*������ :void Key_Test(void)
//*˵��   :�������
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Key_Test(void)
{
    // ������⺯��
    // �ر�LED2
    LED2_H();
    // �����ȴ�
    MsCount = 0;
    TIM3_Cmd(ENABLE);
    while(MsCount < COUNTNUM)
    {
        if(FlagStruct.Key1Flag == TRUE)
        {
            FlagStruct.Key1Flag = FALSE;
            LED2_L();
            printf("�����ѱ�����\r\n");
            break;
        }
    }
    if(MsCount >= COUNTNUM)
    {
        printf("5S�ڰ���δ������\r\n");
    }
}


//*****************************************************************************/
//*������ :void ModefyConfig(void)
//*˵��   :ϵͳ�����޸ĺ���
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void ModifyConfig(void)
{
    // ���ڲ�����16���� 0:1200  1:2400  2:4800  3:9600  4:14400 5:19200  6:38400 7:56000  8:115200  9:128000 10:230400 11:460800
    u32 SerailBaud[] = {0X04B0, 0X0960, 0X12C0, 0X2580,0X3840, 0X4B00 , 0X9600, 0XDAC0,  0X01C200, 0x01F400, 0X038400, 0X070800};
    switch(USART_3.USART_Date[2])
    {
    case LORAINITDEF:       // �޸�Lora��ʼ������
        LoraDataStruct.LoRaChan = USART_3.USART_Date[3];        // lora�ŵ�
        LoraDataStruct.LoRaSF = USART_3.USART_Date[4];          // lora��Ƶ����
        if(RF1278_Init(LoraDataStruct.LoRaChan, LoraDataStruct.LoRaSF)) // Lora��Ƶ��ʼ�������ж��޸��Ƿ�ɹ�
        {
            LEDFlicker(0,2);        // ��ʼ���ɹ���ʾ
            FlagStruct.LoRaInitFlag = TRUE;     // �޸�Lora��ʼ��״̬
            printf("�޸ĳɹ�!\r\n");  // ���������ʾ��Ϣ
            printf("Loraͨ��ͨ��Ϊ %d, ��Ƶ����Ϊ %d\r\n", LoraDataStruct.LoRaChan, LoraDataStruct.LoRaSF);
        }
        else
        {
            printf("Lora��ʼ���޸�ʧ��!\r\n");
            FlagStruct.LoRaInitFlag = FALSE;
        }
        break;
    case USART2BAUD:        // �޸Ĵ���2������
        Usart2_Module_Disable();    // ����ʧ��
        Usart2_Module_Init(SerailBaud[USART_3.USART_Date[3]]);      // �趨���ڲ�����
        printf("����2�������޸�Ϊ %ld\r\n", SerailBaud[USART_3.USART_Date[3]]);   // ���ڴ�ӡ�������޸Ľ��
        break;
    case USART1BAUD:        // �޸Ĵ���1������
        Usart1_Module_Disable();
        Usart1_Module_Init(SerailBaud[USART_3.USART_Date[3]]);
        printf("����1�������޸�Ϊ %ld\r\n", SerailBaud[USART_3.USART_Date[3]]);
        break;
      
    default:
      break;
        
    }
}

//*****************************************************************************/
//*������ :void InfraredTest(void)
//*˵��   :�����߼������ݽ���
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void InfraredTest(void)
{
    // ��Ժ�����ָ�������س���
    u8 DetArr = USART_1.USART_Date[1];
    if(DetArr == 0X68)
    {
        // Ӳ���ͺ����߲���ͨ��
        LEDFlicker(1, 2);
        
    }
    else if(DetArr == 0X78)
    {
        // Ӳ������δͨ���������߲���ͨ��
        LEDFlicker(2, 1);
    }
    else
    {
        // Ӳ���ͺ����߶�δ���ͨ��
        DetArr = 0X00;
    }
    printf("Ӳ�������Ϊ %2X\r\n", DetArr);
}
