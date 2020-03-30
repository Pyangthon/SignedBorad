#include "SysInitApp.h"

u16 MsCount = 0;        // 计数标志位
u16 SceCount = 0;       // 秒数标志位
u16 CountDown = 300;    // 倒计时计数器
bool HaltState = FALSE; // 休眠标志位
//*****************************************************************************/
//*函数名 :void SPDT_Init(void)
//*说明   :初始化继电器端口
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void SPDT_Init(void)
{
    // 初始化继电器端口
    GPIO_Init(SPDT_PORT, SPDT_EN_PIN, GPIO_Mode_Out_PP_High_Slow);       // PC7
    // 初始化为关闭继电器
    SPDT_EN_OFF();
    FlagStruct.SPDTIEnFlag = FALSE;
}

//*****************************************************************************/
//*函数名 :void SPDT_Ctrl_Port_Init(void)
//*说明   :初始化继电器控制下的端口，根据编译条件命令PB_LSB_MODE控制端口初始化模式。
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void SPDT_Ctrl_Port_Init(void)
{
#if PB_LSB_MODE
    // 将PB0-3初始化为高速推挽输出高
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);
    // 默认输出低电平
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_1, RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_2, RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_3, RESET);
#else
    // 将PB0-3初始化为上拉无中断输入
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);
#endif
    // 初始化串口1
    Usart1_Module_Init(2400);   // 当前版本用于唐山项目红外接收
    USART_Cmd(USART1,DISABLE);  //不使能USART1
}


//*****************************************************************************/
//*函数名 :void Peripheral_Init(void)
//*说明   :外设初始化
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/

void System_Init(void)
{
    SysClockInit();     // 系统时钟初始化，内部高速时钟，16MHz   
    GPIO_Init_Config();
    RS485_Init();       // RS485初始化，串口2，波特率9600，默认接收
    Usart3_Module_Init(2400);     // 串口3初始化，用于接收上位机指令数据
    LED_Init();         // LED提示部分初始化
    Key_Init();         
    ValveTest_Init();
    SPDT_Init();        //继电器初始化,默认继电器关闭
    Lora_Gpio_Init();   // LoRa模块端口初始化 
    ADS1115_Init();     // ADS1115ADC初始化
    SPDT_Ctrl_Port_Init();
    Timer3_init();
    ADC_Config_Init();  // ADC初始化
//    Timer2_init();    // 该定时器用于休眠倒计时，暂未使用
    if(RF1278_Init(2, 2))
    {
        LEDFlicker(0,2);
        FlagStruct.LoRaInitFlag = TRUE;     // LoRa射频初始化标志位置1
    }  
    ZeroBiaVoltConfig();        // 配置零偏电压参数
    if(ZeroBisVoltTset(0) == TRUE)          // 检测零偏电压 
    {
        printf("System Init OK!\n");
    }
    
}
//*****************************************************************************/
//*函数名 :void ZeroBiaVoltConfig(void)
//*说明   :零偏电压相关参数配置
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void ZeroBiaVoltConfig(void)
{
    FlagStruct.FristVoltTest = TRUE;
    ADSZBStruct.ZeroBiaVoltThre0 = 10;
    ADSZBStruct.ZeroBiaVoltThre1 = 30;
}

//*****************************************************************************/
//*函数名 :void GPIO_Init_Config(void)
//*说明   :GPIO初始化配置
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void GPIO_Init_Config(void)
{
    GPIO_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);//SWIM
    GPIO_Init(GPIOA, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  //NRST
    GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow );  //【SART1_TX】    
    GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //【USART1_X】
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
//*函数名 :void ResetDefault(void)
//*说明   :初始化串口，继电器，LED
//*参数   :无
//*返回值 :无
//*作者   :
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
//*函数名 :void ZeroBisVoltTest(u8 State)
//*说明   :获取ADC的零偏电压
//*参数   :State  是否需要打印零偏电压值
//*        1 打印   0 不打印
//*返回值 :无
//*作者   :
//*****************************************************************************/
bool ZeroBisVoltTset(u8 State)
{   
    u16 temp = 0;               // 存放ADC通道采样值零时变量
    float Volt_temp = 0.0;      // 存放ADC采样电压值
    if((State == 0) && (FlagStruct.ZeroBiaVoltFlag == TRUE))        // TRUE表示零偏电压采集已完成，state == 0 表示不需进行零偏电压采集
    {             // 判断是否需要进行零偏电压重置采集
        return FALSE;
    }
    else
    {
        temp = GetAdcAvg(0);        // 获取通道0的采样值
        Volt_temp = temp * 4.096 / 0X7fff;  // 计算零偏电压
        if(Volt_temp * 1000 > ADSZBStruct.ZeroBiaVoltThre0)        // 判断获取零偏电压时是否存在被测板
        {
            printf("请去除被测板后重新检测零偏电压!!!\r\n"); // 有则输出提示信息
            FlagStruct.ZeroBiaVoltFlag = FALSE;        // 将零偏电压采集成功标志位置0，表示采集失败，仍需重新采集
            return FALSE;     // 并退出函数
        }
        else
        {
            ADSZBStruct.ZeroBiaVolt0 = Volt_temp;       // 没有被测板则将采样电压存入零偏电压值结构体中等待取用
        }
        temp = GetAdcAvg(1);        //  获取通道1的零偏电压
        Volt_temp = temp * 4.096 / 0X7fff;   // 保存通道1的零偏电压值
        if(Volt_temp * 1000 > ADSZBStruct.ZeroBiaVoltThre1)
        {
            printf("请去除被测板后重新检测零偏电压!!!\r\n"); // 有则输出提示信息
            FlagStruct.ZeroBiaVoltFlag = FALSE;        // 将零偏电压采集成功标志位置0，表示采集失败，仍需重新采集
            return FALSE;     // 并退出函数
        }
        else
        {
            ADSZBStruct.ZeroBiaVolt1 = Volt_temp;
            FlagStruct.ZeroBiaVoltFlag = TRUE;
        }
        if(State == 1)      // 判断是否需要打印零偏电压值
        {
            printf("通道 0 零偏电压为 %f mV\r\n", ADSZBStruct.ZeroBiaVolt0 * 1000);
            printf("通道 1 零偏电压为 %f mV\r\n", ADSZBStruct.ZeroBiaVolt1 * 1000);
        }
    }
    return TRUE;
}

//*****************************************************************************/
//*函数名 :void PrintArr(u8 *Arr,int length)
//*说明   :16进制格式打印数组
//*参数   :*Arr 需要被输出的数组
//*        Length 数组的长度
//*返回值 :
//*作者   :
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
//*函数名 :void Dormancy(void)
//*说明   :进入休眠，通过倒计时计数标志位CountDown是否到0
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Dormancy(void)
{
    HaltState = FALSE;  // 重置休眠标志位
    DisableGPIO();      // 配置GPIO无漏电流产生
    DisableCLK();       // 关闭所有时钟
    halt();             // 休眠,外部中断触发后，又从此处开始运行
    System_Init();      // 重新初始化所有外设
    enableInterrupts(); // 开启中断
}

//*****************************************************************************/
//*函数名 :void DisableGPIO(void)
//*说明   :配置GPIO为空载状态
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void DisableGPIO(void)
{
    // 暂时未开发
}
//*****************************************************************************/
//*函数名 :void DisableClk(void)
//*说明   :关闭所有时钟
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void DisableCLK(void)       
{
    // 暂时未开发
}