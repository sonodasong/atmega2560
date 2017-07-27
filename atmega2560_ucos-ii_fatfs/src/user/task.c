#include "task.h"

void blink(void *pdata)
{
	(void)pdata;
	while (1) {
		ledOn();
		OSTimeDly(1);
		ledOff();
		OSTimeDly(29);
		ledOn();
		OSTimeDly(1);
		ledOff();
		OSTimeDly(219);
	}
}

void serial(void *pdata)
{
	char *str;

	(void)pdata;
	while (1) {
		usart0Read(&str);
		usart0Print(str);
	}
}

extern void disk_timerproc (void);

void fatfsTask(void *pdata)
{
	FATFS FatFs;
	/* File object */
	FIL fil;
	/* Line buffer */
	char line[100];
	/* FatFs return code */
	FRESULT fr;

	(void)pdata;

	/* Register work area to the default drive */
	fr = f_mount(&FatFs, "", 0);
	//usart0Hex8(fr);

	/* Open a text file */
	fr = f_open(&fil, "test.txt", FA_READ);

	/* Read all lines and display it */
	while (f_gets(line, sizeof line, &fil)) {
		ledOn();
		usart0Print(line);
	}
	f_close(&fil);
	while (1) {
		OSTimeDly(250);
	}
}

void fatfsTimerTask(void *pdata)
{
	(void)pdata;
	while (1) {
		disk_timerproc();
		OSTimeDly(2);
	}
}
