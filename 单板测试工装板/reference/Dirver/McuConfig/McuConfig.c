#include "McuConfig.h"

#define RELOAD_VALUE       254    //�������Ź�����

RTC_T  Rtc; //RTC����

///*******************************************************************************
//* ��    �ƣ�void CLK_Configuration(void)
//* ��    �ܣ����õ�Ƭ��ϵͳʱ��
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����
//* ���÷�������
//*******************************************************************************/
void CLK_Configuration(void)
{
  
//    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTCʱ��ʹ��
//    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);//LCDʱ��ʹ��
    CLK_DeInit();//ʱ�ӳ�ʼ��
    CLK_HSICmd(ENABLE);//�ڲ�����ʱ��ʹ��
//    CLK_LSEConfig(CLK_LSE_ON);//32.768K����ʹ��
//    while(SET != CLK_GetFlagStatus(CLK_FLAG_LSERDY));
    CLK_ClearFlag();
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//ϵͳʱ��ѡ���ڲ�����ʱ��
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
    while(SET != CLK_GetFlagStatus(CLK_FLAG_HSIRDY));
    CLK_ClearFlag();
//    CLK_RTCClockConfig(CLK_RTCCLKSource_HSE, CLK_RTCCLKDiv_1); //RTCʱ��Դѡ��LSE������Ƶ
//    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTCʱ��ʹ��
    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);//LCDʱ��ʹ��
    Delay_ms(10);//��ʱ1msʹ�ȶ�����Ȼ���ܳ���LCDʱ��ʹ����Ч
}

