//*******************************************************************************
//Module Name: display.c
//Module Date: 04/03/2015
//Module Auth: wq
//Description:
//Others     :
//Revision History:
//Date        Rel Ver.    Notes
//04/03/2015   1.0        None
//*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "Display.h"

//*******************************************************************************
//��������
//*******************************************************************************
__CONST uint8_t DigitTab[30] =
{
    // 0    1     2     3     4     5     6    7
    0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0,
    // 8    9     A   b11   C12   d13   E14    F15
    0xFE, 0xF6, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E,
    //r16 -17   H18   =19   R20   S21   L22  P23
    0x0A, 0x02, 0x6E, 0x90, 0xEE, 0xB6, 0X1C, 0XCE,
    //n24 o25   G26   LR27  L-28,  29
    0X2A, 0x3A, 0XBC, 0X5E, 0X1E, 0X00

};
//*******************************************************************************
//LCD SEG ����Ƭ�� SEGӳ��  ��ֲ��
//*******************************************************************************
__CONST uint8_t SegTab[22] =
{
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21
};
//*******************************************************************************
//��ʾ���� LCD COM ��˳��ӳ�� ��ֲ��
//*******************************************************************************
__CONST uint8_t ComTab[7][2] =
{

    {0, 1}, {1, 1}, {2, 1}, {3, 1}, {2, 0}, {0, 0}, {1, 0}
    //  A     B       C       D       E        F        G
    //1 comλ��
    //2 seg�Ƿ��1    1 ���� 0 ��
};


//�ַ�COM��SEGֵ ��ֲ��
//*******************************************************************************
//Z1      Z2      Z3      Z4      Z5     Z6    Z7
//ʣ��   �ۼ�     ����   ���ֵ   ���   �쳣   m3
//Z8      Z9      Z10     Z11     Z12    Z13
//Ԫ     �ź�1    �ź�2  �ź�3   �ź�4   USB
//Z14     Z15     Z16     Z17     Z18    Z19
//������  �����  ����    ����   �Ÿ���  ::(ð��)
//Z20     Z21     Z22     Z23     Z24    Z25
//����1  ����2    ����3   ����4  ����5  ����6
//4H       5H      6H
//4λС��  3λС�� 2λС��
//*******************************************************************************
__CONST uint8_t CharTab[28][2] =
{
    { 3,  1}, { 2,  1}, { 1,  1}, { 0,  1}, { 0, 18}, { 0, 19}, { 1, 19},
    { 2, 19}, { 0,  0}, { 1,  0}, { 2,  0}, { 3,  0}, { 3,  2},
    { 3,  4}, { 3,  8}, { 3, 18}, { 3, 16}, { 3, 19}, { 3,  6},
    { 0, 20}, { 1, 20}, { 0, 21}, { 3, 21}, { 2, 21}, { 1, 21},
    { 3, 10}, { 3, 12}, { 3, 14}
    //1 comλ��
    //2 segλ��
};

//��ֲ��
__CONST uint8_t ComPortConvert[4] = {3, 2, 1, 0};



//��ʾ����
uint8_t DispBuff[8] = {0};

//*******************************************************************************
//* Function Name   : LCD_GLASS_Init
//* Description     : LCD��ʼ��
//* Inputs          : None
//* Outputs         : None
//* Return          : None
//* Notes           :
//       The LCD is configured as follow:
//     - clock source = LSE (32.768 KHz)
//     - Voltage source = Internal
//     - Prescaler = 2
//     - Divider = 18 (16 + 2)
//     - Mode = 1/8 Duty, 1/4 Bias
//     - LCD frequency = (clock source * Duty) / (Prescaler * Divider)
//                     = 114 Hz ==> Frame frequency = 28,5 Hz
//*******************************************************************************/
void LCD_GLASS_Init(void)
{
    /* Initialize the LCD */
    LCD_Init(LCD_Prescaler_1, LCD_Divider_18, LCD_Duty_1_4,
    LCD_Bias_1_3, LCD_VoltageSource_External);
    //��ֲ��
    //                          Seg  0  1  2  3  4  5  6  7  8  9  10 11 12 13
    /* Mask register Seg Driver Pin: 39,38,37,36,0, 1, 2, 3, 4, 5,  6, 7, 8, 9  */
    LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0xFF);  //0~7
    LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0xFF);  //8~15
    LCD_PortMaskConfig(LCD_PortMaskRegister_2, 0x3F);  //16~23
    LCD_PortMaskConfig(LCD_PortMaskRegister_3, 0x00);  //24~31
    LCD_PortMaskConfig(LCD_PortMaskRegister_4, 0x00);  //32~39
    LCD_PortMaskConfig(LCD_PortMaskRegister_5, 0x00);  //40~47
    LCD_ContrastConfig(LCD_Contrast_Level_7);               //������ѹ 3.3V
    LCD_DeadTimeConfig(LCD_DeadTime_0);                 //���ڶԱȶ�,Խ��Խ��˸
    LCD_PulseOnDurationConfig(LCD_PulseOnDuration_7);   //��ʾ��������
    LCD_Cmd(ENABLE); /*!< Enable LCD peripheral */
}


