#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "fose/PluginAPI.h"
#include "fose_common/SafeWrite.h"

#include <hooks.h>
#include <log.h>
#include <settings.h>

extern "C"
{
	BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
	{
		if (dwReason == DLL_PROCESS_ATTACH)	{ settings.hnd = (HMODULE)hDllHandle; }
		if (dwReason == DLL_PROCESS_DETACH) { DeleteCriticalSection(&filenameCS); DeleteCriticalSection(&logCS); }
		return TRUE;
	}

	bool FOSEPlugin_Query(const FOSEInterface* fose, PluginInfo* info)
	{
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Mod Limit Fix";
		info->version = 2.7;

		InitializeCriticalSection(&filenameCS);
		InitializeCriticalSection(&logCS);
		gLog.Open("mod_limit_fix.log");

		V("DLL loaded at %p", settings.hnd);

		if (fose->isEditor)
		{
			F("Editor is running. Mod limit fix will not be applied.");
			return false;
		}

		M("FOSE version %.2f detected", (fose->foseVersion >> 24) +
			(((fose->foseVersion >> 16) & 0xFF) * 0.1) +
			(((fose->foseVersion & 0xFF) >> 4) * 0.01));

		if (fose->foseVersion < 0x01020020)
		{
			F("FOSE version is too low, please use v1.22.");
			return false;
		}
		return true;
	}

	bool FOSEPlugin_Load(const FOSEInterface* fose)
	{
		M("Initializing mod limit fix...");

		V("Initializing settings...");
		InitSettings();
		if (settings.bDebug)	{ gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage); }

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

		V("Hooking _getstream, _fclose and _openfile...");

		PatchJump(getstreamAddy, &f_getstream);
		PatchJump(fcloseAddy, &f_fclose);
		PatchCall(openfileAddy, &f_openfile_w);

		V("Filling stack...");
		CFILE** addy = newAddy + settings.iMaxHnd - 1;
		while (addy >= newAddy + 20)
		{
			spush(stack, addy--);
		}
		V("Stack contains: %d filestreams.", stack->top + 1);

		f_unlock(1);

		stack->dbg = settings.bDebug;

		M("Mod limit fix has been successfully applied. Enjoy the new mod limit!");

		return true;
	}
};
