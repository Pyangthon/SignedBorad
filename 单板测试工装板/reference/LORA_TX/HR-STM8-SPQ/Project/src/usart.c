#include "usart.h"
#include "EErom.h"

u8  RxBuffer[BUFFER_LEN];
u8  u1_flag = 0; 

//4G 
u32 Lora_Freq[]={
  433000000 , //CH0
  434000000,  //CH1 
  435000000,  //CH2 
  436000000,  //  CH3 
  437000000,  //  CH4 
  438000000,  //  CH5
  439000000,  //  CH6
  440000000,  //CH7
  441000000,  //CH8  
  442000000,  //CH9
  443000000,  //CH10
  444000000,  //CH11
  445000000,  //CH12 
  446000000,  //CH13
  447000000,  //CH14
  448000000,  //CH15
  449000000,  //CH16
  450000000,  //CH17
  451000000,  //CH18
  452000000,  //CH19
  453000000,  //CH20 
  454000000,  //CH21
  455000000,  //CH22
  456000000,  //CH23
  457000000,  //CH24 
  458000000,  //CH25
  459000000,  //CH26
  460000000,  //CH27
  461000000,  //CH28 
  462000000,  //CH29
  463000000,  //CH30
  464000000,  //CH31
  465000000,  //CH32
  466000000,  //CH33
  467000000,  //CH34
  468000000,  //CH35  
  469000000,  //CH36 
  470000000,  //CH37
  471000000,  //CH38
  472000000,  //CH39
  473000000,  //CH40
  474000000,  //CH41   
  475000000,  //CH42
  476000000,  //CH43
  477000000,  //CH44
  478000000,  //CH45
  479000000,  //CH46
  480000000,  //CH47
  481000000,  //CH48
  482000000,  //CH49
  483000000,  //CH50
  484000000,  //CH51
  485000000,  //CH52
  486000000,  //CH53
  487000000,  //CH54 
  488000000,  //CH55
  489000000,  //CH56
  490000000,  //CH57
  491000000,  //CH58
  492000000,  //CH59
  493000000,  //CH60
  494000000,  //CH61
  495000000,  //CH62
  496000000,  //CH63
  497000000,  //CH64
  498000000,  //CH65
  499000000,  //CH66
  500000000,  //CH67
  501000000,  //CH68
  502000000,  //CH69
  503000000,  //CH70
  504000000,  //CH71
  505000000,  //CH72
  506000000,  //CH73
  507000000,  //CH74
  508000000,  //CH75
  509000000,  //CH76
};

/****************USART1��ʼ������***********/
void Usart_Init(u32 spend){
  
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_In_FL_No_IT);	   //RXD
	//rxd��ʼ��Ϊ�����ж���������ģʽ	
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Slow);	//TXD
	//txd��ʼ��Ϊ�ߵ�ƽ�����������ģʽ
    GPIO_Init(GPIOC,GPIO_Pin_4,GPIO_Mode_Out_PP_Low_Fast);  //����PC4 RS485ʹ��
    
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);  //ʹ��USART1ʱ��
    USART_DeInit(USART1);
    
    USART_Init(USART1,spend,USART_WordLength_8b,
			USART_StopBits_1,USART_Parity_No,
			(USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx));
	/*���ô��ڲ���:���ںţ������ʣ��ֳ��ȣ�����λ��У��λ���շ�ģʽ*/
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//�򿪴��ڽ����ж�
    USART_Cmd(USART1,ENABLE);
    
	/*ʹ�ܴ���*/
    RS485_RECV_MODE();
    //RS485_SEND_MODE();
}


