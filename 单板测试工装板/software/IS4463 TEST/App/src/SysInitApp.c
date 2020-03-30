#include "SysInitApp.h"

//*****************************************************************************/
//*������ :void SPDT_Init(void)
//*˵��   :��ʼ���̵����˿�
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void SPDT_Init(void)
{
    // ��ʼ���̵����˿�
    GPIO_Init(SPDT_PORT, SPDT_EN_PIN, GPIO_Mode_Out_PP_High_Slow);       // PC7
    // ��ʼ��Ϊ�رռ̵���
    SPDT_EN_OFF();
}
//*****************************************************************************/
//*������ :void SPDT_Ctrl_Port_Init(void)
//*˵��   :��ʼ���̵��������µĶ˿ڣ����ݱ�����������PB_LSB_MODE���ƶ˿ڳ�ʼ��ģʽ��
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void SPDT_Ctrl_Port_Init(void)
{
#if PB_LSB_MODE
    // ��PB0-3��ʼ��Ϊ�������������
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);
    // Ĭ������͵�ƽ
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_1, RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_2, RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_3, RESET);
#else
    // ��PB0-3��ʼ��Ϊ�������ж�����
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);
#endif
    // ��ʼ������1
    Usart1_Module_Init(115200);
}
u16 MsCount = 0;

//*****************************************************************************/
//*������ :void Peripheral_Init(void)
//*˵��   :�����ʼ��
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/

void System_Init(void)
{
    SysClockInit();     // ϵͳʱ�ӳ�ʼ�����ڲ�����ʱ�ӣ�16MHz   
    
//    GPIO_Init_Config();
    RS485_Init();       // RS485��ʼ��������2��������9600��Ĭ�Ͻ���
    Usart3_Module_Init(115200);     // ����3��ʼ�������ڽ�����λ��ָ������
    LED_Init();         // LED��ʾ���ֳ�ʼ��
    Key_Init(1);         // ������ʼ������ʼ��ģʽΪ�������룬PDMSB�ж�
    //SPDT_Init();        //�̵�����ʼ��,Ĭ�ϼ̵����ر�
    // ADS1115ADC��ʼ��,Ŀǰ��Ӳ���ϵ�ȱʧ����ʱ�����������
    //ADS_GPIO_Init();
    //SPDT_Ctrl_Port_Init();
    Timer3_init();
}

void GPIO_Init_Config(void)
{
    GPIO_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);//SWIM
    GPIO_Init(GPIOA, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  //NRST
    GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow );  //��SART1_TX��    
    GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //��USART1_X��
    GPIO_Init(GPIOA, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow );  //COM0
    GPIO_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow );  //COM1
    GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow );  //COM2
    GPIO_Init(GPIOA, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow );  //SEG0
                                                         
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //SEG10
    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //SEG11
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //SEG12
    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //SEG13
    GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //SEG14
    GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //SEG15
    GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //SEG16
    GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //SEG17
  
    GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_EN
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //IR_EN
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //SEG22
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //SEG23
    GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //ADC4
    GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //LSE1
    GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //LSE2
    GPIO_Init(GPIOC, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_MOSI
  
    GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Slow);  //SEG7
    GPIO_Init(GPIOD, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  //COM3
    GPIO_Init(GPIOD, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Slow);  //SEG8
    GPIO_Init(GPIOD, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Slow);  //SEG9
    GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //SEG18
    GPIO_Init(GPIOD, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //SEG19
    GPIO_Init(GPIOD, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //SEG20
    GPIO_Init(GPIOD, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //SEG21
  
    GPIO_Init(GPIOE, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //SEG1
    GPIO_Init(GPIOE, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //SEG2
    GPIO_Init(GPIOE, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //SEG3
    GPIO_Init(GPIOE, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //USART2_RX
    GPIO_Init(GPIOE, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //USART2_TX
    GPIO_Init(GPIOE, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //SEG6
    GPIO_Init(GPIOE, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //POWER
    GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //PWRKEY


    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_CS
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //FLASH_MISO
    GPIO_Init(GPIOF, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);  //NO
    GPIO_Init(GPIOF, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);  //NO
    GPIO_Init(GPIOF, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //kEY 
    GPIO_Init(GPIOF, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //RTC_INT
    GPIO_Init(GPIOF, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //RST_C
    GPIO_Init(GPIOF, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //CLK_C
  
    GPIO_Init(GPIOG, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);  //USART3_RX
    GPIO_Init(GPIOG, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);  //USART3_TX
    GPIO_Init(GPIOG, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow); //I2C_SCL
    GPIO_Init(GPIOG, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow); //I2C_SDA
    GPIO_Init(GPIOG, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);  //MOT_A
    GPIO_Init(GPIOG, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);  //BUZZ
    GPIO_Init(GPIOG, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);  //MOT_B
    GPIO_Init(GPIOG, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);  //ADC_EN
}




