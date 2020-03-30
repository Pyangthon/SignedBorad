
#ifndef AES_H
#define AES_H


extern void AesEncrypt(unsigned char *SreData,unsigned char Len, unsigned char *AesKey);
extern void AesDecrypt(unsigned char *SreData,unsigned char Len, unsigned char *AesKey);

extern void AES_Test(void);


#endif