/******************************************************************************************************
*������ :void UsartSend(USART_TypeDef* USARTx, char *str, char Len) 
*˵��   :�������ݷ��ͺ���
*����   :USARTx: x = 1 ~ 3  str: �������ݵ��׵�ַ   Len:  ���ݵĳ���
*����ֵ :��
*******************************************************************************************************/
void UsartSend(USART_TypeDef* USARTx, u8 *str, u8 Len) 
{
      RS485_SEND_MODE();
      for(int i =0; i < Len; i++)
      {
        USART_ClearFlag(USARTx,USART_FLAG_TC); //���TCλ
        USART_SendData8(USARTx,str[i]);//��������
        while (USART_GetFlagStatus(USART1,USART_FLAG_TC) !=SET); //��ѯ֪��������ϣ��ȴ�TC=1
      } 
      RS485_RECV_MODE();
} 

//�����������
void u1_clear_rxbuffer(void)
{
	u16 i;
	u1_flag=0;
	for(i = 0;i < BUFFER_LEN;i ++){
	  RxBuffer[i]=0;
	}
}

//��С��ת��
void ReverStr(const u8* old_data,u8* new_data,u8 len)
{
	u8 i;
	for(i=0;i<len;i++){
	  new_data[i]=old_data[len-i-1];
	}
        //UsartSend(USART1,new_data,4);
}
//���������ַ�
u8 Link_Str(u8 *new_str,u8* new_len,const u8* old_str,u8 len)
{
  u8 i;
  u8 size;
  size = * new_len;
  if(size+len>255){
    return 0;
  }
  for(i=0;i<size;i++){
    new_str[size+len-1-i] = new_str[size-1-i];
  }
  for(i=0;i<len;i++){
    new_str[i] = old_str[i];
  }
  * new_len = * new_len+len;
  return 1;
}

//��鴮����������
u8 chack_Data(u8 *data)
{
	u8 MSB, LSB;
	N_CRC16(data, data[4]+5,&MSB, &LSB);
	if( (LSB==data[data[4]+5]) && (MSB==data[data[4]+5+1])){
	return 1;
	}
	return 0;
}
//��Ӧ�����������
void Response_Config(u8* data,u8 falg)
{
	u8 buf[9];
	buf[0] = 0XFD;
        memcpy(buf+1,data,3);
        if(falg==1){
	  buf[4] = 0X02;
          buf[5] = 0X4F;
	  buf[6] = 0X4B;
        }
        else{
          buf[4] = 0X00;
        }
        N_CRC16(buf, buf[4]+5,&buf[buf[4]+6], &buf[buf[4]+5]);
        UsartSend(USART1,buf,buf[4]+7);
}

//���ÿ�����ID
u8 SetKzq_Id(u8 *data)
{
  if(data[0]==6){
    memset(KZQ_ID,0,6);
    EEPROM_Write(EEPROMID_ADDR,data+1,6);//д��EEROM
    EEPROM_Read(EEPROMID_ADDR,KZQ_ID,6);
    //UsartSend(USART1,KZQ_ID,6);
    //memcpy(KZQ_ID,data+1,data[0]);
    return 1;
  }
  return 0;
}

//����LORA����
u8 Set_Lora(u8 *data)
{
   u8 i; 
   u16 Power;
   u32 Freq;
   Lora_type lora_t;
   //ReverStr(data+1,(u8*)&Freq,4);
   memcpy((u8*)&Freq,data+1,4);
   for(i=0;i<77;i++){
      if(Freq==Lora_Freq[i]){
	Freq = i;
	break;
      }
    }
   if(i==77){
      return 0;
    }
  memcpy((u8*)&Power,data+5,2);
  if(Power>0 && Power<=11){
	Power = 3;
  }else if(Power>11 && Power<=14){
	Power = 2;
  }else if(Power>14 && Power<=17){
	Power = 1;
  }else if(Power>17 && Power<=20){
	Power = 0;
  }
  //ReverStr(data+5,(u8*)&Power,2);
  //void Set_LoraConfig(u8 Freq,u8 Power,u8 Bw,u8 SF,u8 CR)
  lora_t.LoraFreq = (u8)Freq;
  lora_t.LoraPower = (u8)Power;
  lora_t.LoraBw = data[7];
  lora_t.LoraSF = data[8];
  lora_t.LoraCR = data[9];
  EEPROM_Write(EEPROMLORA_ADDR,(u8*)&lora_t,5);//д��EEROM
  //EEPROM_Read(EEPROMLORA_ADDR,KZQ_ID,5);
  Set_LoraConfig((u8)Freq,(u8)Power,data[7],data[8],data[9]);
  
  return 1;
  
}
//��ȡ��������ַ
void GetKzq_Id(u8 *data)
{
  u8 buf[13];
  buf[0] = 0XFD;
  memcpy(buf+1,data,3);
  buf[4]=0X06;
  memcpy(buf+5,KZQ_ID,6);
  N_CRC16(buf, buf[4]+5,&buf[buf[4]+6], &buf[buf[4]+5]);
  UsartSend(USART1,buf,buf[4]+7);
}

