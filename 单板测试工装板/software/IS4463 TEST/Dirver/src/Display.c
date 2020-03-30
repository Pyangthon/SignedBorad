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
//数字译码
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
//LCD SEG 到单片机 SEG映射  移植改
//*******************************************************************************
__CONST uint8_t SegTab[22] =
{
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21
};
//*******************************************************************************
//显示数字 LCD COM 口顺序映射 移植改
//*******************************************************************************
__CONST uint8_t ComTab[7][2] =
{

    {0, 1}, {1, 1}, {2, 1}, {3, 1}, {2, 0}, {0, 0}, {1, 0}
    //  A     B       C       D       E        F        G
    //1 com位置
    //2 seg是否减1    1 不减 0 减
};


//字符COM、SEG值 移植改
//*******************************************************************************
//Z1      Z2      Z3      Z4      Z5     Z6    Z7
//剩余   累计     购入   请充值   表号   异常   m3
//Z8      Z9      Z10     Z11     Z12    Z13
//元     信号1    信号2  信号3   信号4   USB
//Z14     Z15     Z16     Z17     Z18    Z19
//读卡中  命令错  阀开    阀关   磁干扰  ::(冒号)
//Z20     Z21     Z22     Z23     Z24    Z25
//电量1  电量2    电量3   电量4  电量5  电量6
//4H       5H      6H
//4位小数  3位小数 2位小数
//*******************************************************************************
__CONST uint8_t CharTab[28][2] =
{
    { 3,  1}, { 2,  1}, { 1,  1}, { 0,  1}, { 0, 18}, { 0, 19}, { 1, 19},
    { 2, 19}, { 0,  0}, { 1,  0}, { 2,  0}, { 3,  0}, { 3,  2},
    { 3,  4}, { 3,  8}, { 3, 18}, { 3, 16}, { 3, 19}, { 3,  6},
    { 0, 20}, { 1, 20}, { 0, 21}, { 3, 21}, { 2, 21}, { 1, 21},
    { 3, 10}, { 3, 12}, { 3, 14}
    //1 com位置
    //2 seg位置
};

//移植改
__CONST uint8_t ComPortConvert[4] = {3, 2, 1, 0};



//显示缓存
uint8_t DispBuff[8] = {0};

//*******************************************************************************
//* Function Name   : LCD_GLASS_Init
//* Description     : LCD初始化
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
    //移植改
    //                          Seg  0  1  2  3  4  5  6  7  8  9  10 11 12 13
    /* Mask register Seg Driver Pin: 39,38,37,36,0, 1, 2, 3, 4, 5,  6, 7, 8, 9  */
    LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0xFF);  //0~7
    LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0xFF);  //8~15
    LCD_PortMaskConfig(LCD_PortMaskRegister_2, 0x3F);  //16~23
    LCD_PortMaskConfig(LCD_PortMaskRegister_3, 0x00);  //24~31
    LCD_PortMaskConfig(LCD_PortMaskRegister_4, 0x00);  //32~39
    LCD_PortMaskConfig(LCD_PortMaskRegister_5, 0x00);  //40~47
    LCD_ContrastConfig(LCD_Contrast_Level_7);               //驱动电压 3.3V
    LCD_DeadTimeConfig(LCD_DeadTime_0);                 //调节对比度,越大越闪烁
    LCD_PulseOnDurationConfig(LCD_PulseOnDuration_7);   //显示的脉冲宽度
    LCD_Cmd(ENABLE); /*!< Enable LCD peripheral */
}


