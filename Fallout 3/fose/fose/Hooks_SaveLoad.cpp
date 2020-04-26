#include "fose_common/SafeWrite.h"
#include "Hooks_SaveLoad.h"
#include "Serialization.h"

bool g_gameLoaded = false;
static const char* LoadGameMessage = "---Finished loading game: %s";
static const char* SaveGameMessage = "---Finished saving game: %s";

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	static const UInt32 kLoadGamePatchAddr = 0x006CDB83;
	static const UInt32 kLoadGameRetnAddr = 0x006CDB88;

	static const UInt32 kSaveGamePatchAddr =	0x006CB6F3;		// push SaveGameMessage
	static const UInt32 kSaveGameRetnAddr =		0x006CB6F8;

	static const UInt32 kNewGamePatchAddr =		0x0067E277;		// overwrite nullsub(void) call
	static const UInt32 kDeleteGamePatchAddr =	0x006D16CC;		// DeleteFile() call	
	static const UInt32 kRenameGamePatchAddr =	0x006DB9C1;		// call to rename()
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	static const UInt32 kLoadGamePatchAddr =	0x006D1A43;
	static const UInt32 kLoadGameRetnAddr =		0x006D1A48;

	static const UInt32 kSaveGamePatchAddr =	0x006CF5B3;		// push SaveGameMessage
	static const UInt32 kSaveGameRetnAddr =		0x006CF5B8;

	static const UInt32 kNewGamePatchAddr =		0x006816D7;		// overwrite nullsub(void) call
	static const UInt32 kDeleteGamePatchAddr =	0x006D54FC;		// DeleteFile() call	
	static const UInt32 kRenameGamePatchAddr =	0x006DF821;		// call to rename()
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	static const UInt32 kLoadGamePatchAddr =	0x006D1773;
	static const UInt32 kLoadGameRetnAddr =		0x006D1778;

	static const UInt32 kSaveGamePatchAddr =	0x006CF2E3;		// push SaveGameMessage
	static const UInt32 kSaveGameRetnAddr =		0x006CF2E8;

	static const UInt32 kNewGamePatchAddr =		0x006815F7;		// overwrite nullsub(void) call
	static const UInt32 kDeleteGamePatchAddr =	0x006D522C;		// DeleteFile() call	
	static const UInt32 kRenameGamePatchAddr =	0x006DF721;		// call to rename()
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	static const UInt32 kLoadGamePatchAddr =	0x006D20F3;
	static const UInt32 kLoadGameRetnAddr =		0x006D20F8;

	static const UInt32 kSaveGamePatchAddr =	0x006CFC63;		// push SaveGameMessage
	static const UInt32 kSaveGameRetnAddr =		0x006CFC68;

	static const UInt32 kNewGamePatchAddr =		0x00681E47;		// overwrite nullsub(void) call
	static const UInt32 kDeleteGamePatchAddr =	0x006D5B8C;		// DeleteFile() call	
	static const UInt32 kRenameGamePatchAddr =	0x006DFE91;		// call to rename()
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	static const UInt32 kLoadGamePatchAddr =	0x006D197A;
	static const UInt32 kLoadGameRetnAddr =		0x006D197F;

	static const UInt32 kSaveGamePatchAddr =	0x006CF4B3;		// push SaveGameMessage
	static const UInt32 kSaveGameRetnAddr =		0x006CF4B8;

	static const UInt32 kNewGamePatchAddr =		0x00681497;		// overwrite nullsub(void) call
	static const UInt32 kDeleteGamePatchAddr =	0x006D54CC;		// DeleteFile() call	
	static const UInt32 kRenameGamePatchAddr =	0x006DF7D1;		// call to rename()
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	static const UInt32 kLoadGamePatchAddr =	0x006D110A;
	static const UInt32 kLoadGameRetnAddr =		0x006D110F;

	static const UInt32 kSaveGamePatchAddr =	0x006CEC43;		// push SaveGameMessage
	static const UInt32 kSaveGameRetnAddr =		0x006CEC48;

	static const UInt32 kNewGamePatchAddr =		0x00680E57;		// overwrite nullsub(void) call
	static const UInt32 kDeleteGamePatchAddr =	0x006D4BCC;		// DeleteFile() call	
	static const UInt32 kRenameGamePatchAddr =	0x006DEEA1;		// call to rename()
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	static const UInt32 kLoadGamePatchAddr =	0x006D103A;
	static const UInt32 kLoadGameRetnAddr =		0x006D103F;

	static const UInt32 kSaveGamePatchAddr =	0x006CEB73;		// push SaveGameMessage
	static const UInt32 kSaveGameRetnAddr =		0x006CEB78;

	static const UInt32 kNewGamePatchAddr =		0x00680DE7;		// overwrite nullsub(void) call
	static const UInt32 kDeleteGamePatchAddr =	0x006D4AFC;		// DeleteFile() call	
	static const UInt32 kRenameGamePatchAddr =	0x006DEDD1;		// call to rename()
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	static const UInt32 kLoadGamePatchAddr =	0x006D113A;
	static const UInt32 kLoadGameRetnAddr =		0x006D113F;

	static const UInt32 kSaveGamePatchAddr =	0x006CEC73;		// push SaveGameMessage
	static const UInt32 kSaveGameRetnAddr =		0x006CEC78;

	static const UInt32 kNewGamePatchAddr =		0x00680E17;		// overwrite nullsub(void) call
	static const UInt32 kDeleteGamePatchAddr =	0x006D4BFC;		// DeleteFile() call	
	static const UInt32 kRenameGamePatchAddr =	0x006DEF91;		// call to rename()
