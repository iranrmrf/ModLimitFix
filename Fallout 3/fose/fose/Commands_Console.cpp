#include "Commands_Console.h"

#include "GameForms.h"

bool Cmd_PrintToConsole_Execute(COMMAND_ARGS)
{
	*result = 0;
	char buffer[kMaxMessageLength];

	if (ExtractFormatStringArgs(0, buffer, paramInfo, scriptData, opcodeOffsetPtr, scriptObj, eventList, 21))
	{
		if (strlen(buffer) < 512)
		{
			*result = 1;
			Console_Print("%s", buffer);
		}
		else
			Console_Print("PrintToConsole >> Max length exceeded (512 chars)");
	}

	return true;
}

static Bitfield<UInt32> ModDebugStates[8];

bool Cmd_SetDebugMode_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 bEnableDebug = 0;
	UInt32 modIndexArg = 0xFFFF;

	if (!ExtractArgs(EXTRACT_ARGS, &bEnableDebug, &modIndexArg))
		return true;

	UInt8 modIndex = modIndexArg;
	if (modIndexArg == 0xFFFF)
		modIndex = scriptObj->GetModIndex();

	if (modIndex > 0 && modIndex < 0xFF)
	{
		UInt8 modBit = modIndex % 32;			//which bit to toggle
		UInt8 arrIdx = modIndex / 32;			//index into bitfield array
		if (bEnableDebug)
			ModDebugStates[arrIdx].Set(1 << modBit);
		else
			ModDebugStates[arrIdx].UnSet(1 << modBit);

		if (IsConsoleMode())
			Console_Print("Debug statements toggled %s for mod %02X", (bEnableDebug ? "on" : "off"), modIndex);
	}						

	return true;
}

bool Cmd_DebugPrint_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt8 modIndex = scriptObj->GetModIndex();
	UInt8 modBit = modIndex % 32;
	modIndex /= 32;

	if (ModDebugStates[modIndex].IsSet(1 << modBit))
		Cmd_PrintToConsole_Execute(PASS_COMMAND_ARGS);

	return true;
}

bool Cmd_GetDebugMode_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 modIndexArg = 0xFFFF;

	if (!ExtractArgs(EXTRACT_ARGS, &modIndexArg))
		return true;

	UInt8 modIndex = modIndexArg;
	if (modIndexArg == 0xFFFF)
		modIndex = scriptObj->GetModIndex();

	UInt8 modBit = modIndex % 32;
	modIndex /= 32;

	if (ModDebugStates[modIndex].IsSet(1 << modBit)) {
		*result = 1;
	}

	return true;
}