//��ȡLORA����
void Get_Lora(u8 *data)
{
  u8 buf[16];
  u32 Freq=0;
  u16 Power=0;
  
  buf[0] = 0XFD;
  memcpy(buf+1,data,3);
  buf[4] = 0X09;
  Get_LoraConfig(&buf[5],&buf[9],&buf[11],&buf[12],&buf[13]);
  
  Freq = Lora_Freq[buf[5]];
  
  //ReverStr((u8*)&Freq,&buf[5],4);
  memcpy(&buf[5],(u8*)&Freq,4);
  //UsartSend(USART1,&buf[5],4);
  if(buf[9]==0){
	Power = 20;
  }else if(buf[9]==1){
	Power = 17;
  }else if(buf[9]==2){
	Power = 14;
  }else if(buf[9]==3){
	Power = 11;
  }
  memcpy(&buf[9],(u8*)&Power,2);
  //ReverStr((u8*)&Power,&buf[9],2);
  N_CRC16(buf, buf[4]+5,&buf[15], &buf[14]); 
  UsartSend(USART1,buf,buf[4]+7);
}

//RS486���� 1.���ڹ������ã�2 ��������������
void Rs485_Event(void)
{
  u8 Response_flag=0;
  if(u1_flag){
    IWDG_ReloadCounter();  //�������Ź�ι��
    if(RxBuffer[0]==0XFC && chack_Data(RxBuffer)){
       
        switch(RxBuffer[3]){  
        case  0x01:  //���ÿ�������ַ
          if(SetKzq_Id(&RxBuffer[4])){
            Response_flag=1;
          }else{
            Response_flag=0;
          }
          Response_Config(&RxBuffer[1],Response_flag);
          break;
          
        case 0X02:  //����Lora����
          if(Set_Lora(&RxBuffer[4])){
            Response_flag=1;
          }else{
            Response_flag=0;
          }
          Response_Config(&RxBuffer[1],Response_flag);
          break;
          
        case 0X11:  //��ȡ��������ַ
          GetKzq_Id(&RxBuffer[1]);
          break;
          
        case 0X12:  //��ȡLora����
          Get_Lora(&RxBuffer[1]);
          break;
        }
      
    }else if(RxBuffer[0]==0XAA && RxBuffer[5] == 0X3A){
          // UsartSend(USART1,RxBuffer,u1_flag);
         
           FLASH_Unlock(FLASH_MemType_Program);
           while (FLASH_GetFlagStatus(FLASH_FLAG_PUL) == RESET)
        {}
           FLASH_EraseByte(UPDATAFLAG_FLAG);
           
           FLASH_ProgramByte(UPDATAFLAG_FLAG,RxBuffer[0]);//����������־λ
           
           RxBuffer[0] = FLASH_ReadByte(UPDATAFLAG_FLAG);
           
           FLASH_Lock(FLASH_MemType_Program);
           
           while(1){}//�ȴ���λ  
        
      }else { 
       Link_Str(RxBuffer,&u1_flag,KZQ_ID,6);
       RF1278_SendPacket(RxBuffer,u1_flag);
       Rf1278_ModeSet(100);
      // RF1278_ReadRssiSnr(&riss);
       //UsartSend(USART1,RxBuffer,u1_flag);
     }
    u1_clear_rxbuffer();
   }
}
