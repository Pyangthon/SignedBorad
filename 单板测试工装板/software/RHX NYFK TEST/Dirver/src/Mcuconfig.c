#include "Mcuconfig.h"

RTC_T Rtc;  //RTC��ʼ��
/*******************************************************************************
* ��    �ƣ�void CLK_Configuration(void)
* ��    �ܣ����õ�Ƭ��ϵͳʱ��
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�������
*******************************************************************************/
void CLK_Configuration(void)
{    
    CLK_DeInit();//ʱ�ӳ�ʼ��
    CLK_HSICmd(ENABLE);//�ڲ�����ʱ��ʹ��
    CLK_LSEConfig(CLK_LSE_ON);//32.768K����ʹ��
    while(SET != CLK_GetFlagStatus(CLK_FLAG_LSERDY));
    CLK_ClearFlag();
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//ϵͳʱ��ѡ���ڲ�����ʱ��
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
    while(SET != CLK_GetFlagStatus(CLK_FLAG_HSIRDY));
    CLK_ClearFlag();
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1); //RTCʱ��Դѡ��LSE������Ƶ
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTCʱ��ʹ��
    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);//LCDʱ��ʹ��
    Delay_ms(10);//��ʱ1msʹ�ȶ�����Ȼ���ܳ���LCDʱ��ʹ����Ч
}

