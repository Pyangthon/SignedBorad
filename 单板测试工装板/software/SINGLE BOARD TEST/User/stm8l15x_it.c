/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/stm8l15x_it.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_it.h"

/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER(NonHandledInterrupt,0)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif

/**
  * @brief TRAP interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(FLASH_IRQHandler,1)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief DMA1 channel0 and channel1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL0_1_IRQHandler,2)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief DMA1 channel2 and channel3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL2_3_IRQHandler,3)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief External IT PORTE/F and PVD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIE_F_PVD_IRQHandler,5)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTB / PORTG Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIB_G_IRQHandler,6)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTD /PORTH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_H_IRQHandler,7)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    Delay_ms(100);      // ��ʱ300ms�ж��Ƿ����������ش���
    if(READ_KEY1() != RESET)
    {
        FlagStruct.Key1Flag = TRUE;
    }
    if(READ_KEY2() != RESET)
    {
        FlagStruct.Key2Flag = TRUE;

    }
    if(READ_KEY3() != RESET)
    {
        FlagStruct.Key3Flag = TRUE;

    }
    if(READ_KEY4() != RESET)
    {
        FlagStruct.Key4Flag = TRUE;
    } 
    EXTI_ClearITPendingBit(EXTI_IT_PortD);
}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */

INTERRUPT_HANDLER(EXTI0_IRQHandler,8)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */

    // �ж��Ƿ�����������
    if(RF_DIO0() == 1)
    {
        if(GetRF1278_State() == 1)
        {
            // ���ö˿�Ϊ�͵�ƽ���ر��ж�, ���ý��ձ�־λΪ1
            //disableInterrupts();
            // ���ձ�־λ��1����ʾ��Ҫ���н�������
            LoraDataStruct.LoRaRXFlag = TRUE; 
        }
    }
    // �����־λ
    EXTI_ClearITPendingBit(EXTI_IT_Pin0);
    


}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI1_IRQHandler,9)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    
    Delay_ms(5);    // ��ʱ5ms����
    if(READ_FUN_KEY() == RESET)
    {
        FlagStruct.FunKeyFlag = 1;
    }
    EXTI_ClearITPendingBit(EXTI_IT_Pin1);
}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI2_IRQHandler,10)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */

}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI3_IRQHandler,11)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI4_IRQHandler,12)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    Delay_ms(10);
    if(READ_KEY1() == RESET)
    {
        FlagStruct.Key1Flag = TRUE;
    }
     EXTI_ClearITPendingBit(EXTI_IT_Pin4);
    
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI5_IRQHandler,13)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    Delay_ms(10);
    if(READ_KEY2() == RESET)
    {
        FlagStruct.Key2Flag = TRUE;

    }
     EXTI_ClearITPendingBit(EXTI_IT_Pin5);
}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI6_IRQHandler,14)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    Delay_ms(50);
    if(READ_KEY3() != RESET)
    {
        FlagStruct.Key3Flag = TRUE;
        FlagStruct.ValveCount = 0X01;
    }
    EXTI_ClearITPendingBit(EXTI_IT_Pin6);
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI7_IRQHandler,15)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    Delay_ms(50);
    if(READ_KEY4() != RESET)
    {
        FlagStruct.Key4Flag = TRUE;
        FlagStruct.ValveCount = 0X02;
    }
     EXTI_ClearITPendingBit(EXTI_IT_Pin7);
}
/**
  * @brief LCD /AES Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(LCD_AES_IRQHandler,16)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief CLK switch/CSS/TIM1 break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SWITCH_CSS_BREAK_DAC_IRQHandler,17)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief ADC1/Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(ADC1_COMP_IRQHandler,18)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief TIM2 Update/Overflow/Trigger/Break /USART2 TX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler,19)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    CountDown--;
    if(CountDown == 0)
    {
        HaltState = TRUE;
        CountDown = DEFCOUNTDOWN;
    }
    TIM2_ClearITPendingBit(TIM2_IT_Update);
}

/**
  * @brief Timer2 Capture/Compare / USART2 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_CC_USART2_RX_IRQHandler,20)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    // ����2�����ж�
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        USART_2.USART_Date[USART_2.Length] =  USART_ReceiveData8(USART2); //��������
       
        if(USART_2.USART_Date[0] == RESPONSECOM)
        {
            USART_2.Length++;
            if(USART_2.USART_Date[USART_2.Length] == CONFIRCOM)
            {
                USART_2.Falg = 1;
            }
        }
        else
        {
            USART_2.Length = 0;
            memset(USART_2.USART_Date,0,sizeof(USART_2.USART_Date));//�������
        }
        USART_2.Length++;
        
    }
    
    USART_ClearFlag(USART2,USART_FLAG_RXNE);
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler,21)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    MsCount++;
    if(MsCount == 50000)
    {
        MsCount = 0;
    }
    if((MsCount % 1000) == 0) 
    {
       FlagStruct.SecondFlag = 1;
    }
    TIM3_ClearITPendingBit(TIM3_IT_Update);
}
/**
  * @brief Timer3 Capture/Compare /USART3 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_CC_USART3_RX_IRQHandler,22)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    // ����3�����ж�
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
    
        USART_3.USART_Date[USART_3.Length] =  USART_ReceiveData8(USART3); //��������
        if(USART_3.USART_Date[0]  == RESPONSECOM)
        {             
             if(USART_3.USART_Date[USART_3.Length] == CONFIRCOM)
             {
                  USART_3.Falg = 1;
             }
         
             USART_3.Length++; //������������
             if(USART_3.Length >= BUFFER_LEN)
             {
                 USART_3.Length = 0;
             }
        }
        else
        {
        memset(USART_3.USART_Date,0,sizeof(USART_3.USART_Date));//�������
        USART_3.Length = 0;
        }
    } 
    
    USART_ClearFlag(USART3,USART_FLAG_RXNE);
 
    
}
/**
  * @brief TIM1 Update/Overflow/Trigger/Commutation Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_COM_IRQHandler,23)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    
}
/**
  * @brief TIM1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CC_IRQHandler,24)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
   
}

/**
  * @brief TIM4 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler,25)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    SceCount++;
   if(SceCount % 3000 == 0)
   {
       LEDFlicker(3, 1);
   }
    
    if(SceCount == 9000)
    {
        SceCount = 0;
    }
//    TIM4_ClearFlag(TIM4_FLAG_Update);
    TIM4_ClearITPendingBit(TIM4_IT_Update);
}
/**
  * @brief SPI1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI1_IRQHandler,26)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */		
}

/**
  * @brief USART1 TX / TIM5 Update/Overflow/Trigger/Break Interrupt  routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler,27)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief USART1 RX / Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
     if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        USART_1.USART_Date[USART_1.Length] =  USART_ReceiveData8(USART1); //��������
        if(USART_1.USART_Date[0] == 0xF1)
        {
            USART_1.Length++;
            if(USART_1.USART_Date[USART_1.Length-1] == 0XF2)
            {
                
                USART_1.Falg = TRUE;
                InfraredTest();
            }
        }
        else
        {
            USART_1.Length = 0;
            memset(USART_1.USART_Date, 0, sizeof(USART_1.USART_Date));
        }
    }
    USART_ClearFlag(USART1,USART_FLAG_RXNE);
}

/**
  * @brief I2C1 / SPI2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C1_SPI2_IRQHandler,29)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/