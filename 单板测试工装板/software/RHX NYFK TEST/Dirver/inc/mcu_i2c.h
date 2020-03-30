/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MCU_I2C_H
#define _MCU_I2C_H

/* Includes ------------------------------------------------------------------*/

#include "stm8l15x.h"

#define IIC_GPIO          GPIOG
#define IIC_SCL_GPIO_PIN  GPIO_Pin_2
#define IIC_SDA_GPIO_PIN  GPIO_Pin_3

#define SCL_1            GPIO_SetBits(IIC_GPIO, IIC_SCL_GPIO_PIN)
#define SCL_0            GPIO_ResetBits(IIC_GPIO, IIC_SCL_GPIO_PIN)

#define SDA_1            GPIO_SetBits(IIC_GPIO, IIC_SDA_GPIO_PIN)
#define SDA_0            GPIO_ResetBits(IIC_GPIO, IIC_SDA_GPIO_PIN)

#define SDAM             GPIO_ReadInputDataBit(IIC_GPIO, IIC_SDA_GPIO_PIN)  

#define SET_SCL_OUT()    GPIO_Init(IIC_GPIO, IIC_SCL_GPIO_PIN, GPIO_Mode_Out_PP_High_Fast )
#define SET_SDA_OUT()    GPIO_Init(IIC_GPIO, IIC_SDA_GPIO_PIN, GPIO_Mode_Out_PP_High_Fast )
#define SET_SDA_IN()     GPIO_Init(IIC_GPIO, IIC_SDA_GPIO_PIN, GPIO_Mode_In_PU_No_IT )

/* Exported types ------------------------------------------------------------*/

typedef struct
{
    uint8_t DeviceAddr;
    uint8_t MemAddrL;
    uint8_t MemAddrH;
    uint8_t *DataPtr;
    uint16_t DataLength;
    uint8_t Option;
} I2C_DataBlock;

/* Exported macros -----------------------------------------------------------*/

#define I2C_OPT_DEFAULT   0x00        /* I2C Default Option                   */
#define I2C_OPT_MEM16     0x01        /* I2C Device Memary 16 bits Address    */

/* Private macros ------------------------------------------------------------*/

#define I2C_SW_MODE          0        /* 0: Hardware I2C, 1: Software simulate*/

/* Exported constants --------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

void IIC_Init(void);
void IIC_Lowpower(void);
uint8_t IIC_Write(I2C_DataBlock blk);
uint8_t IIC_Read(I2C_DataBlock blk);

#endif /* _MCU_I2C_H */
/****************************** END OF FILE ***********************************/