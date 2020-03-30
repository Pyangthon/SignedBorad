
/*******************************************
* @File    SysInitApp.c 
* @brief   单板工装测试板的配置文件  
* @author  
* @date     
* @version V0.1 
* @par Copyright (c)
* @par History
            None
*********************************************/
#include "SysInitApp.h"

/***************************************************************************
* 函数名称: void SPDT_Init(void)
* 功能  	: 初始化继电器端口，初始化继电器控制的GPIO口
* 参数  	: None
* 作者  	:
* 创建时间: 2020年1月14日
* 修改时间:
****************************************************************************/  
void SPDT_Init(void)
{
    // 初始化继电器控制端口 PC7
    GPIO_Init(SPDT_PORT, SPDT_EN_PIN, GPIO_Mode_Out_PP_High_Fast);
    // 将其置低, 默认关闭
    GPIO_ResetBits(SPDT_PORT, SPDT_EN_PIN);
}




        

