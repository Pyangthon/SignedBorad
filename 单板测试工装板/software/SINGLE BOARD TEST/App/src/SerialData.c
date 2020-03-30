#include "SerialData.h"

u8 UpDataArr[2] = {0};  // 指令和数据数组
Global_Flag_TypeDef FlagStruct;     // 全局标志位结构体
ADSZeroBiaData_TypeDef ADSZBStruct; // ADS初始数据结构体

//*****************************************************************************/
//*函数名 :void Wait_Implement(void)
//*说明   :等待上位机下发的数据，判断指定位的数据，进入指定的函数执行
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Wait_Implement(void)
{       
    switch(USART_3.USART_Date[1])   // 选择需要执行的函数
    {   
    case LORACOM:
        LoRa_Test();                // LoRa测试函数
        break;                
    case CURRENTDET:                
        Current_Test();             // 电流测试函数
        break;
    case OPENVALVE:
        Valve_Test(OPENVALVE);     // 开阀测试函数
        break;
    case CLOSEVALVE:
        Valve_Test(CLOSEVALVE);     // 关阀测试函数
        break;
    case RSCOMDET:
        RS485_Test();               // RS485通信测试函数
        break;                                
    case RESETDET:      
        ResetDefault();             // 复位指令
        break;               
    case METERDET:
        Meter_Test();               // 计量检测
        break;
    case VOLTDET:
        Volt_Test();                // 电压检测
        break;
    case KEYDET:
        Key_Test();                 // 按键测试
    case INFRAREDDET:
        InfraredTest();
        break;
    case MODCONDET:
        ModifyConfig();             // 系统配置函数，修改系统参数
        break;
    default:      
        UpDataArr[0] = ERRORCOM;    // 错误指令
        ReturnTestDet(UpDataArr, 2); // 非已定义的测试指令
        break;                   
    } 
    CountDown = DEFCOUNTDOWN;
    USART_3.Falg = 0;
    memset(USART_3.USART_Date, 0, sizeof(USART_3.USART_Date));
    USART_3.Length = 0;
}

//*****************************************************************************/
//*函数名 :void ReturnTestDet(u8 *det, u8 Len)
//*说明   :上传测试结果
//*参数   :Det    测试结果指令
//*        Len    上传指令长度
//*返回值 :无
//*作者   :
//*****************************************************************************/
void ReturnTestDet(u8 *Det, u8 Len)
{
    u8 temp;
    u8 UploadDetArr[10] = {0};                  // 上传数组
    UploadDetArr[0] = UPDATACOM;                // 上传数据开始位
    for(temp = 0; temp < Len; temp++)           // 写入数据位
    {
        UploadDetArr[temp+1] = Det[temp];
    }
    UploadDetArr[Len + 1] = UPCHECKDET;         // 校验位
    UploadDetArr[Len + 2] = UPCONFIR;           // 数据结束位
    printf("本次检测结果为: ");
    PrintArr(UploadDetArr, Len+3);
    USART_3.Length = 0; 
    memset(USART_3.USART_Date,0,sizeof(USART_3.USART_Date));  // 清除串口3数据缓存器             
}

//*****************************************************************************/
//*函数名 :void Current_Test(void)
//*说明   :电流检测
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Current_Test(void)
{
    int temp = 0;    
    ADSDATA_TypeDef ADSDataStruct;      // ADS数据存储结构体
    if(FlagStruct.SPDTIEnFlag == TRUE)
    {
        SPDT_EN_OFF();                      // 在检测电流前先关闭继电器，保证无电流干扰
        FlagStruct.SPDTIEnFlag = FALSE;
    }
    if((ADSZBStruct.ZeroBiaVolt0 * 1000 > ADSZBStruct.ZeroBiaVoltThre0)     // 判断通道0、1的零偏电压是否超过阀值
        || (ADSZBStruct.ZeroBiaVolt1 * 1000 > ADSZBStruct.ZeroBiaVoltThre1) 
            || (FlagStruct.ZeroBiaVoltFlag == FALSE))           // 判断零偏电压是否采集成功
    {
        printf("零偏电压存在误差，请去除被测板后重新获取零偏电压!!!!\r\n");
        return;
    }
    temp = GetAdcAvg(0);                // 获取通道0采样值
    ADSDataStruct.Chan0Volt = temp * 4.096 / 0X7fff;    // 保存通道0的电压值
    ADSDataStruct.Chan0Curr = (ADSDataStruct.Chan0Volt - ADSZBStruct.ZeroBiaVolt0) / 50;    // 获取通道0的电流值
    if(ADSDataStruct.Chan0Curr*1000 >= 1)     // 如果通道0的电流大于1mA则打印电流值     mA级电流
    {
        printf("通道 a 电流 %f mA\r\n", ADSDataStruct.Chan0Curr * 1000);  // 打印电流值
    }
    else if(ADSDataStruct.Chan0Curr * 1000 < 1)   // 如果通道0的电流值小于或等于1mA则测试通道1，uA级电流
    {
        temp = GetAdcAvg(1);            // 获取通道1的采样值
        ADSDataStruct.Chan1Volt = temp * 4.096 / 0X7fff;        // 计算通道1的电压值
        ADSDataStruct.Chan1Curr = (ADSDataStruct.Chan1Volt - ADSZBStruct.ZeroBiaVolt1) / 200;   // 计算通道1的电流值
        if(ADSDataStruct.Chan1Curr * 1000 >= 1)
        {
            printf("通道 a 电流 %f mA\r\n", ADSDataStruct.Chan1Curr * 1000);  // 打印电流值，这里因为测试过程中发现有时会发现到这里是刚好唤醒或突变，
                                                                              // 应属正常值，在下位机进行处理将通道b采集到的值以通道a的名义向上发送
        }
        else
        {
            printf("通道 b 电流 %f uA\r\n", ADSDataStruct.Chan1Curr*1000000);  // 打印通道1电流值
        }
    }
}
//*****************************************************************************/
//*函数名 :void Volt_Test(void)
//*说明   :电压检测
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Volt_Test(void)
{
    u16 VoltValve_Int = 0;      // 保存获取的电压值
    if(FlagStruct.FristVoltTest == TRUE && FlagStruct.SPDTIEnFlag == FALSE)    // 判断是否是第一次获取电压
    {
        FlagStruct.FristVoltTest = FALSE;   // 改变获取电压标志位  
        SPDT_EN_ON();                       // 打开继电器
        FlagStruct.SPDTIEnFlag = TRUE;      // 将继电器标志位置为打开
        VoltValve_Int = VadcGet_2();        // 获取电压采样值
        Delay_ms(100);                      // 延时100ms
        Volt_Test();                        // 第一次采集实际上是不准确的，这里使用递归再次采集电压，让第一次采集的值被覆盖，保证采集的准确性
    }
    else
    {
        VoltValve_Int = VadcGet_2();        // 获取电压采样值
        printf("本次测试电压值为 %.2f V\r\n", VoltValve_Int / 100.0);
    }
}

