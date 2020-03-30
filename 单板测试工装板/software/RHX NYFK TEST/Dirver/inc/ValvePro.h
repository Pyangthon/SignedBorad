#ifndef VALVE_PRO_H
#define VALVE_PRO_H

#include "stm8l15x.h"
#include "ht24lc32.h"
#include "TestItems.h"

#define OPEN_TIME   3    //默认开阀时间 5s 考虑到电量低情况
#define CLOSE_TIME  3    //默认关阀时间 5s 考虑到电量低情况

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

#define FA_OPEN_H()         GPIO_SetBits(FA_PORT, FA_OPEN_PIN)          // PF0  开阀
#define FA_OPEN_L()         GPIO_ResetBits(FA_PORT, FA_OPEN_PIN)
#define FA_CLOSE_H()        GPIO_SetBits(FA_PORT, FA_CLOSE_PIN)
#define FA_CLOSE_L()        GPIO_ResetBits(FA_PORT, FA_CLOSE_PIN)

#define FB_OPEN_H()         GPIO_SetBits(FB_PORT, FB_OPEN_PIN)
#define FB_OPEN_L()         GPIO_ResetBits(FB_PORT, FB_OPEN_PIN)
#define FB_CLOSE_H()        GPIO_SetBits(FB_PORT, FB_CLOSE_PIN)
#define FB_CLOSE_L()        GPIO_ResetBits(FB_PORT, FB_CLOSE_PIN)
#define VALVE_SLEEP_H()     GPIO_SetBits(FB_PORT, VALVE_SLEEP_PIN)
#define VALVE_SLEEP_L()     GPIO_ResetBits(FB_PORT, VALVE_SLEEP_PIN)


/*定时器结构体*/
typedef struct
{
  
    uint16_t Time;  /*定时时间，基准时间1ms*/
        bool Flag; /*定时到了，标志位*/
        
} TypeTimer_T;


/*阀门参数结构体*/
typedef struct
{
    unsigned char stu;   //阀门状态  
    unsigned char Action;//阀门动作标志位  TRUE 运动 FALSE 运动停止
    unsigned char Falg;  //阀门
    unsigned int  cause; //关阀原因
    unsigned char Control;//阀门控制参数  0：可开阀 1：关阀控制
    unsigned char check; //校验位
    
} TypeValce_T;


extern TypeValce_T ValveDevice;

extern void ValveStop(u8 ValveNum);
extern void ValveOpen(u8 ValveNum);
//extern void ValveClose(Valve_Cause cause);
extern void ValveClose(u16 cause, u8 ValveNum);
extern void ValveCtrlInit(void);
extern void ValveTimerFun(u8 ValNum);
#endif



