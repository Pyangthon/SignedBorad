
#ifndef __TESTITEMS_H_
#define __TESTITEMS_H_

// 引入头文件
#include "SysInitApp.h"

// 定义测试指令
#define LORACOM     0XBA        // LoRa通信指令
#define LORAERRDET  0XEA        // LoRa通信错误指令
#define CURRENTDET  0XBC        // 电流检测指令
#define CURRERRDET  0XEC        // 电流检测失败指令
#define KEYDET      0XBD        // 按键检测指令
#define RSCOMDET    0XBE        // RS485通信指令
#define RSERRDET    0XEE        // RS485通信失败指令
#define UARTDET     0XCA        // 串口通信指令
#define UARTERRDET  0XEB        // 串口通信失败指令 
#define SPDTDET     0X11        // 继电器部分检测指令
#define ALLDET      0XAA        // 全检测指令
#define DETERROR    0XAE        // 检测失败指令
#define ERRORCOM    0X55        // 错误指令
#define RESPONSECOM 0XAF        // 启动响应指令
#define CONFIRCOM   0X68        // 确认指令
#define UPDATACOM   0XA0        // 上传数据开始
#define UPCONFIR    0XF0        // 上传确认指令
#define EMPTYDET    0X00        // 空指令
#define CHECKDET    0X5F        // 校验指令

#define COUNTNUM    60         // 默认计数时长


// 全局标志位结构体
typedef struct  
{
    u8 LoRaInitFlag;        // LoRa初始化标志位
    u8 LoRaTestFlag;        // LoRa测试标志位
    u8 LoRaRXFlag;          // LoRa接收中断标志位
    u8 RS485TestFlag;       // RS485测试标志位
    u8 ReceDataFlag;        // 数据接收次数标志位
    u8 Key1Flag;            // 按键1
    u8 Key2Flag;            // 按键2
    u8 Key3Flag;            // 按键3
    u8 Key4Flag;            // 按键4 
    u8 FunKeyFlag;          // 功能按键
    u16 SecondFlag;         // 秒数
    u8 FunFlag;             // 功能按键
    bool KeyState;          // 按键状态
}Global_Flag_TypeDef;

// 声明全局变量
extern Global_Flag_TypeDef MyFlagSturct;

extern u8 LoRa_Str1[];
extern u8 LoRa_Str2[];
extern bool Flag_PA3;
// 等待上位机指令
extern void Wait_Implement(void);
// 上传本地测试结果
extern void ReturnTestDet(u8 Det);
// LoRa测试函数
extern void LoRa_Test(void);
// 数据校验函数
extern void Rece_DataCheck(u8 Mode);
// RS485测试函数
extern void RS485_Test(void);
// IO通断测试函数
extern void Key_Test(void);
// 按键效果处理
extern u8 Key_Scan(void);
extern void RS485_Rece(void);
#endif