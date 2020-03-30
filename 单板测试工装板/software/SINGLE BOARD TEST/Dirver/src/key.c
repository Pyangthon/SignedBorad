
#include "key.h"

//*****************************************************************************/
//*函数名 :void Key_Init(void)
//*说明   :按键io口初始化，配置为上拉PDMSB中断输入
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void Key_Init(void)
{  
    GPIO_Init(KEY_PORT, KEY1_PIN, GPIO_Mode_In_PU_IT);
    GPIO_Init(KEY_PORT, KEY2_PIN, GPIO_Mode_In_PU_IT);
    EXTI_SetPinSensitivity(EXTI_Pin_4, EXTI_Trigger_Rising);
    EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Rising);
    // 功能按键 
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_In_PU_IT);

    // 中断配置
    EXTI_SetPinSensitivity(EXTI_Pin_1, EXTI_Trigger_Falling);
    
}
//*****************************************************************************/
//*函数名 :void ValveTest_Init(void)
//*说明   :阀门检测端口初始化
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/

void ValveTest_Init(void)
{
    GPIO_Init(KEY_PORT, KEY3_PIN, GPIO_Mode_In_PU_IT);
    GPIO_Init(KEY_PORT, KEY4_PIN, GPIO_Mode_In_PU_IT);  
    EXTI_SetPinSensitivity(EXTI_Pin_6, EXTI_Trigger_Rising);
    EXTI_SetPinSensitivity(EXTI_Pin_7, EXTI_Trigger_Rising);
   
}
//*****************************************************************************/
//*函数名 :void DeInitValve(void)
//*说明   :阀门检测端口设置为输出
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/

void DeInitValve(void)
{
    GPIO_Init(KEY_PORT, KEY3_PIN, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(KEY_PORT, KEY4_PIN, GPIO_Mode_Out_PP_Low_Slow);  
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








