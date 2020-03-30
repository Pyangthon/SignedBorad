
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
    CLK_Configuration();  //时钟配置  16M
    FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
    Usart_Init(115200);   //USART1初始化

    Lora_Gpio_Init();
    RF1278_Init(0,9);
    Rf1278_ModeSet(100);
    //SysData_Init();   //系统数据初始化
    enableInterrupts(); //使能全局中断  
    IWDG_Config();  //看门狗定配置
    //处理集中器数据；处理RS485数据 


    
    while(1){

    Lora_Event();
    IWDG_ReloadCounter();  //独立看门狗喂狗
    Rs485_Event();
    //text1();

  }   
}
