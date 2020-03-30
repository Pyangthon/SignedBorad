

//#include "Stm8l15x.h"
//#include "delay.h"
#include "Spi.h"
#include "Si446x.h"
#include "Si446x_defs.h"
#include "Radio_extend.h"
#include "Phylayer.h"

/*点抄模式相关配置*/

#define P2P_RF_MODEM_MOD_TYPE_12 0x11, 0x20, 0x0C, 0x00, 0x2A, 0x00, 0x07, 0x05, 0xDC, 0x00, 0x01, 0x8C, 0xBA, 0x80, 0x00, 0x09
#define P2P_RF_MODEM_FREQ_DEV_0_1 0x11, 0x20, 0x01, 0x0C, 0x13
#define P2P_RF_MODEM_TX_RAMP_DELAY_12 0x11, 0x20, 0x0C, 0x18, 0x01, 0x80, 0x08, 0x03, 0x80, 0x00, 0x20, 0x20, 0x00, 0xE8, 0x00, 0x55
#define P2P_RF_MODEM_BCR_NCO_OFFSET_2_12 0x11, 0x20, 0x0C, 0x24, 0x06, 0x0C, 0xAB, 0x03, 0x03, 0x00, 0xC2, 0x00, 0x54, 0x23, 0x81, 0x57
#define P2P_RF_MODEM_AFC_LIMITER_1_3 0x11, 0x20, 0x03, 0x30, 0x02, 0x8A, 0x80
#define P2P_RF_MODEM_AGC_WINDOW_SIZE_12 0x11, 0x20, 0x0C, 0x38, 0x11, 0x13, 0x13, 0x80, 0x02, 0x60, 0x00, 0x00, 0x28, 0x0C, 0x84, 0x23
#define P2P_RF_MODEM_RAW_CONTROL_10 0x11, 0x20, 0x0A, 0x45, 0x8F, 0x02, 0x36, 0x01, 0x00, 0xFF, 0x06, 0x00, 0x18, 0x40
#define P2P_RF_MODEM_SPIKE_DET_2 0x11, 0x20, 0x02, 0x54, 0x07, 0x07
#define P2P_RF_MODEM_DSA_CTRL1_5 0x11, 0x20, 0x05, 0x5B, 0x40, 0x04, 0x11, 0x78, 0x20
#define P2P_RF_FREQ_CONTROL_INTE_8 0x11, 0x40, 0x08, 0x00, 0x4B, 0x09, 0x3A, 0x72, 0x4E, 0xC5, 0x20, 0xFE


/*网络模式相关配置*/

#define NET_RF_MODEM_MOD_TYPE_12 0x11, 0x20, 0x0C, 0x00, 0x2A, 0x00, 0x07, 0x00, 0x5D, 0xC0, 0x01, 0x8C, 0xBA, 0x80, 0x00, 0x00
#define NET_RF_MODEM_FREQ_DEV_0_1 0x11, 0x20, 0x01, 0x0C, 0x61
#define NET_RF_MODEM_TX_RAMP_DELAY_12 0x11, 0x20, 0x0C, 0x18, 0x01, 0x80, 0x08, 0x03, 0x80, 0x00, 0xB0, 0x10, 0x0C, 0xE8, 0x00, 0x71
#define NET_RF_MODEM_BCR_NCO_OFFSET_2_12 0x11, 0x20, 0x0C, 0x24, 0x04, 0x89, 0x80, 0x02, 0x44, 0x00, 0xC2, 0x00, 0x54, 0x23, 0x80, 0x1C
#define NET_RF_MODEM_AFC_LIMITER_1_3 0x11, 0x20, 0x03, 0x30, 0x02, 0x9E, 0x80
#define NET_RF_MODEM_AGC_WINDOW_SIZE_12 0x11, 0x20, 0x0C, 0x38, 0x11, 0x19, 0x19, 0x80, 0x02, 0x40, 0x00, 0x00, 0x28, 0x0C, 0x84, 0x23
#define NET_RF_MODEM_RAW_CONTROL_10 0x11, 0x20, 0x0A, 0x45, 0x8F, 0x01, 0x1B, 0x01, 0x00, 0xFF, 0x06, 0x00, 0x18, 0x40
#define NET_RF_MODEM_SPIKE_DET_2 0x11, 0x20, 0x02, 0x54, 0x04, 0x07
#define NET_RF_MODEM_DSA_CTRL1_5 0x11, 0x20, 0x05, 0x5B, 0x40, 0x04, 0x09, 0x78, 0x20
#define NET_RF_FREQ_CONTROL_INTE_8 0x11, 0x40, 0x08, 0x00, 0x4A, 0x0D, 0xA3, 0x0D, 0x4E, 0xC5, 0x20, 0xFE


const uint8_t ConfigtableP2P[] =
{
    16, P2P_RF_MODEM_MOD_TYPE_12, \
    5 , P2P_RF_MODEM_FREQ_DEV_0_1, \
    16, P2P_RF_MODEM_TX_RAMP_DELAY_12, \
    16, P2P_RF_MODEM_BCR_NCO_OFFSET_2_12, \
    7 , P2P_RF_MODEM_AFC_LIMITER_1_3, \
    16, P2P_RF_MODEM_AGC_WINDOW_SIZE_12, \
    14, P2P_RF_MODEM_RAW_CONTROL_10, \
    6 , P2P_RF_MODEM_SPIKE_DET_2, \
    9 , P2P_RF_MODEM_DSA_CTRL1_5, \
    12, P2P_RF_FREQ_CONTROL_INTE_8,
    0x00 \
};

