#include "SysInitApp.h"

u16 MsCount = 0;        // ������־λ
u16 SceCount = 0;       // ������־λ
u16 CountDown = 300;    // ����ʱ������
bool HaltState = FALSE; // ���߱�־λ
//*****************************************************************************/
//*������ :void SPDT_Init(void)
//*˵��   :��ʼ���̵����˿�
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void SPDT_Init(void)
{
    // ��ʼ���̵����˿�
    GPIO_Init(SPDT_PORT, SPDT_EN_PIN, GPIO_Mode_Out_PP_High_Slow);       // PC7
    // ��ʼ��Ϊ�رռ̵���
    SPDT_EN_OFF();
    FlagStruct.SPDTIEnFlag = FALSE;
}

//*****************************************************************************/
//*������ :void SPDT_Ctrl_Port_Init(void)
//*˵��   :��ʼ���̵��������µĶ˿ڣ����ݱ�����������PB_LSB_MODE���ƶ˿ڳ�ʼ��ģʽ��
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void SPDT_Ctrl_Port_Init(void)
{
#if PB_LSB_MODE
    // ��PB0-3��ʼ��Ϊ�������������
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);
    // Ĭ������͵�ƽ
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_1, RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_2, RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_3, RESET);
#else
    // ��PB0-3��ʼ��Ϊ�������ж�����
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);
#endif
    // ��ʼ������1
    Usart1_Module_Init(2400);   // ��ǰ�汾������ɽ��Ŀ�������
    USART_Cmd(USART1,DISABLE);  //��ʹ��USART1
}


//*****************************************************************************/
//*������ :void Peripheral_Init(void)
//*˵��   :�����ʼ��
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/

void System_Init(void)
{
    SysClockInit();     // ϵͳʱ�ӳ�ʼ�����ڲ�����ʱ�ӣ�16MHz   
    GPIO_Init_Config();
    RS485_Init();       // RS485��ʼ��������2��������9600��Ĭ�Ͻ���
    Usart3_Module_Init(2400);     // ����3��ʼ�������ڽ�����λ��ָ������
    LED_Init();         // LED��ʾ���ֳ�ʼ��
    Key_Init();         
    ValveTest_Init();
    SPDT_Init();        //�̵�����ʼ��,Ĭ�ϼ̵����ر�
    Lora_Gpio_Init();   // LoRaģ��˿ڳ�ʼ�� 
    ADS1115_Init();     // ADS1115ADC��ʼ��
    SPDT_Ctrl_Port_Init();
    Timer3_init();
    ADC_Config_Init();  // ADC��ʼ��
//    Timer2_init();    // �ö�ʱ���������ߵ���ʱ����δʹ��
    if(RF1278_Init(2, 2))
    {
        LEDFlicker(0,2);
        FlagStruct.LoRaInitFlag = TRUE;     // LoRa��Ƶ��ʼ����־λ��1
    }  
    ZeroBiaVoltConfig();        // ������ƫ��ѹ����
    if(ZeroBisVoltTset(0) == TRUE)          // �����ƫ��ѹ 
    {
        printf("System Init OK!\n");
    }
    
}
//*****************************************************************************/
//*������ :void ZeroBiaVoltConfig(void)
//*˵��   :��ƫ��ѹ��ز�������
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void ZeroBiaVoltConfig(void)
{
    FlagStruct.FristVoltTest = TRUE;
    ADSZBStruct.ZeroBiaVoltThre0 = 10;
    ADSZBStruct.ZeroBiaVoltThre1 = 30;
}

