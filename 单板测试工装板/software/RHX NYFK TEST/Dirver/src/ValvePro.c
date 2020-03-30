#include "ValvePro.h"

TypeTimer_T ValveOpenTimer;     //开阀定时器
TypeTimer_T ValveCloseTimer;    //关阀定时器
TypeValce_T ValveDevice;        //定义阀门设备


/*******************************************************************************
*函数名:void ValveStop()
*功能:停止关阀/开阀控制
*输入:无
*输出:无
*备注:无
*******************************************************************************/
void ValveStop(u8 ValveNum)
{
//    FA_OPEN_0();
//    FA_CLOSE_0();
    if(ValveNum == 1)
    {
        FA_OPEN_L();
        FA_CLOSE_L();
    }
    else if(ValveNum == 2)
    {
        FB_OPEN_L();
        FB_CLOSE_L();
    }
}

/*******************************************************************************
*函数名:void ValveTimerFun()
*功能:阀门控制定时器
*输入:无
*输出:无
*备注:无
*******************************************************************************/
void ValveTimerFun(u8 ValNum)
{
    //开阀定时器相关操作
    while(ValveOpenTimer.Time > 0)
    {
        ValveOpenTimer.Time--;
        Delay_ms(600);
        if(ValveOpenTimer.Time == 0)
        {
           if(ValNum == 1)
            {
                ValveStop(1);	        //停止阀门控制
            }
            else
            {
                ValveStop(2);
            }

            ValveDevice.Action = FALSE; //阀门动作停止
        }
    }
    //关阀定时器相关操作
    while(ValveCloseTimer.Time > 0)
    {
        ValveCloseTimer.Time--;
        Delay_ms(600);
        if(ValveCloseTimer.Time == 0)
        {
            if(ValNum == 1)
            {
                ValveStop(1);	        //停止阀门控制
            }
            else
            {
                ValveStop(2);
            }
            ValveDevice.Action = FALSE; //阀门动作停止
        }
    }
}

/*******************************************************************************
*函数名:void ValveClose(Valve_Cause cause)
*功能:关阀
*输入:no:1  复位关阀
         0  故障关阀
*输出:无
*备注:无
*******************************************************************************/
// void ValveClose(Valve_Cause cause)
void ValveClose(u16 cause, u8 ValveNum)
{   
    Delay_ms(500);
    switch(ValveNum)
    {
    case 1:    
        FA_CLOSE_H();FA_OPEN_L();
        break;
    case 2:
        FB_CLOSE_H();FB_OPEN_L();
        break;
    default:
        FA_CLOSE_H();FA_OPEN_L();
        FB_CLOSE_H();FB_OPEN_L();
        break;
    }
      ValveCloseTimer.Time = CLOSE_TIME;
      ValveCloseTimer.Flag = TRUE;
      ValveOpenTimer.Flag = FALSE;
      
      ValveOpenTimer.Time = 0;
      ValveOpenTimer.Flag = FALSE;

      ValveDevice.Action = RUN;;//关阀动作 
      ValveDevice.stu = FALSE; //关阀标志位
      ValveDevice.cause = cause;
      ValveTimerFun(ValveNum);
//      EepromWriteData(ValveAdd, (u8*)&ValveDevice, sizeof(TypeValce_T));  
}

/*******************************************************************************
*函数名:void ValveOpen(void)
*功能:开阀
*输入:无
*输出:无
*备注:无
*******************************************************************************/
void ValveOpen(u8 ValveNum)
{   
    Delay_ms(100);
    switch(ValveNum)
    {
    case 1:
       FA_OPEN_H(); 
       FA_CLOSE_L();
        break;
    case 2:
       FB_OPEN_H();
       FB_CLOSE_L();
        break;
    default:
        ValveClose(0, 3);   // 故障，全部关阀    
    } 
    ValveOpenTimer.Time = OPEN_TIME; 
    ValveOpenTimer.Flag = TRUE;
    ValveCloseTimer.Flag = FALSE;

    ValveCloseTimer.Time = 0;
    ValveCloseTimer.Flag = FALSE;

    ValveDevice.Action = RUN;//开阀动作
    ValveDevice.stu = TRUE; //开阀
    ValveTimerFun(ValveNum);
    LED_RGB_Fli(1, LED_R_PIN);
//    EepromWriteData(ValveAdd, (u8*)&ValveDevice, sizeof(TypeValce_T));  
    
}
//*****************************************************************************/
//*函数名 :
//*说明   :
//*参数   :
//*返回值 :
//*作者   :
//*****************************************************************************/
void ValveCtrlInit(void)
{
    GPIO_Init(FA_PORT, FA_OPEN_PIN, GPIO_Mode_Out_PP_Low_Fast);    // 初始化阀门控制GPIO
    GPIO_Init(FA_PORT, FA_CLOSE_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(FB_PORT, FB_OPEN_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(FB_PORT, FB_CLOSE_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(FB_PORT, VALVE_SLEEP_PIN, GPIO_Mode_Out_PP_High_Fast);
    VALVE_SLEEP_L();
    FA_OPEN_L();        // 将阀门设置为停止状态
    FA_CLOSE_L();
    FB_OPEN_L();
    FB_CLOSE_L();
   // VALVE_SLEEP_H();
}

