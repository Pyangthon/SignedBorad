/**
  ******************************************************************************
  * @file     smartcard.c
  * @author   MCD Application Team
  * @version  V1.1.0
  * @date     11-March-2011
  * @brief    This file contains all the functions for the smart card peripheral.
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
  
/* Includes ------------------------------------------------------------------*/
#include "smartcard.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables definition and initialization ----------------------------*/
SC_ATR SC_A2R;
uint8_t SC_ATR_Table[40];
static __IO uint8_t SCData = 0;
CONST uint32_t F_Table[16] = {0, 372, 558, 744, 1116, 1488, 1860, 0,
                              0, 512, 768, 1024, 1536, 2048, 0, 0};
CONST uint32_t D_Table[8] = {0, 1, 2, 4, 8, 16, 0, 0};

/* Private function prototypes -----------------------------------------------*/
/* Transport Layer -----------------------------------------------------------*/
/*-------------- APDU -----------*/
static void SC_SendData(SC_ADPU_Commands *SC_ADPU, SC_ADPU_Responce *SC_ResponceStatus);

/*------------ ATR ------------*/
static void SC_AnswerReq(SC_State *SCState, uint8_t *card, uint8_t length);  /* Ask ATR */
static uint8_t SC_decode_Answer2reset(uint8_t *card);  /* Decode ATR */

/* Physical Port Layer -------------------------------------------------------*/
static void SC_Init(void);
static void SC_DeInit(void);
static void SC_VoltageConfig(uint32_t SC_Voltage);
static void SC_SendDataCard(uint8_t SCData);
static uint8_t SC_Detect(void);
static ErrorStatus UART1_ByteReceive(uint8_t *Data, uint32_t TimeOut);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Handles all Smartcard states and sends and receives all communication
  *         data between Smartcard and reader.
  * @param  SCState: pointer to an SC_State enumeration that will contain the 
  *         Smartcard state.
  * @param  SC_ADPU: pointer to an SC_ADPU_Commands structure that will be initialized.
  * @param  SC_Response: pointer to a SC_ADPU_Responce structure which will be 
  *         initialized.
  * @retval None
  */
void SC_Handler(SC_State *SCState, SC_ADPU_Commands *SC_ADPU, SC_ADPU_Responce *SC_Response)
{
  uint32_t i = 0;

  switch (*SCState)
  {
    case SC_POWER_ON:
      if (SC_ADPU->Header.INS == SC_GET_A2R)
      {
        /* Smartcard initialization ------------------------------------------*/
        SC_Init();

        /* Reset Data from SC buffer -----------------------------------------*/
        for (i = 0; i < 40; i++)
        {
          SC_ATR_Table[i] = (uint8_t)0;
        }

        /* Reset SC_A2R Structure --------------------------------------------*/
        SC_A2R.TS = (uint8_t)0;
        SC_A2R.T0 = (uint8_t)0;
        for (i = 0; i < SETUP_LENGTH; i++)
        {
          SC_A2R.T[i] = (uint8_t)0;
        }
        for (i = 0; i < HIST_LENGTH; i++)
        {
          SC_A2R.H[i] = (uint8_t)0;
        }
        SC_A2R.Tlength = (uint8_t)0;
        SC_A2R.Hlength = (uint8_t)0;

        /* Next State --------------------------------------------------------*/
        *SCState = (SC_State)SC_RESET_LOW;
      }
      break;
    case SC_RESET_LOW:
      if (SC_ADPU->Header.INS == SC_GET_A2R)
      {
        /* If card is detected then Power ON, Card Reset and wait for an answer) */
        if (SC_Detect())  // 检测智能卡模式是否存在
        {
           while (((*SCState) != SC_POWER_OFF) && ((*SCState) != SC_ACTIVE))
           {
              SC_AnswerReq(SCState, &SC_ATR_Table[0],(uint8_t)40); /* Check for answer to reset */
           }
        }
        else
        {
           (*SCState) = (SC_State)SC_POWER_OFF;
        }
      }
      break;

    case SC_ACTIVE:
      if (SC_ADPU->Header.INS == SC_GET_A2R)
      {
         if (SC_decode_Answer2reset(&SC_ATR_Table[0]) == T0_PROTOCOL)
         {
           (*SCState) = (SC_State)SC_ACTIVE_ON_T0;
         }
         else
         {
           (*SCState) = (SC_State)SC_POWER_OFF;
         }
      }
      break;

    case SC_ACTIVE_ON_T0:
      SC_SendData(SC_ADPU, SC_Response);
      break;

    case SC_POWER_OFF:
      SC_DeInit(); /* Disable Smartcard interface */
      break;

    default:
      (*SCState) = (SC_State)SC_POWER_OFF;
    }
}

