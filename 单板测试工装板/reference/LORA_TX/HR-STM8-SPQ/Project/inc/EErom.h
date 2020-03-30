#ifndef __EEROM_H__
#define __EEROM_H__


#define EEPROM_STARTADDR   0x1000  // 定义起始地址
#define EEPROMFALF_ADDR    0x1000//内存初始化标志位地址
#define EEPROMLORA_ADDR   (sizeof(unsigned char)+EEPROMFALF_ADDR)//lora数据地址
#define EEPROMID_ADDR     (sizeof(Lora_type)+EEPROMLORA_ADDR) //节点ID地址

typedef struct{
  unsigned char LoraFreq;    //频率
  unsigned char LoraPower;   //功率  
  unsigned char LoraBw;      //带宽
  unsigned char LoraSF;      //SF 扩频因子
  unsigned char LoraCR;      //纠错码率
}Lora_type;

extern u8 KZQ_ID[6];

extern unsigned char EEPROM_Read(unsigned int Addr,unsigned char *RxBuffer,unsigned char Length);
extern unsigned char EEPROM_Write(unsigned int Addr,unsigned char *RxBuffer,unsigned char Lenth);
extern unsigned char data_chk(unsigned char *ptr,unsigned char size);
extern void SysData_Init(void);
#endif