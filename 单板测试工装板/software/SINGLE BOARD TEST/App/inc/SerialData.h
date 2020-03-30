#ifndef __SERIALDATA_H_
#define __SERIALDATA_H_

#include "SysInitApp.h"
#include "LoraTest.h"
// 定义测试指令
#define UPDATACOM       0XA0        // 上传数据开始
#define UPCONFIR        0XF0        // 上传确认指令

#define LORACOM         0XBA        // LoRa通信指令
#define LORAERRDET      0XEA        // LoRa通信错误指令
#define CURRENTDET      0XBC        // 电流检测指令
#define RSCOMDET        0XBE        // RS485通信指令
#define RSERRDET        0XEE        // RS485通信失败指令
#define USARTDET        0XCA        // 串口通信指令
#define SPDTDET         0X11        // 继电器部分检测指令
#define ALLDET          0XAA        // 全检测指令
#define DETERROR        0XAE        // 检测失败指令
#define ERRORCOM        0X55        // 错误指令
#define RESPONSECOM     0XAF        // 启动响应指令
#define CONFIRCOM       0X68        // 确认指令
#define UPCHECKDET      0X00        // 上传校验位
#define DOCHECKDET      0X5F        // 校验指令
#define RESETDET        0XCC        // 复位系统指令
#define MODCONDET       0XCE        // 配置修改指令
#define LORAINITDEF     0XDA        // lora初始化参数修改
#define USART2BAUD      0X02        // 串口2波特率修改
#define USART1BAUD      0X01        // 串口1波特率修改指令
#define VOLTDET         0XDE        // 电压检测指令
#define KEYDET          0XDF        // 按键检测指令
#define INFRAREDDET     0XED        // 红外检测

#define CURRA2MULT      0X32        // 电流放大器A2放大倍数
#define CURRA4MULT      0XC8        // 电流放大器A4放大倍数
#define DEFCOUNTDOWN    300         // 默认全局休眠时间(300S)


// 全局标志位结构体
typedef struct  
{
    u8 LoRaInitFlag;            // LoRa初始化标志位
    u8 LoRaTestFlag;            // LoRa测试标志位
    u8 RS485TestFlag;           // RS485测试标志位
    u8 ReceDataFlag;            // 数据接收次数标志位
    bool Key1Flag;
    bool Key2Flag;
    bool Key3Flag;
    bool Key4Flag;
    u8 FunKeyFlag;              // 功能按键
    u16 SecondFlag;             // 秒数
    bool SPDTIEnFlag;           // 继电器开启标志位
    bool ZeroBiaVoltFlag;       // 零偏电压采集成功标志位
    bool FristVoltTest;         // 第一次采集电压标志位
    bool KeyTestFlag;           // 按键检测标志位
    u8 ValveCount;
}Global_Flag_TypeDef;

typedef struct 
{
    float ZeroBiaVolt0;     // 通道0零偏电压
    float ZeroBiaVolt1;     // 通道1零偏电压
    u8 ZeroBiaVoltThre0;     // 通道0零偏电压基准值 
    u8 ZeroBiaVoltThre1;    // 通道1零偏电压基准值
    
}ADSZeroBiaData_TypeDef;

typedef struct
{
    float Chan0Volt;        // 通道0测试电压
    float Chan1Volt;        // 通道1测试电压
    float Chan0Curr;        // 通道0测试电流
    float Chan1Curr;        // 通道1测试电流
}ADSDATA_TypeDef;

extern Global_Flag_TypeDef FlagStruct;
extern u8 UpDataArr[2];
extern ADSZeroBiaData_TypeDef ADSZBStruct;

// 等待上位机指令
extern void Wait_Implement(void);
// 上传本地测试结果
extern void ReturnTestDet(u8 *Det, u8 Len);
// 电流检测函数
extern void Current_Test(void);
// 系统配置修改函数
extern void ModifyConfig(void);
// 获取电压值
extern void Volt_Test(void);
// 按键检测函数
extern void Key_Test(void);
// 红外检测函数
extern void InfraredTest(void);

#endif

