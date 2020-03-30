/*
 * radio_extend.h
 *
 *  Created on: 2016-12-5
 *      Author: lenovo
 */

#ifndef RADIO_EXTEND_H_
#define RADIO_EXTEND_H_

#include"Si446x.h"

typedef enum
{
    SI446X_STATE_NOCHANGE = 0,
    SI446X_STATE_SLEEP,
    SI446X_STATE_ACTIVE,
    SI446X_STATE_READY,
    SI446X_STATE_READY2,
    SI446X_STATE_TX_TUNE,
    SI446X_STATE_RX_TUNE,
    SI446X_STATE_TX,
    SI446X_STATE_RX

} SI446X_STATE;

#define NetMode 0x0A
#define P2PMode 0x05

#define RF_IRQFLAGS_RXDONE  0x10
#define RF_IRQFLAGS_TXDONE  0x20
#define RF_IRQFLAGS_RFAF    0x01
#define RF_IRQFLAGS_TFAE    0x02

#define RADIO_TX_ALMOST_EMPTY_THRESHOLD 0x30
#define RADIO_RX_ALMOST_FULL_THRESHOLD  0x30

void RF_config();
uint8_t RF_Tx(uint8_t *buffer, uint8_t length, uint8_t channel);
void RF_Rx(uint8_t channel, uint8_t len);
uint8_t RF_RxData(uint8_t *buffer);
int16_t RF_PktRSSI(void);

void RF_RS_SET(uint8_t rs);
void RF_PA_SET(uint8_t pa);
void RF_GPIO_OFF();
void RF_GPIO_ON();

void Si4463ConfigNetorP2P(uint8_t NP);

//extern uint16_t rf_time;

#endif /* RADIO_EXTEND_H_ */
