#pragma once

#include <chrono>

#include <types.h>

CRITICAL_SECTION logCS;

#define LOG( func, fmt, ... ) CS(func(fmt, __VA_ARGS__), &logCS)

#define F( fmt, ... ) LOG( _FATALERROR,	"%s " fmt, GetTime(), __VA_ARGS__ )
#define E( fmt, ... ) LOG( _ERROR,		"%s " fmt, GetTime(), __VA_ARGS__ )
#define W( fmt, ... ) LOG( _WARNING,	"%s " fmt, GetTime(), __VA_ARGS__ )
#define M( fmt, ... ) LOG( _MESSAGE,	"%s " fmt, GetTime(), __VA_ARGS__ )
#define V( fmt, ... ) LOG( _VMESSAGE,	"%s " fmt, GetTime(), __VA_ARGS__ )
#define D( fmt, ... ) LOG( _DMESSAGE,	"%s " fmt, GetTime(), __VA_ARGS__ )

char* GetTime()
{
	static char buff[9];
	time_t timet;
	time(&timet);
	tm tmt;
	localtime_s(&tmt, &timet);
	strftime(buff, 9, "%d%H%M%S", &tmt);
	return buff;
}
