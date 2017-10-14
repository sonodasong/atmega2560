#ifndef __UTIL_H__
#define __UTIL_H__

#include "define.h"

void enablePullup(void);
void disablePullup(void);
void strClr(char *buf, uint8 size);
uint8 strCpy(char *src, char *dst, uint8 size);
void ledInit(void);
void ledOn(void);
void ledOff(void);
void probeInit(void);
void probeOn(void);
void probeOff(void);

#endif
