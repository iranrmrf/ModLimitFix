#include "fose_editor.h"
#include "fose/CommandTable.h"
#include "fose/Hooks_Script.h"

IDebugLog	gLog("fose_editor.log");

extern "C"
{

void FOSE_Initialize(void)
{
	__try
	{
		_MESSAGE("FOSE editor: initialize (version = %d.%d.%d %08X)", FOSE_VERSION_INTEGER, FOSE_VERSION_INTEGER_MINOR, FOSE_VERSION_INTEGER_BETA, CS_VERSION);

#if 0
		while(!IsDebuggerPresent())
		{
			Sleep(10);
		}

		Sleep(1000 * 5);
#endif

		CommandTable::Init();
		Hook_Script_Init();
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		_ERROR("exception");
	}
}

void FOSE_DeInitialize(void)
{
	_MESSAGE("FOSE editor: deinitialize");
}

};
