// 该文件下是整个单板工装测试板的测试代码

//引入头文件
#include "TestItems.h"

// 定义全局变量
Global_Flag_TypeDef MyFlagSturct = {0};

bool Flag_PA3 = FALSE;


//*****************************************************************************/
//*函数名 :void Wait_Implement(void)
//*说明   :等待上位机下发的数据，判断指定位的数据，进入指定的函数执行
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Wait_Implement(void)
{
    
    if(USART_3.Falg != FALSE)   // 判断是否有数据收到,判断串口3接收标志位的值
    {
        
        if(USART_3.USART_Date[2] == CHECKDET)       // 判断校验位
        {
           
            switch(USART_3.USART_Date[1]) // 选择需要执行的函数
            {   
            case LORACOM:
               
                LoRa_Test();    // 进入LoRa测试函数
                break;
                
            case CURRENTDET:    // 电流测试函数，硬件缺失
                
                break;
            case KEYDET:
               
                Key_Test();     // IO通断测试函数
                break;
            case RSCOMDET:
               
                RS485_Test();   // RS485通信测试函数
                break;
                    
            default:
               
                ReturnTestDet(ERRORCOM); // 非已定义的测试指令
                break;
                    
            }
        }      
    }
    if(MyFlagSturct.FunKeyFlag == 1)
    {
        MyFlagSturct.FunKeyFlag = 0;
        LED_Off(4);
        memset(USART_3.USART_Date, 0, sizeof(USART_3.USART_Date));
        memset(USART_2.USART_Date, 0, sizeof(USART_2.USART_Date));
        USART_3.Falg = 0;
        USART_2.Falg = 0;
        USART_3.Length = 0;
        USART_2.Length = 0;
        USART_3.USART_Halt_Falg = 0;
        USART_3.USART_Halt_Falg = 0;
    }
    
}

//*****************************************************************************/
//*函数名 :void ReturnTestDet(u8 det)
//*说明   :上传测试结果
//*说明   :第三位为校验位，默认0x00
//*参数   :Det    测试结果指令
//*返回值 :无
//*作者   :
//*****************************************************************************/
void ReturnTestDet(u8 Det)
{
    
    u8 UploadDetArr[4] = {0};       // 定义上传数组,4个数据
    UploadDetArr[0] = UPDATACOM;    // 上传数据开始位
    UploadDetArr[3] = UPCONFIR;     // 上传数据结束位   
    UploadDetArr[1] = Det;          // 实际的测试数据指令   
    UsartSend(USART3, UploadDetArr, 4);
//    UsartSend(USART3, "\r\n", 2);
    
}


