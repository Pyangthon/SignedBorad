#ifndef VALVE_PRO_H
#define VALVE_PRO_H

#include "stm8l15x.h"
#include "ht24lc32.h"
#include "TestItems.h"

#define OPEN_TIME   3    //Ĭ�Ͽ���ʱ�� 5s ���ǵ����������
#define CLOSE_TIME  3    //Ĭ�Ϲط�ʱ�� 5s ���ǵ����������

#define OPEN  1
#define CLOSE 0

#define RUN  TRUE
#define STOP FALSE

#define FA_OPEN_GPIO        GPIOG
#define FA_OPEN_GPIO_PIN    GPIO_Pin_4
#define FA_CLOSE_GPIO       GPIOG
#define FA_CLOSE_GPIO_PIN   GPIO_Pin_6


#define FA_OPEN_1()         GPIO_SetBits(FA_OPEN_GPIO, FA_OPEN_GPIO_PIN)
#define FA_OPEN_0()         GPIO_ResetBits(FA_OPEN_GPIO, FA_OPEN_GPIO_PIN)

#define FA_CLOSE_1()        GPIO_SetBits(FA_CLOSE_GPIO, FA_CLOSE_GPIO_PIN)
#define FA_CLOSE_0()        GPIO_ResetBits(FA_CLOSE_GPIO, FA_CLOSE_GPIO_PIN)

#define FA_PORT             GPIOF
#define FA_OPEN_PORT        GPIOF
#define FA_OPEN_PIN         GPIO_Pin_0
#define FA_CLOSE_PORT       GPIOF
#define FA_CLOSE_PIN        GPIO_Pin_1

#define FB_PORT             GPIOB
#define FB_OPEN_PORT        GPIOB
#define FB_OPEN_PIN         GPIO_Pin_6
#define FB_CLOSE_PORT       GPIOB
#define FB_CLOSE_PIN        GPIO_Pin_7
#define VALVE_SLEEP_PIN     GPIO_Pin_5

#define FA_OPEN_H()         GPIO_SetBits(FA_PORT, FA_OPEN_PIN)          // PF0  ����
#define FA_OPEN_L()         GPIO_ResetBits(FA_PORT, FA_OPEN_PIN)
#define FA_CLOSE_H()        GPIO_SetBits(FA_PORT, FA_CLOSE_PIN)
#define FA_CLOSE_L()        GPIO_ResetBits(FA_PORT, FA_CLOSE_PIN)

#define FB_OPEN_H()         GPIO_SetBits(FB_PORT, FB_OPEN_PIN)
#define FB_OPEN_L()         GPIO_ResetBits(FB_PORT, FB_OPEN_PIN)
#define FB_CLOSE_H()        GPIO_SetBits(FB_PORT, FB_CLOSE_PIN)
#define FB_CLOSE_L()        GPIO_ResetBits(FB_PORT, FB_CLOSE_PIN)
#define VALVE_SLEEP_H()     GPIO_SetBits(FB_PORT, VALVE_SLEEP_PIN)
#define VALVE_SLEEP_L()     GPIO_ResetBits(FB_PORT, VALVE_SLEEP_PIN)


/*��ʱ���ṹ��*/
typedef struct
{
  
    uint16_t Time;  /*��ʱʱ�䣬��׼ʱ��1ms*/
        bool Flag; /*��ʱ���ˣ���־λ*/
        
} TypeTimer_T;


/*���Ų����ṹ��*/
typedef struct
{
    unsigned char stu;   //����״̬  
    unsigned char Action;//���Ŷ�����־λ  TRUE �˶� FALSE �˶�ֹͣ
    unsigned char Falg;  //����
    unsigned int  cause; //�ط�ԭ��
    unsigned char Control;//���ſ��Ʋ���  0���ɿ��� 1���ط�����
    unsigned char check; //У��λ
    
} TypeValce_T;


extern TypeValce_T ValveDevice;

extern void ValveStop(u8 ValveNum);
extern void ValveOpen(u8 ValveNum);
//extern void ValveClose(Valve_Cause cause);
extern void ValveClose(u16 cause, u8 ValveNum);
extern void ValveCtrlInit(void);
extern void ValveTimerFun(u8 ValNum);
#endif



