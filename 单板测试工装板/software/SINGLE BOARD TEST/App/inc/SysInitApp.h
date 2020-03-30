#ifndef __SYS_INIT_APP_H_
#define __SYS_INIT_APP_H_

#include "stm8l15x_gpio.h"
#include "usart.h"
#include "Lora.h"
#include "LoraSpiGpio.h"
#include "Clk.h"
#include "Delay.h"
#include "led.h"
#include "RS485.h"
#include "ADS1115.h"
#include "key.h"
#include "stm8l15x_tim2.h"
#include "Mcuconfig.h"
#include "SerialData.h"
#include "Adc.h"



// 定义PB0-3初始化端口模式, SET 高速推挽输出模式， RESET 上拉输入模式
#define PB_LSB_MODE     1

// 定义继电器控制脚
#define SPDT_PORT        GPIOC
#define SPDT_EN_PIN      GPIO_Pin_7

// 宏定义继电器控制函数
// 继电器关闭
#define SPDT_EN_OFF()     GPIO_ResetBits(SPDT_PORT, SPDT_EN_PIN)
// 继电器开启
#define SPDT_EN_ON()      GPIO_SetBits(SPDT_PORT, SPDT_EN_PIN)

extern u16 MsCount;
extern u16 SceCount;
extern u16 CountDown;
extern bool HaltState;
// 继电器初始化
extern void SPDT_Init(void);
// 继电器控制端口初始化
extern void SPDT_Ctrl_Port_Init(void);
// 外设硬件初始化函数
extern void System_Init(void);
// GPIO配置函数
extern void GPIO_Init_Config(void);
// 写入Lora默认参数
extern void WriteLoraDef(void);
// 设置系统串口参数位空
extern void ResetDefault(void);
// 测试零偏电压
extern bool ZeroBisVoltTset(u8 State);
// 打印数组
extern void PrintArr(u8 *Arr,int Length);
// 休眠配置
extern void Dormancy(void);
// 配置GPIO为空载状态
extern void DisableGPIO(void);
// 关闭所有时钟
extern void DisableCLK(void);
// 配置零偏电压相关参数
extern void ZeroBiaVoltConfig(void);
#endif