/**
  * @brief  Enables or disables the power to the Smartcard.
  * @param  NewState: new state of the Smartcard power supply.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SC_PowerCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
     GPIO_SetBits(GPIOB, SC_CMDVCC);
  }
  else
  {
     GPIO_ResetBits(GPIOB, SC_CMDVCC);
  }
}

/**
  * @brief  Sets or clears the Smartcard reset pin.
  * @param  ResetState: this parameter specifies the state of the Smartcard
  *         reset pin.
  * @retval None
  */
void SC_Reset(BitAction ResetState)
{
  if (ResetState != RESET)
  {
     GPIO_SetBits(GPIOC, SC_RESET);
  }
  else
  {
     GPIO_ResetBits(GPIOC, SC_RESET);
  }
}

/**
  * @brief   Resends the byte that failed to be received (by the Smartcard)correctly.
  * @param   None
  * @retval  None
  */
void SC_ParityErrorHandler(void)
{
    USART_SendData9(USART2,SCData);
    while (USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET)
    {
    }
}

/**
  * @brief   Configures the IO speed (BaudRate) communication.
  * @param   None
  * @retval  None
  */
void SC_PTSConfig(void)
{

  uint32_t workingbaudrate = 0;
  uint32_t apbclock = 0;
  uint8_t locData = 0, PTSConfirmStatus = 1;

  /* Reconfigure the UART1 Baud Rate -------------------------------------------*/
  apbclock = (uint32_t)CLK_GetClockFreq();
  apbclock /= (USART2->PSCR * 2);

  if ((SC_A2R.T0 & (uint8_t)0x10) == (uint8_t)0x10)
  {
    if (SC_A2R.T[0] != (uint8_t)0x11)
    {
      /* Send PTSS */
      SCData = (uint8_t)0xFF;
      SC_SendDataCard(SCData);

      /* Send PTS0 */
      SCData = (uint8_t)0x10;
      SC_SendDataCard(SCData);

      /* Send PTS1 */
      SCData = SC_A2R.T[0];
      SC_SendDataCard(SCData);

      /* Send PCK */
      SCData = (uint8_t)((uint8_t)0xFF^(uint8_t)0x10^(uint8_t)SC_A2R.T[0]);
      SC_SendDataCard(SCData);

      /* Flush the UART1 DR */
      (void)USART_ReceiveData8(USART2);

      if ((UART1_ByteReceive(&locData, SC_Receive_Timeout)) == SUCCESS)
      {
        if (locData != (uint8_t)0xFF)
        {
           PTSConfirmStatus = (uint8_t)0x00;
        }
      }
      if ((UART1_ByteReceive(&locData, SC_Receive_Timeout)) == SUCCESS)
      {
         if (locData != (uint8_t)0x10)
         {
            PTSConfirmStatus = (uint8_t)0x00;
         }
      }
      if ((UART1_ByteReceive(&locData, SC_Receive_Timeout)) == SUCCESS)
      {
         if (locData != SC_A2R.T[0])
         {
             PTSConfirmStatus = (uint8_t)0x00;
         }
      }
      if ((UART1_ByteReceive(&locData, SC_Receive_Timeout)) == SUCCESS)
      {
         if (locData != ((uint8_t)0xFF^(uint8_t)0x10^(uint8_t)SC_A2R.T[0]))
         {
              PTSConfirmStatus = (uint8_t)0x00;
         }
      }
      else
      {
          PTSConfirmStatus = (uint8_t)0x00;
      }
      /* PTS Confirm */
      if (PTSConfirmStatus == (uint8_t)0x01)
      {
          workingbaudrate = apbclock * D_Table[(SC_A2R.T[0] & (uint8_t)0x0F)];
          workingbaudrate /= F_Table[((SC_A2R.T[0] >> 4) & (uint8_t)0x0F)];

         /* UART1 configuration ----------------------------------------------------*/
         /* UART1 configured as follow:
              - Word Length = 9 Bits
              - 0.5/1.5 Stop Bit
              - Even parity
              - BaudRate = ---- baud
              - Tx and Rx enabled
              - UART1 Clock enabled
            */
          USART_Init(USART2,(uint32_t)workingbaudrate ,USART_WordLength_9b ,USART_StopBits_1_5 ,USART_Parity_Even ,USART_Mode_Rx | USART_Mode_Tx );
          USART_ClockInit(USART2,USART_Clock_Enable,USART_CPOL_Low,USART_CPHA_1Edge,USART_LastBit_Enable);  //时钟初始化
        }
     }
  }
}

