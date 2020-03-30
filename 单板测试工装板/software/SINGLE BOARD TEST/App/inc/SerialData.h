#ifndef __SERIALDATA_H_
#define __SERIALDATA_H_

#include "SysInitApp.h"
#include "LoraTest.h"
// �������ָ��
#define UPDATACOM       0XA0        // �ϴ����ݿ�ʼ
#define UPCONFIR        0XF0        // �ϴ�ȷ��ָ��

#define LORACOM         0XBA        // LoRaͨ��ָ��
#define LORAERRDET      0XEA        // LoRaͨ�Ŵ���ָ��
#define CURRENTDET      0XBC        // �������ָ��
#define RSCOMDET        0XBE        // RS485ͨ��ָ��
#define RSERRDET        0XEE        // RS485ͨ��ʧ��ָ��
#define USARTDET        0XCA        // ����ͨ��ָ��
#define SPDTDET         0X11        // �̵������ּ��ָ��
#define ALLDET          0XAA        // ȫ���ָ��
#define DETERROR        0XAE        // ���ʧ��ָ��
#define ERRORCOM        0X55        // ����ָ��
#define RESPONSECOM     0XAF        // ������Ӧָ��
#define CONFIRCOM       0X68        // ȷ��ָ��
#define UPCHECKDET      0X00        // �ϴ�У��λ
#define DOCHECKDET      0X5F        // У��ָ��
#define RESETDET        0XCC        // ��λϵͳָ��
#define MODCONDET       0XCE        // �����޸�ָ��
#define LORAINITDEF     0XDA        // lora��ʼ�������޸�
#define USART2BAUD      0X02        // ����2�������޸�
#define USART1BAUD      0X01        // ����1�������޸�ָ��
#define VOLTDET         0XDE        // ��ѹ���ָ��
#define KEYDET          0XDF        // �������ָ��
#define INFRAREDDET     0XED        // ������

#define CURRA2MULT      0X32        // �����Ŵ���A2�Ŵ���
#define CURRA4MULT      0XC8        // �����Ŵ���A4�Ŵ���
#define DEFCOUNTDOWN    300         // Ĭ��ȫ������ʱ��(300S)


// ȫ�ֱ�־λ�ṹ��
typedef struct  
{
    u8 LoRaInitFlag;            // LoRa��ʼ����־λ
    u8 LoRaTestFlag;            // LoRa���Ա�־λ
    u8 RS485TestFlag;           // RS485���Ա�־λ
    u8 ReceDataFlag;            // ���ݽ��մ�����־λ
    bool Key1Flag;
    bool Key2Flag;
    bool Key3Flag;
    bool Key4Flag;
    u8 FunKeyFlag;              // ���ܰ���
    u16 SecondFlag;             // ����
    bool SPDTIEnFlag;           // �̵���������־λ
    bool ZeroBiaVoltFlag;       // ��ƫ��ѹ�ɼ��ɹ���־λ
    bool FristVoltTest;         // ��һ�βɼ���ѹ��־λ
    bool KeyTestFlag;           // ��������־λ
    u8 ValveCount;
}Global_Flag_TypeDef;

typedef struct 
{
    float ZeroBiaVolt0;     // ͨ��0��ƫ��ѹ
    float ZeroBiaVolt1;     // ͨ��1��ƫ��ѹ
    u8 ZeroBiaVoltThre0;     // ͨ��0��ƫ��ѹ��׼ֵ 
    u8 ZeroBiaVoltThre1;    // ͨ��1��ƫ��ѹ��׼ֵ
    
}ADSZeroBiaData_TypeDef;

typedef struct
{
    float Chan0Volt;        // ͨ��0���Ե�ѹ
    float Chan1Volt;        // ͨ��1���Ե�ѹ
    float Chan0Curr;        // ͨ��0���Ե���
    float Chan1Curr;        // ͨ��1���Ե���
}ADSDATA_TypeDef;

extern Global_Flag_TypeDef FlagStruct;
extern u8 UpDataArr[2];
extern ADSZeroBiaData_TypeDef ADSZBStruct;

// �ȴ���λ��ָ��
extern void Wait_Implement(void);
// �ϴ����ز��Խ��
extern void ReturnTestDet(u8 *Det, u8 Len);
// ������⺯��
extern void Current_Test(void);
// ϵͳ�����޸ĺ���
extern void ModifyConfig(void);
// ��ȡ��ѹֵ
extern void Volt_Test(void);
// ������⺯��
extern void Key_Test(void);
// �����⺯��
extern void InfraredTest(void);

#endif