//*****************************************************************************/
//*函数名 :void Key_Test(void)
//*说明   :按键检测
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Key_Test(void)
{
    // 按键检测函数
    // 关闭LED2
    LED2_H();
    // 开启等待
    MsCount = 0;
    TIM3_Cmd(ENABLE);
    while(MsCount < COUNTNUM)
    {
        if(FlagStruct.Key1Flag == TRUE)
        {
            FlagStruct.Key1Flag = FALSE;
            LED2_L();
            printf("按键已被按下\r\n");
            break;
        }
    }
    if(MsCount >= COUNTNUM)
    {
        printf("5S内按键未被按下\r\n");
    }
}


//*****************************************************************************/
//*函数名 :void ModefyConfig(void)
//*说明   :系统配置修改函数
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void ModifyConfig(void)
{
    // 串口波特率16进制 0:1200  1:2400  2:4800  3:9600  4:14400 5:19200  6:38400 7:56000  8:115200  9:128000 10:230400 11:460800
    u32 SerailBaud[] = {0X04B0, 0X0960, 0X12C0, 0X2580,0X3840, 0X4B00 , 0X9600, 0XDAC0,  0X01C200, 0x01F400, 0X038400, 0X070800};
    switch(USART_3.USART_Date[2])
    {
    case LORAINITDEF:       // 修改Lora初始化参数
        LoraDataStruct.LoRaChan = USART_3.USART_Date[3];        // lora信道
        LoraDataStruct.LoRaSF = USART_3.USART_Date[4];          // lora扩频因子
        if(RF1278_Init(LoraDataStruct.LoRaChan, LoraDataStruct.LoRaSF)) // Lora射频初始化，并判断修改是否成功
        {
            LEDFlicker(0,2);        // 初始化成功提示
            FlagStruct.LoRaInitFlag = TRUE;     // 修改Lora初始化状态
            printf("修改成功!\r\n");  // 串口输出提示信息
            printf("Lora通信通道为 %d, 扩频因子为 %d\r\n", LoraDataStruct.LoRaChan, LoraDataStruct.LoRaSF);
        }
        else
        {
            printf("Lora初始化修改失败!\r\n");
            FlagStruct.LoRaInitFlag = FALSE;
        }
        break;
    case USART2BAUD:        // 修改串口2波特率
        Usart2_Module_Disable();    // 串口失能
        Usart2_Module_Init(SerailBaud[USART_3.USART_Date[3]]);      // 设定串口波特率
        printf("串口2波特率修改为 %ld\r\n", SerailBaud[USART_3.USART_Date[3]]);   // 串口打印波特率修改结果
        break;
    case USART1BAUD:        // 修改串口1波特率
        Usart1_Module_Disable();
        Usart1_Module_Init(SerailBaud[USART_3.USART_Date[3]]);
        printf("串口1波特率修改为 %ld\r\n", SerailBaud[USART_3.USART_Date[3]]);
        break;
      
    default:
      break;
        
    }
}

//*****************************************************************************/
//*函数名 :void InfraredTest(void)
//*说明   :红外线检测和数据接收
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void InfraredTest(void)
{
    // 针对红外线指令设计相关程序
    u8 DetArr = USART_1.USART_Date[1];
    if(DetArr == 0X68)
    {
        // 硬件和红外线测试通过
        LEDFlicker(1, 2);
        
    }
    else if(DetArr == 0X78)
    {
        // 硬件测试未通过，红外线测试通过
        LEDFlicker(2, 1);
    }
    else
    {
        // 硬件和红外线都未检测通过
        DetArr = 0X00;
    }
    printf("硬件检测结果为 %2X\r\n", DetArr);
}
