#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "definitions.h"

#define EXPORT __declspec(dllexport)

#define EXPAND(x) x

#define STRINGIFY(x) #x
#define STRING(x) STRINGIFY(x)

#define MLF_PREPEND_EXTENDER(f) EXPAND(MLF_EXTENDER_NAME)##f

struct Interface { DWORD extenderVersion; DWORD runtimeVersion; DWORD editorVersion; DWORD isEditor; };
struct PluginInfo { enum { kInfoVersion = 1 }; DWORD infoVersion; const char* name; DWORD version; };

BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
{
	return TRUE;
}

EXPORT bool MLF_PREPEND_EXTENDER(Plugin_Query)(const Interface* interface, PluginInfo* info)
{
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = STRING(MLF_GAME) " Mod Limit Fix";
	info->version = 3.0;
	return !interface->isEditor;
}

EXPORT bool MLF_PREPEND_EXTENDER(Plugin_Load)(const Interface* interface)
{
	int new_nstream = 2048;
	int& nstream = MLF_N_STREAM;
	void**& piob = MLF_PIOB;
	MLF_LOCK(1);
	void** newpiob = (void**)MLF_RECALLOC_CRT(piob, new_nstream, sizeof(void*));
	for (int i = nstream; i < new_nstream; i++) { newpiob[i] = nullptr; }
	nstream = new_nstream;
	piob = newpiob;
	MLF_UNLOCK(1);
	return true;
}
