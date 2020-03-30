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
    GPIO_Init(LED_PORT, LED_1_PIN, GPIO_Mode_Out_PP_High_Fast); 
    GPIO_Init(LED_PORT, LED_R_PIN, GPIO_Mode_Out_PP_High_Fast);    
          
    GPIO_Init(LED_PORT, LED_G_PIN, GPIO_Mode_Out_PP_High_Fast);    
    GPIO_Init(LED_PORT, LED_B_PIN, GPIO_Mode_Out_PP_High_Fast);
    
    GPIO_SetBits(LED_PORT, LED_1_PIN|LED_R_PIN|LED_G_PIN|LED_B_PIN);
    
}


void LEDFlicker( u8 i)
{
    
    while(i--)
    {
        GPIO_ResetBits(LED_PORT, LED_1_PIN);        
        Delay_ms(200);
        GPIO_SetBits(LED_PORT, LED_1_PIN);
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


    
    //        if(GetKeySta(KEY_PORT, KEY_PIN1) == RESET)
//        {
//            if(Key1Sta == 0)
//            {
//                GPIO_ResetBits(LED_PORT, LED_1_PIN);
//                Key1Sta = !Key1Sta;
//            }
//            else
//            {
//                GPIO_SetBits(LED_PORT, LED_1_PIN);
//                
//                Key1Sta = !Key1Sta;
//            }
//        }
//        else if(GetKeySta(KEY_PORT, KEY_PIN2) == RESET)
//        {
//            if(Key2Sta == 0)
//            {
//                GPIO_ResetBits(LED_PORT, LED_R_PIN|LED_G_PIN|LED_B_PIN);
//                Key2Sta = !Key2Sta;
//            }
//            else
//            {
//                GPIO_SetBits(LED_PORT, LED_R_PIN|LED_G_PIN|LED_B_PIN);
//                Key2Sta = !Key2Sta;
//            }
//        }
//        else
//        {
//            ;
//        }
 
//          GPIO_ResetBits(LED_PORT, LED_1_PIN);
//          GPIO_ResetBits(LED_PORT, LED_R_PIN|LED_G_PIN|LED_B_PIN);
//        if(RFInit_Flag == 0)
//        {
//            if(RF1278_Init(10, 2))      // 初始化1278，设置信道为10， 扩频因子为2,并判断是否是初始化成功
//            {
//                RFInit_Flag = 1;        // 使RF初始化标志位变为1
//                LEDFlicker(3);
//                Delay_ms(100);
//            }
//        }
//        else if(RFInit_Flag == 1)
//        {
//             RF1278_Standby();          // 模块进入待机状态
//             if(GetRF1278_State() == 3)
//             {
//                 RFInit_Flag = 2;
//                 LEDFlicker(4);
//             }
//        }
//        else if(RFInit_Flag == 2)
//        {
//            Rf1278_ModeSet(5);
//        }
