//引入头文件
#include "LoraTest.h"

// 定义全局变量
Lora_TypeDef LoraDataStruct;
Valve_TypeDef ValveStruct;
u8 LoraDataArr[LORADEFSIZE] = {0};      // Lora数据发送
u8 DataCheckArr[2] = {0XAA, 0XAB};                  // 默认数据校验数组
                      
u8 CmdAndAddArr[12] = {0X11, 0X22, 0X03, 0X44, 0X0A, 0X0B, 0X0C, 0X0D, 0XA0, 0XB0, 0XC0, 0XD0};
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
    u8 LoraDataArr[LORADEFSIZE] = {0};
    if(FlagStruct.LoRaInitFlag == TRUE)       // 判断初始化是否成功
    {        
        LoraSendData(LORATEST,LoraDataArr, LORADEFSIZE);
        
        Rf1278_ModeSet(128);    // 开启接收
        RF1278_ClearIrq();	            
        MsCount = 0;            // 复位计数器
        TIM3_Cmd(ENABLE);       // 开启定时器3
        while(MsCount < COUNTNUM)     // 等待三秒，接收数据
        {
            if(LoraDataStruct.LoRaRXFlag == TRUE)
            {
                RF1278_RecePacket(LoraDataStruct.LoRaReceArr, 30);      // 接收数据
                Rece_DataCheck(LORACOM, LoraDataStruct.LoRaReceArr);    // 校验数据
                RF1278_ReadRssiSnr(&LoraDataStruct.LoRaRrsi);           // 读取灵敏度值
                printf("Lora灵敏度值为: %d\r\n", LoraDataStruct.LoRaRrsi);
                if(LoraDataStruct.LoRaRrsi > LORADEFRRSI)               // 接收到数据后,判断灵敏度值是否低于标准值
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
                ReturnTestDet(UpDataArr, 2);                // 上传LORA测试的结果
                break;
            }
        } 
        if(MsCount >= COUNTNUM)
        {
            LoraDataStruct.LoRaRXFlag = FALSE;  // lora接收标志位复位
            UpDataArr[0] = LORAERRDET;          // 上传数组0位保存为lora测试错误指令 
            ReturnTestDet(UpDataArr, 2);        // 上传LORA测试的结果            
        }
    }   
    else
    {
        RF1278_Init(2, 2);  // 没有初始化的情况下就进行初始化
        FlagStruct.LoRaInitFlag = TRUE;
        LEDFlicker(0, 1);
    }
    memset(UpDataArr, 0, sizeof(UpDataArr));
    TIM3_Cmd(DISABLE);  // 关闭定时器3
}
//*****************************************************************************/
//*函数名 :void _Rece_DataCheck(u8 Mode)
//*说明   :接收数据校验函数
//*参数   :mode    选择接收模式
//*        *Cbuf   需要被校验到的数组
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Rece_DataCheck(u8 Mode, u8 *Cbuf)
{
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
        memset(LoraDataStruct.LoRaReceArr, 0, sizeof(LoraDataStruct.LoRaReceArr));
    }
    else if(Mode == RSCOMDET)
    {
        if(USART_2.USART_Date[2] == RSCOMDET & 0XF0)
        {
            FlagStruct.RS485TestFlag = RSCOMDET;
        }
        else
        {
            FlagStruct.RS485TestFlag = RSERRDET;
        }
    }
    
}

