#include "fose_editor.h"
#include <Windows.h>

BOOL WINAPI DllMain(
        HANDLE  hDllHandle,
        DWORD   dwReason,
        LPVOID  lpreserved
        )
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
			FOSE_Initialize();
			break;

		case DLL_PROCESS_DETACH:
			FOSE_DeInitialize();
			break;
	};

	return TRUE;
}
