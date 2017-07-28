#ifndef __USART0_H__
#define __USART0_H__

#include "define.h"

/* queue size is 2 ^ UART0_RX_Q_SIZE */
#define USART0_RX_Q_SIZE			2
/* buffer size is 2 ^ UART0_RX_SIZE */
#define USART0_RX_SIZE				4
#define USART0_RX_TIMEOUT			0xFFFFFFFF
#define USART0_RX_EOF				'\r'

#define USART0_TX_TIMEOUT			0xFFFFFFFF

#define USART0_ENABLE_PRINTF		TRUE

void usart0Init(void);

INT8U usart0Read(char **str);

INT8U usart0Print(char *str);
#if USART0_ENABLE_PRINTF
void usart0Printf(char *fmt, ...);
#endif
INT8U usart0Hex8(uint8 hex8);
INT8U usart0Hex16(uint16 hex16);
INT8U usart0Hex32(uint32 hex32);
INT8U usart0LongInt(uint32 x);

#endif