//*****************************************************************************/
//*函数名 :void Valve_Test(u8 Det)
//*说明   :阀门测试测试
//*参数   :Det        阀门指令，开阀或者关阀
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Valve_Test(u8 Det)
{
    // 发送开关阀指令
    FlagStruct.Key3Flag = FALSE;
    FlagStruct.Key4Flag = FALSE;
    LoraDataArr[0] = 0X01;
    LoraDataArr[1] = 0X00;
    LoraSendData(Det, LoraDataArr, 2);
    Rf1278_ModeSet(128);     // 开启接收
    // 开启定时器开始检测
    MsCount = 0;
    TIM3_Cmd(ENABLE);
    while(MsCount < COUNTNUM)     
    {
        if(FlagStruct.Key3Flag == TRUE || FlagStruct.Key4Flag == TRUE)
        {
            if(FlagStruct.ValveCount == 0X01)
            {
                printf("开阀成功\r\n");
                LEDFlicker(1,2);
                break;
            }
            else if(FlagStruct.ValveCount == 0X02)
            {
                printf("关阀成功\r\n");
                LEDFlicker(2,2);
                break;
            }
        }
    }
    if(MsCount >= 60)   // 判断如果超时则会反馈失败信息
    {
        
        printf("未检测到阀门状态\r\n");
            
    }
    TIM3_Cmd(DISABLE);          // 关闭定时器
    FlagStruct.ValveCount = 0;
//    memset(UpDataArr, 0, sizeof(UpDataArr));    
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
    for(temp = 0; temp < 12; temp++) // 写入命令序列，原地址，目标地址
    {
        LoraDataStruct.LoRaSendArr[temp+2] = CmdAndAddArr[temp];
    }
    LoraDataStruct.LoRaSendArr[14] = Det;       // 需要发送的指令
    for(temp = 0; temp < Buflen; temp++)
    {
        LoraDataStruct.LoRaSendArr[temp+15] = Cbuf[temp];   // 数据位
    }
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 3] = DataCheckArr[0];  // 校验位
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 2] = DataCheckArr[1];
    LoraDataStruct.LoRaSendArr[LORADATALENGTH + Buflen - 1] = LORADATATAIL;     // 帧尾   
    RF1278_SendPacket(LoraDataStruct.LoRaSendArr, LORADATALENGTH+Buflen);       // 通过LORA模块进行发送
    LEDFlicker(0, 1);
    printf("LoRa发送数据为: ");
    PrintArr(LoraDataStruct.LoRaSendArr, LORADATALENGTH+Buflen);
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
        USART_Cmd(USART1,ENABLE);       //使能串口1
        Delay_ms(50);
    }
    if((USART_1.USART_Date[0] == 0X59) || (USART_1.USART_Date[0] == 0x00))   // 检测如果串口1的数据缓存器是否有数据
    {   
        UsartSend(USART1, "R", 1);      // 如果没有就发送R读取传感器的值
        Delay_ms(20);
    }
    Delay_ms(100);
    if(USART_1.Falg == TRUE)   // 当数据接收完成后
    {
        USART_1.Falg = FALSE;
        LEDFlicker(1, 3);   // LED提示
        UpDataArr[0] = METERDET;    // 上传数组0位为计量指令
        UpDataArr[1] = USART_1.USART_Date[3];   //1位为计量值，该值仅为0-255 
        ReturnTestDet(UpDataArr, 2);   // 上传数据(串口3)
        USART_1.Length = 0; // 串口1长度复位
        memset(USART_1.USART_Date, 0, sizeof(USART_1.USART_Date));
    }
    else
    {
        UpDataArr[0] = METERERRDET; // 没收到数据则将上传0设置测试失败指令
        UpDataArr[1] = 0X00;    
        ReturnTestDet(UpDataArr, 2);
    }
}

//*****************************************************************************/
//*函数名 :void RS485_Test(void)
//*说明   :RS485测试
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void RS485_Test(void)
{
    LoraDataArr[0] = 0X00;
    LoraDataArr[1] = 0X00;
    LoraSendData(RSCOMDET, LoraDataArr, 2);
    Rf1278_ModeSet(128);     // 开启接收
    MsCount = 0;
    TIM3_Cmd(ENABLE);
    while(MsCount < COUNTNUM)
    {
        if(USART_2.Falg == 1)
        {
            USART_2.Falg = 0;
            Rece_DataCheck(RSCOMDET, USART_2.USART_Date);
            UpDataArr[0] = FlagStruct.RS485TestFlag;
            UpDataArr[1] = 0X01;
            ReturnTestDet(UpDataArr, 2);
            break;
        }
    }
    if(MsCount >= COUNTNUM)
    {
        UpDataArr[0] = FlagStruct.RS485TestFlag;
        UpDataArr[1] = 0X01;
        ReturnTestDet(UpDataArr, 2);
    }
    TIM3_Cmd(DISABLE);
    MsCount = 0;
    memset(USART_2.USART_Date, 0, sizeof(USART_2.USART_Date));
    USART_2.Length = 0;
}
