#include <Windows.h>

#include "nvse/PluginAPI.h"
#include "nvse/SafeWrite.h"

#include <hooks.h>
#include <log.h>
#include <settings.h>

extern "C"
{
	BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
	{
		if (dwReason == DLL_PROCESS_ATTACH)	{ settings.hnd = (HMODULE)hDllHandle; }
		return TRUE;
	}

	bool NVSEPlugin_Query(const NVSEInterface * nvse, PluginInfo * info)
	{
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Mod Limit Fix";
		info->version = 2.5;

		gLog.Open("mod_limit_fix.log");

		if (nvse->isEditor)
		{
			F("Editor is running. Mod limit fix will not be applied.");
			return false;
		}
		
		M("NVSE version %.2f detected", (nvse->nvseVersion >> 24) +
			(((nvse->nvseVersion >> 16) & 0xFF) * 0.1) +
			(((nvse->nvseVersion & 0xFF) >> 4) * 0.01));

		if (nvse->nvseVersion < 0x05010040)
		{
			F("NVSE version is too low, please use v5.14.");
			return false;
		}
		return true;
	}

	bool NVSEPlugin_Load(const NVSEInterface * nvse)
	{
		M("Initializing mod limit fix...");

		V("Initializing settings...");
		InitSettings();
		if (settings.bDebugLog)	{ gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage); }

		V("Initializing offsets...");
		InitOffsets();

		CFILE** oldAddy = *filePtr;
		V("Old buffer array: %p", oldAddy);

		CFILE** newAddy = (CFILE**)f_calloc_crt(settings.iMaxHnd, 4);
		if (!newAddy)
		{	
			F("Failed to calloc for new buffer array.");
			return false; 
		}
		V("New buffer array: %p", newAddy);

		stack = createstack(settings.iMaxHnd - 20);
		if (!stack)
		{
			F("Failed to allocate handle stack.");
			return false;
		}
		V("New buffer stack: %p", stack);

		f_lock(1);

		V("Copying old handles...");
		memcpy((void*)newAddy, (void*)oldAddy, 0x50);
		SafeWrite32((DWORD)maxAddy, settings.iMaxHnd);
		SafeWrite32((DWORD)filePtr, (DWORD)newAddy);

		V("Freeing old buffer array");

		f_free((void*)oldAddy);

		V("Hooking _getstream and _fclose...");

		Hook((void*)getstreamAddy, &f_getstream, 0x138);
		Hook((void*)fcloseAddy, &f_fclose, 0x7C);

		V("Filling stack...");
		CFILE** addy = newAddy + settings.iMaxHnd - 1;
		while (addy >= newAddy + 20)
		{
			spush(stack, addy--);
		}
		V("Stack contains: %d filestreams.", stack->top + 1);

		f_unlock(1);

		stack->dbg = settings.bDebugLog;

		M("Mod limit fix has been successfully applied. Enjoy the new mod limit!");

		return true;
	}
};