//*******************************************************************************
//* Function Name   : LCD_WritePixel
//* Description     : ����LCD�������ص�
//* Inputs          : com��seg ���ص�
//*                   disp  0 - clear Display
//*                         1 - Set Display
//* Outputs         : None
//* Return          : None
//* Notes           : None
//*******************************************************************************/
void LCD_WritePixel(uint8_t com, uint8_t seg, uint8_t disp)  // 1 2 1
{
    uint8_t LcdRamReg = 0;
    uint8_t LcdSeg = 0;

    LcdSeg = SegTab[seg];

    LCD->CR4 &= (uint8_t)~LCD_CR4_PAGECOM;

#if 1
    if(com > 3 || seg > 21)
        return;

    //comת�� �ߵ�λת��
    com = ComPortConvert[com];

    if(LcdSeg < 28)
    {
        LcdRamReg =  com * 28 + LcdSeg;
        if(disp)          //��Ӧ����ʾ
            LCD->RAM[LcdRamReg / 8] |= 0x01 << (LcdRamReg % 8);
        else              //��Ӧ�˲���ʾ
            LCD->RAM[LcdRamReg / 8] &= ~(0x01 << (LcdRamReg % 8));
    }
    else
    {
        LcdSeg -= 28;

        LcdRamReg =  com * 16 + LcdSeg;
        if(disp)          //��Ӧ����ʾ
            LCD->RAM[14 + LcdRamReg / 8] |= 0x01 << (LcdRamReg % 8);
        else              //��Ӧ�˲���ʾ
            LCD->RAM[14 + LcdRamReg / 8] &= ~(0x01 << (LcdRamReg % 8));
    }
#endif
}


//*******************************************************************************
//* Function Name   : LCD_Clear
//* Description     : ���LCD��ʾ
//* Inputs          : None
//* Outputs         : None
//* Return          : None
//* Notes           : None
//*******************************************************************************/
void LCD_Clear(void)
{
    uint8_t idx;

    LCD->CR4 &= ~LCD_CR4_PAGECOM;
    for(idx = 0; idx < 22; idx ++)  LCD->RAM[idx] = 0x00;
    LCD->CR4 |= LCD_CR4_PAGECOM;
    for(idx = 0; idx < 22; idx ++)  LCD->RAM[idx] = 0x00;
}

//*******************************************************************************/
//*��������void DispNum(uint8_t Position , uint8_t Num)
//*���ܣ���ָ��λ����ʾ��Ӧ������
//*����: uint8_t Position  ��ʾλ�� 1~7
//	   uint8_t Num       ��ʾ����
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
//*******************************************************************************/
void DispNum(uint8_t Position , uint8_t Num)
{
    uint8_t disp_buff = 0;
    uint8_t SegLoca = 0;  //Segλ��
    uint8_t i = 0;

    if((Position == 0 || Position > 8))
        return;
    if(Num > 30)
        return;
    if(Position > 8)
        return;
    else
        SegLoca = Position * 2 + 1;   //SEG

    disp_buff = DigitTab[Num];		//��ȡ������

    for(i = 0; i < 7; i++)
    {
        if(ComTab[i][1])    //SEG��1
        {
            LCD_WritePixel(ComTab[i][0], SegLoca, disp_buff & 0x80);
        }
        else
        {
            LCD_WritePixel(ComTab[i][0], SegLoca - 1, disp_buff & 0x80);
        }
        disp_buff <<= 1;
    }

}

