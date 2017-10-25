#include "spi.h"

static uint8 *spiRxBuf;
static uint8 *spiTxBuf;
static uint16 spiSize;
static uint16 spiCnt;
static uint8 spiFill;
static uint8 spiFirstByte;
static OS_EVENT *spiRdy;

static void (*spiHandlerPtr)(void);
static void spiBufRHandler(void);
static void spiBufWHandler(void);
static void spiBufRwHandler(void);
static void spiRegBufRHandler(void);
static void spiRegBufWHandler(void);
static void spiRegBufWRHandler(void);

void spiInit(void)
{
	/* MOSI pin configuration */
	DDRB |= ex(2);
	/* SCK pin configuration */
	DDRB |= ex(1);
	/* SS pin configuration */
	DDRB |= ex(0);
	/* 1 MHz */
	/* CPOL = 0, CPHA = 0 */
	/* MSB first */
	SPCR = 0xD1;
	spiRdy = OSSemCreate(0);
}

INT8U spiBufR(uint8 *buf, uint16 size, uint8 fill)
{
	INT8U err;

	spiRxBuf = buf;
	spiSize = size;
	spiCnt = 0;
	spiFill = fill;
	spiHandlerPtr = spiBufRHandler;
	SPDR = fill;
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	return err;
}

INT8U spiBufW(uint8 *buf, uint16 size)
{
	INT8U err;

	spiTxBuf = buf;
	spiSize = size;
	spiCnt = 1;
	spiHandlerPtr = spiBufWHandler;
	SPDR = buf[0];
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	return err;
}

INT8U spiBufRw(uint8 *rxBuf, uint8 *txBuf, uint16 size)
{
	INT8U err;

	spiRxBuf = rxBuf;
	spiTxBuf = txBuf;
	spiSize = size;
	spiCnt = 0;
	spiHandlerPtr = spiBufRwHandler;
	SPDR = txBuf[0];
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	return err;
}

INT8U spiRegBufR(uint8 reg, uint8 *firstByte, uint8 *buf, uint16 size, uint8 fill)
{
	INT8U err;

	spiRxBuf = buf;
	spiSize = size;
	spiCnt = 0xFFFF;
	spiFill = fill;
	spiHandlerPtr = spiRegBufRHandler;
	SPDR = reg;
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	*firstByte = spiFirstByte;
	return err;
}

INT8U spiRegBufW(uint8 reg, uint8 *firstByte, uint8 *buf, uint16 size)
{
	INT8U err;

	spiTxBuf = buf;
	spiSize = size;
	spiCnt = 0xFFFF;
	spiHandlerPtr = spiRegBufWHandler;
	SPDR = reg;
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	*firstByte = spiFirstByte;
	return err;
}

INT8U spiRegBufWR(uint8 reg, uint8 *firstByte, uint8 *txBuf, uint8 *rxBuf, uint16 size)
{
	INT8U err;

	spiTxBuf = txBuf;
	spiRxBuf = rxBuf;
	spiSize = size;
	spiCnt = 0xFFFF;
	spiHandlerPtr = spiRegBufWRHandler;
	SPDR = reg;
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	*firstByte = spiFirstByte;
	return err;
}

/* 250 kHz*/
void spiClockSlow(void)
{
	SPCR &= 0xFC;
	SPCR |= 0x02;
}

/* 1 MHz */
void spiClockFast(void)
{
	SPCR &= 0xFC;
	SPCR |= 0x01;
}

static void spiBufRHandler(void)
{
	spiRxBuf[spiCnt] = SPDR;
	spiCnt++;
	if (spiCnt < spiSize) {
		SPDR = spiFill;
	} else {
		OSIntEnter();
		OSSemPost(spiRdy);
		OSIntExit();
	}
}

static void spiBufWHandler(void)
{
	if (spiCnt < spiSize) {
		SPDR = spiTxBuf[spiCnt];
		spiCnt++;
	} else {
		OSIntEnter();
		OSSemPost(spiRdy);
		OSIntExit();
	}
}

static void spiBufRwHandler(void)
{
	spiRxBuf[spiCnt] = SPDR;
	spiCnt++;
	if (spiCnt < spiSize) {
		SPDR = spiTxBuf[spiCnt];
	} else {
		OSIntEnter();
		OSSemPost(spiRdy);
		OSIntExit();
	}
}

static void spiRegBufRHandler(void)
{
	if (spiCnt == 0xFF) {
		spiFirstByte = SPDR;
		SPDR = spiFill;
		spiCnt = 0;
	} else {
		spiRxBuf[spiCnt] = SPDR;
		spiCnt++;
		if (spiCnt < spiSize) {
			SPDR = spiFill;
		} else {
			OSIntEnter();
			OSSemPost(spiRdy);
			OSIntExit();
		}
	}
}

static void spiRegBufWHandler(void)
{
	if (spiCnt == 0xFF) {
		spiFirstByte = SPDR;
		SPDR = spiTxBuf[0];
		spiCnt = 1;
	} else {
		if (spiCnt < spiSize) {
			SPDR = spiTxBuf[spiCnt];
			spiCnt++;
		} else {
			OSIntEnter();
			OSSemPost(spiRdy);
			OSIntExit();
		}
	}
}

static void spiRegBufWRHandler(void)
{
	if (spiCnt == 0xFF) {
		spiFirstByte = SPDR;
		SPDR = spiTxBuf[0];
		spiCnt = 0;
	} else {
		spiRxBuf[spiCnt] = SPDR;
		spiCnt++;
		if (spiCnt < spiSize) {
			SPDR = spiTxBuf[spiCnt];
		} else {
			OSIntEnter();
			OSSemPost(spiRdy);
			OSIntExit();
		}
	}
}

ISR(SPI_STC_vect)
{
	(*spiHandlerPtr)();
}
