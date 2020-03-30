#include "key.h"

Global_Flag_TypeDef FlagSturct = {FALSE, FALSE};

void KeyGpioInit(void)
{
    
    // ��ʼ�������˿�
    GPIO_Init(KEY_PORT, KEY_PIN1 | KEY_PIN0, GPIO_Mode_In_PU_IT);
    EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Rising); 
    EXTI_SetPinSensitivity(EXTI_Pin_1,EXTI_Trigger_Rising); 
    // ���ð����˿�Ϊ�ߵ�ƽ
//    GPIO_SetBits(KEY_PORT, KEY_PIN1);
//    GPIO_SetBits(KEY_PORT, KEY_PIN0);       
}

BitStatus GetKeySta(GPIO_TypeDef *GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
    // ��ⰴ���Ƿ���
    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == RESET)
    {
        
        Delay_ms(100);// ��ʱ����
        // �ٴμ��ȷ��״̬
        if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == RESET)
        {   // �ȴ������ͷ�
            while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == SET) ;
            // ���ذ��°���״̬
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
