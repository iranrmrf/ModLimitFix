#include <Windows.h>

#include "nvse/PluginAPI.h"
#include "nvse/SafeWrite.h"

#include <settings.h>
#include <hooks.h>

DWORD WINAPI StackDebug(LPVOID param)
{
	while (1)
	{
		Sleep(2000);
		Console_Print(
			"Stack allocated at: %#.8x | "
			"Contains: %d filestreams | "
			"Percentage remaining: %.2f%",
			stack, stack->top + 1, (float)(stack->top + 1) / stack->size * 100.0
			);
	}
}

void MessageHandler(NVSEMessagingInterface::Message* msg)
{
	switch (msg->type)
	{
	case NVSEMessagingInterface::kMessage_PostLoadGame:
		ResumeThread(settings.dbg);
		break;
	default:
		break;
	}
}

extern "C"
{
	BOOL WINAPI DllMain(
		HANDLE  hDllHandle,
		DWORD   dwReason,
		LPVOID  lpreserved
		)
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

	bool NVSEPlugin_Query(const NVSEInterface * nvse, PluginInfo * info)
	{
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Mod Limit Fix";
		info->version = 2.0;

		if (nvse->isEditor)
		{
			return false;
		}

		gLog.Open("mod_limit_fix.log");

		if (nvse->nvseVersion < NVSE_VERSION_INTEGER)
		{
			_FATALERROR("NVSE version is too low, please use the latest version of NVSE.");
			return false;
		}

		return true;
	}

	bool NVSEPlugin_Load(const NVSEInterface * nvse)
	{
		NVSEMessagingInterface* msgInt = (NVSEMessagingInterface*)nvse->QueryInterface(kInterface_Messaging);
		msgInt->RegisterListener(nvse->GetPluginHandle(), "NVSE", MessageHandler);

		InitSettings();

		gLog.SetLogLevel(IDebugLog::kLevel_Message);

		if (settings.bVerboseLog)
		{
			gLog.SetLogLevel(IDebugLog::kLevel_VerboseMessage);
		}

		_MESSAGE("Initializing mod limit fix...");

		_VMESSAGE("Old file handle buffer located at: %#.8x", oldAddy);

		newAddy = (DWORD)f_calloc_crt(settings.iMaxHnd, 4);
		if (!newAddy)
		{	
			_FATALERROR("Failed to calloc for new file handle buffer.");
			return false; 
		}
		_VMESSAGE("New file handle buffer located at: %#.8x", newAddy);

		stack = createstack(settings.iMaxHnd - 20);
		if (!stack)
		{
			_VMESSAGE("Failed to allocate filestream stack.");
			return false;
		}
		_VMESSAGE("Free filestream stack located at: %#.8x", stack);

		f_lock(1);

		memcpy((void*)newAddy, (void*)oldAddy, 0x50);
		SafeWrite32(maxAddy, settings.iMaxHnd);
		SafeWrite32(filePtr, newAddy);

		f_unlock(1);

		_VMESSAGE("Freeing old file handle buffer at: %#.8x", oldAddy);

		f_free((void*)oldAddy);

		_VMESSAGE("Hooking _getstream and _fclose functions...");

		CreateHook((void*)0x00ED8501, &f_getstream, 0x138);
		CreateHook((void*)0x00EC9907, &f_fclose, 0x7C);

		for (int i = settings.iMaxHnd - 1; i > 19; i--)
		{
			spush(stack, (CFILE**)(newAddy + 4 * i));
		}
		_VMESSAGE("Stack contains: %d filestreams.", stack->top + 1);

		if (settings.bDebug)
		{
			if (settings.dbg = CreateThread(NULL, NULL, StackDebug, NULL, CREATE_SUSPENDED, NULL))
			{
				_VMESSAGE("Successfully started stack debug thread.");
			}
			else
			{
				_VMESSAGE("Failed to start stack debug thread.");
			}
		}

		_MESSAGE("Mod limit fix has been successfully applied. Enjoy the new mod limit!");

		return true;
	}
};
