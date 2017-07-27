#include "util.h"

void enablePullup(void)
{
	MCUCR &= rex(PUD);
}

void disablePullup(void)
{
	MCUCR |= ex(PUD);
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
