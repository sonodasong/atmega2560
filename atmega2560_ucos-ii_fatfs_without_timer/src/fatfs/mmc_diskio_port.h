#ifndef __MMC_DISKIO_PORT_H__
#define __MMC_DISKIO_PORT_H__

#include <library.h>
#include "diskio.h"

#define CS_LOW()					PORTG &= rex(5)
#define CS_HIGH()					PORTG |= ex(5)
#define MMC_CD()					TRUE
#define MMC_WP()					FALSE
#define FCLK_SLOW()					spiClockSlow()
#define FCLK_FAST()					spiClockFast()
#define rcvr_spi_multi(p, cnt)		spiBufR(p, cnt, 0xFF)
#define xmit_spi_multi(p, cnt);		spiBufW((uint8 *)p, cnt)

void power_on(void);
void power_off(void);
BYTE xchg_spi(BYTE dat);

#endif
