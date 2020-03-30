#ifndef __TESTITEMS_H_
#define __TESTITEMS_H_

// 引入头文件
#include "SysInitApp.h"

#define LORADATAHEAD    0X68        // LORA数据帧头
#define LORADATATAIL    0XEE        // LORA数据帧尾
#define LORATEST        0X31        // LORA测试指令
#define LORADEFSIZE     0X02        // LORA数据默认长度
#define METERDET        0XCB        // 计量指令
#define METERERRDET     0XCD        // 计量测试失败指令

#define OPENVALVE       0XB1        // 开阀
#define CLOSEVALVE      0XB2        // 关阀

#define OPENVALVEA      0X01        // 开阀1
#define CLOSEVALVEA     0X02        // 关阀1
#define OPENVALVEB      0X03        // 开阀2
#define CLOSEVALVEB     0X04        // 关阀2
#define CTRVALERR       0X10        // 阀控器控制失败指令

#define LORADATAERR     0XEB        // Lora测试数据错误
#define LORADATALENGTH  0X12        // 除数据外默认长度
#define COUNTNUM        60          // 默认计数时长
#define LORADEFRRSI     70          // 默认LORA灵敏度值

typedef struct
{
    bool Valve1State;               // 阀门1状态
    bool Valve2State;               // 阀门2状态
}Valve_TypeDef;

typedef struct
{
    bool LoRaRXFlag;                // Lora接收标志位
    u8 LoRaReceArr[25];             // Lora接收数组
    u8 LoRaSendArr[25];             // Lora发送数组
    u8 LoRaCmd;                     // Lora命令
    u8 LoRaData[2];                 // Lora数据数组
    u8 LoRaCheck[2];                // Lora校验位数组   
    u8 LoRaRrsi;                    // Lora灵敏度值
    u8 LoRaChan;                    // Lora信道
    u8 LoRaSF;                      // Lora扩频因子
}Lora_TypeDef;

// 声明全局变量
extern Valve_TypeDef ValveStruct;       // 阀控结构体
extern Lora_TypeDef LoraDataStruct;     // Lora控制结构体
extern u8 DataCheckArr[2];              // Lora数据校验数组
extern u8 LoraDataArr[LORADEFSIZE];     // Lora数据数组
extern u8 CmdAndAddArr[12];             // 命令和地址数组
// LoRa测试
extern void LoRa_Test(void);
// 数据校验
extern void Rece_DataCheck(u8 Mode, u8 *Cbuf);
// IO通断测试
extern void Valve_Test(u8 Det);
// Lora指令发送
extern void LoraSendData(u8 Det, u8 *Cbuf, u8 Buflen);
// 计量测试
extern void Meter_Test(void);
// RS485测试函数
extern void RS485_Test(void);

#endif


