
#ifndef __TESTITEMS_H_
#define __TESTITEMS_H_

// ����ͷ�ļ�
#include "SysInitApp.h"

// �������ָ��
#define LORACOM     0XBA        // LoRaͨ��ָ��
#define LORAERRDET  0XEA        // LoRaͨ�Ŵ���ָ��
#define CURRENTDET  0XBC        // �������ָ��
#define CURRERRDET  0XEC        // �������ʧ��ָ��
#define KEYDET      0XBD        // �������ָ��
#define RSCOMDET    0XBE        // RS485ͨ��ָ��
#define RSERRDET    0XEE        // RS485ͨ��ʧ��ָ��
#define UARTDET     0XCA        // ����ͨ��ָ��
#define UARTERRDET  0XEB        // ����ͨ��ʧ��ָ�� 
#define SPDTDET     0X11        // �̵������ּ��ָ��
#define ALLDET      0XAA        // ȫ���ָ��
#define DETERROR    0XAE        // ���ʧ��ָ��
#define ERRORCOM    0X55        // ����ָ��
#define RESPONSECOM 0XAF        // ������Ӧָ��
#define CONFIRCOM   0X68        // ȷ��ָ��
#define UPDATACOM   0XA0        // �ϴ����ݿ�ʼ
#define UPCONFIR    0XF0        // �ϴ�ȷ��ָ��
#define EMPTYDET    0X00        // ��ָ��
#define CHECKDET    0X5F        // У��ָ��

#define COUNTNUM    60         // Ĭ�ϼ���ʱ��


// ȫ�ֱ�־λ�ṹ��
typedef struct  
{
    u8 LoRaInitFlag;        // LoRa��ʼ����־λ
    u8 LoRaTestFlag;        // LoRa���Ա�־λ
    u8 LoRaRXFlag;          // LoRa�����жϱ�־λ
    u8 RS485TestFlag;       // RS485���Ա�־λ
    u8 ReceDataFlag;        // ���ݽ��մ�����־λ
    u8 Key1Flag;            // ����1
    u8 Key2Flag;            // ����2
    u8 Key3Flag;            // ����3
    u8 Key4Flag;            // ����4 
    u8 FunKeyFlag;          // ���ܰ���
    u16 SecondFlag;         // ����
}Global_Flag_TypeDef;

// ����ȫ�ֱ���
extern Global_Flag_TypeDef MyFlagSturct;

extern u8 LoRa_Str1[];
extern u8 LoRa_Str2[];

// �ȴ���λ��ָ��
extern void Wait_Implement(void);
// �ϴ����ز��Խ��
extern void ReturnTestDet(u8 Det);
// LoRa���Ժ���
extern void LoRa_Test(void);
// ����У�麯��
extern void Rece_DataCheck(u8 Mode);
// RS485���Ժ���
extern void RS485_Test(void);
// IOͨ�ϲ��Ժ���
extern void Key_Test(void);
// ����Ч������
extern u8 Key_Scan(void);
extern void RS485_Rece(void);
#endif