#include "SerialData.h"

int main(void)
{
    System_Init();  
    enableInterrupts();
    while(1)
    {

        // �Ŵ����������ѹ=���Ե���X��������X�Ŵ���+��ƫ��ѹ
        if(USART_3.Falg == 1)   // �ж��Ƿ��������յ�,�жϴ���3���ձ�־λ��ֵ
        { 
            Wait_Implement();       // ִ����Ӧ��ָ���
        }
        if(FlagStruct.FunKeyFlag == 1)  // �жϹ��ܰ����Ƿ���
        {
            ResetDefault();     // ���ϵͳ���ã�Ĭ�ϲ���Ҫ���²ɼ���ƫ��ѹ
        } 
       
    }    
}

