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

void fatfsTask(void *pdata)
{
	FATFS FatFs;
	FIL fil;
	char line[100];

	(void)pdata;
	f_mount(&FatFs, "", 0);
	f_open(&fil, "test.txt", FA_READ);
	while (f_gets(line, sizeof line, &fil)) {
		usart0Print(line);
	}
	f_close(&fil);
	while (1) {
		OSTimeDly(250);
	}
}

#define BUFF_SIZE		16

void fatfsTask1(void *pdata)
{
	FATFS FatFs;
	FIL fil;
	char line[BUFF_SIZE];
	UINT rc, i;
	char *str;

	(void)pdata;
	f_mount(&FatFs, "", 0);
	while (1) {
		f_open(&fil, "test.txt", FA_READ | FA_WRITE);
		strBufClr(line, BUFF_SIZE);
		f_read(&fil, line, BUFF_SIZE - 1, &rc);
		line[rc] = '\0';
		usart0Printf("%s\r\n", line);
		usart0Read(&str);
		i = strCpy(str, line, BUFF_SIZE - 1);
		if (i < rc) {
			i = rc;
		}
		f_lseek(&fil, 0);
		f_write(&fil, line, i, &rc);
		f_close(&fil);
	}
}

extern void disk_timerproc (void);

void fatfsTimerTask(void *pdata)
{
	(void)pdata;
	while (1) {
		disk_timerproc();
		OSTimeDly(1);
	}
}
