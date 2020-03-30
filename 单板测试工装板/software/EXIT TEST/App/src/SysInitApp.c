#include "SysInitApp.h"

// ����LoRaģʽ���ܴ���

//void LORAModelTest(void)
//{
//    unsigned char RF1278_state;     // ������LoRa״̬��
//    unsigned char cbuf[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
//    Lora_Gpio_Init();               // ��ʼ��LoRaGPIO��
//    RF1278_Init(10, 2);             // ��ʼ��LoRa��Ƶ
////    RF1278_CadInit(80);
////    RF1278_CadSample();
//    LED_Init();                     // LED��ʼ��
//    // ���Դ���ģʽ
////    RF1278_Standby();         // ����ģʽ����, LED3��
//    // ������Ƶģʽ
////    RF1278_EntryLoRa();       
//    // ����˯��ģʽ
////    RF1278_Sleep();           // ˯��ģʽ����, LED0��
//    // ���Խ���ģʽ
////    Rf1278_ModeSet(10);    '     // ����ģʽ����, LED1��
//    RF1278_SendPacket(cbuf, 10);
//    
//    
//    
//    
//    while(1)
//    {
//        RF1278_state = GetRF1278_State();
//        if(RF1278_state != 0xff)
//        {
////            LED_Run(1);
////            if(RF1278_state == '3'|'2'|'1'|'0')
////            {
////                LED_Run(4);
////            }
//            LED_Run(RF1278_state);
//            
//            
//        }
//        else
//        {
//            
////            LED_Run(4);
//            ;
//        }
//        
//    }
//
//}

void RS485Test(void)
{
    unsigned char RS_Send_Buf[8] = {1};
    Usart2_Module_Init(9600);
    GPIO_Init(RS485_EN_PORT, RS485_EN_PIN, GPIO_Mode_Out_PP_High_Fast);
    
    GPIO_SetBits(RS485_EN_PORT, RS485_EN_PIN);
    
    UsartSend(USART2, RS_Send_Buf, 8);
    
}


//
//void Uart3Config()
//{
//    Usart2_Module_Init(115200);
//    
//    
//}
///***************************************************************************
//* ��������: void SPDT_Init(void)
//* ����  	: ��ʼ���̵����˿ڣ���ʼ���̵������Ƶ�GPIO��
//* ����  	: None
//* ����  	:
//* ����ʱ��: 2020��1��14��
//* �޸�ʱ��:
//****************************************************************************1  
void SPDT_Init(void)
{
    GPIO_Init(SPDT_PORT, SPDT_EN_PIN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast);
    
    GPIO_SetBits(SPDT_PORT, SPDT_EN_PIN);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

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

///***************************************************************************
//* ��������: 
//* ����  	:
//* ����  	:
//* ����  	:
//* ����ʱ��:
//* �޸�ʱ��:
//****************************************************************************




