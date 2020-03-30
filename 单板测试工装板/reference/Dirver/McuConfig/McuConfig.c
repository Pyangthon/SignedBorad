#include "McuConfig.h"

#define RELOAD_VALUE       254    //独立看门狗参数

RTC_T  Rtc; //RTC日期

///*******************************************************************************
//* 名    称：void CLK_Configuration(void)
//* 功    能：配置单片机系统时钟
//* 入口参数：
//* 出口参数：
//* 说    明：
//* 调用方法：无
//*******************************************************************************/
void CLK_Configuration(void)
{
  
//    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTC时钟使能
//    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);//LCD时钟使能
    CLK_DeInit();//时钟初始化
    CLK_HSICmd(ENABLE);//内部高速时钟使能
//    CLK_LSEConfig(CLK_LSE_ON);//32.768K晶振使能
//    while(SET != CLK_GetFlagStatus(CLK_FLAG_LSERDY));
    CLK_ClearFlag();
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//系统时钟选择内部高速时钟
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
    while(SET != CLK_GetFlagStatus(CLK_FLAG_HSIRDY));
    CLK_ClearFlag();
//    CLK_RTCClockConfig(CLK_RTCCLKSource_HSE, CLK_RTCCLKDiv_1); //RTC时钟源选择LSE，不分频
//    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTC时钟使能
    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);//LCD时钟使能
    Delay_ms(10);//延时1ms使稳定，不然可能出现LCD时钟使能无效
}

///*******************************************************************************
//* 名    称：void GPIO_Configuration(void)
//* 功    能：GPIO配置
//* 入口参数：
//* 出口参数：
//* 说    明：LCD相应IO脚不用配置 没用到的IO配置为推挽输出 低电平
//* 调用方法：无
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
    GPIO_Init(GPIOE, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //NB模块外部电源控制引脚
    GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //POWEN_ON_OFF_NB_麦度


    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //CY0
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //CY1
    GPIO_Init(GPIOF, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOF, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOF, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //IC_INT 没用IC卡
    GPIO_Init(GPIOF, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //IC_SCL 没用IC卡
    GPIO_Init(GPIOF, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //IC_VDD 没用IC卡
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
//* 名    称：void EXTI_Configuration(void)
//* 功    能：外部中断配置
//* 入口参数：
//* 出口参数：
//* 说    明：根据外部硬件电路配置成相应的上升或者下降沿触发
//* 调用方法：无
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
//* 名    称：void TIM1_Configuration(void)
//* 功    能：定时器1配置，定时基准时间 1ms
//* 入口参数：
//* 出口参数：
//* 说    明：
//* 调用方法：无
//*******************************************************************************/
void TIM1_Configuration(void)
{
    /* Enable TIM1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);
    // TIM1_DeInit();
    TIM1_SetCounter(0);
    TIM1_TimeBaseInit(16, TIM1_CounterMode_Up , 1000, 0);
    TIM1_ARRPreloadConfig(ENABLE);//预装值
    TIM1_ClearITPendingBit(TIM1_IT_Update);
    TIM1_ITConfig(TIM1_IT_Update, ENABLE); //中断开启
    TIM1_Cmd(ENABLE);//默认关闭
}

///******************************************************************************
//*函数名:void Timer3_init(void)
//*功能:按键定时器  100ms
//*输入:无
//*输出:无
//*备注:无
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
//* Description     : 看门狗配置
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
    //清除看门狗复位标志
    if (RST_GetFlagStatus(RST_FLAG_IWDGF) != RESET)
    {
        RST_ClearFlag(RST_FLAG_IWDGF);
    }
    CLK_LSICmd(ENABLE);//使能内部LSI 38KHZ
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
//* 名    称：void Rtc_Configuration(void)
//* 功    能：RTC配置
//* 入口参数：
//* 出口参数：
//* 说    明：
//* 调用方法：无
//*******************************************************************************/
void Rtc_Configuration(void)
{
    RTC_InitTypeDef   RTC_InitStr;

    //内部时钟
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
//* 名    称：void RTC_Alarm_Config(void)
//* 功    能：RTC闹钟配置函数
//* 入口参数：
//* 出口参数：
//* 说    明：
//* 调用方法：无
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
//* 名    称：void RTC_WAKEINIT(void)
//* 功    能：RTC配置唤醒时间
//* 入口参数：
//* 出口参数：
//* 说    明：
//* 调用方法：无
//*******************************************************************************/
void RTC_WAKEINIT(void)
{
    //32.768k/16 = 2.048khz  = 0.489ms
    //38K/16 = 2.375khz   =  0.421ms
    RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
    RTC_WakeUpCmd(DISABLE);//必须先关闭才能写counter

    //内部时钟 1s
    RTC_SetWakeUpCounter(1); //1s=2375*0.421  2s=4751

    RTC_WakeUpCmd(ENABLE);//使能唤醒
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//使能唤醒中断
    
}
///*******************************************************************************
//* 名    称：void Stm8l15xConfig(void)
//* 功    能：MCU配置函数初始化模块函数
//* 入口参数：
//* 出口参数：
//* 说    明：
//* 调用方法：无
//*******************************************************************************/
void Stm8l15xConfig(void)
{  
   CLK_Configuration();  //系统时钟配置
         GPIO_Config();  //端口初始化
   Rtc_Configuration();  //初始化RTC时钟
//      LCD_GLASS_Init();  //LCD液晶初始化
//           LCD_Clear();  //LCD清屏
//       LCD_Cmd(ENABLE);  //LCD使能
//         Timer3_init();  //TIM3初始化
//       Timer2_init();  //TIM2初始化
        RTC_WAKEINIT();  //配置RTC时钟为1s中断
//    RTC_Alarm_Config();  //闹钟配置
//Usart3_Module_Init();  //直读头
//Usart1_Module_Init();  //NB通信
//  EXTI_Configuration();  //配置外部中断
    enableInterrupts();  //使能中断总开关

}

