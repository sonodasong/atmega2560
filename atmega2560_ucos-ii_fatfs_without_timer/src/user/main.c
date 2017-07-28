#include "user.h"

static OS_STK stack0[1536];
static OS_STK stack1[128];

static void tickInit(void)
{
	TCNT1 = 0;
	OCR1A = 249;
	OCR1B = 0;
	TCCR1A = 0x00;
	TCCR1B = 0x0C;
	TCCR1C = 0x00;
	TIFR1 = ex(OCF1A);
	TIMSK1 = ex(OCIE1A);
}

static void disableWiznet(void) {
	PORTB |= ex(4);
	DDRB |= ex(4);
}

int main(void)
{
	cli();
	tickInit();
	disableWiznet();

	OSInit();

	enablePullup();
	spiInit();
	usart0Init();

	ledInit();

	/* minimun stack size roughly 1280 */
	OSTaskCreate(fatfsTask, (void *)0, &stack0[1535], 0);
	OSTaskCreate(blink, (void *)0, &stack1[127], 1);

	OSStart();

	return 0;
}
