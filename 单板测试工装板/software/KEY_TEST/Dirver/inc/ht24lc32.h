/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HT24LC32_H
#define _HT24LC32_H

#include "mcu_i2c.h"

#include "Delay.h"

#define HT24LC32_ADDR       0xA0      /* HT24LC32 Device Address              */

uint8_t HT24LC32_WriteData(uint16_t addr, uint8_t *src, uint16_t len);
uint8_t HT24LC32_ReadData(uint16_t addr, uint8_t *dst, uint16_t len);
uint8_t DataChk(uint8_t *ptr, uint8_t size);
uint8_t EepromWriteData(uint16_t addr, uint8_t *dst, uint16_t len);
uint8_t EepromReadData(uint16_t addr, uint8_t *dst, uint16_t len);
#endif /* _HT24LC32_H */