/**
  * @brief  Manages the Smartcard transport layer: send APDU commands and receives the APDU response.
  * @param  SC_ADPU: pointer to a SC_ADPU_Commands structure which will be initialized.
  * @param  SC_Response: pointer to a SC_ADPU_Response structure which will be initialized.
  * @retval None
  */
static void SC_SendData(SC_ADPU_Commands *SC_ADPU, SC_ADPU_Responce *SC_ResponceStatus)
{
  uint32_t i = 0;
  uint8_t locData = 0;

  /* Reset response buffer ---------------------------------------------------*/
  for (i = 0; i < LCmax; i++)
  {
     SC_ResponceStatus->Data[i] = (uint8_t)0;
  }

  SC_ResponceStatus->SW1 = (uint8_t)0;
  SC_ResponceStatus->SW2 = (uint8_t)0;

  /* Send header -------------------------------------------------------------*/
  SCData = SC_ADPU->Header.CLA;
  SC_SendDataCard(SCData);

  SCData = SC_ADPU->Header.INS;
  SC_SendDataCard(SCData);

  SCData = SC_ADPU->Header.P1;
  SC_SendDataCard(SCData);

  SCData = SC_ADPU->Header.P2;
  SC_SendDataCard(SCData);

  /* Send body length to/from SC ---------------------------------------------*/
  if (SC_ADPU->Body.LC)
  {
     SCData = SC_ADPU->Body.LC;
     SC_SendDataCard(SCData);
  }
  else if (SC_ADPU->Body.LE)
  {
     SCData = SC_ADPU->Body.LE;
     SC_SendDataCard(SCData);
  }
  
  /* Flush the UART1 DR */
  (void)USART_ReceiveData8(USART2);

  /* --------------------------------------------------------
     Wait Procedure byte from card:
     1 - ACK
     2 - NULL
     3 - SW1; SW2
    -------------------------------------------------------- */

   if ((UART1_ByteReceive(&locData, SC_Receive_Timeout)) == SUCCESS)
   {
      if (((locData & (uint8_t)0xF0) == (uint8_t)0x60) || ((locData & (uint8_t)0xF0) == (uint8_t)0x90))
      {
         /* SW1 received */
         SC_ResponceStatus->SW1 = locData;

         if ((UART1_ByteReceive(&locData, SC_Receive_Timeout)) == SUCCESS)
         {
            /* SW2 received */
            SC_ResponceStatus->SW2 = locData;
         }
      }
      else if (((locData & (uint8_t)0xFE) == (((uint8_t)~(SC_ADPU->Header.INS)) & (uint8_t)0xFE))||((locData & (uint8_t)0xFE) == (SC_ADPU->Header.INS & (uint8_t)0xFE)))
      {
           SC_ResponceStatus->Data[0] = locData;/* ACK received */
      }
   }

   /* If no status bytes received ---------------------------------------------*/
   if (SC_ResponceStatus->SW1 == (uint8_t)0x00)
   {
     /* Send body data to SC -------------------------------------------------*/
     if (SC_ADPU->Body.LC)
     {
        for (i = 0; i < SC_ADPU->Body.LC; i++)
        {
           SCData = SC_ADPU->Body.Data[i];
           SC_SendDataCard(SCData);
        }
        /* Flush the UART1 DR */
        (void)USART_ReceiveData8(USART2);
     }

     /* Or receive body data from SC ------------------------------------------*/
     else if (SC_ADPU->Body.LE)
     {
       for (i = 0; i < SC_ADPU->Body.LE; i++)
       {
         if (UART1_ByteReceive(&locData, SC_Receive_Timeout) == SUCCESS)
         {
            SC_ResponceStatus->Data[i] = locData;
         }
       }
     }
     /* Wait SW1 --------------------------------------------------------------*/
     i = 0;
     while (i < 10)
     {
       if (UART1_ByteReceive(&locData, SC_Receive_Timeout) == SUCCESS)
       {
          SC_ResponceStatus->SW1 = locData;
          i = 11;
       }
       else
       {
          i++;
       }
      }
      /* Wait SW2 ------------------------------------------------------------*/
      i = 0;
      while (i < 10)
      {
         if (UART1_ByteReceive(&locData, SC_Receive_Timeout) == SUCCESS)
         {
            SC_ResponceStatus->SW2 = locData;
            i = 11;
         }
         else
         {
            i++;
         }
      }
    }
}