//*****************************************************************************/
//*函数名 :void LoRa_Test(void)
//*说明   :LoRa模块测试函数
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void LoRa_Test(void)
{ 
//    // 串口提示数组
//    u8 LoRa_Str1[] = {"LoRa Initialization successful!\r\n"};
//    u8 LoRa_Str2[] = {"LoRa Startup failure!\r\n"};
//    u8 LoRa_Send_DataArr[5] = {0x01, 0x03, 0x05, 0x07, 0x09};   // LoRa发送数据数组   
//    if(MyFlagSturct.LoRaInitFlag == FALSE)
//    {
//        if(RF1278_Init(2, 2))
//        {
//            MyFlagSturct.LoRaInitFlag = TRUE;   // LoRa射频初始化标志位置1
//            UsartSend(USART3, LoRa_Str1, 34);
//        }
//        else
//        {           
//            UsartSend(USART3, LoRa_Str2, 23);             // 串口输出测试LoRa模块初始化失败,LoRa测试结束
//        }      
//    }
//    
//    if(MyFlagSturct.LoRaInitFlag == TRUE)       // 判断初始化是否成功
//    {        
//        RF1278_SendPacket(LoRa_Send_DataArr, 5);   
//        
//        Rf1278_ModeSet(50);     // 开启接收       
//        TIM3_Cmd(ENABLE);   // 开启定时器4
//        MsCount = 0;      // 复位计数器
//        while(MsCount < COUNTNUM)     // 等待三秒，接收数据
//        {
//            if(MyFlagSturct.LoRaRXFlag == 1)
//            {
//                Rece_DataCheck(LORACOM);
//                if(MyFlagSturct.ReceDataFlag == 5)    // 接收到数据后，判断数据的正确性 
//                {
//                    MyFlagSturct.LoRaTestFlag = LORACOM;
//                    MyFlagSturct.LoRaRXFlag = 0;
//                    LED0_L();
//                }
//                else
//                {
//                    MyFlagSturct.LoRaTestFlag = LORAERRDET;
//                    MyFlagSturct.LoRaRXFlag = 0;
//                }
//                
//                ReturnTestDet(MyFlagSturct.LoRaTestFlag);   // 上传LORA测试的结果
//                memset(USART_3.USART_Date,0,sizeof(USART_3.USART_Date));                // 清除串口3数据缓存器                
//                TIM3_Cmd(DISABLE);  // 关闭定时器2
//                MsCount = 0;      // 计数时间标志位清0
//                break;
//            }
//        } 
//        if(MsCount == COUNTNUM)
//        {
//            MsCount = 0;
//            MyFlagSturct.LoRaTestFlag = LORAERRDET;
//            MyFlagSturct.LoRaRXFlag = 0;
//            ReturnTestDet(MyFlagSturct.LoRaTestFlag);   // 上传LORA测试的结果
//            memset(USART_3.USART_Date,0,sizeof(USART_3.USART_Date));                // 清除串口3数据缓存器                
//            TIM3_Cmd(DISABLE);  // 关闭定时器2
//        }
////        if(MyFlagSturct.LoRaRXFlag == 0)
////        {
////            TIM3_Cmd(DISABLE);
////            MsCount = 0;
////            
////        }
//    }    
}
//*****************************************************************************/
//*函数名 :void _Rece_DataCheck(u8 Mode)
//*说明   :接收数据校验函数
//*参数   :mode    选择接收模式
//*返回值 :DataVar 校验成功次数(0-5之间)
//*作者   :
//*****************************************************************************/
void Rece_DataCheck(u8 Mode)
{
    u8 Data_Array[] = {0xff, 0xfe, 0xfd, 0xfc, 0xfb};   // 本地比较数组                        
    
    u8 Rece_DataArr[5] = {0};   // LoRa接收数据数组
        
    u8 DataVar; // 控制循环变量
    if(Mode == LORACOM) // LoRa
    {
        
//        RF1278_RecePacket(Rece_DataArr, 5);// 调用LoRa接收数据函数
    }
    else if(Mode == RSCOMDET)   // RS485
    {
        for(DataVar = 0; DataVar < 5; DataVar++)
        {
            Rece_DataArr[DataVar] = USART_2.USART_Date[DataVar];
        }
    }
    
    for(DataVar = 0; DataVar < 5; DataVar++)    // 与本地数据做5次比较
    {
        
         if(Rece_DataArr[DataVar] != Data_Array[DataVar])   // 判断本地数据与接收的数据是否相等
         {  
             break;// 若不相等直接结束本次LoRa测试
         }
         
    }
    MyFlagSturct.ReceDataFlag = DataVar; 
    
}

//*****************************************************************************/
//*函数名 :void RS485_Test(void)
//*说明   :RS485测试函数, 发出一段数据，然后等待接收
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void RS485_Test(void)
{
    
    // 发送数组
    u8 RS_SendArr[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee};
    // 发送数据
    RS485_Send(RS_SendArr, 5);
    // 开启定时器2
    TIM3_Cmd(ENABLE);
    // 等待三秒，接收数据
    while(MsCount < COUNTNUM)
    {
        if(USART_2.Length != 0)
        {
            Rece_DataCheck(RSCOMDET);
            
           if(MyFlagSturct.ReceDataFlag == 5)
           {
               MyFlagSturct.RS485TestFlag = RSCOMDET;
               LED1_L();
           }
           else
           {
               MyFlagSturct.RS485TestFlag = DETERROR;
           }
           ReturnTestDet(MyFlagSturct.RS485TestFlag);
           memset(USART_2.USART_Date,0,sizeof(USART_2.USART_Date));       // 清除串口2 
           TIM3_Cmd(DISABLE);// 关闭定时器1
           MsCount = 0;
           break;      
        }
    } 
    if(MsCount == COUNTNUM)
    {
        MsCount = 0;
        TIM3_Cmd(DISABLE);
        memset(USART_2.USART_Date, 0, sizeof(USART_2.USART_Date));
    }
}


