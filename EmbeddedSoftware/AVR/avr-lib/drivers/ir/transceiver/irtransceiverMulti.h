/** 
 * @defgroup infrared IR Driver Library
 * @code #include <drivers/ir/transceiver/transceiver.h> @endcode
 * 
 * @brief  
 *
 *
 * @author	Andreas Fritiofson, Anders Runeson
 * @date	2007
 */

/**@{*/

#ifndef IRTRANSCEIVER_H_
#define IRTRANSCEIVER_H_

/*-----------------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------------*/
#include <stdio.h>

/*-----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

#ifndef MAX_NR_TIMES
#define MAX_NR_TIMES		127 								//max ir pulses+pauses, used for dimensioning the buffer 
#endif

#define TRUE 1
#define FALSE 0

#ifndef IR_RX_ACTIVE_LOW
#define IR_RX_ACTIVE_LOW    1
#endif

#ifndef IR_TX_ACTIVE_LOW
#define IR_TX_ACTIVE_LOW	0
#endif

#ifndef IR_TX_ENABLE
#define IR_TX_ENABLE	0
#endif

#ifndef IR_RX_ENABLE
#define IR_RX_ENABLE	0
#endif

#ifndef IR_SUPPORTED_NUM_CHANNELS
#define IR_SUPPORTED_NUM_CHANNELS 3
#endif

/**
 * @brief Type of the callback function pointer
 * parameters: channel, buffer, length
 */
typedef void (*irRxCallback_t)(uint8_t, uint16_t*, uint8_t);
typedef void (*irTxCallback_t)(uint8_t);


/*-----------------------------------------------------------------------------
 * Public Function Prototypes
 *---------------------------------------------------------------------------*/
int IrTransceiver_Transmit(uint8_t channel, uint16_t *buffer, uint8_t start, uint8_t length, uint16_t modfreqkHz);

void IrTransceiver_Init(void);
uint8_t IrTransceiver_GetStoreEnableRx(uint8_t channel);
void IrTransceiver_DisableRx(uint8_t channel);
void IrTransceiver_EnableRx(uint8_t channel);
void IrTransceiver_ResetRx(uint8_t channel);

void IrTransceiver_InitRxChannel(uint8_t channel, uint16_t *buffer, irRxCallback_t callback, uint8_t pcint_id, volatile uint8_t* port, volatile uint8_t* pin, volatile uint8_t* ddr,uint8_t nr, uint8_t pcint);
void IrTransceiver_DeInitRxChannel(uint8_t channel, uint8_t pcint_id, volatile uint8_t* port, volatile uint8_t* pin, volatile uint8_t* ddr,uint8_t nr, uint8_t pcint);
void IrTransceiver_InitTxChannel(uint8_t channel, irTxCallback_t callback, volatile uint8_t *port, volatile uint8_t *pin, volatile uint8_t *ddr,uint8_t nr, uint8_t pcint);

//void IrTransceiver_Init_RX_Channel(uint8_t channel, uint16_t *buffer, irCallback_t callback, uint8_t pcint_id, volatile uint8_t* port, volatile uint8_t* pin, volatile uint8_t* ddr,uint8_t nr, uint8_t pcint);

/* Active TX mod freq in kHz */
extern uint16_t drvIrTxModFreqkHz;

/*-----------------------------------------------------------------------------
 * Private Function Prototypes
 *---------------------------------------------------------------------------*/

void IrTransceiver_Store(uint8_t channel);

#endif /*IRTRANSCEIVER_H_*/
