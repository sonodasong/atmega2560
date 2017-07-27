#include "mmc_diskio_port.h"

void power_on(void)
{
	/* enable pull-up resistor for MISO */
	PORTB |= ex(3);
	/* CS pin configuration */
	PORTG |= ex(5);
	DDRG |= ex(5);
}

void power_off(void)
{
	/* disable pull-up resistor for MISO */
	PORTB &= rex(3);
	/* restore CS pin configuration */
	DDRG &= rex(5);
	PORTG &= rex(5);
}

BYTE xchg_spi(BYTE dat)
{
	spiBufWR(&dat, &dat, 1);
	return dat;
}

/*
int wait_ready(UINT wt)
{
	BYTE d;

	wt = wt / (1000 / OS_TICKS_PER_SEC);
	do {
		d = xchg_spi(0xFF);
		OSTimeDly(1);
		wt--;
	} while (d != 0xFF && wt);
	return (d == 0xFF) ? 1 : 0;
}

int rcvr_datablock(BYTE *buff, UINT btr)
{
	BYTE token;
	UINT wt;

	wt = 200 / (1000 / OS_TICKS_PER_SEC);
	do {
		token = xchg_spi(0xFF);
		OSTimeDly(1);
		wt--;
	} while ((token == 0xFF) && wt);
	if (token != 0xFE) return 0;
	rcvr_spi_multi(buff, btr);
	xchg_spi(0xFF);
	xchg_spi(0xFF);
	return 1;
}
*/
