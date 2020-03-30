#ifndef __TESTITEMS_H_
#define __TESTITEMS_H_

#include "Delay.h"
#include "key.h"
#include "led.h"
#include "Lora.h"
#include "usart.h"
#include "LoraSpiGpio.h"
#include "Clk.h"
#include "ValvePro.h"
#include "RS485.h"
#include "stm8l15x_adc.h"
#include "CRC16.h"

#define LORADATAHEAD    0X68
#define LORADATATAIL    0XEE
#define LORADATACHECK   0X5F
#define LORATEST        0X31
#define LORAARRSIZE     0X02
#define RSCOMDET        0XBE

#define LORADATAERR     0XEB

#define LORADATALENGTH  0X12

#define OPENVALVE       0XB1
#define CLOSEVALVE      0XB2

#define VALVEA          0X01
#define VALVEB          0X02


typedef struct
{
    bool LoRaRXFlag;        // Lora接收标志位
    u8 LoRaReceArr[25];     // Lora接收数组         
    u8 LoRaSendArr[25];     // Lora发送数组
    u8 LoRaCmd;             // Lora命令
    u8 LoRaData[2];         // Lora数据数组
    u8 LoRaCheck[2];        // Lora校验位数组    
}Lora_TypeDef;

extern const u8 CmdSerNumArr[4];
extern const u8 TargetAddArr[4];
extern const u8 SourceAddArr[4];
extern const u8 DataCheckArr[2];

extern Lora_TypeDef LoraDataStruct;
extern void LoRaDataManage(void);
extern void LoraSendData(u8 Det, u8 *Cbuf, u8 Buflen);
extern void System_Init(void);
extern void WriteLoraDef(void);
extern void RS485Test(void);

#endif
