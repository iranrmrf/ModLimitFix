#include "fose.h"
#include "CommandTable.h"
#include "Hooks_DirectInput8Create.h"
#include "Hooks_Gameplay.h"
#include "Hooks_SaveLoad.h"
#include "Hooks_Script.h"
#include "Core_Serialization.h"
#include "Utilities.h"

#ifdef NOGORE
IDebugLog	gLog("fose_ng.log");
#else
IDebugLog	gLog("fose.log");
#endif

UInt32 logLevel = IDebugLog::kLevel_Message;

UInt32 waitForDebugger;
UInt32 createHookWindow;
UInt32 et;

void WaitForDebugger(void)
{
	_MESSAGE("Waiting for debugger");
	while(!IsDebuggerPresent())
	{
		Sleep(10);
	}

	Sleep(1000 * 2);
}

extern "C" {

void FOSE_Initialize(void)
{
#ifndef _DEBUG
	__try {
#endif

		FILETIME	now;
		GetSystemTimeAsFileTime(&now);

		_MESSAGE("FOSE runtime: initialize (version = %d.%d.%d %08X %08X%08X)",
			FOSE_VERSION_INTEGER, FOSE_VERSION_INTEGER_MINOR, FOSE_VERSION_INTEGER_BETA, FALLOUT_VERSION,
			now.dwHighDateTime, now.dwLowDateTime);
		_MESSAGE("imagebase = %08X", GetModuleHandle(NULL));

#ifdef _DEBUG
		logLevel = IDebugLog::kLevel_DebugMessage;
		if (GetFOSEConfigOption_UInt32("DEBUG", "LogLevel", &logLevel) && logLevel)
			if (logLevel>IDebugLog::kLevel_DebugMessage)
				logLevel = IDebugLog::kLevel_DebugMessage;
		SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
		if (GetFOSEConfigOption_UInt32("RUNTIME DEBUG", "WaitForDebugger", &waitForDebugger) && waitForDebugger)
			WaitForDebugger();

#else
		if (GetFOSEConfigOption_UInt32("RELEASE", "LogLevel", &logLevel) && logLevel)
			if (logLevel>IDebugLog::kLevel_DebugMessage)
				logLevel = IDebugLog::kLevel_DebugMessage;
#endif
		gLog.SetLogLevel((IDebugLog::LogLevel)logLevel);

		MersenneTwister::init_genrand(GetTickCount());
		CommandTable::Init();

		Hook_DirectInput8Create_Init();
		Hook_Gameplay_Init();
		Hook_SaveLoad_Init();
		Hook_Script_Init();

#if _DEBUG
		// waits for v0002
		// ### can't be enabled without initing the plugin mgr
//		Init_CoreSerialization_Callbacks();
#endif

		FlushInstructionCache(GetCurrentProcess(), NULL, 0);

#ifndef _DEBUG
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		_ERROR("exception");
	}
#endif

	_MESSAGE("init complete");
}

void FOSE_DeInitialize(void)
{
	_MESSAGE("FOSE: deinitialize");
}

};
