#include "NB_Iot_BC95.h"

Dispaly_T WaitTimer = {0};
NBState_Typ nbs = {0};


///******************************************************************************
//*��������void NB_Power_ON(void)   
//*�������ܣ�NBģ���ϵ�
//*��������
//*����ֵ����
//*���ߣ�
//*******************************************************************************/
void NB_Power_ON(void)    
{
      NB_POWER_ON;
      DelayMs(10,TRUE);
      NB_POWERKEY_ON;
      DelayMs(500,TRUE);
      NB_POWERKEY_OFF;
}
///******************************************************************************
//*��������void NB_Power_OFF(void)   
//*�������ܣ�NBģ�����
//*��������
//*����ֵ����
//*���ߣ�
//*******************************************************************************/
void NB_Power_OFF(void)     
{
      NB_POWER_OFF;
      //DelayMs(10,TRUE);
      //NB_POWERKEY_ON;

}
///*******************************************************************************
//*������:void Wait_Time(void)
//*����:�ȴ�ʱ�亯��   �ú��������� stm8l15x_it.c RTC�ж��� 
//*����:��
//*���:��
//*��ע:��
//*******************************************************************************/
void Wait_Time(void)
{
  if(WaitTimer.Time > 0)
  {
    WaitTimer.Time--;
    if(WaitTimer.Time == 0)
    {
      WaitTimer.Flag = TRUE;
    }
  }
}
///******************************************************************************
//*��������void SetWaitTime(unsigned int time) 
//*�������ܣ����õȴ���Ӧʱ�亯��
//*������time  ʱ�� ��s��
//*����ֵ����
//*���ߣ�
//*******************************************************************************/
void SetWaitTime(unsigned int time) 
{
   WaitTimer.Time = time;
}
///******************************************************************************
//*��������unsigned char NB_SendCmd(unsigned char *cmd,unsigned char *ack,unsigned int waittime) 
//*�������ܣ�NB BC95 �������� �ȴ� ack ֵ
//*������cmd  ����  ack  ��Ӧֵ  waittime  �ȴ�ʱ��
//*����ֵ��0 �ɹ�  1 ʧ��
//*���ߣ�
//*******************************************************************************/
unsigned char NB_SendCmd(unsigned char *cmd,unsigned char *ack,unsigned int waittime)   
{
    unsigned char res = 0;
     
     UsartSend(USART1,cmd,(unsigned int)(strlen((const char *)cmd)));
     USART_1.Length = 0;
     memset(USART_1.USART_Date, 0, Max_Lenght);
     
     while(--waittime)	//�ȴ�����ʱ
    {
        DelayMs(500, TRUE);
        if(USART_1.Length != 0)//���յ�����
        {
            if(strstr((const char *)USART_1.USART_Date, (const char *)ack))//���յ��ڴ���Ӧ����
            {
                res = 0;
                USART_1.Length = 0;
              //  memset(USART_1.USART_Date,0,Max_Lenght);
                break;
            }
            else
            {
                res = 1;
                USART_1.Length = 0;
                memset(USART_1.USART_Date,0,Max_Lenght);
                break;
            }
        }
    }
    return res;
}

///******************************************************************************
//*������:char WaitResponseData(void)
//*����:�ȴ�Ӧ������
//*����:��
//*���:0:��ʾ�ɹ�  1����ʾʧ��
//*��ע:��
//*******************************************************************************/
char WaitResponseData(unsigned char *Data)
{ 
      char *temp;  char res = 1;
     
      USART_1.Length = 0;
      memset(USART_1.USART_Date,0,Max_Lenght);
      SetWaitTime(10); //���õȴ�ʱ��
      WaitTimer.Flag = FALSE;
      while(WaitTimer.Flag != TRUE)
      {
            DelayMs(1000,TRUE);
            DispNum(7, (WaitTimer.Time) / 10); //wait/10-I
            DispNum(8, (WaitTimer.Time) % 10); //wait/10
            
           if(USART_1.Length != 0) //�������
           {
              if(strstr((const char *)USART_1.USART_Date, "+M2MCLIRECV:") != NULL)
              {
                  temp = strstr((const char *)USART_1.USART_Date, ":");
                
//                  StrToHex((char *)Data, temp + 1, strlen(temp) / 2);          
                  res = 0;
                  break;

              }
              else
              {
                 USART_1.Length = 0;
                 memset(USART_1.USART_Date,0,Max_Lenght);
              }
           }    
      }
      
      return res;
}

