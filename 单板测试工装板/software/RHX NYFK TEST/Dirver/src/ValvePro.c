#include "ValvePro.h"

TypeTimer_T ValveOpenTimer;     //������ʱ��
TypeTimer_T ValveCloseTimer;    //�ط���ʱ��
TypeValce_T ValveDevice;        //���巧���豸


/*******************************************************************************
*������:void ValveStop()
*����:ֹͣ�ط�/��������
*����:��
*���:��
*��ע:��
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
*������:void ValveTimerFun()
*����:���ſ��ƶ�ʱ��
*����:��
*���:��
*��ע:��
*******************************************************************************/
void ValveTimerFun(u8 ValNum)
{
    //������ʱ����ز���
    while(ValveOpenTimer.Time > 0)
    {
        ValveOpenTimer.Time--;
        Delay_ms(600);
        if(ValveOpenTimer.Time == 0)
        {
           if(ValNum == 1)
            {
                ValveStop(1);	        //ֹͣ���ſ���
            }
            else
            {
                ValveStop(2);
            }

            ValveDevice.Action = FALSE; //���Ŷ���ֹͣ
        }
    }
    //�ط���ʱ����ز���
    while(ValveCloseTimer.Time > 0)
    {
        ValveCloseTimer.Time--;
        Delay_ms(600);
        if(ValveCloseTimer.Time == 0)
        {
            if(ValNum == 1)
            {
                ValveStop(1);	        //ֹͣ���ſ���
            }
            else
            {
                ValveStop(2);
            }
            ValveDevice.Action = FALSE; //���Ŷ���ֹͣ
        }
    }
}

/*******************************************************************************
*������:void ValveClose(Valve_Cause cause)
*����:�ط�
*����:no:1  ��λ�ط�
         0  ���Ϲط�
*���:��
*��ע:��
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

      ValveDevice.Action = RUN;;//�ط����� 
      ValveDevice.stu = FALSE; //�ط���־λ
      ValveDevice.cause = cause;
      ValveTimerFun(ValveNum);
//      EepromWriteData(ValveAdd, (u8*)&ValveDevice, sizeof(TypeValce_T));  
}

/*******************************************************************************
*������:void ValveOpen(void)
*����:����
*����:��
*���:��
*��ע:��
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
        ValveClose(0, 3);   // ���ϣ�ȫ���ط�    
    } 
    ValveOpenTimer.Time = OPEN_TIME; 
    ValveOpenTimer.Flag = TRUE;
    ValveCloseTimer.Flag = FALSE;

    ValveCloseTimer.Time = 0;
    ValveCloseTimer.Flag = FALSE;

    ValveDevice.Action = RUN;//��������
    ValveDevice.stu = TRUE; //����
    ValveTimerFun(ValveNum);
    LED_RGB_Fli(1, LED_R_PIN);
//    EepromWriteData(ValveAdd, (u8*)&ValveDevice, sizeof(TypeValce_T));  
    
}
//*****************************************************************************/
//*������ :
//*˵��   :
//*����   :
//*����ֵ :
//*����   :
//*****************************************************************************/
void ValveCtrlInit(void)
{
    GPIO_Init(FA_PORT, FA_OPEN_PIN, GPIO_Mode_Out_PP_Low_Fast);    // ��ʼ�����ſ���GPIO
    GPIO_Init(FA_PORT, FA_CLOSE_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(FB_PORT, FB_OPEN_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(FB_PORT, FB_CLOSE_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(FB_PORT, VALVE_SLEEP_PIN, GPIO_Mode_Out_PP_High_Fast);
    VALVE_SLEEP_L();
    FA_OPEN_L();        // ����������Ϊֹͣ״̬
    FA_CLOSE_L();
    FB_OPEN_L();
    FB_CLOSE_L();
   // VALVE_SLEEP_H();
}

