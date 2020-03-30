#include "Clk.h"

//*****************************************************************************/
//*函数名 :void SysClockInit(void)
//*说明   :初始化系统时钟，选择内部高速时钟，16MHz
//*参数   :无
//*返回值 :无
//*作者   :
//*****************************************************************************/
void SysClockInit(void)
{

    CLK_DeInit();  // 时钟恢复默认状态                                 
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);   // 不分频 16M

    CLK_SYSCLKSourceSwitchCmd(ENABLE);      // 使能时钟源开关    
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);   // 选择片内高速时钟

    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);  // 等到时钟的开启
}

