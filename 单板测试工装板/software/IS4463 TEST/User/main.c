#include "SysInitApp.h"
#include "TestItems.h"


int main(void)
{        
    System_Init();
    
    UsartSend(USART3, "System Init OK\r\n", 17);
    
    RS485_Send("RS485 Init OK\r\n", 15);
    
    enableInterrupts();
    
    while(1)
    {
        
    }
           
}