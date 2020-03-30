#include "led.h"


/*----------------------------
FUNC_NAME : LED_Init()     
FUNC_DESC : 初始化LED端口
FUNC_IN   : None
FUNC_OUT  : None
FUNC_OTHER: 端口输出模式为通用推挽高速输出
----------------------------*/
void LED_Init(void)
{
    GPIO_Init(LED_PORT, LED_0_PIN, GPIO_Mode_Out_PP_High_Fast); 
    GPIO_Init(LED_PORT, LED_R_PIN, GPIO_Mode_Out_PP_High_Fast);    
    GPIO_Init(LED_PORT, LED_G_PIN, GPIO_Mode_Out_PP_High_Fast);    
    GPIO_Init(LED_PORT, LED_B_PIN, GPIO_Mode_Out_PP_High_Fast);
    
    GPIO_SetBits(LED_PORT, LED_0_PIN|LED_R_PIN|LED_G_PIN|LED_B_PIN);
}


void LED0Flicker( u8 i)
{
    while(i--)
    {
        GPIO_ResetBits(LED_PORT, LED_0_PIN);        
        Delay_ms(200);
        GPIO_SetBits(LED_PORT, LED_0_PIN);
        Delay_ms(200);
    }
}
   

void LED_RGB_Fli(u8 i, GPIO_Pin_TypeDef led)
{
    while(i--)
    {
        GPIO_ResetBits(LED_PORT, led);        
        Delay_ms(200);
        GPIO_SetBits(LED_PORT, led);
        Delay_ms(200);
    }
}
