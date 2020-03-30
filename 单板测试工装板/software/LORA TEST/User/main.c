#include "SysInitApp.h"
#include "RS485.h"
#include "Clk.h"
#include "Delay.h"
#include "led.h"
#include "stm8l15x_it.h"
#include "Lora.h"
#include "LoraSpiGpio.h"

u8 JudgeData();

// 测试板程序
void main(void)
{
    u8 send_array[3] = {0x11, 0x22, 0x33};      // 发送数组
    u8 retChe = 0;                              // 接收数据判断标志位
    SysClockInit();                             
    LED_Init();
    LED_Run(4);                                 // 提示系统启动完成
    Delay_ms(300);          
    LED_Off(4);                 
    Delay_ms(100);
    RS485Init();                                // 初始化RS485通信
    Lora_Gpio_Init();                           // LoRa模块GPIO初始化
    if(RF1278_Init(2, 2))                       // 初始化射频模块频道为2，扩频因子为2，并判断是否初始化成功
    {
        LEDFlicker(0, 3);                       // 提示初始化成功
    }
    enableInterrupts(); // 开启中断 
    while(1)
    {
        
        if(retChe == 0)                         // 第一次检测首先向被测板发送测试数据
        {
            RF1278_SendPacket(send_array, 3);
            Delay_ms(1500);
            Rf1278_ModeSet(5);                  // 设置为接收模式
        }
        if(RXFlag == 1)                         // 当被测板接收到数据后返回一段数据，此时判断接收标志位是否置1
        {
            retChe = JudgeData();               // 当接收标志位置1时，调用数据接收判断函数
            if(retChe)                          // 判断数据接收标志位
            {
                LEDFlicker(1, 4);               // 是1则闪烁提示(LED1闪烁4次)
                printf("数据接收成功。");       // 调用485通信重写printf函数打印提示信息 
            }
            else
            {
                LEDFlicker(2,1);                // 不是则LED2闪烁1次
            }
        }
        
    }      
}

u8 JudgeData()
{
    u8 ChackArray[] = {0x00, 0x10, 0xAA};       // 测试数组
    u8 RecArray[3] = {0};                       // 接收数据数组
    u8 chackFre;                                // 
    RF1278_RecePacket(RecArray, 3);
    Delay_ms(300);
    for(chackFre = 0; chackFre < 3; chackFre++) // 判断接收数据是否正常
    {
        if(ChackArray[chackFre] != RecArray[chackFre])  // 数据有不同则立即返回
        {
            break;
        }
    }
    return (chackFre == 3?1:0);     // 判断检查标志位是否等于3，等于3则返回1，否则返回0
}

