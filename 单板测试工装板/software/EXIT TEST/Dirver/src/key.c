#include "key.h"

void KeyGpioInit(void)
{
    // 初始化按键端口
    GPIO_Init(KEY_PORT, KEY_PIN1 | KEY_PIN2, GPIO_Mode_In_PU_No_IT);
    // 设置按键端口为高电平
    GPIO_SetBits(KEY_PORT, KEY_PIN1);
    GPIO_SetBits(KEY_PORT, KEY_PIN2);       
}

BitStatus GetKeySta(GPIO_TypeDef *GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
    // 检测按键是否按下
    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == RESET)
    {
        // 延时消抖
        Delay_ms(100);
        // 再次检测确认状态
        if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == RESET)
        {   // 等待按键释放
            while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == SET) ;
            // 返回按下按键状态
            return RESET;
        }
        else
        {
            return SET;
        }
    }
    else
    {
        return SET;
    }
    
}
