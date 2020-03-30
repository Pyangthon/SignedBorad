#include "W25Qxx.h"

unsigned char W25QXX_BUF[256] = {0};


///******************************************************************************************************
//进入掉电模式
///******************************************************************************************************
void W25QXX_PowerDown(void)   
{ 
  	SPI_CS_L;                            //使能器件   
        SPIWrite8bit(W25X_PowerDown);        //发送掉电命令  
	SPI_CS_H;                            //取消片选     	      
        delay_us(3);                         //等待TPD  
}   
///******************************************************************************************************
//唤醒
///******************************************************************************************************
void W25QXX_WAKEUP(void)   
{  
  	SPI_CS_L;                            //使能器件   
        SPIWrite8bit(W25X_ReleasePowerDown); //send W25X_PowerDown command 0xAB    
	SPI_CS_H;                            //取消片选     	      
        delay_us(3);                         //等待TRES1
}
///******************************************************************************************************
//函数名：unsigned char W25QXX_ReadSR(void)   
//        读取W25QXX的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//返回值：BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
///******************************************************************************************************
unsigned char W25QXX_ReadSR(void)   
{  
	unsigned char byte=0;   
	SPI_CS_L;                            //使能器件   
	SPIWrite8bit(W25X_ReadStatusReg); //发送读取状态寄存器命令    
	byte = SPIRead8bit();          //读取一个字节  
	SPI_CS_H;                            //取消片选     
	return byte;   
} 
///******************************************************************************************************
//函数名：void W25QXX_Write_SR(u8 sr) 
//功能：写W25QXX状态寄存器  只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
//参数: sr 需要写的数据
//返回值：无
//作者： Mr.HE
///******************************************************************************************************
void W25QXX_Write_SR(unsigned char sr)   
{   
	SPI_CS_L;                            //使能器件   
	SPIWrite8bit(W25X_WriteStatusReg);   //发送写取状态寄存器命令    
	SPIWrite8bit(sr);                   //写入一个字节  
	SPI_CS_H;                        //取消片选     	      
} 
///******************************************************************************************************
//函数名：void W25QXX_Write_Enable(void)  
//功能：W25QXX写使能	将WEL置位  
//参数: 无
//返回值：无
//作者： Mr.HE
///******************************************************************************************************
void W25QXX_Write_Enable(void)   
{
	SPI_CS_L;                            //使能器件   
        SPIWrite8bit(W25X_WriteEnable);      //发送写使能  
	SPI_CS_H;                            //取消片选     	      
} 
///******************************************************************************************************
//函数名：void W25QXX_Write_Disable(void)  
//功能：W25QXX写禁止
//参数: 无
//返回值：无
//作者： Mr.HE
///******************************************************************************************************
void W25QXX_Write_Disable(void)   
{  
	SPI_CS_L;                            //使能器件   
        SPIWrite8bit(W25X_WriteDisable);     //发送写禁止指令    
	SPI_CS_H;                            //取消片选     	      
}
///******************************************************************************************************
//函数名：unsigned int W25QXX_ReadID(void)
//功能：读取芯片ID
//参数：无
//返回值如下:				   
//0XEF13,表示芯片型号为W25Q80  
//0XEF14,表示芯片型号为W25Q16    
//0XEF15,表示芯片型号为W25Q32  
//0XEF16,表示芯片型号为W25Q64 
//0XEF17,表示芯片型号为W25Q128
//作者：Mr.He
///******************************************************************************************************
unsigned int W25QXX_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_CS_L;				    
	SPIWrite8bit(0x90);//发送读取ID命令	    
	SPIWrite8bit(0x00); 	    
	SPIWrite8bit(0x00); 	    
	SPIWrite8bit(0x00); 	 			   
	Temp |= SPIRead8bit()<<8;  
	Temp |= SPIRead8bit();	 
	SPI_CS_H;				    
	return Temp;
}
///******************************************************************************************************
//函数名：void W25QXX_Wait_Busy(void)   
//功能：等待空闲
//参数：无
//返回值：无
//作者：Mr.He
///******************************************************************************************************
void W25QXX_Wait_Busy(void)   
{   
	while((W25QXX_ReadSR()&0x01) == 0x01);   // 等待BUSY位清空
} 
///******************************************************************************************************
//函数名：void W25QXX_Erase_Total_Sector(void)  
//功能：擦除整个芯片
//参数：无
//返回值：无
//作者：Mr.He
///******************************************************************************************************
void W25QXX_Erase_Total_Sector(void)   
{  
  
    W25Qxx_EN_ON; 
    //监视falsh擦除情况,测试用   
    //printf("fe:%x\r\n",Dst_Addr);	  
    //Dst_Addr*=4096;
    W25QXX_Write_Enable();                  //SET WEL 	 
    W25QXX_Wait_Busy();   
    SPI_CS_L;                            //使能器件   
    SPIWrite8bit(W25X_ChipErase);      //发送扇区擦除指令 
    //SPIWrite8bit((unsigned char)((Dst_Addr)>>16));  //发送24bit地址    
    //SPIWrite8bit((unsigned char)((Dst_Addr)>>8));   
    //SPIWrite8bit((unsigned char)Dst_Addr);  
    SPI_CS_H;                            //取消片选     	      
    W25QXX_Wait_Busy();   		//等待擦除完成
    W25Qxx_EN_OFF; 
}
///******************************************************************************************************
//函数名：void W25QXX_Erase_Sector(unsigned long Dst_Addr)   
//功能：擦除一个扇区  擦除一个扇区的最少时间:150ms
//参数：Dst_Addr:扇区地址 根据实际容量设置
//返回值：无
//作者：Mr.He
///******************************************************************************************************
void W25QXX_Erase_Sector(unsigned long Dst_Addr)   
{  
    //监视falsh擦除情况,测试用   
    //printf("fe:%x\r\n",Dst_Addr);	  
    Dst_Addr*=4096;
    W25QXX_Write_Enable();                  //SET WEL 	 
    W25QXX_Wait_Busy();   
    SPI_CS_L;                            //使能器件   
    SPIWrite8bit(W25X_SectorErase);      //发送扇区擦除指令 
    SPIWrite8bit((unsigned char)((Dst_Addr)>>16));  //发送24bit地址    
    SPIWrite8bit((unsigned char)((Dst_Addr)>>8));   
    SPIWrite8bit((unsigned char)Dst_Addr);  
    SPI_CS_H;                            //取消片选     	      
    W25QXX_Wait_Busy();   		//等待擦除完成
}
///******************************************************************************************************
//函数名：void W25QXX_Read(unsigned char * pBuffer,unsigned long ReadAddr,unsigned int NumByteToRead)   
//功能：读取SPI FLASH   在指定地址开始读取指定长度的数据
//参数：pBuffer:数据存储区  ReadAddr:开始读取的地址(24bit)  NumByteToRead:要读取的字节数(最大65535)
//返回值：无
//作者：Mr.He
///******************************************************************************************************
void W25QXX_Read(unsigned char * pBuffer,unsigned long ReadAddr,unsigned int NumByteToRead)   
{ 
 	unsigned int i;   										    
	SPI_CS_L;                            //使能器件   
    SPIWrite8bit(W25X_ReadData);         //发送读取命令   
    SPIWrite8bit((unsigned char)((ReadAddr)>>16));  //发送24bit地址    
    SPIWrite8bit((unsigned char)((ReadAddr)>>8));   
    SPIWrite8bit((unsigned char)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
    { 
        pBuffer[i] = SPIRead8bit();   //循环读数  
    }
	SPI_CS_H;  				    	      
} 
///******************************************************************************************************
//函数名：void W25QXX_Write_Page(unsigned char* pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)
//功能：SPI在一页(0~65535)内写入少于256个字节的数据  在指定地址开始写入最大256字节的数据
//参数：
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!
//返回值：无
//作者；Mr.He
///******************************************************************************************************
void W25QXX_Write_Page(unsigned char* pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)
{
 	unsigned int i;  
    W25QXX_Write_Enable();                  //SET WEL 
    SPI_CS_L;                            //使能器件   
    SPIWrite8bit(W25X_PageProgram);      //发送写页命令   
    SPIWrite8bit((unsigned char)((WriteAddr)>>16)); //发送24bit地址    
    SPIWrite8bit((unsigned char)((WriteAddr)>>8));   
    SPIWrite8bit((unsigned char)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)
    SPIWrite8bit(pBuffer[i]);//循环写数  
    SPI_CS_H;                            //取消片选 
    W25QXX_Wait_Busy();					   //等待写入结束
}
///******************************************************************************************************
//函数名：void W25QXX_Write_NoCheck(unsigned char* pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)   
//功能：
//无检验写SPI FLASH  必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//参数：
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
//返回值：无
//作者：Mr.He
///******************************************************************************************************
void W25QXX_Write_NoCheck(unsigned char* pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)   
{ 			 		 
	unsigned int pageremain;
//        W25Qxx_EN_ON;        //开启W25Q64电源 
      	pageremain = 256 - WriteAddr % 256; //单页剩余的字节数	
        
	if(NumByteToWrite <= pageremain)
        {
          pageremain = NumByteToWrite;//不大于256个字节
        }
	while(1)
	{	   
		W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
                
		if(NumByteToWrite == pageremain)
                {
                  break;//写入结束了
                }
                else //NumByteToWrite > pageremain
		{
			pBuffer += pageremain;   //数据内容起始地址 +256
			WriteAddr += pageremain; //需要写入数据的地址 +256	

			NumByteToWrite -= pageremain;	      //减去已经写入了的字节数
			if(NumByteToWrite > 256)
                        {
                          pageremain = 256; //一次可以写入256个字节
                        }
			else 
                        {
                          pageremain = NumByteToWrite;       //不够256个字节了
                        }
		}
	};
//        W25Qxx_EN_OFF;        //关闭W25Q64电源  
} 
///******************************************************************************************************
//大小：8M（Byte）（128块（Block），每块64K字节，每块16个扇区（Sector），每个扇区4K字节，每个扇区16页，每页256个字节）
//函数名：void W25QXX_Write(unsigned char * pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)   
//功能： 写SPI FLASH  在指定地址开始写入指定长度的数据   该函数带擦除操作!
//参数:
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)						
//NumByteToWrite:要写入的字节数(最大65535)
//返回值：无
//作者：Mr.He
///******************************************************************************************************		 
void W25QXX_Write(unsigned char * pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)
{ 
     unsigned int y = 0 , i = 0; 
     unsigned int Page = 0;     //扇区内地址
     unsigned int secoff=0;      //扇区内地址偏移
     unsigned int Pageremain = 0;//扇区内剩余地址
     unsigned int offic = 0;
	
//     W25Qxx_EN_ON;        //开启W25Q64电源       
//     if(WriteAddr > 4096)   //地址大于4096
//        return;
	  
        Page = (WriteAddr & 0x0FFF) / 256;  //该扇区的多少页
      secoff = (WriteAddr & 0x0FFF) % 256;  //扇区内地址偏移
      Pageremain = 256 - secoff; //该页剩余多少空间
        	
      W25QXX_Erase_Sector(Origination_ADD / 4096);//擦除需要保存的扇区
      
      for(y = 0 ; y < 16 ; y++ )
      {
           W25QXX_Read(W25QXX_BUF,(WriteAddr & 0xF000) + (256 * y),256);//读出一个页的内
		   
           if(y == Page)//找到所在的页
           {
               if(Pageremain >= NumByteToWrite)//写的长度小于扇区地址
               { 
                       for(i = 0; i < NumByteToWrite; i++)
                       {
                         W25QXX_BUF[secoff++] = pBuffer[i + offic];                       
                       }
                       offic += NumByteToWrite;
               }
               else //写的长度大于扇区剩余地址
               {
                       for(i = 0; i < Pageremain; i++)
                       {
                         W25QXX_BUF[secoff++] = pBuffer[i + offic];
                       }
                       NumByteToWrite = NumByteToWrite - Pageremain;//剩余数据长度
                       Page += 1;
                       offic += Pageremain;
                       secoff = 0;
                       Pageremain = 256;
               }               
           }
           W25QXX_Write_NoCheck(W25QXX_BUF,Origination_ADD + (256 * y),256);//写入数据读出的数据	   
      }
      
          memset(W25QXX_BUF,0,sizeof(W25QXX_BUF));
          W25QXX_Erase_Sector(WriteAddr / 4096);//擦除需要保存的扇区
      for( y = 0 ; y < 16 ; y++)
      {
          W25QXX_Read(W25QXX_BUF,Origination_ADD + (256 * y),256);//读出一个页的内容
          W25QXX_Write_NoCheck(W25QXX_BUF,(WriteAddr & 0xF000) + (256 * y),256);//写入数据读出的数据 
      }  
//       W25QXX_PowerDown();
 //      W25Qxx_EN_OFF;        //关闭W25Q64电源  
}





  
