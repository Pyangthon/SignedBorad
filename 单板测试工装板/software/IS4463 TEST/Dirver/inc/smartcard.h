/**
  ******************************************************************************
  * @file     smartcard.h
  * @author   MCD Application Team
  * @version  V1.1.0
  * @date     11-March-2011
  * @brief    This file contains all functions prototypes and macros for the 
  *           smartcard peripheral.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SMARTCARD_H
#define __SMARTCARD_H

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"
#include "stm8l15x.h"

/* Exported constants --------------------------------------------------------*/
#define T0_PROTOCOL        (uint8_t)0x00  /* T0 protocol */
#define DIRECT             (uint8_t)0x3B  /* Direct bit convention */
#define INDIRECT           (uint8_t)0x3F  /* Indirect bit convention */
#define SETUP_LENGTH       (uint8_t)20
#define HIST_LENGTH        (uint8_t)20
#define LCmax              (uint8_t)20
#define SC_Receive_Timeout (uint16_t)0x1000 /* Direction to reader */


/* SC Tree Structure -----------------------------------------------------------
                              MasterFile
                           ________|___________
                          |        |           |
                        System   UserData     Note
------------------------------------------------------------------------------*/

/* SC ADPU Command: Operation Code -------------------------------------------*/
#define SC_CLA_GSM11       (uint8_t)0xA0

/*------------------------ Data Area Management Commands ---------------------*/
#define SC_SELECT_FILE     (uint8_t)0xA4
#define SC_GET_RESPONCE    (uint8_t)0xC0
#define SC_STATUS          (uint8_t)0xF2
#define SC_UPDATE_BINARY   (uint8_t)0xD6
#define SC_READ_BINARY     (uint8_t)0xB0
#define SC_WRITE_BINARY    (uint8_t)0xD0
#define SC_UPDATE_RECORD   (uint8_t)0xDC
#define SC_READ_RECORD     (uint8_t)0xB2

/*-------------------------- Administrative Commands -------------------------*/
#define SC_CREATE_FILE     (uint8_t)0xE0

/*-------------------------- Safety Management Commands ----------------------*/
#define SC_VERIFY          (uint8_t)0x20
#define SC_CHANGE          (uint8_t)0x24
#define SC_DISABLE         (uint8_t)0x26
#define SC_ENABLE          (uint8_t)0x28
#define SC_UNBLOCK         (uint8_t)0x2C
#define SC_EXTERNAL_AUTH   (uint8_t)0x82
#define SC_GET_CHALLENGE   (uint8_t)0x84

/*-------------------------- Answer to reset Commands ------------------------*/
#define SC_GET_A2R         (uint8_t)0x00


/* SC STATUS: Status Code ----------------------------------------------------*/
#define SC_EF_SELECTED     (uint8_t)0x9F
#define SC_DF_SELECTED     (uint8_t)0x9F
#define SC_OP_TERMINATED   (uint16_t)0x9000

/* Smartcard Inteface GPIO pins */
#define SC_3_5V            GPIO_Pin_7 /* GPIOG Pin 7 */
#define SC_RESET           GPIO_Pin_5 /* GPIOG Pin 5 */
#define SC_CMDVCC          GPIO_Pin_4 /* GPIOG Pin 4  */
#define SC_OFF             GPIO_Pin_7 /* GPIOE Pin 7 */
#define SC_IO              GPIO_Pin_3 /* GPIOA Pin 3 */
#define SC_CLK             GPIO_Pin_4 /* GPIOA Pin 4 */

/* Smartcard Voltage */
#define SC_Voltage_5V      (uint8_t)0
#define SC_Voltage_3V      (uint8_t)1

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    SC_POWER_ON     = (uint8_t)0x00,
    SC_RESET_LOW    = (uint8_t)0x01,
    SC_RESET_HIGH   = (uint8_t)0x02,
    SC_ACTIVE       = (uint8_t)0x03,
    SC_ACTIVE_ON_T0 = (uint8_t)0x04,
    SC_POWER_OFF    = (uint8_t)0x05
} SC_State;

/* ATR structure - Answer To Reset -------------------------------------------*/
typedef struct
{
    uint8_t TS;               /* Bit Convention */
    uint8_t T0;               /* High nibble = Number of setup byte; low nibble = Number of historical byte */
    uint8_t T[SETUP_LENGTH];  /* Setup array */
    uint8_t H[HIST_LENGTH];   /* Historical array */
    uint8_t Tlength;          /* Setup array dimension */
    uint8_t Hlength;          /* Historical array dimension */
} SC_ATR;

/* ADPU-Header command structure ---------------------------------------------*/
typedef struct
{
    uint8_t CLA;  /* Command class */
    uint8_t INS;  /* Operation code */
    uint8_t P1;   /* Selection Mode */
    uint8_t P2;   /* Selection Option */
} SC_Header;

/* ADPU-Body command structure -----------------------------------------------*/
typedef struct
{
    uint8_t LC;           /* Data field length */
    uint8_t Data[LCmax];  /* Command parameters */
    uint8_t LE;           /* Expected length of data to be returned */
} SC_Body;

/* ADPU Command structure ----------------------------------------------------*/
typedef struct
{
    SC_Header Header;
    SC_Body Body;
} SC_ADPU_Commands;

/* SC response structure -----------------------------------------------------*/
typedef struct
{
    uint8_t Data[LCmax];  /* Data returned from the card */
    uint8_t SW1;          /* Command Processing status */
    uint8_t SW2;          /* Command Processing qualification */
} SC_ADPU_Responce;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* APPLICATION LAYER ---------------------------------------------------------*/
void SC_Handler(SC_State *SCState, SC_ADPU_Commands *SC_ADPU, SC_ADPU_Responce *SC_Response);
void SC_PowerCmd(FunctionalState NewState);
void SC_Reset(BitAction ResetState);
void SC_ParityErrorHandler(void);
void SC_PTSConfig(void);

#endif /* __SMARTCARD_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
