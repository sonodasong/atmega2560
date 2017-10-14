#include "util.h"

void enablePullup(void)
{
	MCUCR &= rex(PUD);
}

void disablePullup(void)
{
	MCUCR |= ex(PUD);
}

void strClr(char *buf, uint8 size)
{
	while (size != 0) {
		buf[size - 1] = '\0';
		size--;
	}
}

uint8 strCpy(char *src, char *dst, uint8 size)
{
	uint8 i;

	i = 0;
	while (src[i] != '\0' && i < size) {
		dst[i] = src[i];
		i++;
	}
	return i;
}

void ledInit(void)
{
	DDRB |= ex(7);
}

void ledOn(void)
{
	PORTB |= ex(7);
}

void ledOff(void)
{
	PORTB &= rex(7);
}

void probeInit(void)
{
	DDRC |= ex(1);
}

void probeOn(void)
{
	PORTC |= ex(1);
}

void probeOff(void)
{
	PORTC &= rex(1);
}
