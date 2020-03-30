
#include "key.h"

//*****************************************************************************/
//*������ :void Key_Init(void)
//*˵��   :����io�ڳ�ʼ��������Ϊ����PDMSB�ж�����
//*����   :Mode   �����ĳ�ʼ��ģʽ  0   �������ж�����
//*                                 1   �����ж�����
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Key_Init(u8 Mode)
{
    // �˿ڳ�ʼ��
    if(Mode)
    {
        GPIO_Init(KEY_PORT, KEY1_PIN, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_PORT, KEY2_PIN, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_PORT, KEY3_PIN, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_PORT, KEY4_PIN, GPIO_Mode_In_PU_IT);    
        
        EXTI_SetPortSensitivity(EXTI_Port_D, EXTI_Trigger_Falling);
        EXTI_SelectPort(EXTI_Port_D);
        EXTI_SetHalfPortSelection(EXTI_HalfPort_D_MSB, ENABLE);
        
        // ���ܰ��� 
        GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_In_PU_IT);
    
        // �ж�����
        EXTI_SetPinSensitivity(EXTI_Pin_1, EXTI_Trigger_Falling);
    }
    else
    {
        GPIO_Init(KEY_PORT, KEY1_PIN, GPIO_Mode_In_PU_No_IT);
        GPIO_Init(KEY_PORT, KEY2_PIN, GPIO_Mode_In_PU_No_IT);
        GPIO_Init(KEY_PORT, KEY3_PIN, GPIO_Mode_In_PU_No_IT);
        GPIO_Init(KEY_PORT, KEY4_PIN, GPIO_Mode_In_PU_No_IT);
        EXTI_SetHalfPortSelection(EXTI_HalfPort_D_MSB, DISABLE);
    }

    
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
    u8 IO_State;
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
    return (BitStatus)(IO_State);
    
}








