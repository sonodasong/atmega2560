#include "mmc_diskio_port.h"

void power_on(void)
{
	/* enable pull-up resistor for MISO */
	PORTB |= ex(3);

	/* CS pin configuration */
	CS_HIGH();
	DDRG |= ex(5);

	OSTimeDly(100 / (1000 /OS_TICKS_PER_SEC));
}

void power_off(void)
{
}

BYTE xchg_spi(BYTE dat)
{
	spiBufWR(&dat, &dat, 1);
	return dat;
}