//*****************************************************************************/
//*函数名 :void Key_Test(void)
//*说明   :IO通断测试
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Key_Test(void)
{
    u8 ReturnDat = 0x00; 
    Key_Init(0);    // 将按键初始化为上拉无中断输入
    ReturnDat = Key_Scan();
//    if(ReturnDat != 0)
//    {
        USART_3.Length = 0;
        memset(USART_3.USART_Date,0,sizeof(USART_3.USART_Date));       // 清除串口2 
        USART_3.Falg = 0;
//    }
    LED1_L();
    if(ReturnDat != 0)
    {
        if(MyFlagSturct.Key1Flag != 0)
        {
            ReturnTestDet(MyFlagSturct.Key1Flag);
        }
        if(MyFlagSturct.Key2Flag != 0)
        {
            ReturnTestDet(MyFlagSturct.Key2Flag);
        }
        if(MyFlagSturct.Key3Flag != 0)
        {
            ReturnTestDet(MyFlagSturct.Key3Flag);
        }
        if(MyFlagSturct.Key4Flag != 0)
        {
            ReturnTestDet(MyFlagSturct.Key4Flag);
        }
    }
    else
    {
        ReturnTestDet(ReturnDat);
    }
}

//*****************************************************************************/
//*函数名 :u8 Key_Scan(void)
//*说明   :按键检测函数，当按键被按下时，LED灯会亮起，按键松开是LED灯熄灭
//*参数   :无
//*返回值 :Count   本次IO通断测试总次数
//*作者   :
//*****************************************************************************/
u8 Key_Scan(void)
{
    // 通断次数统计
    u8 Count = 0X00;
    u16 CurrentTime;
    MsCount = 0;
    // 复位按键标志位
    MyFlagSturct.Key1Flag = 0;
    MyFlagSturct.Key2Flag = 0;
    MyFlagSturct.Key3Flag = 0;
    MyFlagSturct.Key4Flag = 0;
    TIM3_Cmd(ENABLE);
    
    while(MsCount <= COUNTNUM)
    {
        CurrentTime = MsCount;
        if(READ_KEY1() == RESET)
        {
            
            if((MsCount >= (CurrentTime+1)) && (READ_KEY1() == RESET))
            {                
                MyFlagSturct.Key1Flag++;
                Count = 1;
                while(READ_KEY1() == RESET);                 
            }
        }        
        else if(READ_KEY2()  == RESET)
        {
            
            if((MsCount >= (CurrentTime+1)) && (READ_KEY2() == RESET))
            {
                MyFlagSturct.Key2Flag++;
                Count = 1;
                while(READ_KEY2() == RESET);
            }
        }
        
        else if(READ_KEY3()  == RESET)
        {
            
            if((MsCount >= (CurrentTime+1)) && (READ_KEY3() == RESET))
            {
               
                MyFlagSturct.Key3Flag++;
                Count = 1;
                while(READ_KEY3() == RESET);
                 
            }
        }
        else if(READ_KEY4()  == RESET)
        {
            
            if((MsCount >= (CurrentTime+1)) && (READ_KEY4() == RESET))
            {
                MyFlagSturct.Key4Flag++;
                Count = 1;
                while(READ_KEY4() == RESET);
            }
        }
    }
    return Count;
}


void RS485_Rece(void)
{
    u8 RS_Arr[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee};
    u8 RSDataLen = 0;
    RS_EN_RX();
    if(USART_2.Length != 0)
    {
        for(;RSDataLen < USART_2.Length; RSDataLen++)
        {
            if(RS_Arr[RSDataLen] != USART_2.USART_Date[RSDataLen])
            {
                break;
            }
        }
        
//        ReturnTestDet(MyFlagSturct.RS485TestFlag);
        
    }
    if((RSDataLen == USART_2.Length) && (RSDataLen != 0))
        {
//            MyFlagSturct.RS485TestFlag = RSCOMDET;
            RS485_Send(RS_Arr, 6);
            LED2_L();
        }
        else
        {
            MyFlagSturct.RS485TestFlag = RSERRDET;
        }
    if(USART_2.Length != 0)
    {
        USART_2.Length = 0;
        memset(USART_2.USART_Date, 0, sizeof(USART_2.USART_Date));
    }
    
}