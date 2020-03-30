/*******************************************************************************  
Module Name: eeprom.c 
Module Date: 19/03/2015   
Module Auth: CHEN LIANG
Description:            
Others     :
Revision History:  
Date        Rel Ver.    Notes  
19/03/2015   1.0        None
*******************************************************************************/ 

/* Includes ------------------------------------------------------------------*/ 
#include "stm8l15x_flash.h"
#include "stm8l15x.h"
#include "EErom.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lora.h"

u8 KZQ_ID[6] = {0x00,0X20,0X19,0X04,0X00,0X26};

int __eeprom_wait_for_last_operation(void)
{
  FLASH_Status_TypeDef status = FLASH_WaitForLastOperation(FLASH_MemType_Data);
  return !!(status&(FLASH_Status_Successful_Operation));
}
/*******************************************************************************  
函 数 名: EEPROM_Read()
功        能: EEPROM读数据
说        明: 
调        用: 
全局变量:
入口参数: Addr:内部偏移地址 RxBuffer:读取字符串  Length:字符串长度

*******************************************************************************/
unsigned char EEPROM_Read(unsigned int Addr,unsigned char *RxBuffer,unsigned char Length)
{
  u8 len;
  FLASH_Unlock(FLASH_MemType_Data);
  while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET)
        {}
  for(len=0;len<Length;len++){ 
    RxBuffer[len] = FLASH_ReadByte(Addr+len);   
   }
  FLASH_Lock(FLASH_MemType_Data);
  return 1;
}

/*********************************************************************  
函 数 名: EEPROM_Write()
功        能: EEPROM写数据
说        明: 
调        用: 
全局变量:
入口参数: Addr:内部偏移地址 RxBuffer:需要写入字符串  Length:字符串长度

*********************************************************************/

unsigned char EEPROM_Write(unsigned int Addr,unsigned char *RxBuffer,unsigned char Lenth)
{
  u8 len;
  FLASH_Unlock(FLASH_MemType_Data);
  while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET)
        {}
  for(len=0;len<Lenth;len++){
    FLASH_EraseByte(Addr+len);      
    FLASH_ProgramByte(Addr+len,RxBuffer[len]);
   }
  FLASH_Lock(FLASH_MemType_Data);
  return 1;
}

/*******************************************************************************
* Function Name   : data_chk
* Description     :字符串校验，
* Calls           :
* Called By       :
* Inputs          : None
* Outputs         : 返回字符串内容之和，有溢出
* Return          : None
* Notes           : None
*******************************************************************************/

unsigned char data_chk(unsigned char *ptr,unsigned char size)
{
    unsigned char ii,i2;
    i2=0;
    for(ii=0;ii<size;ii++)
        {
        i2=i2+ptr[ii];
        }
    return(i2);
}
//内存初始化函数
void SysData_Init(void)
{
  u8 falg=0;//内存初始华标记
  Lora_type lora_t={0};
  if(EEPROM_Read(EEPROMFALF_ADDR,(u8*)&falg,1)){
    if(falg == 0XAA){//不是第一次初始化
      EEPROM_Read(EEPROMLORA_ADDR,(u8*)&lora_t,5);
      Set_LoraConfig(lora_t.LoraFreq,lora_t.LoraPower,lora_t.LoraBw,lora_t.LoraSF,lora_t.LoraCR);//设置lora参数
      memset(KZQ_ID,0,6);
      EEPROM_Read(EEPROMID_ADDR,KZQ_ID,6);
    }else{//第一次初始化数据
      lora_t.LoraFreq = 57;
      lora_t.LoraPower = 0;
      lora_t.LoraBw = 7;
      lora_t.LoraSF = 9;
      lora_t.LoraCR = 1;
      EEPROM_Write(EEPROMLORA_ADDR,(u8*)&lora_t,5);//配置lora参数
      Set_LoraConfig(lora_t.LoraFreq,lora_t.LoraPower,lora_t.LoraBw,lora_t.LoraSF,lora_t.LoraCR);//设置lora参数
      EEPROM_Write(EEPROMID_ADDR,KZQ_ID,6);//配置ID
      falg = 0XAA;
      EEPROM_Write(EEPROMFALF_ADDR,(u8*)&falg,1);//配置lora参数
    }
  }
}
