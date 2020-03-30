#include "Clk.h"

//*****************************************************************************/
//*������ :void SysClockInit(void)
//*˵��   :��ʼ��ϵͳʱ�ӣ�ѡ���ڲ�����ʱ�ӣ�16MHz
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void SysClockInit(void)
{

    CLK_DeInit();  // ʱ�ӻָ�Ĭ��״̬                                 
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);   // ����Ƶ 16M

    CLK_SYSCLKSourceSwitchCmd(ENABLE);      // ʹ��ʱ��Դ����    
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);   // ѡ��Ƭ�ڸ���ʱ��

    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);  // �ȵ�ʱ�ӵĿ���
}