const uint8_t ConfigtableNet[] =
{
    16, NET_RF_MODEM_MOD_TYPE_12, \
    5 , NET_RF_MODEM_FREQ_DEV_0_1, \
    16, NET_RF_MODEM_TX_RAMP_DELAY_12, \
    16, NET_RF_MODEM_BCR_NCO_OFFSET_2_12, \
    7 , NET_RF_MODEM_AFC_LIMITER_1_3, \
    16, NET_RF_MODEM_AGC_WINDOW_SIZE_12, \
    14, NET_RF_MODEM_RAW_CONTROL_10, \
    6 , NET_RF_MODEM_SPIKE_DET_2, \
    9 , NET_RF_MODEM_DSA_CTRL1_5, \
    12, NET_RF_FREQ_CONTROL_INTE_8,
    0x00 \
};


void Si4463ConfigNetorP2P(uint8_t NP)
{
    uint8_t i;
    uint16_t j = 0;
    const uint8_t   *ptr;
    FSK_OCS_ON;
    BitInterOff;	//关闭外部bit中断
    if(NP == P2PMode)
        ptr = ConfigtableP2P;
    else
        ptr = ConfigtableNet;
    while((i = *(ptr + j)) != 0)
    {
        j += 1;
        SI446X_CMD((INT8U *)ptr + j, i);
        //       IWDG_ReloadCounter();
        j += i;
    }
}



void SI446X_FRR_A_READ(uint8_t *buffer)
{
    uint8_t size = 4;
    uint8_t cmd[1];

    cmd[0] = FRR_A_READ;
    SI446X_WAIT_CTS();
    SPI_CS_L;
    SPI_ExchangeByte(cmd[0]);
    while (size--)
    {
        *buffer++ = SPI_ExchangeByte(0xFF);
    }
    SPI_CS_H;
}

void delayms_i(uint16_t time)
{
    uint16_t i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 100; j++);
}


/////////////////////////////////////////////////////////////
void RF_config()
{
    uint8_t buff[10];
    SI446X_RESET();         // SI446X 模块复位
    delayms_i(800);
    SI446X_CONFIG_INIT();   // 寄存器初始化，寄存器来自WDS配置的头文件

    SI446X_START_RX(0, 0, 0,
                    SI446X_STATE_NOCHANGE,
                    SI446X_STATE_ACTIVE,
                    SI446X_STATE_ACTIVE);  // 进入接收模式
    //RF_GPIO_ON();
    //SI446X_SET_POWER(0x7f); // 将输出功率配置为最大
    //SI446X_SET_PROPERTY_X(PKT_LEN,TxPkgCfgTab[0],&TxPkgCfgTab[1]);
    //SI446X_SET_PROPERTY_X(PKT_LEN,RxPkgCfgTab[0],&RxPkgCfgTab[1]);
    //SI446X_GET_PROPERTY_X(PKT_LEN,13,RxCfgTab);
    SI446X_PART_INFO(buff);
    SI446X_INT_STATUS(buff);
    SI446X_GPIO_CONFIG(81, 84, 20, 23, 0, 0, 0);   //4463 GPIO配置

    SI446X_CHANGE_STATE(SI446X_STATE_RX);
}



//RSSI
void SI446X_GET_MODEM_STATUS(uint8_t *buffer)
{
    uint8_t cmd[1];
    cmd[0] = GET_MODEM_STATUS;
    SI446X_CMD(cmd, 1);
    SI446X_READ_RESPONSE(buffer, 9);

}

int16_t RF_PktRSSI(void)
{
    int16_t rf_rssi = 0;
    uint8_t status[10];
    SI446X_GET_MODEM_STATUS(status);
    SI446X_FRR_A_READ(status);//print("v =%d",status[0]);
    rf_rssi = (int16_t)((status[0] >> 1) - 70 - SI446X_GET_PROPERTY_1((SI446X_PROPERTY)0x204e));
    return rf_rssi;

}




//5-20dbm
uint8_t pa_pwr_lvl_dbm[16] =
{
    10, 12, 14, 16, 18, 20, 23, 26, 29, 32, 35, 40, 50, 60, 70, 127
    //5-10            //11-15        //16 -20
};
void RF_PA_SET(uint8_t pa)
{
    SI446X_SET_POWER(pa_pwr_lvl_dbm[pa - 5]);
}


/*
// Set properties:           RF_PA_MODE_4
// Number of properties:     4
// Group ID:                 0x22
// Start ID:                 0x00
// Default values:           0x08, 0x7F, 0x00, 0x5D,
// Descriptions:
//   PA_MODE - Selects the PA operating mode, and selects resolution of PA power adjustment (i.e., step size).
//   PA_PWR_LVL - Configuration of PA output power level.
//   PA_BIAS_CLKDUTY - Configuration of the PA Bias and duty cycle of the TX clock source.
//   PA_TC - Configuration of PA ramping parameters.
*/

//#define RF_PA_MODE_4 0x11, 0x22, 0x04, 0x00, 0x04, 0x7F, 0x00, 0x3D
//默认08 group2 发射电流很大
//改成04 组1    正常    意义不知


void RF_GPIO_OFF()
{
    SI446X_GPIO_CONFIG(2, 2, 0, 2, 0, 0, 0);
}

void RF_GPIO_ON()
{
    //  SI446X_GPIO_CONFIG(3, 3, 32|0x40, 33|0x40, 0, 0, 0);
    SI446X_GPIO_CONFIG(3, 3, 32, 33, 0, 0, 0);
    //SI446X_GPIO_CONFIG(17, 20, 32, 33, 0, 0, 0);
    // SI446X_GPIO_CONFIG(16, 4, 32, 33, 0, 0, 0);
}





