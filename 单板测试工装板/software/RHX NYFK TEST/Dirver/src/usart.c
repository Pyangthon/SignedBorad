#include "usart.h"



USART_STU USART_1 = {0,0,0};
USART_STU USART_2 = {0,0,0};
USART_STU USART_3 = {0,0,0};
///******************************************************************************************************
//*函数名 :void Usart1_Module_Init(void)
//*说明   :串口1初始化函数
//*参数   :无
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
void Usart1_Module_Init(unsigned long Baud){
  
//    memset(&g_uart_rxbuf, 0, sizeof(g_uart_rxbuf));
    USART_DeInit(USART1); //初始化端口为默认值
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);  //使能USART1时钟

    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_FL_No_IT);  //设置PC2端口浮空输入
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);//设置PC3端口为推挽输出
    

  
    USART_Init(USART1,(uint32_t)Baud ,USART_WordLength_8b ,USART_StopBits_1 ,USART_Parity_No ,(USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx));
    
    USART_ITConfig(USART1, USART_IT_RXNE , ENABLE);   //使能接收中断
    
    USART_Cmd(USART1,ENABLE);  //使能USART1
    
} 
//******************************************************************************************************
//*函数名 :void Usart2_Module_Init(unsigned long Baud)
//*说明   :串口2初始化函数
//*参数   :无
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
void Usart2_Module_Init(unsigned long Baud){
  
    USART_DeInit(USART2); //初始化端口为默认值
    CLK_PeripheralClockConfig(CLK_Peripheral_USART2,ENABLE);  //使能USART2时钟
    
    GPIO_Init(GPIOE,GPIO_Pin_3,GPIO_Mode_In_FL_No_IT);  //设置PE3端口为上拉输入
    GPIO_Init(GPIOE,GPIO_Pin_4,GPIO_Mode_Out_PP_Low_Fast);//设置PE4端口为推挽输出
    
    
  
    USART_Init(USART2,(uint32_t)Baud ,USART_WordLength_8b ,USART_StopBits_1 ,USART_Parity_No , (USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx));
    
    USART_ITConfig(USART2, USART_IT_RXNE , ENABLE);   //使能接收中断
    
    USART_Cmd(USART2,ENABLE);  //使能USART2
  
}
///******************************************************************************************************
//*函数名 :void Usart3_Module_Init(unsigned long Baud)
//*说明   :串口3初始化函数
//*参数   :无
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
void Usart3_Module_Init(unsigned long Baud)
{
  
    USART_DeInit(USART3); //初始化端口为默认值
    CLK_PeripheralClockConfig(CLK_Peripheral_USART3,ENABLE);  //使能USART3时钟

    GPIO_Init(GPIOG,GPIO_Pin_0,GPIO_Mode_In_FL_No_IT);  //设置PG0端口为上拉输入
    GPIO_Init(GPIOG,GPIO_Pin_1,GPIO_Mode_Out_PP_Low_Fast);//设置PG1端口为推挽输出
    
    USART_Init(USART3,(uint32_t)Baud ,USART_WordLength_8b ,USART_StopBits_1 ,USART_Parity_No ,(USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx) );
    
    USART_ITConfig(USART3, USART_IT_RXNE , ENABLE);   //使能接收中断
    
    USART_Cmd(USART3,ENABLE);  //使能USART3
    
}
///******************************************************************************
//*函数名:void Usart3_ReMap(unsigned long baund)
//*功能:串口3重映射到PF0,1直读表头
//*参数:
//*作者:
//*备注:注意串口IO映射问题
//*******************************************************************************/
void Usart3_Module_ReMap_Init(unsigned long Baud)
{
    /*将串口3映射到F脚*/
    SYSCFG_REMAPPinConfig(REMAP_Pin_USART3TxRxPortF, ENABLE);

    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast);	//TXD
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_In_PU_No_IT);

    CLK_PeripheralClockConfig(CLK_Peripheral_USART3, ENABLE);
    /*配置串口时钟*/

    USART_Init(USART3, Baud, USART_WordLength_8b,USART_StopBits_1, USART_Parity_Even,USART_Mode_Rx);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    USART_Cmd(USART3, ENABLE);
}

///******************************************************************************************************
//*函数名 :void Usart3_Module_Disable(void)
//*说明   :串口3失能
//*参数   :无
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
void Usart3_Module_Disable(void)
{
  
    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_OD_Low_Fast);	//TXD
    //txd初始化为高电平互补推挽输出模式
    GPIO_Init(GPIOF, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);	//RX
    CLK_PeripheralClockConfig(CLK_Peripheral_USART3, DISABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
    USART_Cmd(USART3, DISABLE);
    
}
///******************************************************************************************************
//*函数名 :void Usart1_Module_Disable(void)
//*说明   :串口3失能
//*参数   :无
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
void Usart1_Module_Disable(void)
{
    USART_Cmd(USART1, DISABLE);  
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_OD_Low_Fast);	//TXD
    //txd初始化为高电平互补推挽输出模式
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);	//RX
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, DISABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);  
}
///******************************************************************************************************
//*函数名 :void Usart2_Module_Disable(void)
//*说明   :串口2失能
//*参数   :无
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
void Usart2_Module_Disable(void)
{
    USART_Cmd(USART2, DISABLE);  
    GPIO_Init(GPIOE, GPIO_Pin_4, GPIO_Mode_Out_OD_Low_Fast);	//TXD
    //txd初始化为高电平互补推挽输出模式
    GPIO_Init(GPIOE, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);	//RX
    CLK_PeripheralClockConfig(CLK_Peripheral_USART2, DISABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);  
}
///******************************************************************************************************
//*函数名 :void UsartSend(USART_TypeDef* USARTx, unsigned char *str, int Len) 
//*说明   :串口数据发送函数
//*参数   :USARTx: x = 1 ~ 3  str: 发送数据的首地址   Len:  数据的长度
//*返回值 :无
//*作者   :Mr.He
//*******************************************************************************************************/
void UsartSend(USART_TypeDef* USARTx, unsigned char *str, int Len) 
{

      for(int i =0; i < Len; i++)
      {
          USART_SendData8(USARTx,str[i]);
          while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)!=SET); 
          USART_ClearFlag(USARTx,USART_FLAG_TXE);  
//          IWDG_ReloadCounter();//喂狗 

      }                                       
} 




