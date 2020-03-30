#include "SysInitApp.h"
#include "TestItems.h"


void OpenValve(void)
{
    GPIO_SetBits(GPIOG, GPIO_Pin_4);
    GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    Delay_ms(1000);
    GPIO_ResetBits(GPIOG, GPIO_Pin_4);
    GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    Delay_ms(10);
}

void CloseValve(void)
{
    GPIO_SetBits(GPIOG, GPIO_Pin_6);
    GPIO_ResetBits(GPIOG, GPIO_Pin_4);
    Delay_ms(1000);
    GPIO_ResetBits(GPIOG, GPIO_Pin_4);
    GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    Delay_ms(10);
}

int main(void)
{
    SysClockInit();
    // ³õÊ¼»¯G6G4
    GPIO_Init(GPIOG, GPIO_Pin_6, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOG, GPIO_Pin_4, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_In_PU_IT);
    EXTI_SetPinSensitivity(EXTI_Pin_2, EXTI_Trigger_Rising);
    GPIO_ResetBits(GPIOG, GPIO_Pin_4);
    GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    MyFlagSturct.FunFlag = 0;
    
    enableInterrupts();
    while(1)
    {
        if(MyFlagSturct.KeyState == TRUE)
        {
            MyFlagSturct.KeyState = FALSE;
           if(MyFlagSturct.FunFlag == 1)
           {
               
               OpenValve();
               Delay_ms(10);

           }
           else
           {
               if(MyFlagSturct.FunFlag != 0)
               {
                   CloseValve();
                   MyFlagSturct.FunFlag = 0;
               }
           }
        }
        if(MyFlagSturct.FunFlag > 2)
        {
            MyFlagSturct.FunFlag = 0;
        }
    }
}