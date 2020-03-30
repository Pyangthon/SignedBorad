
#include "key.h"

//*****************************************************************************/
//*函数名 :void Key_Init(void)
//*说明   :按键io口初始化，配置为上拉PDMSB中断输入
//*参数   :Mode   按键的初始化模式  0   上拉无中断输入
//*                                 1   上拉中断输入
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Key_Init(u8 Mode)
{
    // 端口初始化
    if(Mode)
    {
        GPIO_Init(KEY_PORT, KEY1_PIN, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_PORT, KEY2_PIN, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_PORT, KEY3_PIN, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_PORT, KEY4_PIN, GPIO_Mode_In_PU_IT);    
        
        EXTI_SetPortSensitivity(EXTI_Port_D, EXTI_Trigger_Falling);
        EXTI_SelectPort(EXTI_Port_D);
        EXTI_SetHalfPortSelection(EXTI_HalfPort_D_MSB, ENABLE);
        
        // 功能按键 
        GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_In_PU_IT);
    
        // 中断配置
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
//*函数名 :BitStatus IO_Read(u8 io_no)
//*说明   :获取IO通断测试端口的电平状态
//*参数   :io_no      需要读取的io口  (1-4之间)
//*返回值 :IO_State   读取的端口的状态 SET 高电平， RESET 低电平
//*作者   :
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








