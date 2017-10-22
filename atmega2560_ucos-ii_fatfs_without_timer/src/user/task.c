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

#define BUFF_SIZE		16

void fatfsTask(void *pdata)
{
	FATFS FatFs;
	FIL fil;
	char line[BUFF_SIZE];
	UINT rc, i;
	char *str;

	(void)pdata;
	f_mount(&FatFs, "", 0);
	while (1) {
		strClr(line, BUFF_SIZE);
		f_open(&fil, "test.txt", FA_READ);
		f_read(&fil, line, BUFF_SIZE - 1, &rc);
		f_close(&fil);
		line[rc] = '\0';
		usart0Printf("%s\r\n", line);
		usart0Read(&str);
		i = strCpy(str, line, BUFF_SIZE - 1);
		if (i < rc) {
			i = rc;
		}
		f_open(&fil, "test.txt", FA_WRITE);
		f_write(&fil, line, i, &rc);
		f_close(&fil);
	}
}
