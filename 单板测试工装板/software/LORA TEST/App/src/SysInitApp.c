
/*******************************************
* @File    SysInitApp.c 
* @brief   ���幤װ���԰�������ļ�  
* @author  
* @date     
* @version V0.1 
* @par Copyright (c)
* @par History
            None
*********************************************/
#include "SysInitApp.h"

/***************************************************************************
* ��������: void SPDT_Init(void)
* ����  	: ��ʼ���̵����˿ڣ���ʼ���̵������Ƶ�GPIO��
* ����  	: None
* ����  	:
* ����ʱ��: 2020��1��14��
* �޸�ʱ��:
****************************************************************************/  
void SPDT_Init(void)
{
    // ��ʼ���̵������ƶ˿� PC7
    GPIO_Init(SPDT_PORT, SPDT_EN_PIN, GPIO_Mode_Out_PP_High_Fast);
    // �����õ�, Ĭ�Ϲر�
    GPIO_ResetBits(SPDT_PORT, SPDT_EN_PIN);
}




        

