#include "CommandTable.h"
#include "GameAPI.h"
#include "Hooks_Gameplay.h"
#include "fose_common\SafeWrite.h"
#include "GameInterface.h"
#include "PluginAPI.h"
#include "PluginManager.h"

void ToggleUIMessages(bool bEnable)
{
	// Disable: write an immediate return at function entry
	// Enable: restore the push instruction at function entry
	SafeWrite8((UInt32)QueueUIMessage, bEnable ? 0x6A : 0xC3);
}

bool RunCommand_NS(COMMAND_ARGS, Cmd_Execute cmd)
{
	ToggleUIMessages(false);
	bool cmdResult = cmd(PASS_COMMAND_ARGS);
	ToggleUIMessages(true);

	return cmdResult;
}

#if FALLOUT_VERSION == FALLOUT_VERSION_1_7
	static const UInt32 kMainMenuFromIngameMenuPatchAddr = 0x006799C4;	// 4th reference to g_osGlobals after RaceSexMenu_func0008
	static const UInt32 kMainMenuFromIngameMenuRetnAddr	 = 0x00433A30;	// original call

	static const UInt32 kExitGameViaQQQPatchAddr		 = 0x0051ED15;	// Inside Cmd_QuitGame_Execute, call ConsolePrintF
	static const UInt32 kExitGameViaQQQRetnAddr			 = 0x006195D0;	// original call

	static const UInt32 kExitGameFromMenuPatchAddr       = 0x0067B06B;	// Sets the proper bit in OsGlobals, to be confirmed
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	static const UInt32 kMainMenuFromIngameMenuPatchAddr = 0x00679AF4;	// 4th reference to g_osGlobals after RaceSexMenu_func0008
	static const UInt32 kMainMenuFromIngameMenuRetnAddr	 = 0x00433A20;	// original call

	static const UInt32 kExitGameViaQQQPatchAddr		 = 0x0051F345;	// Inside Cmd_QuitGame_Execute, call ConsolePrintF
	static const UInt32 kExitGameViaQQQRetnAddr			 = 0x006196B0;	// original call

	static const UInt32 kExitGameFromMenuPatchAddr       = 0x0067B19B;
#else
#error
#endif

static enum QuitGameMessage
{
	kQuit_ToMainMenu,
	kQuit_ToWindows,
	kQuit_QQQ,
};

void __stdcall SendQuitGameMessage(QuitGameMessage msg)
{
	UInt32 msgToSend = FOSEMessagingInterface::kMessage_ExitGame;
	if (msg == kQuit_ToMainMenu)
		msgToSend = FOSEMessagingInterface::kMessage_ExitToMainMenu;
	else if (msg == kQuit_QQQ)
		msgToSend = FOSEMessagingInterface::kMessage_ExitGame_Console;

	PluginManager::Dispatch_Message(0, msgToSend, NULL, 0, NULL);
}

static __declspec(naked) void ExitGameFromMenuHook(void)
{
	__asm {
		pushad

		push	kQuit_ToWindows
		call	SendQuitGameMessage

		popad
		mov byte ptr [ eax + 1], 1
		retn
	}
}

static __declspec(naked) void ExitGameViaQQQHook(void)
{
	__asm {
		pushad

		push	kQuit_QQQ
		call	SendQuitGameMessage

		popad
		jmp		[kExitGameViaQQQRetnAddr]
	}
}

static __declspec(naked) void MainMenuFromIngameMenuHook(void)
{
	__asm {
		pushad

		push	kQuit_ToMainMenu
		call	SendQuitGameMessage

		popad
		jmp		[kMainMenuFromIngameMenuRetnAddr]
	}
}

void Hook_Gameplay_Init()
{
	// patch enchanted item check for saving cloned forms
	// conveniently the code and hence the patch are almost identical to that in Oblivion

	// inconveniently, the patched code is never called - Fallout doesn't bother saving the created
	// base objects. Given the code path is intact we may be able to hook it back up to
	// make it work
#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	SafeWrite8(0x006D9F7D, 0x20);
	WriteRelJump(0x006DA06F, 0x006DA102);
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	SafeWrite8(0x006DDD8D, 0x20);				// unknown
	WriteRelJump(0x006DDE7F, 0x006DDF12);
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	SafeWrite8(0x006DDCDD, 0x20);				// unknown
	WriteRelJump(0x006DDDCF, 0x006DDE62);
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	SafeWrite8(0x006DE42D, 0x20);				// unknown
	WriteRelJump(0x006DE51F, 0x006DE5B2);
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	SafeWrite8(0x006DDD2D, 0x20);				// unknown
	WriteRelJump(0x006DDE1F, 0x006DDEB2);
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	SafeWrite8(0x006DD45D, 0x20);				// unknown
	WriteRelJump(0x006DD54F, 0x006DD5E2);
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	SafeWrite8(0x006DD35D, 0x20);				// unknown
	WriteRelJump(0x006DD44F, 0x006DD4E2);
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	SafeWrite8(0x006DD52D, 0x20);				// unknown
	WriteRelJump(0x006DD61F, 0x006DD6B2);
#else
#error unsupported fallout version
#endif

	// hook exit to main menu or to windows
	WriteRelCall(kMainMenuFromIngameMenuPatchAddr, (UInt32)&MainMenuFromIngameMenuHook);
	WriteRelCall(kExitGameViaQQQPatchAddr, (UInt32)&ExitGameViaQQQHook);
	WriteRelCall(kExitGameFromMenuPatchAddr, (UInt32)&ExitGameFromMenuHook);

}
