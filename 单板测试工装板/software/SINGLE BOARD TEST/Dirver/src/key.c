
#include "key.h"

//*****************************************************************************/
//*������ :void Key_Init(void)
//*˵��   :����io�ڳ�ʼ��������Ϊ����PDMSB�ж�����
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Key_Init(void)
{  
    GPIO_Init(KEY_PORT, KEY1_PIN, GPIO_Mode_In_PU_IT);
    GPIO_Init(KEY_PORT, KEY2_PIN, GPIO_Mode_In_PU_IT);
    EXTI_SetPinSensitivity(EXTI_Pin_4, EXTI_Trigger_Rising);
    EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Rising);
    // ���ܰ��� 
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_In_PU_IT);

    // �ж�����
    EXTI_SetPinSensitivity(EXTI_Pin_1, EXTI_Trigger_Falling);
    
}
//*****************************************************************************/
//*������ :void ValveTest_Init(void)
//*˵��   :���ż��˿ڳ�ʼ��
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/

void ValveTest_Init(void)
{
    GPIO_Init(KEY_PORT, KEY3_PIN, GPIO_Mode_In_PU_IT);
    GPIO_Init(KEY_PORT, KEY4_PIN, GPIO_Mode_In_PU_IT);  
    EXTI_SetPinSensitivity(EXTI_Pin_6, EXTI_Trigger_Rising);
    EXTI_SetPinSensitivity(EXTI_Pin_7, EXTI_Trigger_Rising);
   
}
//*****************************************************************************/
//*������ :void DeInitValve(void)
//*˵��   :���ż��˿�����Ϊ���
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/

void DeInitValve(void)
{
    GPIO_Init(KEY_PORT, KEY3_PIN, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(KEY_PORT, KEY4_PIN, GPIO_Mode_Out_PP_Low_Slow);  
}

//*****************************************************************************/
//*������ :BitStatus IO_Read(u8 io_no)
//*˵��   :��ȡIOͨ�ϲ��Զ˿ڵĵ�ƽ״̬
//*����   :io_no      ��Ҫ��ȡ��io��  (1-4֮��)
//*����ֵ :IO_State   ��ȡ�Ķ˿ڵ�״̬ SET �ߵ�ƽ�� RESET �͵�ƽ
//*����   :
//*****************************************************************************/

BitStatus IO_Read(u8 IO_No)
{
    BitStatus IO_State;
    switch(IO_No)
    {
    case 1: 
        IO_State = READ_KEY1();
        break;
    case 2:
        IO_State = READ_KEY2();
        break;
    case 3:
        IO_State = READ_KEY3();
        break;
    case 4:
        IO_State = READ_KEY4();
        break;
    default:
        break;           
    }
    return IO_State;
    
}