///******************************************************************************
//*��������unsigned char NB_send_CoAP_msg(int dataLen, char *data, int waittime) 
//*�������ܣ�NB ��������
//*������dataLen�� ���ݳ���   *data ��������  waittime  �������ݵȴ�ʱ��
//*����ֵ������ֵ0�����ͳɹ�������UDPΪ���Ĵ��䣬���������Ƿ���յ�ģ�����޷�ȷ�ϵģ�
//         ����ֵ1������ʧ��
//*���ߣ�
//*******************************************************************************/
unsigned char NB_send_CoAP_msg(int dataLen, char *data, int waittime)
{
    //eg:AT+NMGS=6,010412345678
    char ptr[230] = "AT+NMGS=";
    uint8_t LenChar[4];
    memset(LenChar, 0, 4);
    
    //itoa_i(dataLen, (char *)LenChar);
    //strcat(ptr, (const char *)LenChar);
    //strcat(ptr, ",");
    strcat(ptr, data);
    strcat(ptr, "\r\n");
    if(!NB_SendCmd((uint8_t *)ptr, (uint8_t *)"OK", 2000))
    {
        return 0;
    }
    return 1;
}
///******************************************************************************
//*������:cahr Get_NB_Parameter(void)
//*����:��ȡNBģ�����
//*����:��
//*���:��
//*��ע:��
//*******************************************************************************/
char Get_NB_Parameter(void)
{
      int res = 0;
  
      if(NB_SendCmd((u8 *)NB_AT_CGSN, (u8 *)NB_ACK_OK, 10) == 0) //��ȡ�豸��
      {
        if(strstr((char*)(USART_1.USART_Date+10),"CGSN:"))
        {
          memcpy(nbs.IMEI, strstr((char*)(USART_1.USART_Date+10),"CGSN:")+6, 15);
        }
        else
        {
           res = 1;
        }
      }
      
      if(NB_SendCmd((u8 *)NB_AT_CSQ, (u8 *)NB_ACK_OK, 10) == 0) //��ȡNB�����ź�ǿ��
      {
        if(strstr((char*)(USART_1.USART_Date+10),"CSQ:"))
        {
          memcpy(nbs.NBNss, strstr((char*)(USART_1.USART_Date+10),"CSQ:")+5, 2);
        }
        else
        {
          res = 1;
         }
      }
      
      if(NB_SendCmd((u8 *)NB_AT_NCCID, (u8 *)NB_ACK_OK, 10) == 0) //��ȡNBICCID
      {
        if(strstr((char*)(USART_1.USART_Date + 10),"ICCID:"))
        {
           memcpy(nbs.NBICCID, strstr((char*)(USART_1.USART_Date+10),"ICCID:")+7, 20);        
        }
         else
         {
           res = 1;
         }        
      }  
      
      return res;
}
///******************************************************************************
//*������:unsigned char NBRegister(void)
//*����:NB ע������
//*����:��
//*���:0:��ʾ�����ɹ� 1����ʾ����ʧ��
//*��ע:��
//*******************************************************************************/
unsigned char NBRegister(void)
{
        char res = 0 , count = 0;
        
        NB_Power_ON();   //ģ���ϵ�
        
        while((0 != NB_SendCmd((u8 *)NB_AT_CEREG,(u8 *)NB_ACK_CEREG,10)) && (count <= 15))//����Զ������ɹ�û
        {  
          count++;         
          DelayMs(200,TRUE);
        }
        
        if(count >= 30)   //ģ������ʧ��
        {
           res = 1;
        }
        else    //ģ�������ɹ�
        {       
            if(Get_NB_Parameter() == 0)  //��ȡNBģ����غ���
            {
              
              if(0 != NB_SendCmd((u8 *)NB_AT_NCDP_SET,(u8 *)NB_ACK_OK,10))//ģ��ע��ƽ̨
              {     
                  res = 0;
                  //break;
              }
            }
            else
            {
               res = 1;
            }
        }
        
   return res;
}



