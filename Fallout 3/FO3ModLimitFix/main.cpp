#include <Windows.h>

#include "fose/GameAPI.h"
#include "fose/PluginAPI.h"
#include "fose_common/SafeWrite.h"

#include <hooks.h>
#include <log.h>
#include <offsets.h>
#include <settings.h>

extern "C"
{
	BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
	{
		switch (dwReason)
		{
		case DLL_PROCESS_ATTACH:
			settings.hnd = (HMODULE)hDllHandle;
			break;
		default:
			break;
		}
		return TRUE;
	}

	bool FOSEPlugin_Query(const FOSEInterface *fose, PluginInfo * info)
	{
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Mod Limit Fix";
		info->version = 2.1;

		if (fose->isEditor)
		{
			return false;
		}

		gLog.Open("mod_limit_fix.log");

		if (fose->foseVersion < FOSE_VERSION_INTEGER)
		{
			_FATALERROR("FOSE version is too low, please use the latest version of FOSE.");
			return false;
		}

		return true;
	}

	bool FOSEPlugin_Load(const FOSEInterface *fose)
	{
		InitSettings();

		gLog.SetLogLevel(IDebugLog::kLevel_Message);

		if (settings.bVerboseLog)
		{
			gLog.SetLogLevel(IDebugLog::kLevel_VerboseMessage);
		}

		if (settings.bDebugLog)
		{
			gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);
		}

		MESSAGE("Initializing mod limit fix...");

		VMESSAGE("Old file handle buffer located at: %#.8x", oldAddy);

		newAddy = (DWORD)f_calloc_crt(settings.iMaxHnd, 4);
		if (!newAddy)
		{	
			FATALERROR("Failed to calloc for new file handle buffer.");
			return false; 
		}
		VMESSAGE("New file handle buffer located at: %#.8x", newAddy);

		stack = createstack(settings.iMaxHnd - 20);
		if (!stack)
		{
			FATALERROR("Failed to allocate filestream stack.");
			return false;
		}
		VMESSAGE("Free filestream stack located at: %#.8x", stack);

		f_lock(1);

		memcpy((void*)newAddy, (void*)oldAddy, 0x50);
		SafeWrite32(maxAddy, settings.iMaxHnd);
		SafeWrite32(filePtr, newAddy);

		f_unlock(1);

		VMESSAGE("Freeing old file handle buffer at: %#.8x", oldAddy);

		f_free((void*)oldAddy);

		VMESSAGE("Hooking _getstream and _fclose functions...");

		Hook((void*)getstreamAddy, &f_getstream, 0x130);
		Hook((void*)fcloseAddy, &f_fclose, 0x7C);

		for (int i = settings.iMaxHnd - 1; i > 19; i--)
		{
			spush(stack, (CFILE**)(newAddy + 4 * i));
		}
		VMESSAGE("Stack contains: %d filestreams.", stack->top + 1);

		stack->dbg = settings.bDebugLog;

		MESSAGE("Mod limit fix has been successfully applied. Enjoy the new mod limit!");

		return true;
	}
};
