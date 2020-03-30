#ifndef __W25Qxx_H
#define __W25Qxx_H

#include "SPI.h"
#include "Delay.h"
#include "string.h"
// #include "systemMessage.h"



#define W25Qxx_EN_ON   GPIO_ResetBits(GPIOF,GPIO_Pin_7)
#define W25Qxx_EN_OFF  GPIO_SetBits(GPIOF,GPIO_Pin_7)


#define Origination_ADD  0x0C0000    //保存读取出来的数据起始地址

////////////////////////////////////////////////////////////////////////////////// 
//指令表
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	        0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	        0x90 
#define W25X_JedecDeviceID		0x9F 

extern void W25QXX_Erase_Sector(unsigned long Dst_Addr);
extern void W25QXX_Read(unsigned char * pBuffer,unsigned long ReadAddr,unsigned int NumByteToRead);   
extern void W25QXX_Write(unsigned char * pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite); 
extern void W25QXX_Write_NoCheck(unsigned char* pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite) ;
extern void W25QXX_PowerDown(void);
extern void W25QXX_WAKEUP(void);   
extern void W25QXX_Erase_Total_Sector(void);


#endif
