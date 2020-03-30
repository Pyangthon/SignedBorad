#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
//#include "adc.h"
#include "ads115.h"
   
 int main(void)
 {	
	float t1; 
  u16 t,result;
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	LCD_Init();			 	
    ADS1115_Init(); 
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(50,60,200,16,16,"Voltage1:00.000V");
  LCD_ShowString(50,80,200,16,16,"Voltage2:00.000V");
  LCD_ShowString(50,100,200,16,16,"Voltage3:00.000V");
	LCD_ShowString(50,120,200,16,16,"Voltage4:00.000V");
	//显示提示信息
	POINT_COLOR=BLUE;//设置字体为蓝色
	while(1)
	{    
		  //通道0
		  result=lvbo(0xe3,0xc2);    
		  t1=4.096*2*result/65535;     //转换成电压
          LCD_ShowxNum(122,20,result,5,16,0x80);
  		  t=t1;
		  LCD_ShowxNum(122,60,t,2,16,0x80);
          result=(t1-t)*1000;
		  LCD_ShowxNum(146,60,result,3,16,0x80);
          //delay_ms(5);
		  //通道1
		  result=lvbo(0xe3,0xd2);    
		  t1=4.096*2*result/65535;     //转换成电压
          t=t1;
		  LCD_ShowxNum(122,80,t,2,16,0x80);
          result=(t1-t)*1000;
		  LCD_ShowxNum(146,80,result,3,16,0x80);
          //delay_ms(5);
		  //通道2
		  result=lvbo(0xe3,0xe2);    
		  t1=4.096*2*result/65535;     //转换成电压
          t=t1;
		  LCD_ShowxNum(122,100,t,2,16,0x80);
          result=(t1-t)*1000;
		  LCD_ShowxNum(146,100,result,3,16,0x80);
		  //delay_ms(5);
		  //通道3
		  result=lvbo(0xe3,0xf2);    
		  t1=4.096*2*result/65535;     //转换成电压
          t=t1;
		  LCD_ShowxNum(122,120,t,2,16,0x80);
          result=(t1-t)*1000;
		  LCD_ShowxNum(146,120,result,3,16,0x80); 
          //delay_ms(100);
	}
 }

