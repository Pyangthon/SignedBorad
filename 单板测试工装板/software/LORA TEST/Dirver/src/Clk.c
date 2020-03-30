/*******************************************
* @File   Clk.c  
* @brief  ��ʼ��ʱ��   
* @author  
* @date     
* @version V0.1 
* @par Copyright (c)
* @par History
            None
*********************************************/
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

    CLK_DeInit();  // ʱ�ӻָ�Ĭ��״̬                                 
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);   // 1��Ƶ 16M

    CLK_SYSCLKSourceSwitchCmd(ENABLE);      // ʹ��ʱ��Դ����    
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);   // ѡ��Ƭ�ڸ���ʱ��

    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);  // �ȵ�ʱ�ӵĿ���
}