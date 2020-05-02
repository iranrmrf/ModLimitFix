#pragma once

#include <chrono>

#define F(fmt, ...)	_FATALERROR ("%s " fmt, GetTime(), ## __VA_ARGS__)
#define E(fmt, ...)	_ERROR		("%s " fmt, GetTime(), ## __VA_ARGS__)
#define W(fmt, ...) _WARNING	("%s " fmt, GetTime(), ## __VA_ARGS__)
#define M(fmt, ...) _MESSAGE	("%s " fmt, GetTime(), ## __VA_ARGS__)
#define V(fmt, ...) _VMESSAGE	("%s " fmt, GetTime(), ## __VA_ARGS__)
#define D(fmt, ...) _DMESSAGE	("%s " fmt, GetTime(), ## __VA_ARGS__)

char* GetTime()
{
	static char msgBuff[32];
	time_t timet;
	time(&timet);
	tm tmt;
	localtime_s(&tmt, &timet);
	strftime(msgBuff, sizeof(msgBuff), "%d%H%M%S", &tmt);
	return msgBuff;
}