//*******************************************************************************
//* Function Name   : LCD_WritePixel
//* Description     : 驱动LCD单个像素点
//* Inputs          : com、seg 像素点
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

    //com转换 高地位转换
    com = ComPortConvert[com];

    if(LcdSeg < 28)
    {
        LcdRamReg =  com * 28 + LcdSeg;
        if(disp)          //对应段显示
            LCD->RAM[LcdRamReg / 8] |= 0x01 << (LcdRamReg % 8);
        else              //对应端不显示
            LCD->RAM[LcdRamReg / 8] &= ~(0x01 << (LcdRamReg % 8));
    }
    else
    {
        LcdSeg -= 28;

        LcdRamReg =  com * 16 + LcdSeg;
        if(disp)          //对应段显示
            LCD->RAM[14 + LcdRamReg / 8] |= 0x01 << (LcdRamReg % 8);
        else              //对应端不显示
            LCD->RAM[14 + LcdRamReg / 8] &= ~(0x01 << (LcdRamReg % 8));
    }
#endif
}


//*******************************************************************************
//* Function Name   : LCD_Clear
//* Description     : 清空LCD显示
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
//*函数名：void DispNum(uint8_t Position , uint8_t Num)
//*功能：在指定位置显示响应的数组
//*参数: uint8_t Position  显示位置 1~7
//	   uint8_t Num       显示内容
//*作者：wq
//*创建时间：
//*修改时间：
//*******************************************************************************/
void DispNum(uint8_t Position , uint8_t Num)
{
    uint8_t disp_buff = 0;
    uint8_t SegLoca = 0;  //Seg位置
    uint8_t i = 0;

    if((Position == 0 || Position > 8))
        return;
    if(Num > 30)
        return;
    if(Position > 8)
        return;
    else
        SegLoca = Position * 2 + 1;   //SEG

    disp_buff = DigitTab[Num];		//获取断译码

    for(i = 0; i < 7; i++)
    {
        if(ComTab[i][1])    //SEG减1
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
//*函数名：void DispChar(uint8_t Character)
//*功能：在LCD屏上显示 字符
//*参数: uint8_t Character 字符编号
//-------------------------------------------------------------------------
//Z1      Z2      Z3      Z4      Z5     Z6    Z7     ( 0 ~  6）
//剩余   累计     购入   请充值   表号   异常   m3
//Z8      Z9      Z10     Z11     Z12    Z13          ( 7 ~  12)
//元     信号1    信号2  信号3   信号4   USB
//Z14     Z15     Z16     Z17     Z18    Z19          (13 ~  18)
//读卡中  命令错  阀开    阀关   磁干扰  ::(冒号)
//Z20     Z21     Z22     Z23     Z24    Z25          (19 ~  24)
//电量1  电量2    电量3   电量4  电量5  电量6
//4H       5H      6H                                 (25 ~  27)
//4位小数  3位小数 2位小数   元    m^3  P1  P2
// -------------------------------------------------------------------------
//*作者：wq
//*创建时间：
//*修改时间：
//*******************************************************************************/
void DispChar(uint8_t Character)
{
    if(Character > 28)
        Character = 28;
    //通过查表找到对应字符的com，seg值
    LCD_WritePixel(CharTab[Character][0], CharTab[Character][1], 1);
}
//*******************************************************************************/
//*函数名：void ClearChar(uint8_t Character)
//*功能： 清除指定的字符
//*参数: uint8_t Character 字符值
//*作者：wq
//*创建时间：
//*修改时间：
//*******************************************************************************/
void ClearChar(uint8_t Character)
{
    if(Character > 28)
        Character = 28;
    //通过查表找到对应字符的com，seg值
    LCD_WritePixel(CharTab[Character][0], CharTab[Character][1], 0);
}

//*******************************************************************************/
//*函数名：void Disp2NumStr(uint8_t Position , uint8_t Num)
//*功能：在指定位置显示2位数值，第一位为0也显示
//*参数: uint8_t Position  显示位置 1~9
//	   uint8_t Num       显示内容
//*作者：wq
//*创建时间：
//*修改时间：
//*******************************************************************************/
void Disp2NumStr(uint8_t Position , uint8_t Num)
{
    if(Num > 99)
        return;

    DispNum(Position, Num / 10);
    DispNum(Position + 1, Num % 10);
}

//*******************************************************************************/
//*函数名：void Disp1Bcd(uint8_t Position , uint8_t Num)
//*功能：在指定位置显示一个字节的BCD码数据
//*参数: uint8_t Position  显示位置 1~8
//	   uint8_t Num       显示内容
//*作者：wq
//*创建时间：
//*修改时间：
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
//*函数名：void Num2BCD(uint32_t num,uint8_t *tmp)
//*功能：数字转换为BCD码
//*参数: uint32_t num 数值
//	   uint8_t *tmp 显示缓存指针
//*返回值: 数据位数
//*作者：wq
//*创建时间：
//*修改时间：
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
            PlaseCount++;  //统计前面 0 个数
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
//*函数名：void DispNumString(uint8_t star,int32_t num)
//*功能：显示一串数字
//*参数: uint32_t num  数值
//	   uint8_t end  显示结束位1~8    从右往左
//	   uint8_t Dot 1、2  小数点1位或者2位， 有小数点结束显示为必须是6，其他值表示无小数点
//*作者：wq
//*创建时间：
//*修改时间：
//*******************************************************************************/
void DispNumString(uint8_t end, int32_t num, uint8_t Dot)
{
    uint8_t i = 0;
    uint8_t tmp[8] = {0};
    uint8_t digit = 0;  //位数
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
        //显示相应位置数据
        for(i = 0; i < digit; i++)
        {
            if(tmp[i] < 26)
                DispNum(end, tmp[digit - 1 - i]);
            end--;
        }
        DispChar(27);   //小数点
        if(digit < 3)   //对应位补0
        {
            for(i = (3 - digit); i > 0; i--)
            {
                DispNum(end--, 0);
            }
        }
        break;
    case 1:
        //end =3;
        //显示相应位置数据
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
    //显示负号
    if(negative == TRUE)
    {
        DispBar(end);
    }
}

//*******************************************************************************/
//*函数名：void DispHexString(uint8_t Position,uint8_t Len,uint32_t dat)
//*功能：显示一串HEX数字
//*参数: uint8_t Position  起始位置 1~9
//	   uint8_t Len  显示长度 1~6
//	   uint32_t dat 显示内容
//*作者：wq
//*创建时间：
//*修改时间：
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
//*函数名:void Dispaly_OFF(void) 
//*功能:显示关闭
//*输入:无
//*输出:无
//*备注:无
//*******************************************************************************/
void Dispaly_OFF(void)   //关闭显示
{
      LCD_Cmd(DISABLE);    //LCD使能
}
///******************************************************************************
//*函数名:void Dispaly_ON(void) 
//*功能:显示开
//*输入:无
//*输出:无
//*备注:无
//*******************************************************************************/
void Dispaly_ON(void)   //开始显示
{
      LCD_Cmd(ENABLE);    //LCD使能
}
///******************************************************************************
//*函数名:void Dispaly_ERROR(unsigned char er)
//*功能:LCD 显示错误信息 
//*输入:er  显示的错误代码值
//*输出:无
//*备注:无
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
//*函数名:void DispAll(void)
//*功能:LCD全部显示 
//*输入:无
//*输出:无
//*备注:无
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
//*函数名:void DispBar(uint8_t i)
//*功能:显示字符 - 
//*输入:i 从什么位置开始显示
//*输出:无
//*备注:无
//*******************************************************************************/
void DispBar(uint8_t i)
{
    LCD_WritePixel(1, 2 * i, 1);
}
///******************************************************************************
//*函数名:void Start_Display_Init(void)
//*功能:开始界面初始化
//*输入:无
//*输出:无
//*备注:无
//*******************************************************************************/
void Start_Display_Init(void)
{
  for(int i = 1 ; i < 10; i++)
  {
       DispBar(i);
       DelayMs(500,TRUE);//延时
  }
       DispAll();//显示全部    
}