//*******************************************************************************/
//*��������void DispChar(uint8_t Character)
//*���ܣ���LCD������ʾ �ַ�
//*����: uint8_t Character �ַ����
//-------------------------------------------------------------------------
//Z1      Z2      Z3      Z4      Z5     Z6    Z7     ( 0 ~  6��
//ʣ��   �ۼ�     ����   ���ֵ   ���   �쳣   m3
//Z8      Z9      Z10     Z11     Z12    Z13          ( 7 ~  12)
//Ԫ     �ź�1    �ź�2  �ź�3   �ź�4   USB
//Z14     Z15     Z16     Z17     Z18    Z19          (13 ~  18)
//������  �����  ����    ����   �Ÿ���  ::(ð��)
//Z20     Z21     Z22     Z23     Z24    Z25          (19 ~  24)
//����1  ����2    ����3   ����4  ����5  ����6
//4H       5H      6H                                 (25 ~  27)
//4λС��  3λС�� 2λС��   Ԫ    m^3  P1  P2
// -------------------------------------------------------------------------
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
//*******************************************************************************/
void DispChar(uint8_t Character)
{
    if(Character > 28)
        Character = 28;
    //ͨ������ҵ���Ӧ�ַ���com��segֵ
    LCD_WritePixel(CharTab[Character][0], CharTab[Character][1], 1);
}
//*******************************************************************************/
//*��������void ClearChar(uint8_t Character)
//*���ܣ� ���ָ�����ַ�
//*����: uint8_t Character �ַ�ֵ
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
//*******************************************************************************/
void ClearChar(uint8_t Character)
{
    if(Character > 28)
        Character = 28;
    //ͨ������ҵ���Ӧ�ַ���com��segֵ
    LCD_WritePixel(CharTab[Character][0], CharTab[Character][1], 0);
}

//*******************************************************************************/
//*��������void Disp2NumStr(uint8_t Position , uint8_t Num)
//*���ܣ���ָ��λ����ʾ2λ��ֵ����һλΪ0Ҳ��ʾ
//*����: uint8_t Position  ��ʾλ�� 1~9
//	   uint8_t Num       ��ʾ����
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
//*******************************************************************************/
void Disp2NumStr(uint8_t Position , uint8_t Num)
{
    if(Num > 99)
        return;

    DispNum(Position, Num / 10);
    DispNum(Position + 1, Num % 10);
}

//*******************************************************************************/
//*��������void Disp1Bcd(uint8_t Position , uint8_t Num)
//*���ܣ���ָ��λ����ʾһ���ֽڵ�BCD������
//*����: uint8_t Position  ��ʾλ�� 1~8
//	   uint8_t Num       ��ʾ����
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
//*******************************************************************************/
void Disp1Bcd(uint8_t Position , uint8_t Num)
{
    DispNum(Position, (Num >> 4) & 0x0F);
    DispNum(Position + 1, Num & 0x0F);
}



uint32_t pow10(uint8_t p)
{
    uint8_t i = 0;
    uint32_t result = 1;
    for(i = 0; i < p; i++)
        result = result * 10;
    return result;
}



//*******************************************************************************/
//*��������void Num2BCD(uint32_t num,uint8_t *tmp)
//*���ܣ�����ת��ΪBCD��
//*����: uint32_t num ��ֵ
//	   uint8_t *tmp ��ʾ����ָ��
//*����ֵ: ����λ��
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
//*******************************************************************************/
uint8_t Num2BCD(uint32_t num, uint8_t *tmp)
{
    uint8_t i = 0;
    uint8_t PlaseCount = 0;
    uint8_t tmp_i[9] = {0};
    bool Headfind = FALSE;
    for(i = 0; i < 9; i++)
    {
        tmp_i[i] = num / pow10(8 - i);
        num = num % pow10(8 - i);
        if((tmp_i[i] == 0) && (Headfind == FALSE))
        {
            PlaseCount++;  //ͳ��ǰ�� 0 ����
        }
        else
            Headfind = TRUE;
    }
    for(i = 0 ; i < (9 - PlaseCount); i ++)
    {
        tmp[i] = tmp_i[PlaseCount + i];
    }
    return 9 - PlaseCount;
}


