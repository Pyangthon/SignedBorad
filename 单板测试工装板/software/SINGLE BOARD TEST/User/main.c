#include "SerialData.h"

int main(void)
{
    System_Init();  
    enableInterrupts();
    while(1)
    {

        // 放大器的输出电压=测试电流X采样电阻X放大倍数+零偏电压
        if(USART_3.Falg == 1)   // 判断是否有数据收到,判断串口3接收标志位的值
        { 
            Wait_Implement();       // 执行相应的指令函数
        }
        if(FlagStruct.FunKeyFlag == 1)  // 判断功能按键是否按下
        {
            ResetDefault();     // 清空系统配置，默认不需要重新采集零偏电压
        } 
       
    }    
}

