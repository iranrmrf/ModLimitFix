#include "fose_common/SafeWrite.h"
#include "Hooks_Script.h"
#include "GameTypes.h"

#if RUNTIME

#include "GameForms.h"
#include "GameData.h"

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	static const UInt32 kLookupFormByEditorIDPatchAddr = 0x00454654;
	static const UInt32 kLookupFormByEditorIDRetnAddr = 0x00454659;
	// bool BSCaseInsensitiveStringMap::Lookup(char*, data**) <- stdcall (callee cleans stack)
	static const UInt32 kStringMapLookupCallAddr = _NiTMap_Lookup;

	static const UInt32 kCommentDelimiterContinueAddr = 0x00517D14;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x00517D71;
	static const UInt32 kCommentDelimiterRetnAddr = 0x00517D7E;
	static const UInt32 kCommentDelimiterPatchAddr = 0x00517D60;

	static const UInt32 kExecuteScriptLinePatchAddr = 0x0053D9F0;
	static const UInt32 kExecuteScriptLineRetnAddr = 0x0053D9F6;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	static const UInt32 kLookupFormByEditorIDPatchAddr = 0x004555C4;
	static const UInt32 kLookupFormByEditorIDRetnAddr = 0x004555C9;
	// bool BSCaseInsensitiveStringMap::Lookup(char*, data**) <- stdcall (callee cleans stack)
	static const UInt32 kStringMapLookupCallAddr = _NiTMap_Lookup;

	static const UInt32 kCommentDelimiterContinueAddr = 0x0051A684;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x0051A6E1;
	static const UInt32 kCommentDelimiterRetnAddr = 0x0051A6EE;
	static const UInt32 kCommentDelimiterPatchAddr = 0x0051A6D0;

	static const UInt32 kExecuteScriptLinePatchAddr = 0x005407B0;
	static const UInt32 kExecuteScriptLineRetnAddr = 0x005407B6;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	static const UInt32 kLookupFormByEditorIDPatchAddr = 0x00455144;
	static const UInt32 kLookupFormByEditorIDRetnAddr = 0x00455149;
	// bool BSCaseInsensitiveStringMap::Lookup(char*, data**) <- stdcall (callee cleans stack)
	static const UInt32 kStringMapLookupCallAddr = _NiTMap_Lookup;

	static const UInt32 kCommentDelimiterContinueAddr = 0x0051A0E4;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x0051A141;
	static const UInt32 kCommentDelimiterRetnAddr = 0x0051A14E;
	static const UInt32 kCommentDelimiterPatchAddr = 0x0051A130;

	static const UInt32 kExecuteScriptLinePatchAddr = 0x00540250;
	static const UInt32 kExecuteScriptLineRetnAddr = 0x00540256;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	static const UInt32 kLookupFormByEditorIDPatchAddr = 0x004553A4;
	static const UInt32 kLookupFormByEditorIDRetnAddr = 0x004553A9;
	// bool BSCaseInsensitiveStringMap::Lookup(char*, data**) <- stdcall (callee cleans stack)
	static const UInt32 kStringMapLookupCallAddr = _NiTMap_Lookup;

	static const UInt32 kCommentDelimiterContinueAddr = 0x0051A5F4;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x0051A651;
	static const UInt32 kCommentDelimiterRetnAddr = 0x0051A65E;
	static const UInt32 kCommentDelimiterPatchAddr = 0x0051A640;

	static const UInt32 kExecuteScriptLinePatchAddr = 0x00540760;
	static const UInt32 kExecuteScriptLineRetnAddr = 0x00540766;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	static const UInt32 kLookupFormByEditorIDPatchAddr = 0x00455244;
	static const UInt32 kLookupFormByEditorIDRetnAddr = 0x00455249;
	// bool BSCaseInsensitiveStringMap::Lookup(char*, data**) <- stdcall (callee cleans stack)
	static const UInt32 kStringMapLookupCallAddr = _NiTMap_Lookup;

	static const UInt32 kCommentDelimiterContinueAddr = 0x0051A854;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x0051A8B1;
	static const UInt32 kCommentDelimiterRetnAddr = 0x0051A8BE;
	static const UInt32 kCommentDelimiterPatchAddr = 0x0051A8A0;

	static const UInt32 kExecuteScriptLinePatchAddr = 0x00540AF0;
	static const UInt32 kExecuteScriptLineRetnAddr = 0x00540AF6;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	static const UInt32 kLookupFormByEditorIDPatchAddr = 0x00455114;
	static const UInt32 kLookupFormByEditorIDRetnAddr = 0x00455119;
	// bool BSCaseInsensitiveStringMap::Lookup(char*, data**) <- stdcall (callee cleans stack)
	static const UInt32 kStringMapLookupCallAddr = _NiTMap_Lookup;

	static const UInt32 kCommentDelimiterContinueAddr = 0x00519E24;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x00519E81;
	static const UInt32 kCommentDelimiterRetnAddr = 0x00519E8E;
	static const UInt32 kCommentDelimiterPatchAddr = 0x00519E70;

	static const UInt32 kExecuteScriptLinePatchAddr = 0x00540080;
	static const UInt32 kExecuteScriptLineRetnAddr = 0x00540086;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	static const UInt32 kLookupFormByEditorIDPatchAddr = 0x004551E4;
	static const UInt32 kLookupFormByEditorIDRetnAddr = 0x004551E9;
	// bool BSCaseInsensitiveStringMap::Lookup(char*, data**) <- stdcall (callee cleans stack)
	static const UInt32 kStringMapLookupCallAddr = _NiTMap_Lookup;

	static const UInt32 kCommentDelimiterContinueAddr = 0x00519FE4;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x0051A041;
	static const UInt32 kCommentDelimiterRetnAddr = 0x0051A04E;
	static const UInt32 kCommentDelimiterPatchAddr = 0x0051A030;

	static const UInt32 kExecuteScriptLinePatchAddr = 0x00540270;
	static const UInt32 kExecuteScriptLineRetnAddr = 0x00540276;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	static const UInt32 kLookupFormByEditorIDPatchAddr = 0x004552C4;
	static const UInt32 kLookupFormByEditorIDRetnAddr = 0x004552C9;
	// bool BSCaseInsensitiveStringMap::Lookup(char*, data**) <- stdcall (callee cleans stack)
	static const UInt32 kStringMapLookupCallAddr = _NiTMap_Lookup;

	static const UInt32 kCommentDelimiterContinueAddr = 0x0051A614;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x0051A671;
	static const UInt32 kCommentDelimiterRetnAddr = 0x0051A67E;
	static const UInt32 kCommentDelimiterPatchAddr = 0x0051A660;

	static const UInt32 kExecuteScriptLinePatchAddr = 0x00540920;
	static const UInt32 kExecuteScriptLineRetnAddr = 0x00540926;
