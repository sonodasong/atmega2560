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

#define TEXT_BUFF_SIZE		16
#define IMAGE_BUFF_SIZE		1024

static uint8 buf[IMAGE_BUFF_SIZE];

void fatfsTask(void *pdata)
{
	FATFS FatFs;
	FIL fil;
	UINT rc, i;
	char *str;

	(void)pdata;
	f_mount(&FatFs, "", 0);
	while (1) {
		strClr((char *)buf, TEXT_BUFF_SIZE);
		f_open(&fil, "test.txt", FA_READ);
		f_read(&fil, buf, TEXT_BUFF_SIZE - 1, &rc);
		f_close(&fil);
		buf[rc] = '\0';
		usart0Printf("%s\r\n", buf);
		usart0Read(&str);
		i = strCpy(str, (char *)buf, TEXT_BUFF_SIZE - 1);
		if (i < rc) {
			i = rc;
		}
		f_open(&fil, "test.txt", FA_WRITE);
		f_write(&fil, buf, i, &rc);
		f_close(&fil);
		f_open(&fil, "demo.bmp", FA_READ);
		f_read(&fil, buf, IMAGE_BUFF_SIZE, &rc);
		f_close(&fil);
		usart0Printf("demo.bmp read: %d / %d\r\n", rc, IMAGE_BUFF_SIZE);
	}
}

void fatfsTimerTask(void *pdata)
{
	extern void disk_timerproc(void);

	(void)pdata;
	while (1) {
		disk_timerproc();
		OSTimeDly(1);
	}
}
