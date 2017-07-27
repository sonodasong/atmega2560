#ifndef __SPI_H__
#define __SPI_H__

#include "define.h"

#define SPI_TIMEOUT			0xFFFFFFFF

void spiInit(void);
INT8U spiBufR(uint8 *buf, uint16 size, uint8 fill);
INT8U spiBufW(uint8 *buf, uint16 size);
INT8U spiBufWR(uint8 *txBuf, uint8 *rxBuf, uint16 size);
INT8U spiRegBufR(uint8 reg, uint8 *firstByte, uint8 *buf, uint16 size, uint8 fill);
INT8U spiRegBufW(uint8 reg, uint8 *firstByte, uint8 *buf, uint16 size);
INT8U spiRegBufWR(uint8 reg, uint8 *firstByte, uint8 *txBuf, uint8 *rxBuf, uint16 size);
void spiClockSlow(void);
void spiClockFast(void);

#endif