/**
  * @brief   Requests the reset answer from card.
  * @param   SCState: pointer to an SC_State enumeration that will contain the Smartcard state.
  * @param   card: pointer to a buffer which will contain the card ATR.
  * @param   length: maximum ATR length
  * @retval  None
  */
static void SC_AnswerReq(SC_State *SCstate, uint8_t *card, uint8_t length)
{
    uint8_t Data = 0;
    uint32_t i = 0;

    switch (*SCstate)
    {
    case SC_RESET_LOW:
        /* Check response with reset low ---------------------------------------*/

        for (i = 0; i < length; i++)
        {
            if ((UART1_ByteReceive(&Data, SC_Receive_Timeout)) == SUCCESS)
            {
                card[i] = Data;
            }
        }
        if (card[0])
        {
            (*SCstate) = SC_ACTIVE;
            SC_Reset(SET);
        }
        else
        {
            (*SCstate) = SC_RESET_HIGH;
        }
        break;

    case SC_RESET_HIGH:
        /* Check response with reset high --------------------------------------*/
        SC_Reset(SET); /* Reset High */

        while (length--)
        {
            if ((UART1_ByteReceive(&Data, SC_Receive_Timeout)) == SUCCESS)
            {
                *card++ = Data; /* Receive data for timeout = SC_Receive_Timeout */
            }
        }
        if (card[0])
        {
            (*SCstate) = SC_ACTIVE;
        }
        else
        {
            (*SCstate) = SC_POWER_OFF;
        }
        break;

    case SC_ACTIVE:
        break;

    case SC_POWER_OFF:
        /* Close Connection if no answer received ------------------------------*/
        SC_Reset(SET); /* reset high - a bit is used as level shifter from 3.3 to 5 V */
        SC_PowerCmd(DISABLE);
        break;

    default:
        (*SCstate) = SC_RESET_LOW;
    }
}

/**
  * @brief  Decodes the Answer to reset received from card.
  * @param  Card: pointer to the buffer containing the card ATR.
  * @retval None
  */
