#ifndef __SYS_INIT_APP_H_
#define __SYS_INIT_APP_H_

#include "stm8l15x_gpio.h"



// ����̵������ƽ�
#define SPDT_PORT       GPIOC
#define SPDT_EN_PIN     GPIO_Pin_7
// �궨��̵������ƺ���
// �̵����ر�
#define SPDT_EN_L()     GPIO_ResetBits(SPDT_PORT, SPDT_EN_PIN)
// �̵�������
#define SPDT_EN_H()     GPIO_SetBits(SPDT_PORT, SPDT_EN_PIN)
// �̵�����ʼ��


#endif