//*****************************************************************************/
//*������ :void GPIO_Init_Config(void)
//*˵��   :GPIO��ʼ������
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void GPIO_Init_Config(void)
{
    GPIO_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);//SWIM
    GPIO_Init(GPIOA, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  //NRST
    GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow );  //��SART1_TX��    
    GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //��USART1_X��
    GPIO_Init(GPIOA, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow );  //COM0
    GPIO_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow );  //COM1
    GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow );  //COM2
    GPIO_Init(GPIOA, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow );  //SEG0
                                                         
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //SEG10
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //SEG11
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //SEG12
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //SEG13
    GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //SEG14
    GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //SEG15
    GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //SEG16
    GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //SEG17
  
    GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_EN
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //IR_EN
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //SEG22
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //SEG23
    GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //ADC4
    GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //LSE1
    GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //LSE2
    GPIO_Init(GPIOC, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_MOSI
  
    GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Slow);  //SEG7
    GPIO_Init(GPIOD, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  //COM3
    GPIO_Init(GPIOD, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Slow);  //SEG8
    GPIO_Init(GPIOD, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Slow);  //SEG9
    GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //SEG18
    GPIO_Init(GPIOD, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //SEG19
    GPIO_Init(GPIOD, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //SEG20
    GPIO_Init(GPIOD, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //SEG21
  
    GPIO_Init(GPIOE, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //SEG1
    GPIO_Init(GPIOE, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //SEG2
    GPIO_Init(GPIOE, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //SEG3
    GPIO_Init(GPIOE, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //USART2_RX
    GPIO_Init(GPIOE, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //USART2_TX
    GPIO_Init(GPIOE, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //SEG6
    GPIO_Init(GPIOE, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //POWER
    GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //PWRKEY


    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_CS
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_MISO
    GPIO_Init(GPIOF, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //NO
    GPIO_Init(GPIOF, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //NO
    GPIO_Init(GPIOF, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //kEY 
    GPIO_Init(GPIOF, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //RTC_INT
    GPIO_Init(GPIOF, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //RST_C
    GPIO_Init(GPIOF, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //CLK_C
  
    GPIO_Init(GPIOG, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //USART3_RX
    GPIO_Init(GPIOG, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //USART3_TX
    GPIO_Init(GPIOG, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow); //I2C_SCL
    GPIO_Init(GPIOG, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow); //I2C_SDA
    GPIO_Init(GPIOG, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //MOT_A
    GPIO_Init(GPIOG, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //BUZZ
    GPIO_Init(GPIOG, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //MOT_B
    GPIO_Init(GPIOG, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //ADC_EN
}
//*****************************************************************************/
//*������ :void ResetDefault(void)
//*˵��   :��ʼ�����ڣ��̵�����LED
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void ResetDefault(void)
{
    ZeroBisVoltTset(USART_3.USART_Date[2]);
    FlagStruct.FunKeyFlag = 0;
    LED_Off(4);
    SPDT_EN_OFF();
    FlagStruct.SPDTIEnFlag = FALSE;
    FlagStruct.FristVoltTest = TRUE;
    memset(USART_1.USART_Date, 0, sizeof(USART_1.USART_Date));
    memset(USART_2.USART_Date, 0, sizeof(USART_2.USART_Date));
    memset(USART_3.USART_Date, 0, sizeof(USART_3.USART_Date));
    USART_1.Falg = 0;
    USART_2.Falg = 0;
    USART_3.Falg = 0;
    USART_1.Length = 0;
    USART_2.Length = 0;
    USART_3.Length = 0;
    LEDFlicker(3, 1);  
}
 
//*****************************************************************************/
//*������ :void ZeroBisVoltTest(u8 State)
//*˵��   :��ȡADC����ƫ��ѹ
//*����   :State  �Ƿ���Ҫ��ӡ��ƫ��ѹֵ
//*        1 ��ӡ   0 ����ӡ
//*����ֵ :��
//*����   :
//*****************************************************************************/
bool ZeroBisVoltTset(u8 State)
{   
    u16 temp = 0;               // ���ADCͨ������ֵ��ʱ����
    float Volt_temp = 0.0;      // ���ADC������ѹֵ
    if((State == 0) && (FlagStruct.ZeroBiaVoltFlag == TRUE))        // TRUE��ʾ��ƫ��ѹ�ɼ�����ɣ�state == 0 ��ʾ���������ƫ��ѹ�ɼ�
    {             // �ж��Ƿ���Ҫ������ƫ��ѹ���òɼ�
        return FALSE;
    }
    else
    {
        temp = GetAdcAvg(0);        // ��ȡͨ��0�Ĳ���ֵ
        Volt_temp = temp * 4.096 / 0X7fff;  // ������ƫ��ѹ
        if(Volt_temp * 1000 > ADSZBStruct.ZeroBiaVoltThre0)        // �жϻ�ȡ��ƫ��ѹʱ�Ƿ���ڱ����
        {
            printf("��ȥ�����������¼����ƫ��ѹ!!!\r\n"); // ���������ʾ��Ϣ
            FlagStruct.ZeroBiaVoltFlag = FALSE;        // ����ƫ��ѹ�ɼ��ɹ���־λ��0����ʾ�ɼ�ʧ�ܣ��������²ɼ�
            return FALSE;     // ���˳�����
        }
        else
        {
            ADSZBStruct.ZeroBiaVolt0 = Volt_temp;       // û�б�����򽫲�����ѹ������ƫ��ѹֵ�ṹ���еȴ�ȡ��
        }
        temp = GetAdcAvg(1);        //  ��ȡͨ��1����ƫ��ѹ
        Volt_temp = temp * 4.096 / 0X7fff;   // ����ͨ��1����ƫ��ѹֵ
        if(Volt_temp * 1000 > ADSZBStruct.ZeroBiaVoltThre1)
        {
            printf("��ȥ�����������¼����ƫ��ѹ!!!\r\n"); // ���������ʾ��Ϣ
            FlagStruct.ZeroBiaVoltFlag = FALSE;        // ����ƫ��ѹ�ɼ��ɹ���־λ��0����ʾ�ɼ�ʧ�ܣ��������²ɼ�
            return FALSE;     // ���˳�����
        }
        else
        {
            ADSZBStruct.ZeroBiaVolt1 = Volt_temp;
            FlagStruct.ZeroBiaVoltFlag = TRUE;
        }
        if(State == 1)      // �ж��Ƿ���Ҫ��ӡ��ƫ��ѹֵ
        {
            printf("ͨ�� 0 ��ƫ��ѹΪ %f mV\r\n", ADSZBStruct.ZeroBiaVolt0 * 1000);
            printf("ͨ�� 1 ��ƫ��ѹΪ %f mV\r\n", ADSZBStruct.ZeroBiaVolt1 * 1000);
        }
    }
    return TRUE;
}

//*****************************************************************************/
//*������ :void PrintArr(u8 *Arr,int length)
//*˵��   :16���Ƹ�ʽ��ӡ����
//*����   :*Arr ��Ҫ�����������
//*        Length ����ĳ���
//*����ֵ :
//*����   :
//*****************************************************************************/
void PrintArr(u8 *Arr,int Length)
{
    for(int i=0;i<Length;i++)
    {
        printf("%02X ",Arr[i]);
    }
    printf("\r\n");
}

//*****************************************************************************/
//*������ :void Dormancy(void)
//*˵��   :�������ߣ�ͨ������ʱ������־λCountDown�Ƿ�0
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Dormancy(void)
{
    HaltState = FALSE;  // �������߱�־λ
    DisableGPIO();      // ����GPIO��©��������
    DisableCLK();       // �ر�����ʱ��
    halt();             // ����,�ⲿ�жϴ������ִӴ˴���ʼ����
    System_Init();      // ���³�ʼ����������
    enableInterrupts(); // �����ж�
}

//*****************************************************************************/
//*������ :void DisableGPIO(void)
//*˵��   :����GPIOΪ����״̬
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void DisableGPIO(void)
{
    // ��ʱδ����
}
//*****************************************************************************/
//*������ :void DisableClk(void)
//*˵��   :�ر�����ʱ��
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void DisableCLK(void)       
{
    // ��ʱδ����
}