static uint8_t SC_decode_Answer2reset(uint8_t *card)
{
    uint32_t i = 0, flag = 0, buf = 0, protocol = 0;

    SC_A2R.TS = card[0];  /* Initial character */
    SC_A2R.T0 = card[1];  /* Format character */

    SC_A2R.Hlength = (uint8_t)(SC_A2R.T0 & (uint8_t)0x0F);

    if ((SC_A2R.T0 & (uint8_t)0x80) == (uint8_t)0x80)
    {
        flag = 1;
    }

    for (i = 0; i < 4; i++)
    {
        SC_A2R.Tlength = (uint8_t)(SC_A2R.Tlength + (((SC_A2R.T0 & (uint8_t)0xF0) >> ((uint8_t)4 + i)) & (uint8_t)0x1));
    }

    for (i = 0; i < SC_A2R.Tlength; i++)
    {
        SC_A2R.T[i] = card[i + (uint8_t)2];
    }

    protocol = SC_A2R.T[SC_A2R.Tlength - (uint8_t)1] & (uint8_t)0x0F;

    while (flag)
    {
        if ((SC_A2R.T[SC_A2R.Tlength - (uint8_t)1] & (uint8_t)0x80) == (uint8_t)0x80)
        {
            flag = 1;
        }
        else
        {
            flag = 0;
        }

        buf = SC_A2R.Tlength;
        SC_A2R.Tlength = 0;

        for (i = 0; i < 4; i++)
        {
            SC_A2R.Tlength = (uint8_t)(SC_A2R.Tlength + (((SC_A2R.T[buf - (uint8_t)1] & (uint8_t)0xF0) >> ((uint8_t)4 + i)) & (uint8_t)0x1));
        }

        for (i = 0;i < SC_A2R.Tlength; i++)
        {
            SC_A2R.T[buf + i] = card[i + (uint8_t)2 + buf];
        }
        SC_A2R.Tlength += (uint8_t)buf;
    }

    for (i = 0; i < SC_A2R.Hlength; i++)
    {
        SC_A2R.H[i] = card[i + (uint8_t)2 + SC_A2R.Tlength];
    }

    return (uint8_t)protocol;
}

/**
  * @brief  Initializes all peripheral used for Smartcard interface.
  * @param  None
  * @retval None
  */
static void SC_Init(void)
{
    uint32_t i =0;
    uint32_t workingbaudrate = 9600;
   
    /* Set PA5 as Output open-drain high-impedance level - SmartCard_IO(UART1_Tx) */
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_OD_HiZ_Fast);//USART_TX   推挽输出
    
    /* Set PG5 as Output push-pull low level - SmartCard_RESET */
    GPIO_Init(GPIOC,GPIO_Pin_5,GPIO_Mode_Out_PP_Low_Fast);//USART_RX    上拉输入

    /* Set PA6 as Output push-pull low level - SmartCard_CLK */
    GPIO_Init(GPIOC,GPIO_Pin_4,GPIO_Mode_Out_PP_Low_Fast);//USART_CLK  推挽输出

    /* Set PG4 as Output push-pull low level - SmartCard_5V/3V */
   // GPIO_Init(GPIOG, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);

    /* Set PG7 as Output push-pull high level (inactive state) - SmartCard_CMDVCC */
   // GPIO_Init(GPIOG, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_FAST);

    /*High speed internal clock prescaler: 1*/
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

    /* Set RSTIN HIGH */
    SC_Reset(SET);

    /* Disable CMDVCC */
    SC_PowerCmd(ENABLE); 

    /* Select 5 V */
    //SC_VoltageConfig(SC_Voltage_5V);

     CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);  //使能USART1时钟
     USART_DeInit(USART1); //初始化端口为默认值
    /* UART1 configuration ----------------------------------------------------*/
    /* UART1 configured as follow:
          - Word Length = 9 Bits
          - 0.5/1.5 Stop Bit
          - Even parity
          - BaudRate = 10752 baud
          - Tx and Rx enabled
          - UART1 Clock enabled
    */
    USART_Init(USART1,(uint32_t)workingbaudrate ,USART_WordLength_9b ,USART_StopBits_1_5 ,USART_Parity_Even ,USART_Mode_Rx | USART_Mode_Tx ); 
    USART_ClockInit(USART1,USART_Clock_Enable,USART_CPOL_Low,USART_CPHA_1Edge,USART_LastBit_Enable);  //时钟初始化

    /* UART1 Clock set to 4 MHz (master frequency (16 MHZ) / 4) */
    USART_SetPrescaler(USART1,0x02);
    /* UART1 Guard Time set to 16 Bit */
   USART_SetGuardTime(USART1,0x02);
   USART_ITConfig(USART1, USART_IT_PE , ENABLE);   //使能奇偶校验错误中断

   USART_Cmd(USART1,ENABLE); //使能USART2

   USART_SmartCardNACKCmd(USART1,ENABLE); //使能NACK时钟
   USART_SmartCardCmd(USART1,ENABLE); //使能智能卡模式

    /* Enable CMDVCC */
    SC_PowerCmd(DISABLE);

    /* Set RSTIN HIGH */
    SC_Reset(RESET);

    for (i = 0; i < 6000; i++)
    {
    }
    /* Set RSTIN HIGH */
    SC_Reset(SET);
}

