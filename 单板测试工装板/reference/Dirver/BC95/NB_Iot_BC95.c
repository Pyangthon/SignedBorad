#include "NB_Iot_BC95.h"

Dispaly_T WaitTimer = {0};
NBState_Typ nbs = {0};


///******************************************************************************
//*函数名：void NB_Power_ON(void)   
//*函数功能：NB模块上电
//*参数：无
//*返回值：无
//*作者：
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
//*函数名：void NB_Power_OFF(void)   
//*函数功能：NB模块掉电
//*参数：无
//*返回值：无
//*作者：
//*******************************************************************************/
void NB_Power_OFF(void)     
{
      NB_POWER_OFF;
      //DelayMs(10,TRUE);
      //NB_POWERKEY_ON;

}
///*******************************************************************************
//*函数名:void Wait_Time(void)
//*功能:等待时间函数   该函数放置在 stm8l15x_it.c RTC中断中 
//*输入:无
//*输出:无
//*备注:无
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
//*函数名：void SetWaitTime(unsigned int time) 
//*函数功能：设置等待响应时间函数
//*参数：time  时间 （s）
//*返回值：无
//*作者：
//*******************************************************************************/
void SetWaitTime(unsigned int time) 
{
   WaitTimer.Time = time;
}
///******************************************************************************
//*函数名：unsigned char NB_SendCmd(unsigned char *cmd,unsigned char *ack,unsigned int waittime) 
//*函数功能：NB BC95 发送数据 等待 ack 值
//*参数：cmd  命令  ack  响应值  waittime  等待时间
//*返回值：0 成功  1 失败
//*作者：
//*******************************************************************************/
unsigned char NB_SendCmd(unsigned char *cmd,unsigned char *ack,unsigned int waittime)   
{
    unsigned char res = 0;
     
     UsartSend(USART1,cmd,(unsigned int)(strlen((const char *)cmd)));
     USART_1.Length = 0;
     memset(USART_1.USART_Date, 0, Max_Lenght);
     
     while(--waittime)	//等待倒计时
    {
        DelayMs(500, TRUE);
        if(USART_1.Length != 0)//接收到数据
        {
            if(strstr((const char *)USART_1.USART_Date, (const char *)ack))//接收到期待的应答结果
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
//*函数名:char WaitResponseData(void)
//*功能:等待应答数据
//*输入:无
//*输出:0:表示成功  1：表示失败
//*备注:无
//*******************************************************************************/
char WaitResponseData(unsigned char *Data)
{ 
      char *temp;  char res = 1;
     
      USART_1.Length = 0;
      memset(USART_1.USART_Date,0,Max_Lenght);
      SetWaitTime(10); //设置等待时间
      WaitTimer.Flag = FALSE;
      while(WaitTimer.Flag != TRUE)
      {
            DelayMs(1000,TRUE);
            DispNum(7, (WaitTimer.Time) / 10); //wait/10-I
            DispNum(8, (WaitTimer.Time) % 10); //wait/10
            
           if(USART_1.Length != 0) //接受完成
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
//*函数名：unsigned char NB_send_CoAP_msg(int dataLen, char *data, int waittime) 
//*函数功能：NB 发送数据
//*参数：dataLen： 数据长度   *data 数据内容  waittime  发送数据等待时间
//*返回值：返回值0，发送成功（鉴于UDP为报文传输，数据主机是否接收到模块是无法确认的）
//         返回值1，发送失败
//*作者：
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
//*函数名:cahr Get_NB_Parameter(void)
//*功能:获取NB模块参数
//*输入:无
//*输出:无
//*备注:无
//*******************************************************************************/
char Get_NB_Parameter(void)
{
      int res = 0;
  
      if(NB_SendCmd((u8 *)NB_AT_CGSN, (u8 *)NB_ACK_OK, 10) == 0) //读取设备号
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
      
      if(NB_SendCmd((u8 *)NB_AT_CSQ, (u8 *)NB_ACK_OK, 10) == 0) //读取NB网络信号强度
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
      
      if(NB_SendCmd((u8 *)NB_AT_NCCID, (u8 *)NB_ACK_OK, 10) == 0) //读取NBICCID
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
//*函数名:unsigned char NBRegister(void)
//*功能:NB 注册入网
//*输入:无
//*输出:0:表示入网成功 1：表示入网失败
//*备注:无
//*******************************************************************************/
unsigned char NBRegister(void)
{
        char res = 0 , count = 0;
        
        NB_Power_ON();   //模块上电
        
        while((0 != NB_SendCmd((u8 *)NB_AT_CEREG,(u8 *)NB_ACK_CEREG,10)) && (count <= 15))//检查自动入网成功没
        {  
          count++;         
          DelayMs(200,TRUE);
        }
        
        if(count >= 30)   //模块入网失败
        {
           res = 1;
        }
        else    //模块入网成功
        {       
            if(Get_NB_Parameter() == 0)  //获取NB模块相关函数
            {
              
              if(0 != NB_SendCmd((u8 *)NB_AT_NCDP_SET,(u8 *)NB_ACK_OK,10))//模块注册平台
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



