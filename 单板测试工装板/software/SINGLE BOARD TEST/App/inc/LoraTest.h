#ifndef __TESTITEMS_H_
#define __TESTITEMS_H_

// ����ͷ�ļ�
#include "SysInitApp.h"

#define LORADATAHEAD    0X68        // LORA����֡ͷ
#define LORADATATAIL    0XEE        // LORA����֡β
#define LORATEST        0X31        // LORA����ָ��
#define LORADEFSIZE     0X02        // LORA����Ĭ�ϳ���
#define METERDET        0XCB        // ����ָ��
#define METERERRDET     0XCD        // ��������ʧ��ָ��

#define OPENVALVE       0XB1        // ����
#define CLOSEVALVE      0XB2        // �ط�

#define OPENVALVEA      0X01        // ����1
#define CLOSEVALVEA     0X02        // �ط�1
#define OPENVALVEB      0X03        // ����2
#define CLOSEVALVEB     0X04        // �ط�2
#define CTRVALERR       0X10        // ����������ʧ��ָ��

#define LORADATAERR     0XEB        // Lora�������ݴ���
#define LORADATALENGTH  0X12        // ��������Ĭ�ϳ���
#define COUNTNUM        60          // Ĭ�ϼ���ʱ��
#define LORADEFRRSI     70          // Ĭ��LORA������ֵ

typedef struct
{
    bool Valve1State;               // ����1״̬
    bool Valve2State;               // ����2״̬
}Valve_TypeDef;

typedef struct
{
    bool LoRaRXFlag;                // Lora���ձ�־λ
    u8 LoRaReceArr[25];             // Lora��������
    u8 LoRaSendArr[25];             // Lora��������
    u8 LoRaCmd;                     // Lora����
    u8 LoRaData[2];                 // Lora��������
    u8 LoRaCheck[2];                // LoraУ��λ����   
    u8 LoRaRrsi;                    // Lora������ֵ
    u8 LoRaChan;                    // Lora�ŵ�
    u8 LoRaSF;                      // Lora��Ƶ����
}Lora_TypeDef;

// ����ȫ�ֱ���
extern Valve_TypeDef ValveStruct;       // ���ؽṹ��
extern Lora_TypeDef LoraDataStruct;     // Lora���ƽṹ��
extern u8 DataCheckArr[2];              // Lora����У������
extern u8 LoraDataArr[LORADEFSIZE];     // Lora��������
extern u8 CmdAndAddArr[12];             // ����͵�ַ����
// LoRa����
extern void LoRa_Test(void);
// ����У��
extern void Rece_DataCheck(u8 Mode, u8 *Cbuf);
// IOͨ�ϲ���
extern void Valve_Test(u8 Det);
// Loraָ���
extern void LoraSendData(u8 Det, u8 *Cbuf, u8 Buflen);
// ��������
extern void Meter_Test(void);
// RS485���Ժ���
extern void RS485_Test(void);

#endif


