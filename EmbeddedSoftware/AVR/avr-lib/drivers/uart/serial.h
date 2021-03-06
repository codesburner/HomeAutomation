#ifndef SERIAL_H_
#define SERIAL_H_

/*-----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/
#define UART_RX_BUFFER_SIZE		SERIAL_RX_BUFFER_SIZE
#define UART_TX_BUFFER_SIZE		SERIAL_TX_BUFFER_SIZE

#ifndef CAN_PRINTF
#define CAN_PRINTF 0
#endif

/*-----------------------------------------------------------------------------
 * Public Function Prototypes
 *---------------------------------------------------------------------------*/
void Serial_Init(void);


#endif /*SERIAL_H_*/
