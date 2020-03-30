#include "usart.h"

USART_STU USART_1 = {0,0,0};
USART_STU USART_2 = {0,0,0};
USART_STU USART_3 = {0,0,0};


///******************************************************************************************************
//*������ :void Usart1_Module_Init(void)
//*˵��   :����1��ʼ������
//*����   :Baud ������
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
void Usart1_Module_Init(unsigned long Baud)
{
      USART_DeInit(USART1); //��ʼ���˿�ΪĬ��ֵ
//    memset(&g_uart_rxbuf, 0, sizeof(g_uart_rxbuf));
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);  //ʹ��USART1ʱ��

    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_FL_No_IT);  //����PC2�˿ڸ�������
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_Low_Fast);//����PC3�˿�Ϊ�������
   
    USART_Init(USART1,(uint32_t)Baud ,USART_WordLength_8b ,USART_StopBits_1 ,USART_Parity_No ,(USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx));
    
    USART_ITConfig(USART1, USART_IT_RXNE , ENABLE);   //ʹ�ܽ����ж�
    
    USART_Cmd(USART1,ENABLE);  //ʹ��USART1
    
} 
//******************************************************************************************************
//*������ :void Usart2_Module_Init(unsigned long Baud)
//*˵��   :����2��ʼ������
//*����   :Baud ������
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
void Usart2_Module_Init(unsigned long Baud)
{
  
    USART_DeInit(USART2); //��ʼ���˿�ΪĬ��ֵ
    CLK_PeripheralClockConfig(CLK_Peripheral_USART2,ENABLE);  //ʹ��USART2ʱ��
    
    GPIO_Init(GPIOE,GPIO_Pin_3,GPIO_Mode_In_FL_No_IT);  //����PE3�˿�Ϊ��������
    GPIO_Init(GPIOE,GPIO_Pin_4,GPIO_Mode_Out_PP_Low_Fast);//����PE4�˿�Ϊ�������
    
    
    // ���ô��� �ֳ�Ϊ8λ��ֹͣλ1λ������żУ�飬���ͺͽ���˫��
    USART_Init(USART2,(uint32_t)Baud ,USART_WordLength_8b ,USART_StopBits_1 ,USART_Parity_No,\
        (USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx));
    
    USART_ITConfig(USART2, USART_IT_RXNE , ENABLE);   //ʹ�ܽ����ж�
    
    USART_Cmd(USART2,ENABLE);  //ʹ��USART2
  
}
///******************************************************************************************************
//*������ :void Usart3_Module_Init(unsigned long Baud)
//*˵��   :����3��ʼ������
//*����   :Baud ������
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
void Usart3_Module_Init(unsigned long Baud)
{
    USART_DeInit(USART3); //��ʼ���˿�ΪĬ��ֵ
    CLK_PeripheralClockConfig(CLK_Peripheral_USART3,ENABLE);  //ʹ��USART3ʱ��

    GPIO_Init(GPIOG,GPIO_Pin_0,GPIO_Mode_In_FL_No_IT);  //����PG0�˿�Ϊ��������
    GPIO_Init(GPIOG,GPIO_Pin_1,GPIO_Mode_Out_PP_Low_Fast);//����PG1�˿�Ϊ�������
    USART_Init(USART3,(uint32_t)Baud ,USART_WordLength_8b ,USART_StopBits_1 ,USART_Parity_No ,(USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx) );
    
    USART_ITConfig(USART3, USART_IT_RXNE , ENABLE);   //ʹ�ܽ����ж�
    
    USART_Cmd(USART3,ENABLE);  //ʹ��USART3
    
}
///******************************************************************************
//*������:void Usart3_ReMap(unsigned long baund)
//*����: ����3��ӳ�䵽PF0,1ֱ����ͷ
//*����: Baud ������
//*����:
//*��ע:ע�⴮��IOӳ������
//*******************************************************************************/
void Usart3_Module_ReMap_Init(unsigned long Baud)
{
    /*������3ӳ�䵽F��*/
    SYSCFG_REMAPPinConfig(REMAP_Pin_USART3TxRxPortF, ENABLE);

    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast);	// TXD
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_In_PU_No_IT);

    CLK_PeripheralClockConfig(CLK_Peripheral_USART3, ENABLE);
    /*���ô���ʱ��*/

    USART_Init(USART3, Baud, USART_WordLength_8b,USART_StopBits_1, USART_Parity_Even,USART_Mode_Rx);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    USART_Cmd(USART3, ENABLE);
}

///******************************************************************************************************
//*������ :void Usart3_Module_Disable(void)
//*˵��   :����3ʧ��
//*����   :��
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
void Usart3_Module_Disable(void)
{
  
    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_OD_Low_Fast);	//TXD
    //txd��ʼ��Ϊ�ߵ�ƽ�����������ģʽ
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);	//RX
    CLK_PeripheralClockConfig(CLK_Peripheral_USART3, DISABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
    USART_Cmd(USART3, DISABLE);
    
}
///******************************************************************************************************
//*������ :void Usart1_Module_Disable(void)
//*˵��   :����3ʧ��
//*����   :��
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
void Usart1_Module_Disable(void)
{
    USART_Cmd(USART1, DISABLE);  
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_OD_Low_Fast);	//TXD
    //txd��ʼ��Ϊ�ߵ�ƽ�����������ģʽ
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);	//RX
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, DISABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);  
}
///******************************************************************************************************
//*������ :void Usart2_Module_Disable(void)
//*˵��   :����2ʧ��
//*����   :��
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
void Usart2_Module_Disable(void)
{
    USART_Cmd(USART2, DISABLE);  
    GPIO_Init(GPIOE, GPIO_Pin_4, GPIO_Mode_Out_OD_Low_Fast);	//TXD
    //txd��ʼ��Ϊ�ߵ�ƽ�����������ģʽ
    GPIO_Init(GPIOE, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);	//RX
    CLK_PeripheralClockConfig(CLK_Peripheral_USART2, DISABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);  
}
///******************************************************************************************************
//*������ :void UsartSend(USART_TypeDef* USARTx, unsigned char *str, int Len) 
//*˵��   :�������ݷ��ͺ���
//*����   :USARTx: x = 1 ~ 3  str: �������ݵ��׵�ַ   Len:  ���ݵĳ���
//*����ֵ :��
//*����   :Mr.He
//*******************************************************************************************************/
void UsartSend(USART_TypeDef* USARTx, unsigned char *str, int Len) 
{

    int i = 0;
      for(; i < Len; i++)
      {
          USART_SendData8(USARTx,str[i]);
          while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)!=SET); 
          USART_ClearFlag(USARTx,USART_FLAG_TXE);  
//          IWDG_ReloadCounter();//ι�� 

      }                                       
}

//*****************************************************************************/
//*������ :int putchar(int data)
//*˵��   :��дprintf����
//*����   :data д�������
//*����ֵ :data ���д������
//*����   :
//*****************************************************************************/
int putchar(int data)
{ 
    USART_SendData8(USART3,(u8)data);  //����8λ����
    while(!USART_GetFlagStatus (USART3,USART_FLAG_TXE));//�ȴ��������
    return data; 
}
