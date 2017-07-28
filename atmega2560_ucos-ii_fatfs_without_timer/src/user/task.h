#ifndef __TASK_H__
#define __TASK_H__

#include <library.h>
#include <ff.h>

void blink(void *pdata);
void serial(void *pdata);
void fatfsTask(void *pdata);
void fatfsTask1(void *pdata);
void fatfsTimerTask(void *pdata);

#endif