///*******************************************************************************
//* ��    �ƣ�void GPIO_Configuration(void)
//* ��    �ܣ�GPIO����
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����LCD��ӦIO�Ų������� û�õ���IO����Ϊ������� �͵�ƽ
//* ���÷�������
//*******************************************************************************/
void GPIO_Config(void)
{
    GPIO_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOA, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow ); 
    
    GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOA, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOA, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow );  
                                                         
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow );  
    GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow );  
  
    GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow); 
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow); 
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow); 
    GPIO_Init(GPIOC, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  
  
    GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOD, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOD, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOD, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow); 
    GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOD, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOD, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  
    GPIO_Init(GPIOD, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  
  
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

///*******************************************************************************
//* ��    �ƣ�void EXTI_Configuration(void)
//* ��    �ܣ��ⲿ�ж�����
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ���������ⲿӲ����·���ó���Ӧ�����������½��ش���
//* ���÷�������
//*******************************************************************************/
void EXTI_Configuration(void)
{
    //EXTI_DeInit();
    //EXTI_SetPinSensitivity(EXTI_Pin_0, EXTI_Trigger_Falling); //CY0
    //EXTI_SetPinSensitivity(EXTI_Pin_1, EXTI_Trigger_Falling); //CY1
    //EXTI_SetPinSensitivity(EXTI_Pin_2, EXTI_Trigger_Rising); //KEY
    //EXTI_SetPinSensitivity(EXTI_Pin_3, EXTI_Trigger_Falling); //RTC_INT
    //EXTI_SetPinSensitivity(EXTI_Pin_4, EXTI_Trigger_Falling); //IC_INT
    //EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Rising); //PD5 RF_DIO0
    //EXTI_SetPinSensitivity(EXTI_Pin_7, EXTI_Trigger_Falling); //PA7 GPIO_BUTTON
    //EXTI_SetPinSensitivity (EXTI_Pin_3,EXTI_Trigger_Falling);//PB3 GPIO_FC
    //EXTI_SetPinSensitivity (EXTI_Pin_2,EXTI_Trigger_Falling );//PB2 GPIO_BUTTON
    //EXTI_SetPinSensitivity (EXTI_Pin_3,EXTI_Trigger_Rising_Falling);//PB2 GPIO_BUTTON
}

///*******************************************************************************
//* ��    �ƣ�void TIM1_Configuration(void)
//* ��    �ܣ���ʱ��1���ã���ʱ��׼ʱ�� 1ms
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����
//* ���÷�������
//*******************************************************************************/
void TIM1_Configuration(void)
{
    /* Enable TIM1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);
    // TIM1_DeInit();
    TIM1_SetCounter(0);
    TIM1_TimeBaseInit(16, TIM1_CounterMode_Up , 1000, 0);
    TIM1_ARRPreloadConfig(ENABLE);//Ԥװֵ
    TIM1_ClearITPendingBit(TIM1_IT_Update);
    TIM1_ITConfig(TIM1_IT_Update, ENABLE); //�жϿ���
    TIM1_Cmd(ENABLE);//Ĭ�Ϲر�
}

///******************************************************************************
//*������:void Timer3_init(void)
//*����:������ʱ��  100ms
//*����:��
//*���:��
//*��ע:��
//*******************************************************************************/
void Timer3_init(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM3,ENABLE);
  TIM3_DeInit();  
  TIM3_TimeBaseInit(TIM3_Prescaler_128, TIM3_CounterMode_Up, 12500);    // 100ms    
  TIM3_ARRPreloadConfig(ENABLE); 
  TIM3_ClearITPendingBit(TIM3_IT_Update);
  TIM3_ITConfig(TIM3_IT_Update, ENABLE); 
  TIM3_Cmd(DISABLE);
}

///*******************************************************************************
//* Function Name   : IWDG_Config
//* Description     : ���Ź�����
//* Calls           :
//* Called By       :
//* Inputs          : None
//* Outputs         : None
//* Return          : None
//* Notes           : None
//RST_ClearFlag(RST_FLAG_IWDGF);
//IWDG_ReloadCounter();
//
//*******************************************************************************/
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
///*******************************************************************************
//* ��    �ƣ�void Rtc_Configuration(void)
//* ��    �ܣ�RTC����
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����
//* ���÷�������
//*******************************************************************************/
void Rtc_Configuration(void)
{
    RTC_InitTypeDef   RTC_InitStr;

    //�ڲ�ʱ��
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);    
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);


    RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
    RTC_InitStr.RTC_AsynchPrediv = 0x7F;
    RTC_InitStr.RTC_SynchPrediv = 0x012F;
    RTC_Init(&RTC_InitStr);

    RTC_DateStructInit(&Rtc.Date);
    Rtc.Date.RTC_WeekDay = RTC_Weekday_Wednesday;
    Rtc.Date.RTC_Date = 0x01;
    Rtc.Date.RTC_Month = RTC_Month_November;
    Rtc.Date.RTC_Year = 0x19;
    RTC_SetDate(RTC_Format_BCD, &Rtc.Date);

    RTC_TimeStructInit(&Rtc.Time);
    Rtc.Time.RTC_Hours   = 8;
    Rtc.Time.RTC_Minutes = 0;
    Rtc.Time.RTC_Seconds = 0;
    RTC_SetTime(RTC_Format_BCD, &Rtc.Time);
    
}
///*******************************************************************************
//* ��    �ƣ�void RTC_Alarm_Config(void)
//* ��    �ܣ�RTC�������ú���
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����
//* ���÷�������
//*******************************************************************************/
void RTC_Alarm_Config(void)
{
    RTC_AlarmTypeDef  RTC_AlarmStr;
  
    RTC_AlarmStructInit(&RTC_AlarmStr);
    RTC_AlarmStr.RTC_AlarmTime.RTC_Hours   = 0;
    RTC_AlarmStr.RTC_AlarmTime.RTC_Minutes = 55;
    RTC_AlarmStr.RTC_AlarmTime.RTC_Seconds = 0;
    RTC_AlarmStr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay|RTC_AlarmMask_Hours;
    RTC_SetAlarm(RTC_Format_BIN, &RTC_AlarmStr);

    RTC_ITConfig(RTC_IT_ALRA, ENABLE);
    RTC_AlarmCmd(ENABLE);   
}
///*******************************************************************************
//* ��    �ƣ�void RTC_WAKEINIT(void)
//* ��    �ܣ�RTC���û���ʱ��
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����
//* ���÷�������
//*******************************************************************************/
void RTC_WAKEINIT(void)
{
    //32.768k/16 = 2.048khz  = 0.489ms
    //38K/16 = 2.375khz   =  0.421ms
    RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
    RTC_WakeUpCmd(DISABLE);//�����ȹرղ���дcounter

    //�ڲ�ʱ�� 1s
    RTC_SetWakeUpCounter(1); //1s=2375*0.421  2s=4751

    RTC_WakeUpCmd(ENABLE);//ʹ�ܻ���
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//ʹ�ܻ����ж�
    
}
///*******************************************************************************
//* ��    �ƣ�void Stm8l15xConfig(void)
//* ��    �ܣ�MCU���ú�����ʼ��ģ�麯��
//* ��ڲ�����
//* ���ڲ�����
//* ˵    ����
//* ���÷�������
//*******************************************************************************/
void Stm8l15xConfig(void)
{  
   CLK_Configuration();  //ϵͳʱ������
         GPIO_Config();  //�˿ڳ�ʼ��
   Rtc_Configuration();  //��ʼ��RTCʱ��
//      LCD_GLASS_Init();  //LCDҺ����ʼ��
//           LCD_Clear();  //LCD����
//       LCD_Cmd(ENABLE);  //LCDʹ��
//         Timer3_init();  //TIM3��ʼ��
//       Timer2_init();  //TIM2��ʼ��
        RTC_WAKEINIT();  //����RTCʱ��Ϊ1s�ж�
//    RTC_Alarm_Config();  //��������
//Usart3_Module_Init();  //ֱ��ͷ
//Usart1_Module_Init();  //NBͨ��
//  EXTI_Configuration();  //�����ⲿ�ж�
    enableInterrupts();  //ʹ���ж��ܿ���

}