/*******************************************************************************
* ��    �ƣ�void GPIO_Configuration(void)
* ��    �ܣ�GPIO����
* ��ڲ�����
* ���ڲ�����
* ˵    ����LCD��ӦIO�Ų������� û�õ���IO����Ϊ������� �͵�ƽ
* ���÷�������
*******************************************************************************/
void GPIO_Config(void)
{
    GPIO_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOA, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  //IC_RST
    GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_In_FL_IT );      ;  //key
    
    GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Slow);  //R8025T INT
    GPIO_Init(GPIOA, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow );  //COM0
    GPIO_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow );  //COM1
    GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow );  //COM2
    GPIO_Init(GPIOA, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow );  //SEG0
                                                         
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow );  //SEG10
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow );  //SEG11
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow );  //SEG12
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow );  //SEG13
    GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow );  //SEG14
    GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow );  //SEG15
    GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow );  //SEG16
    GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow );  //SEG17
  
    GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Slow);  //ZD_Power
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  //IR_EN
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //RX1  M TXD
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //TX1  M RXD
    GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //PC4/PMU_RST(NBģ���Դ����)
    GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //LSE1
    GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //LSE2
    GPIO_Init(GPIOC, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //ADC3  1M_510K
  
    GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //SEG7
    GPIO_Init(GPIOD, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //COM3
    GPIO_Init(GPIOD, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //SEG8
    GPIO_Init(GPIOD, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //SEG9
    GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //SEG18
    GPIO_Init(GPIOD, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //SEG19
    GPIO_Init(GPIOD, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //SEG20
    GPIO_Init(GPIOD, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //SEG21
  
    GPIO_Init(GPIOE, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //SEG1
    GPIO_Init(GPIOE, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //SEG2
    GPIO_Init(GPIOE, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //SEG3
    GPIO_Init(GPIOE, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //SEG4
    GPIO_Init(GPIOE, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //SEG5
    GPIO_Init(GPIOE, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //SEG6
    GPIO_Init(GPIOE, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //NBģ���ⲿ��Դ��������
    GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //POWEN_ON_OFF_NB_���


    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //CY0
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //CY1
    GPIO_Init(GPIOF, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOF, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOF, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //IC_INT û��IC��
    GPIO_Init(GPIOF, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //IC_SCL û��IC��
    GPIO_Init(GPIOF, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //IC_VDD û��IC��
    GPIO_Init(GPIOF, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  
  
    GPIO_Init(GPIOG, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //RX3
    GPIO_Init(GPIOG, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Fast);  //TX3
    GPIO_Init(GPIOG, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Slow); //I2C_SCL
    GPIO_Init(GPIOG, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Slow); //I2C_SDA
    GPIO_Init(GPIOG, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //MOT_A
    GPIO_Init(GPIOG, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //BUZZ
    GPIO_Init(GPIOG, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //MOT_B
    GPIO_Init(GPIOG, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //ADC_EN
}

/******************************************************************************
*������:void RTC_Time_Init(void)
*����:RTCʱ���ʼ��
*����:��
*���:��
*��ע:��š��汾��
*******************************************************************************/
void RTC_Time_Init(void)
{
    RTC_DateStructInit(&Rtc.Date);
    Rtc.Date.RTC_WeekDay = RTC_Weekday_Wednesday;
    Rtc.Date.RTC_Date = 0x04;
    Rtc.Date.RTC_Month = RTC_Month_November;
    Rtc.Date.RTC_Year = 0x19;
    RTC_SetDate(RTC_Format_BCD, &Rtc.Date);

    RTC_TimeStructInit(&Rtc.Time);
    Rtc.Time.RTC_Hours   = 0x22;
    Rtc.Time.RTC_Minutes = 0;
    Rtc.Time.RTC_Seconds = 0;
    RTC_SetTime(RTC_Format_BCD, &Rtc.Time); 
}

/*******************************************************************************
* ��    �ƣ�void Rtc_Configuration(void)
* ��    �ܣ�RTC����
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�������
*******************************************************************************/
void Rtc_Configuration(void)
{
    RTC_InitTypeDef   RTC_InitStr;
    RTC_AlarmTypeDef  RTC_AlarmStr;

    //�ⲿʱ��
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);

    RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
    RTC_InitStr.RTC_AsynchPrediv = 0x7F;
    RTC_InitStr.RTC_SynchPrediv = 0x00FF;
    RTC_Init(&RTC_InitStr);
    
    RTC_AlarmCmd(DISABLE); //��������һ��Ҫ ��ʧ��  ������
    RTC_AlarmStructInit(&RTC_AlarmStr);
    RTC_AlarmStr.RTC_AlarmTime.RTC_Hours   = 0;
    RTC_AlarmStr.RTC_AlarmTime.RTC_Minutes = 0x50;
    RTC_AlarmStr.RTC_AlarmTime.RTC_Seconds = 0;
    RTC_AlarmStr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay | RTC_AlarmMask_Hours ;
    RTC_SetAlarm(RTC_Format_BCD, &RTC_AlarmStr); 

    RTC_ITConfig(RTC_IT_ALRA, ENABLE);
    RTC_AlarmCmd(ENABLE);
}
/*******************************************************************************
* ��    �ƣ�void RTC_WAKEINIT(void)
* ��    �ܣ�RTC���û���ʱ��
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�������
*******************************************************************************/
void RTC_WAKEINIT(void)
{
    //32.768k/16 = 2.048khz  = 0.489ms
    //38K/16 = 2.375khz   =  0.421ms
    RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);
    RTC_WakeUpCmd(DISABLE);//�����ȹرղ���дcounter

    //�ڲ�ʱ�� 1s
    RTC_SetWakeUpCounter(2375); //1s=2375*0.421  2s=4751

    RTC_WakeUpCmd(ENABLE);//ʹ�ܻ���
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//ʹ�ܻ����ж�
    
}
/*******************************************************************************
* Function Name   : IWDG_Config
* Description     : ���Ź�����
* Calls           :
* Called By       :
* Inputs          : None
* Outputs         : None
* Return          : None
* Notes           : None
RST_ClearFlag(RST_FLAG_IWDGF);
IWDG_ReloadCounter();

*******************************************************************************/
void IWDG_Config(void)
{
    //������Ź���λ��־
    if (RST_GetFlagStatus(RST_FLAG_IWDGF) != RESET)
    {
        RST_ClearFlag(RST_FLAG_IWDGF);
    }
    CLK_LSICmd(ENABLE);//ʹ���ڲ�LSI 38KHZ
    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
    /* IWDG timeout equal to 214 ms (the timeout may varies due to LSI frequency
       dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    /* IWDG configuration: IWDG is clocked by LSI = 38KHz */
    IWDG_SetPrescaler(IWDG_Prescaler_256);

    /* IWDG timeout equal to 214.7 ms (the timeout may varies due to LSI
    frequency dispersion) */
    /* IWDG timeout = (RELOAD_VALUE + 1) * Prescaler / LSI
                    = (254 + 1) * 256 / 38 000
                    = 1724.63 ms */
    IWDG_SetReload((uint8_t)RELOAD_VALUE);

    /* Disable write access to IWDG_PR and IWDG_RLR registers */
    //IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);

    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    OPT->WDG = 0x02;//Independent watchdog stopped in Halt/Active-halt mode

}












