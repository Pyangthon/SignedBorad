
#include "includes.h"
#include "EErom.h"

void text1(void){

  if(u1_flag){
     UsartSend(USART1,RxBuffer,u1_flag); 
     u1_clear_rxbuffer();
  }
}




int main( void ) 
{
    CLK_Configuration();  //ʱ������  16M
    FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
    Usart_Init(115200);   //USART1��ʼ��

    Lora_Gpio_Init();
    RF1278_Init(0,9);
    Rf1278_ModeSet(100);
    //SysData_Init();   //ϵͳ���ݳ�ʼ��
    enableInterrupts(); //ʹ��ȫ���ж�  
    IWDG_Config();  //���Ź�������
    //�����������ݣ�����RS485���� 


    
    while(1){

    Lora_Event();
    IWDG_ReloadCounter();  //�������Ź�ι��
    Rs485_Event();
    //text1();

  }   
}
