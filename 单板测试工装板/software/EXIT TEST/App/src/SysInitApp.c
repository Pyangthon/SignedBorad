#include "SysInitApp.h"

// 测试LoRa模式功能代码

//void LORAModelTest(void)
//{
//    unsigned char RF1278_state;     // 定义存放LoRa状态码
//    unsigned char cbuf[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
//    Lora_Gpio_Init();               // 初始化LoRaGPIO口
//    RF1278_Init(10, 2);             // 初始化LoRa射频
////    RF1278_CadInit(80);
////    RF1278_CadSample();
//    LED_Init();                     // LED初始化
//    // 测试待机模式
////    RF1278_Standby();         // 待机模式正常, LED3亮
//    // 测试射频模式
////    RF1278_EntryLoRa();       
//    // 测试睡眠模式
////    RF1278_Sleep();           // 睡眠模式正常, LED0亮
//    // 测试接收模式
////    Rf1278_ModeSet(10);    '     // 接收模式正常, LED1亮
//    RF1278_SendPacket(cbuf, 10);
//    
//    
//    
//    
//    while(1)
//    {
//        RF1278_state = GetRF1278_State();
//        if(RF1278_state != 0xff)
//        {
////            LED_Run(1);
////            if(RF1278_state == '3'|'2'|'1'|'0')
////            {
////                LED_Run(4);
////            }
//            LED_Run(RF1278_state);
//            
//            
//        }
//        else
//        {
//            
////            LED_Run(4);
//            ;
//        }
//        
//    }
//
//}

void RS485Test(void)
{
    unsigned char RS_Send_Buf[8] = {1};
    Usart2_Module_Init(9600);
    GPIO_Init(RS485_EN_PORT, RS485_EN_PIN, GPIO_Mode_Out_PP_High_Fast);
    
    GPIO_SetBits(RS485_EN_PORT, RS485_EN_PIN);
    
    UsartSend(USART2, RS_Send_Buf, 8);
    
}


//
//void Uart3Config()
//{
//    Usart2_Module_Init(115200);
//    
//    
//}
///***************************************************************************
//* 函数名称: void SPDT_Init(void)
//* 功能  	: 初始化继电器端口，初始化继电器控制的GPIO口
//* 参数  	: None
//* 作者  	:
//* 创建时间: 2020年1月14日
//* 修改时间:
//****************************************************************************1  
void SPDT_Init(void)
{
    GPIO_Init(SPDT_PORT, SPDT_EN_PIN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast);
    
    GPIO_SetBits(SPDT_PORT, SPDT_EN_PIN);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

///***************************************************************************
//* 函数名称: void SysClockInit(void)
//* 功能  	: 初始化时钟，选择内部高速时钟
//* 参数  	: None
//* 作者  	:
//* 创建时间: 2020年1月14日
//* 修改时间:
//****************************************************************************
void SysClockInit(void)
{

    CLK_DeInit();
    /* High speed internal clock prescaler: 1 */
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

    /* Select HSI as system clock source */
    CLK_SYSCLKSourceSwitchCmd(ENABLE);
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);

    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);
}

///***************************************************************************
//* 函数名称: 
//* 功能  	:
//* 参数  	:
//* 作者  	:
//* 创建时间:
//* 修改时间:
//****************************************************************************




