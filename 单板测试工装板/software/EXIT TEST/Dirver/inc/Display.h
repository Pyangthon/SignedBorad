/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm8l15x.h"
#include "Delay.h"

//******************************************************************************
// Module Name: display.h
// Module Date: 04/03/2015
// Module Auth: CHEN LIANG
//
// Description: 显示相关头文件
//
//Revision History:
//Date        Rel Ver.    Notes
//04/03/2015      1.0     None
//*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/


typedef struct
{
    uint8_t Com;
    uint8_t Seg;
} CharLoca;




/*Function Prototypes ------------------------------------------------------- */
extern void Dispaly_OFF(void) ;
extern void Dispaly_ON(void) ;
extern void LCD_GLASS_Init(void);
extern void LCD_Clear(void);
extern void DispNum(uint8_t Position , uint8_t Num);
extern void DispChar(uint8_t Character);
extern void ClearChar(uint8_t Character);
extern void Disp2NumStr(uint8_t Position , uint8_t Num);
extern void Disp1Bcd(uint8_t Position , uint8_t Num);
extern void DispNumString(uint8_t end, int32_t num, uint8_t Dot);
extern void DispHexString(uint8_t Position, uint8_t Len, uint32_t dat);
extern void DispAll(void);
extern void DispAllBar(void);
extern void DispBar(uint8_t i);
extern void LCD_WritePixel(uint8_t com, uint8_t seg, uint8_t disp);
extern uint32_t pow10(uint8_t p);
extern void Dispaly_ERROR(unsigned char er);
extern void Start_Display_Init(void);


#endif /* __DISPLAY_H*/
