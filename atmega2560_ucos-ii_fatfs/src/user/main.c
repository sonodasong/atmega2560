#include "user.h"

static OS_STK stack0[4096];
static OS_STK stack1[128];
static OS_STK stack2[128];

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
	//probeInit();

	OSTaskCreate(fatfsTask1, (void *)0, &stack2[4095], 0);
	OSTaskCreate(fatfsTimerTask, (void *)0, &stack1[127], 1);
	OSTaskCreate(blink, (void *)0, &stack0[127], 2);

	OSStart();

	return 0;
}
