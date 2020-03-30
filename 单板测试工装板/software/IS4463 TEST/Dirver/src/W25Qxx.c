#include "W25Qxx.h"

unsigned char W25QXX_BUF[256] = {0};


///******************************************************************************************************
//�������ģʽ
///******************************************************************************************************
void W25QXX_PowerDown(void)   
{ 
  	SPI_CS_L;                            //ʹ������   
        SPIWrite8bit(W25X_PowerDown);        //���͵�������  
	SPI_CS_H;                            //ȡ��Ƭѡ     	      
        delay_us(3);                         //�ȴ�TPD  
}   
///******************************************************************************************************
//����
///******************************************************************************************************
void W25QXX_WAKEUP(void)   
{  
  	SPI_CS_L;                            //ʹ������   
        SPIWrite8bit(W25X_ReleasePowerDown); //send W25X_PowerDown command 0xAB    
	SPI_CS_H;                            //ȡ��Ƭѡ     	      
        delay_us(3);                         //�ȴ�TRES1
}
///******************************************************************************************************
//��������unsigned char W25QXX_ReadSR(void)   
//        ��ȡW25QXX��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//����ֵ��BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
///******************************************************************************************************
unsigned char W25QXX_ReadSR(void)   
{  
	unsigned char byte=0;   
	SPI_CS_L;                            //ʹ������   
	SPIWrite8bit(W25X_ReadStatusReg); //���Ͷ�ȡ״̬�Ĵ�������    
	byte = SPIRead8bit();          //��ȡһ���ֽ�  
	SPI_CS_H;                            //ȡ��Ƭѡ     
	return byte;   
} 
///******************************************************************************************************
//��������void W25QXX_Write_SR(u8 sr) 
//���ܣ�дW25QXX״̬�Ĵ���  ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
//����: sr ��Ҫд������
//����ֵ����
//���ߣ� Mr.HE
///******************************************************************************************************
void W25QXX_Write_SR(unsigned char sr)   
{   
	SPI_CS_L;                            //ʹ������   
	SPIWrite8bit(W25X_WriteStatusReg);   //����дȡ״̬�Ĵ�������    
	SPIWrite8bit(sr);                   //д��һ���ֽ�  
	SPI_CS_H;                        //ȡ��Ƭѡ     	      
} 
///******************************************************************************************************
//��������void W25QXX_Write_Enable(void)  
//���ܣ�W25QXXдʹ��	��WEL��λ  
//����: ��
//����ֵ����
//���ߣ� Mr.HE
///******************************************************************************************************
void W25QXX_Write_Enable(void)   
{
	SPI_CS_L;                            //ʹ������   
        SPIWrite8bit(W25X_WriteEnable);      //����дʹ��  
	SPI_CS_H;                            //ȡ��Ƭѡ     	      
} 
///******************************************************************************************************
//��������void W25QXX_Write_Disable(void)  
//���ܣ�W25QXXд��ֹ
//����: ��
//����ֵ����
//���ߣ� Mr.HE
///******************************************************************************************************
void W25QXX_Write_Disable(void)   
{  
	SPI_CS_L;                            //ʹ������   
        SPIWrite8bit(W25X_WriteDisable);     //����д��ָֹ��    
	SPI_CS_H;                            //ȡ��Ƭѡ     	      
}
///******************************************************************************************************
//��������unsigned int W25QXX_ReadID(void)
//���ܣ���ȡоƬID
//��������
//����ֵ����:				   
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64 
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128
//���ߣ�Mr.He
///******************************************************************************************************
unsigned int W25QXX_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_CS_L;				    
	SPIWrite8bit(0x90);//���Ͷ�ȡID����	    
	SPIWrite8bit(0x00); 	    
	SPIWrite8bit(0x00); 	    
	SPIWrite8bit(0x00); 	 			   
	Temp |= SPIRead8bit()<<8;  
	Temp |= SPIRead8bit();	 
	SPI_CS_H;				    
	return Temp;
}
///******************************************************************************************************
//��������void W25QXX_Wait_Busy(void)   
//���ܣ��ȴ�����
//��������
//����ֵ����
//���ߣ�Mr.He
///******************************************************************************************************
void W25QXX_Wait_Busy(void)   
{   
	while((W25QXX_ReadSR()&0x01) == 0x01);   // �ȴ�BUSYλ���
} 
///******************************************************************************************************
//��������void W25QXX_Erase_Total_Sector(void)  
//���ܣ���������оƬ
//��������
//����ֵ����
//���ߣ�Mr.He
///******************************************************************************************************
void W25QXX_Erase_Total_Sector(void)   
{  
  
    W25Qxx_EN_ON; 
    //����falsh�������,������   
    //printf("fe:%x\r\n",Dst_Addr);	  
    //Dst_Addr*=4096;
    W25QXX_Write_Enable();                  //SET WEL 	 
    W25QXX_Wait_Busy();   
    SPI_CS_L;                            //ʹ������   
    SPIWrite8bit(W25X_ChipErase);      //������������ָ�� 
    //SPIWrite8bit((unsigned char)((Dst_Addr)>>16));  //����24bit��ַ    
    //SPIWrite8bit((unsigned char)((Dst_Addr)>>8));   
    //SPIWrite8bit((unsigned char)Dst_Addr);  
    SPI_CS_H;                            //ȡ��Ƭѡ     	      
    W25QXX_Wait_Busy();   		//�ȴ��������
    W25Qxx_EN_OFF; 
}
///******************************************************************************************************
//��������void W25QXX_Erase_Sector(unsigned long Dst_Addr)   
//���ܣ�����һ������  ����һ������������ʱ��:150ms
//������Dst_Addr:������ַ ����ʵ����������
//����ֵ����
//���ߣ�Mr.He
///******************************************************************************************************
void W25QXX_Erase_Sector(unsigned long Dst_Addr)   
{  
    //����falsh�������,������   
    //printf("fe:%x\r\n",Dst_Addr);	  
    Dst_Addr*=4096;
    W25QXX_Write_Enable();                  //SET WEL 	 
    W25QXX_Wait_Busy();   
    SPI_CS_L;                            //ʹ������   
    SPIWrite8bit(W25X_SectorErase);      //������������ָ�� 
    SPIWrite8bit((unsigned char)((Dst_Addr)>>16));  //����24bit��ַ    
    SPIWrite8bit((unsigned char)((Dst_Addr)>>8));   
    SPIWrite8bit((unsigned char)Dst_Addr);  
    SPI_CS_H;                            //ȡ��Ƭѡ     	      
    W25QXX_Wait_Busy();   		//�ȴ��������
}
///******************************************************************************************************
//��������void W25QXX_Read(unsigned char * pBuffer,unsigned long ReadAddr,unsigned int NumByteToRead)   
//���ܣ���ȡSPI FLASH   ��ָ����ַ��ʼ��ȡָ�����ȵ�����
//������pBuffer:���ݴ洢��  ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)  NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
//����ֵ����
//���ߣ�Mr.He
///******************************************************************************************************
void W25QXX_Read(unsigned char * pBuffer,unsigned long ReadAddr,unsigned int NumByteToRead)   
{ 
 	unsigned int i;   										    
	SPI_CS_L;                            //ʹ������   
    SPIWrite8bit(W25X_ReadData);         //���Ͷ�ȡ����   
    SPIWrite8bit((unsigned char)((ReadAddr)>>16));  //����24bit��ַ    
    SPIWrite8bit((unsigned char)((ReadAddr)>>8));   
    SPIWrite8bit((unsigned char)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
    { 
        pBuffer[i] = SPIRead8bit();   //ѭ������  
    }
	SPI_CS_H;  				    	      
} 
///******************************************************************************************************
//��������void W25QXX_Write_Page(unsigned char* pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)
//���ܣ�SPI��һҳ(0~65535)��д������256���ֽڵ�����  ��ָ����ַ��ʼд�����256�ֽڵ�����
//������
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!
//����ֵ����
//���ߣ�Mr.He
///******************************************************************************************************
void W25QXX_Write_Page(unsigned char* pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)
{
 	unsigned int i;  
    W25QXX_Write_Enable();                  //SET WEL 
    SPI_CS_L;                            //ʹ������   
    SPIWrite8bit(W25X_PageProgram);      //����дҳ����   
    SPIWrite8bit((unsigned char)((WriteAddr)>>16)); //����24bit��ַ    
    SPIWrite8bit((unsigned char)((WriteAddr)>>8));   
    SPIWrite8bit((unsigned char)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)
    SPIWrite8bit(pBuffer[i]);//ѭ��д��  
    SPI_CS_H;                            //ȡ��Ƭѡ 
    W25QXX_Wait_Busy();					   //�ȴ�д�����
}
///******************************************************************************************************
//��������void W25QXX_Write_NoCheck(unsigned char* pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)   
//���ܣ�
//�޼���дSPI FLASH  ����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//������
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
//����ֵ����
//���ߣ�Mr.He
///******************************************************************************************************
void W25QXX_Write_NoCheck(unsigned char* pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)   
{ 			 		 
	unsigned int pageremain;
//        W25Qxx_EN_ON;        //����W25Q64��Դ 
      	pageremain = 256 - WriteAddr % 256; //��ҳʣ����ֽ���	
        
	if(NumByteToWrite <= pageremain)
        {
          pageremain = NumByteToWrite;//������256���ֽ�
        }
	while(1)
	{	   
		W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
                
		if(NumByteToWrite == pageremain)
                {
                  break;//д�������
                }
                else //NumByteToWrite > pageremain
		{
			pBuffer += pageremain;   //����������ʼ��ַ +256
			WriteAddr += pageremain; //��Ҫд�����ݵĵ�ַ +256	

			NumByteToWrite -= pageremain;	      //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite > 256)
                        {
                          pageremain = 256; //һ�ο���д��256���ֽ�
                        }
			else 
                        {
                          pageremain = NumByteToWrite;       //����256���ֽ���
                        }
		}
	};
//        W25Qxx_EN_OFF;        //�ر�W25Q64��Դ  
} 
///******************************************************************************************************
//��С��8M��Byte����128�飨Block����ÿ��64K�ֽڣ�ÿ��16��������Sector����ÿ������4K�ֽڣ�ÿ������16ҳ��ÿҳ256���ֽڣ�
//��������void W25QXX_Write(unsigned char * pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)   
//���ܣ� дSPI FLASH  ��ָ����ַ��ʼд��ָ�����ȵ�����   �ú�������������!
//����:
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)						
//NumByteToWrite:Ҫд����ֽ���(���65535)
//����ֵ����
//���ߣ�Mr.He
///******************************************************************************************************		 
void W25QXX_Write(unsigned char * pBuffer,unsigned long WriteAddr,unsigned int NumByteToWrite)
{ 
     unsigned int y = 0 , i = 0; 
     unsigned int Page = 0;     //�����ڵ�ַ
     unsigned int secoff=0;      //�����ڵ�ַƫ��
     unsigned int Pageremain = 0;//������ʣ���ַ
     unsigned int offic = 0;
	
//     W25Qxx_EN_ON;        //����W25Q64��Դ       
//     if(WriteAddr > 4096)   //��ַ����4096
//        return;
	  
        Page = (WriteAddr & 0x0FFF) / 256;  //�������Ķ���ҳ
      secoff = (WriteAddr & 0x0FFF) % 256;  //�����ڵ�ַƫ��
      Pageremain = 256 - secoff; //��ҳʣ����ٿռ�
        	
      W25QXX_Erase_Sector(Origination_ADD / 4096);//������Ҫ���������
      
      for(y = 0 ; y < 16 ; y++ )
      {
           W25QXX_Read(W25QXX_BUF,(WriteAddr & 0xF000) + (256 * y),256);//����һ��ҳ����
		   
           if(y == Page)//�ҵ����ڵ�ҳ
           {
               if(Pageremain >= NumByteToWrite)//д�ĳ���С��������ַ
               { 
                       for(i = 0; i < NumByteToWrite; i++)
                       {
                         W25QXX_BUF[secoff++] = pBuffer[i + offic];                       
                       }
                       offic += NumByteToWrite;
               }
               else //д�ĳ��ȴ�������ʣ���ַ
               {
                       for(i = 0; i < Pageremain; i++)
                       {
                         W25QXX_BUF[secoff++] = pBuffer[i + offic];
                       }
                       NumByteToWrite = NumByteToWrite - Pageremain;//ʣ�����ݳ���
                       Page += 1;
                       offic += Pageremain;
                       secoff = 0;
                       Pageremain = 256;
               }               
           }
           W25QXX_Write_NoCheck(W25QXX_BUF,Origination_ADD + (256 * y),256);//д�����ݶ���������	   
      }
      
          memset(W25QXX_BUF,0,sizeof(W25QXX_BUF));
          W25QXX_Erase_Sector(WriteAddr / 4096);//������Ҫ���������
      for( y = 0 ; y < 16 ; y++)
      {
          W25QXX_Read(W25QXX_BUF,Origination_ADD + (256 * y),256);//����һ��ҳ������
          W25QXX_Write_NoCheck(W25QXX_BUF,(WriteAddr & 0xF000) + (256 * y),256);//д�����ݶ��������� 
      }  
//       W25QXX_PowerDown();
 //      W25Qxx_EN_OFF;        //�ر�W25Q64��Դ  
}





  
