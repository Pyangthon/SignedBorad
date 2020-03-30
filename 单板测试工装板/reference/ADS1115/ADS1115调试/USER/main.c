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
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();			 	
    ADS1115_Init(); 
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(50,60,200,16,16,"Voltage1:00.000V");
  LCD_ShowString(50,80,200,16,16,"Voltage2:00.000V");
  LCD_ShowString(50,100,200,16,16,"Voltage3:00.000V");
	LCD_ShowString(50,120,200,16,16,"Voltage4:00.000V");
	//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	while(1)
	{    
		  //ͨ��0
		  result=lvbo(0xe3,0xc2);    
		  t1=4.096*2*result/65535;     //ת���ɵ�ѹ
          LCD_ShowxNum(122,20,result,5,16,0x80);
  		  t=t1;
		  LCD_ShowxNum(122,60,t,2,16,0x80);
          result=(t1-t)*1000;
		  LCD_ShowxNum(146,60,result,3,16,0x80);
          //delay_ms(5);
		  //ͨ��1
		  result=lvbo(0xe3,0xd2);    
		  t1=4.096*2*result/65535;     //ת���ɵ�ѹ
          t=t1;
		  LCD_ShowxNum(122,80,t,2,16,0x80);
          result=(t1-t)*1000;
		  LCD_ShowxNum(146,80,result,3,16,0x80);
          //delay_ms(5);
		  //ͨ��2
		  result=lvbo(0xe3,0xe2);    
		  t1=4.096*2*result/65535;     //ת���ɵ�ѹ
          t=t1;
		  LCD_ShowxNum(122,100,t,2,16,0x80);
          result=(t1-t)*1000;
		  LCD_ShowxNum(146,100,result,3,16,0x80);
		  //delay_ms(5);
		  //ͨ��3
		  result=lvbo(0xe3,0xf2);    
		  t1=4.096*2*result/65535;     //ת���ɵ�ѹ
          t=t1;
		  LCD_ShowxNum(122,120,t,2,16,0x80);
          result=(t1-t)*1000;
		  LCD_ShowxNum(146,120,result,3,16,0x80); 
          //delay_ms(100);
	}
 }

