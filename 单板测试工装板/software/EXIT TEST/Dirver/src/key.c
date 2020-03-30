#include "key.h"

void KeyGpioInit(void)
{
    // ��ʼ�������˿�
    GPIO_Init(KEY_PORT, KEY_PIN1 | KEY_PIN2, GPIO_Mode_In_PU_No_IT);
    // ���ð����˿�Ϊ�ߵ�ƽ
    GPIO_SetBits(KEY_PORT, KEY_PIN1);
    GPIO_SetBits(KEY_PORT, KEY_PIN2);       
}

BitStatus GetKeySta(GPIO_TypeDef *GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
    // ��ⰴ���Ƿ���
    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == RESET)
    {
        // ��ʱ����
        Delay_ms(100);
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
