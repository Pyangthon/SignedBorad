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
    GPIO_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);//SWIM
    GPIO_Init(GPIOA, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  //NRST
    GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow );  //��SART1_TX��    
    GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //��USART1_X��
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
  
    GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Slow);  //FLASH_EN
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  //IR_EN
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //SEG22
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //SEG23
    GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //ADC4
    GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //LSE1
    GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //LSE2
    GPIO_Init(GPIOC, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_MOSI
  
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
    GPIO_Init(GPIOE, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //USART2_RX
    GPIO_Init(GPIOE, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //USART2_TX
    GPIO_Init(GPIOE, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //SEG6
    GPIO_Init(GPIOE, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //POWER
    GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //PWRKEY


    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_CS
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_In_FL_No_IT);  //FLASH_MISO
    GPIO_Init(GPIOF, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //NO
    GPIO_Init(GPIOF, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //NO
    GPIO_Init(GPIOF, GPIO_Pin_4, GPIO_Mode_In_FL_IT);  //kEY 
    GPIO_Init(GPIOF, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //RTC_INT
    GPIO_Init(GPIOF, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //RST_C
    GPIO_Init(GPIOF, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //CLK_C
  
    GPIO_Init(GPIOG, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //USART3_RX
    GPIO_Init(GPIOG, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Fast);  //USART3_TX
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
* ��    �ƣ�void TIM1_Configuration(void)
* ��    �ܣ���ʱ��1���ã���ʱ��׼ʱ�� 1ms
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�������
*******************************************************************************/
void TIM1_Configuration(void)
{
    /* Enable TIM1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);
    TIM1_SetCounter(0);
    TIM1_TimeBaseInit(16, TIM1_CounterMode_Up , 1000, 0);
    TIM1_ARRPreloadConfig(ENABLE);//Ԥװֵ
    TIM1_ClearITPendingBit(TIM1_IT_Update);
    TIM1_ITConfig(TIM1_IT_Update, ENABLE); //�жϿ���
    TIM1_Cmd(DISABLE);
}

/******************************************************************************
*������:void Timer3_init(void)
*����:������ʱ��  10ms
*����:��
*���:��
*��ע:��
*******************************************************************************/
void Timer3_init(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM3,ENABLE);
  //TIM3_DeInit();  
  TIM3_TimeBaseInit(TIM3_Prescaler_128, TIM3_CounterMode_Up, 12500);    // 10ms    
  TIM3_ARRPreloadConfig(ENABLE); 
  TIM3_ClearITPendingBit(TIM3_IT_Update);
  TIM3_ITConfig(TIM3_IT_Update, ENABLE); 
  TIM3_Cmd(DISABLE);
}

/******************************************************************************
*������:void Timer2_init(void)
*����:������ʱ��  100ms
*����:��
*���:��
*��ע:��
*******************************************************************************/
void Timer2_init(void)
{
    TIM2_DeInit(); 
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);
    TIM2_TimeBaseInit(TIM2_Prescaler_128, TIM2_CounterMode_Up, 125);    // 1s    
    TIM2_ARRPreloadConfig(ENABLE); 
    TIM2_ClearITPendingBit(TIM2_IT_Update);
    TIM2_ITConfig(TIM2_IT_Update, ENABLE); 
    TIM2_Cmd(DISABLE);
}
//*****************************************************************************/
//*������ :
//*˵��   :
//*����   :
//*����ֵ :
//*����   :
//*****************************************************************************/

void Timer4_init(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4,ENABLE);
  TIM4_DeInit();  
  TIM4_TimeBaseInit(TIM4_Prescaler_128, 124);    // 10ms    
  TIM4_ARRPreloadConfig(ENABLE); 
  TIM4_ClearITPendingBit(TIM4_IT_Update);
  TIM4_ITConfig(TIM4_IT_Update, ENABLE); 
  TIM4_Cmd(DISABLE);
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












