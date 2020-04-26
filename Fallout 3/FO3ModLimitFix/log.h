#pragma once

#include <chrono>

#define FATALERROR(fmt, ...) _FATALERROR ("[%s] " fmt, GetTime(), ## __VA_ARGS__)
#define ERROR(fmt, ...)	_ERROR ("[%s] " fmt, GetTime(), ## __VA_ARGS__)
#define WARNING(fmt, ...) _WARNING ("[%s] " fmt, GetTime(), ## __VA_ARGS__)
#define MESSAGE(fmt, ...) _MESSAGE ("[%s] " fmt, GetTime(), ## __VA_ARGS__)
#define VMESSAGE(fmt, ...) _VMESSAGE ("[%s] " fmt, GetTime(), ## __VA_ARGS__)
#define DMESSAGE(fmt, ...) _DMESSAGE ("[%s] " fmt, GetTime(), ## __VA_ARGS__)

char* GetTime()
{
	static char msgBuff[64];
	time_t timet;
	time(&timet);
	strftime(msgBuff, sizeof(msgBuff), "%Y-%m-%d %H:%M:%S", localtime(&timet));
	return msgBuff;
}
