
#include "Clk.h"

///***************************************************************************
//* ��������: void SysClockInit(void)
//* ����  	: ��ʼ��ʱ�ӣ�ѡ���ڲ�����ʱ��
//* ����  	: None
//* ����  	:
//* ����ʱ��: 2020��1��14��
//* �޸�ʱ��:
//****************************************************************************

void SysClockInit(void)
{

    CLK_DeInit();
    /* High speed internal clock prescaler: 1 */
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

    /* Select HSI as system clock source */
    CLK_SYSCLKSourceSwitchCmd(ENABLE);
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);

    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);
}