/**
  * @brief  Deinitializes all resources used by the Smartcard interface.
  * @param  None
  * @retval None
  */
static void SC_DeInit(void)
{
    /* Disable CMDVCC */
    SC_PowerCmd(ENABLE);

    /* Deinitializes the UART1 */
    USART_DeInit(USART1);

    /* Deinitializes the GPIOG */
    GPIO_DeInit(GPIOC);

    /* Deinitializes the GPIOE */
    GPIO_DeInit(GPIOB);
}

/**
  * @brief  Configures the card power voltage.
  * @param  SC_Voltage: specifies the card power voltage.
  *         This parameter can be one of the following values:
  *         - SC_Voltage_5V: 5V cards.
  *         - SC_Voltage_3V: 3V cards.
  * @retval None
  */
static void SC_VoltageConfig(uint32_t SC_Voltage)
{
    if (SC_Voltage == SC_Voltage_5V)
    {
        /* Select Smartcard 5V */
        GPIO_SetBits(GPIOG, SC_3_5V);
    }
    else
    {
        /* Select Smartcard 3V */
        GPIO_ResetBits(GPIOG, SC_3_5V);
    }
}

/**
  * @brief  Detects whether the Smartcard is present or not.
  * @param  None
  * @retval Smartcard inserted
  *         Smartcard not inserted
  */
static uint8_t SC_Detect(void)
{
    uint8_t bitstatus = 0x00;

    if ((GPIOE->IDR & SC_OFF) != (uint32_t)RESET)
    {
        bitstatus = (uint8_t)SET;
    }
    else
    {
        bitstatus = (uint8_t)RESET;
    }
    return bitstatus;
}
/**
  * @brief   Transmits 9 bit data through the UART1 peripheral and check if the 
  *          data transmit correctly.
  * @param   SCData: the data to transmit.
  * @retval  None
  */
static void SC_SendDataCard(uint8_t SCData)
{
    USART_SendData9(USART1,SCData);
    
    while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET)
    {
    }

    /* If a Frame error is signaled by the card */
    while (USART_GetFlagStatus(USART1,USART_FLAG_FE) != RESET)
    {
        /* Clear the UART1 Frame error flags */
       USART_ReceiveData8(USART1);

        /* Resend the byte that failed to be received (by the Smartcard) correctly */
        SC_ParityErrorHandler();
    }

    /* If a Noise error is signaled by the card */
    while (USART_GetFlagStatus(USART1,USART_FLAG_NF) != RESET)
    {
        /* Clear the UART1 Frame noise flag */
        USART_ReceiveData8(USART1);
    }
    while (USART_GetFlagStatus(USART1,USART_FLAG_OR) != RESET)
    {
        /* Clear the UART1 Frame error flag */
        USART_ReceiveData8(USART1);
    }
}
/**
  * @brief  Receives a new data while the time out not elapsed.
  * @param  None
  * @retval ErrorStatus enumeration value:
  *         SUCCESS: New data has been received
  *         ERROR: time out was elapsed and no further data is received
  */
static ErrorStatus UART1_ByteReceive(uint8_t *Data, uint32_t TimeOut)
{
    uint32_t Counter = 0;

    while ((USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET) && (Counter != TimeOut))
    {
        Counter++;
    }

    if (Counter != TimeOut)
    {
        *Data = (uint8_t)USART_ReceiveData8(USART1);

        return SUCCESS;
    }
    else
    {
        return ERROR;
    }

}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