#else
#error unsupported fallout version
#endif

#else	// GECK

#if CS_VERSION == CS_VERSION_1_1_36
	static const UInt32 kCommentDelimiterContinueAddr = 0x005BEE44;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x005BEEA1;
	static const UInt32 kCommentDelimiterRetnAddr = 0x005BEE9F;
	static const UInt32 kCommentDelimiterPatchAddr = 0x005BEE90;
#elif CS_VERSION == CS_VERSION_1_5_19
	static const UInt32 kCommentDelimiterContinueAddr = 0x005BF1D4;
	static const UInt32 kCommentDelimiterLineFeedAddr = 0x005BF231;
	static const UInt32 kCommentDelimiterRetnAddr = 0x005BF22F;
	static const UInt32 kCommentDelimiterPatchAddr = 0x005BF220;
#else
#error unsupported cs version
#endif

#endif

#if RUNTIME

// currently only looks for quests
// not certain if other forms which retain editorID at run-time need handling as well
static bool __stdcall LookupFormByEditorID(const char* editorID, TESForm** outForm)
{
	DataHandler* dhand = DataHandler::Get();
	if (dhand)
	{
		TESQuest* quest = dhand->GetQuestByName(editorID);
		if (quest)
		{
			*outForm = quest;
			return true;
		}
	}

	return false;
}

