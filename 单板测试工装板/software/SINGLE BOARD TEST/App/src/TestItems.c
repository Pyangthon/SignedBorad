//引入头文件
#include "TestItems.h"

// 定义全局变量
Lora_TypeDef LoraDataStruct;
Valve_TypeDef ValveStruct;
u8 LoraDataArr[LORAARRSIZE] = {0};      // Lora数据发送
u8 DataCheckArr[2] = {0XAA, 0XAB};                  // 默认数据校验数组
                      
u8 CmdAndAddArr[12] = {0X11, 0X22, 0X03, 0X44, 0X0A, 0X0B, 0X0C, 0X0D, 0XA0, 0XB0, 0XC0, 0XD0}
                       // 命令序列数组         // 目标地址数组           // 原地址数组

//*****************************************************************************/
//*函数名 :void LoRa_Test(void)
//*说明   :LoRa模块测试函数
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void LoRa_Test(void)
{ 
    // 串口提示数组
//    u8 LoRa_Str1[] = {"LoRa Initialization successful!\r\n"};
//    u8 LoRa_Str2[] = {"LoRa Startup failure!\r\n"};
    u8 LoraArr[LORADEFSIZE] = {0};
    if(FlagStruct.LoRaInitFlag == TRUE)       // 判断初始化是否成功
    {        
        LoraSendData(LORATEST,LoraArr, LORADEFSIZE);
        LEDFlicker(0, 1);
        Rf1278_ModeSet(100);     // 开启接收
//        UsartSend(USART3, LoRa_Send_DataArr, 5);             
        TIM3_Cmd(ENABLE);   // 开启定时器3
        MsCount = 0;      // 复位计数器
        
        while(MsCount < COUNTNUM)     // 等待三秒，接收数据
        {
            if(LoraDataStruct.LoRaRXFlag == TRUE)
            {
                RF1278_RecePacket(LoraDataStruct.LoRaReceArr, 30);      // 接收数据
                Rece_DataCheck(LORACOM, LoraDataStruct.LoRaReceArr);    // 
                RF1278_ReadRssiSnr(&LoraDataStruct.LoRaRrsi);      // 读取灵敏度值
                if(LoraDataStruct.LoRaRrsi > LORADEFRRSI)   // 接收到数据后,判断灵敏度值是否低于标准值
                {
                    FlagStruct.LoRaTestFlag = LORACOM;                       
                    LED0_L();    // 提示灯亮起                       
                }
                else
                {
                    FlagStruct.LoRaTestFlag = LORAERRDET;   
                }
                UpDataArr[0] = FlagStruct.LoRaTestFlag;     // 保存lora测试结果
                LoraDataStruct.LoRaRXFlag = FALSE;          // 接收标志位复位
                ReturnTestDet(UpDataArr);   // 上传LORA测试的结果
                TIM3_Cmd(DISABLE);  // 关闭定时器3
                MsCount = 0;        // 计数时间标志位清0
                break;
            }
        } 
        if(MsCount >= COUNTNUM)
        {
            TIM3_Cmd(DISABLE);  // 关闭定时器3
            MsCount = 0;        // 计数器清0
            LoraDataStruct.LoRaRXFlag = FALSE;  // lora接收标志位复位
            UpDataArr[0] = LORAERRDET;  // 上传数组0位保存为lora测试错误指令 
            ReturnTestDet(UpDataArr);   // 上传LORA测试的结果
            Rf1278_ModeSet(100);        // 开启接收
        }
    }   
    else
    {
        RF1278_Init(2, 2);  // 没有初始化的情况下就进行初始化
        FlagStruct.LoRaInitFlag = TRUE;
        LEDFlicker(0, 1);
    }
}
//*****************************************************************************/
//*函数名 :void _Rece_DataCheck(u8 Mode)
//*说明   :接收数据校验函数
//*参数   :mode    选择接收模式
//*返回值 :DataVar 校验成功次数(0-5之间)
//*作者   :
//*****************************************************************************/
void Rece_DataCheck(u8 Mode, u8 *Cbuf)
{
    u8 Local_DataArr[] = {0X68, 0X05, 0X31, 0X5F, 0X90};
    u8 DataVar;
    u8 temp;    // 临时变量用于存储接收指令位的取反值
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
//*函数名 :void Valve_Test(u8 Det)
//*说明   :阀门测试测试
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Valve_Test(u8 Det)
{
    // 发送开关阀指令,阀一or阀二
    LoraDataArr[0] = USART_3.USART_Date[2];
    LoraSendData(Det, LoraDataArr, LORAARRSIZE);

    // 检测IO通断
    // 等待10s，查询IO是否产生中断
    MsCount = 0;
    TIM3_Cmd(ENABLE);
    while(MsCount < 50)
    {
        // 检测阀门状态
       if((FlagStruct.Key1Flag == TRUE) || (FlagStruct.Key2Flag == TRUE) ||       // 判断当前是否有阀门响应
           (FlagStruct.Key3Flag == TRUE) || (FlagStruct.Key4Flag == TRUE))
       {
           if((FlagStruct.Key1Count == 1) && (FlagStruct.Key2Count == 1))
           {
                ValveStruct.Valve1State = TRUE;     // 阀1状态开
                UpDataArr[1] = OPVALCONA;
           }
           else if((FlagStruct.Key2Count == 1) && (FlagStruct.Key1Count == 1))
           {
                ValveStruct.Valve1State = FALSE;    // 阀1状态关
                UpDataArr[1] = CLVALCONA;
           }
           else if((FlagStruct.Key3Count == 1) && (FlagStruct.Key4Count == 1))
           {
               ValveStruct.Valve2State = TRUE;      // 阀2状态开
               UpDataArr[1] = OPVALCONB;
           }
           else if((FlagStruct.Key4Count == 1) && (FlagStruct.Key3Count == 1))
           {
               ValveStruct.Valve2State = FALSE;     // 阀2状态开
               UpDataArr[1] = CLVALCONB;
           }
           if(UpDataArr[1] != 0X00)
           {
               UpDataArr[0] = USART_3.USART_Date[2];
               ReturnTestDet(UpDataArr);
               TIM3_Cmd(DISABLE);  // 关闭定时器3
               MsCount = 0;      // 计数时间标志位清0
               break;
           }
       }

    }
    if(MsCount <= 50)
    {
        TIM3_Cmd(DISABLE);  // 关闭定时器2
        MsCount = 0;
        UpDataArr[0] = USART_3.USART_Date[2];
        UpDataArr[1] = CTRVALERR;
        ReturnTestDet(UpDataArr);
    }
        
}

//*****************************************************************************/
//*函数名 :void LoraSendData(u8 Det, u8 *Cbuf, u8 Buflen)
//*说明   :Lora发送封装数据函数 
//*参数   :Det        需要发送的指令
//*        *Cbuf      需要发送的数据
//*        Buflen     数据的长度
//*返回值 :
//*作者   :
//*****************************************************************************/
 
void LoraSendData(u8 Det, u8 *Cbuf, u8 Buflen)
{
    u8 temp;
    LoraDataStruct.LoRaSendArr[0] = LORADATAHEAD;           // 帧头
    LoraDataStruct.LoRaSendArr[1] = LORADATALENGTH+Buflen;  // 数据长度
    LoraDataStruct.LoRaSendArr[14] = Det;       // 需要发送的指令
    for(temp = 0; temp < Buflen; temp++)
    {
        LoraDataStruct.LoRaSendArr[temp+15] = Cbuf[temp];   // 数据位
    }
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 3] = DataCheckArr[0];  // 校验位
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 2] = DataCheckArr[1];
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 1] = LORADATATAIL;     // 帧尾   
    
    RF1278_SendPacket(LoraDataStruct.LoRaSendArr, LORADATALENGTH+Buflen);       // 通过LORA模块进行发送
  
}


//*****************************************************************************/
//*函数名 :void WriteLoraDef(void)
//*说明   :写入lora发送输入的默认值
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void WriteLoraDef(void)
{
    u8 temp;
    for(temp = 0; temp < 12; temp++) // 写入命令序列，原地址，目标地址
    {
        LoraDataStruct.LoRaSendArr[temp+2] = CmdAndAddArr[temp];
    }
}

//*****************************************************************************/
//*函数名 :void Meter_Test(void)
//*说明   :直读气表计量测试
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Meter_Test(void)
{
    if(FlagStruct.SPDTIEnFlag == FALSE)
    {
        SPDT_EN_ON();
        FlagStruct.SPDTIEnFlag = TRUE;
        Delay_ms(50);
        USART_Cmd(USART1,ENABLE);  //使能
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