#else
#error unsupported fallout version
#endif

static void __stdcall DoLoadGameHook(const char* saveFilePath)
{
	g_gameLoaded = true;

	_MESSAGE("DoLoadGameHook: %s", saveFilePath);
	Serialization::HandleLoadGame(saveFilePath);
}

static __declspec(naked) void LoadGameHook(void)
{
	__asm
	{
		pushad
		push		eax				// filepath for savegame
		call		DoLoadGameHook
		popad

		// overwritten code
		push		offset	LoadGameMessage
		jmp			[kLoadGameRetnAddr]
	}
}

static void __stdcall DoSaveGameHook(const char* saveFilePath)
{
	_MESSAGE("DoSaveGameHook: %s", saveFilePath);
	Serialization::HandleSaveGame(saveFilePath);
}

static __declspec(naked) void SaveGameHook(void)
{
	__asm
	{
		pushad
		push		ecx				// filepath for savegame
		call		DoSaveGameHook
		popad

		// overwritten code
		push		offset	SaveGameMessage
		jmp			[kSaveGameRetnAddr]
	}
}

static void NewGameHook(void)
{
	_MESSAGE("NewGameHook");

	Serialization::HandleNewGame();
}

static void __stdcall DeleteGameHook(const char * path)
{
	_MESSAGE("DeleteGameHook: %s", path);

	Serialization::HandleDeleteGame(path);

	DeleteFile(path);
}

static void RenameGameHook(const char * oldPath, const char * newPath)
{
	_MESSAGE("RenameGameHook: %s -> %s", oldPath, newPath);

	Serialization::HandleRenameGame(oldPath, newPath);

	rename(oldPath, newPath);
}

void Hook_SaveLoad_Init(void)
{
	WriteRelJump(kLoadGamePatchAddr, (UInt32)&LoadGameHook);

#if _DEBUG		// this stuff waits for v0002
	WriteRelJump(kSaveGamePatchAddr, (UInt32)&SaveGameHook);
	WriteRelCall(kNewGamePatchAddr, (UInt32)&NewGameHook);
	WriteRelCall(kDeleteGamePatchAddr, (UInt32)&DeleteGameHook);
	SafeWrite8(kDeleteGamePatchAddr + 5, 0x90);		// nop out leftover byte from original instruction
	WriteRelCall(kRenameGamePatchAddr, (UInt32)&RenameGameHook);
#endif

}
