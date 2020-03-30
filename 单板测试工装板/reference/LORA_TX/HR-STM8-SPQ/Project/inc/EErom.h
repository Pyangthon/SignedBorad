#ifndef __EEROM_H__
#define __EEROM_H__


#define EEPROM_STARTADDR   0x1000  // ������ʼ��ַ
#define EEPROMFALF_ADDR    0x1000//�ڴ��ʼ����־λ��ַ
#define EEPROMLORA_ADDR   (sizeof(unsigned char)+EEPROMFALF_ADDR)//lora���ݵ�ַ
#define EEPROMID_ADDR     (sizeof(Lora_type)+EEPROMLORA_ADDR) //�ڵ�ID��ַ

typedef struct{
  unsigned char LoraFreq;    //Ƶ��
  unsigned char LoraPower;   //����  
  unsigned char LoraBw;      //����
  unsigned char LoraSF;      //SF ��Ƶ����
  unsigned char LoraCR;      //��������
}Lora_type;

extern u8 KZQ_ID[6];

extern unsigned char EEPROM_Read(unsigned int Addr,unsigned char *RxBuffer,unsigned char Length);
extern unsigned char EEPROM_Write(unsigned int Addr,unsigned char *RxBuffer,unsigned char Lenth);
extern unsigned char data_chk(unsigned char *ptr,unsigned char size);
extern void SysData_Init(void);
#endif