//*******************************************************************************/
//*��������void DispNumString(uint8_t star,int32_t num)
//*���ܣ���ʾһ������
//*����: uint32_t num  ��ֵ
//	   uint8_t end  ��ʾ����λ1~8    ��������
//	   uint8_t Dot 1��2  С����1λ����2λ�� ��С���������ʾΪ������6������ֵ��ʾ��С����
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
//*******************************************************************************/
void DispNumString(uint8_t end, int32_t num, uint8_t Dot)
{
    uint8_t i = 0;
    uint8_t tmp[8] = {0};
    uint8_t digit = 0;  //λ��
    bool negative = FALSE;
    if(end < 1) return;
    else
    {
        if(Dot == 1)
        {
            if(end > 8) return;
            else end--;
        }
        else
        {
            if(end > 8) return;
        }
    }

    if(num < 0)
    {
        num *= (-1) ;
        negative = TRUE;
    }

    if(((num > 99999999) && (negative == FALSE)) ||
            ((num > 9999999) && (negative == TRUE)))
        return;

    digit = Num2BCD(num, tmp);

    switch(Dot)
    {
    case 2:
        //end =4;
        //��ʾ��Ӧλ������
        for(i = 0; i < digit; i++)
        {
            if(tmp[i] < 26)
                DispNum(end, tmp[digit - 1 - i]);
            end--;
        }
        DispChar(27);   //С����
        if(digit < 3)   //��Ӧλ��0
        {
            for(i = (3 - digit); i > 0; i--)
            {
                DispNum(end--, 0);
            }
        }
        break;
    case 1:
        //end =3;
        //��ʾ��Ӧλ������
        for(i = 0; i < digit; i++)
        {
            if(tmp[i] < 26)
                DispNum(end, tmp[digit - 1 - i]);
            end--;
        }
        DispChar(27);   //DOT2
        if(digit < 2)
        {
            for(i = (2 - digit); i > 0; i--)
            {
                DispNum(end--, 0);
            }
        }
        break;
    default:
        for(i = 0; i < digit; i++)
        {
            if(tmp[i] < 26)
                DispNum(end, tmp[digit - 1 - i]);
            end--;
        }
        if(digit == 0)
        {
            DispNum(end, 0);
        }
        break;
    }
    //��ʾ����
    if(negative == TRUE)
    {
        DispBar(end);
    }
}

//*******************************************************************************/
//*��������void DispHexString(uint8_t Position,uint8_t Len,uint32_t dat)
//*���ܣ���ʾһ��HEX����
//*����: uint8_t Position  ��ʼλ�� 1~9
//	   uint8_t Len  ��ʾ���� 1~6
//	   uint32_t dat ��ʾ����
//*���ߣ�wq
//*����ʱ�䣺
//*�޸�ʱ�䣺
///******************************************************************************
void DispHexString(uint8_t Position, uint8_t Len, uint32_t dat)
{
    uint32_t temp32 = 0x0000000F;
    uint8_t idx;
    uint8_t lenbuf = 0;
    lenbuf = Len;
    for(idx = 0; idx < 8 && Len--; idx++)
    {
        DispNum(Position + lenbuf - 1 - idx, dat & temp32);
        dat >>= 4;
    }
}
///******************************************************************************
//*������:void Dispaly_OFF(void) 
//*����:��ʾ�ر�
//*����:��
//*���:��
//*��ע:��
//*******************************************************************************/
void Dispaly_OFF(void)   //�ر���ʾ
{
      LCD_Cmd(DISABLE);    //LCDʹ��
}
///******************************************************************************
//*������:void Dispaly_ON(void) 
//*����:��ʾ��
//*����:��
//*���:��
//*��ע:��
//*******************************************************************************/
void Dispaly_ON(void)   //��ʼ��ʾ
{
      LCD_Cmd(ENABLE);    //LCDʹ��
}
///******************************************************************************
//*������:void Dispaly_ERROR(unsigned char er)
//*����:LCD ��ʾ������Ϣ 
//*����:er  ��ʾ�Ĵ������ֵ
//*���:��
//*��ע:��
//*******************************************************************************/
void Dispaly_ERROR(unsigned char er)
{
    LCD_Clear();
    DispNum(2,14);//E
    DispNum(3,16);//R
    DispNum(4,16);//R
    DispNum(5,17);//-
    DispNum(6,17);//-
    DispNum(7,er / 10);//
    DispNum(8,er % 10);//
}
///******************************************************************************
//*������:void DispAll(void)
//*����:LCDȫ����ʾ 
//*����:��
//*���:��
//*��ע:��
//*******************************************************************************/
void DispAll(void)
{
    uint8_t i = 0;
    for(i = 0; i < 28; i++)
    {
        DispChar(i);
        DelayMs(10, TRUE);
    }
    for(i = 1; i < 9; i++)
    {
        DispNum(i, 8);
        DelayMs(10, TRUE);
    }
}
///******************************************************************************
//*������:void DispBar(uint8_t i)
//*����:��ʾ�ַ� - 
//*����:i ��ʲôλ�ÿ�ʼ��ʾ
//*���:��
//*��ע:��
//*******************************************************************************/
void DispBar(uint8_t i)
{
    LCD_WritePixel(1, 2 * i, 1);
}
///******************************************************************************
//*������:void Start_Display_Init(void)
//*����:��ʼ�����ʼ��
//*����:��
//*���:��
//*��ע:��
//*******************************************************************************/
void Start_Display_Init(void)
{
  for(int i = 1 ; i < 10; i++)
  {
       DispBar(i);
       DelayMs(500,TRUE);//��ʱ
  }
       DispAll();//��ʾȫ��    
}