// the script parser attempts to look up forms by editorID in a BSCaseInsensitiveStringMap<TESForm>
// which is mostly empty at run-time; however editorIDs for some forms not in map are still available at run-time
// make the parser look elsewhere for those forms
// Main intent is to allow specifying quests by editorID in the console
static __declspec(naked) void LookupFormByEditorIDHook(void)
{
	static char* editorID;
	static TESForm** outForm;

	__asm {
		// grab the args
		pop editorID
		pop outForm

		push outForm
		push editorID
		call	[kStringMapLookupCallAddr]
		test	al, al
		jnz		Done

		// not found in stringmap so check elsewhere
		push outForm
		push editorID
		call	LookupFormByEditorID

	Done:
		jmp [kLookupFormByEditorIDRetnAddr]
	}
}

UInt32* g_ScriptDataBytes = NULL;

static __declspec(naked) void ExecuteScriptLineHook(void)
{
	__asm {
		// grab the 4th arg to ScriptRunner::ExecuteLine()
		mov		eax,	[esp+0x10]
		mov		g_ScriptDataBytes, eax

		// overwritten code
		push	ebp
		mov		ebp, esp
		and		esp, 0xFFFFFFC0
		
		// done
		jmp		[kExecuteScriptLineRetnAddr]
	}
}

#endif

static bool DoParseCommentDelimiterHook(const char* scriptText, UInt32 scriptOffset)
{
	UInt32 numQuotes = 0;
	for (UInt32 i = 0; i < scriptOffset - 1; i++)
	{
		if (scriptText[i] == '"')
			numQuotes++;
	}

	// odd # of quotes means we're inside a string literal
	if (numQuotes / 2.0 == numQuotes / 2)
		return false;
	else
		return true;
}

// script compiler treats any semicolon as a comment delimiter, even if it appears
// inside a string literal.
// problematic for SetUIString, where some trait names/values must contain semicolons
// This hooks the code run when a semicolon is encountered in script text or console input
static void __declspec(naked) ParseCommentDelimiterHook(void)
{
	// on entry:
	// -ebp = scriptText
	// -edi = offset of character following semicolon
	static char* scriptText;
	static UInt32 scriptOffset;

	__asm {
		mov	[scriptText],	ebp
		mov	[scriptOffset],	edi
		pushad
	}

	DoParseCommentDelimiterHook(scriptText, scriptOffset);	// returns true if semicolon within string literal

	__asm {
		test	al,	al
		jz		SkipComment

		// semicolon appears within string literal so accept it and continue parsing line
		popad
		jmp	[kCommentDelimiterContinueAddr]

	SkipComment:
		// semicolon is a comment delimiter so skip rest of line
		popad

		// hook overwrites this loop
	LoopStart:
		cmp	bl,	0x0A
		jz	LineFeed
		mov	bl, [edi+ebp]
		add	edi,	1
		test bl, bl
		jnz LoopStart

		jmp	[kCommentDelimiterRetnAddr]

	LineFeed:
		jmp	[kCommentDelimiterLineFeedAddr]
	}
}

void Hook_Script_Init()
{
#if RUNTIME
	WriteRelJump(kLookupFormByEditorIDPatchAddr, (UInt32)&LookupFormByEditorIDHook);
	WriteRelJump(kExecuteScriptLinePatchAddr, (UInt32)&ExecuteScriptLineHook);
#endif
	// below is used by both GECK and game
	WriteRelJump(kCommentDelimiterPatchAddr, (UInt32)&ParseCommentDelimiterHook);
}
