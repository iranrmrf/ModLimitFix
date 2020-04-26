#include "Commands_UI.h"
#include "GameInterface.h"
#include "GameAPI.h"

static const float fErrorReturnValue = -999;

static enum eUICmdAction {
	kGetFloat,
	kSetFloat,
	kSetString,
	kSetFormattedString,
};

bool GetSetUIValue_Execute(COMMAND_ARGS, eUICmdAction action)
{
	char component[kMaxMessageLength] = { 0 };
	float newFloat;
	char newStr[kMaxMessageLength] = { 0 };
	*result = 0;

	bool bExtracted = false;
	switch (action)
	{
	case kGetFloat:
		bExtracted = ExtractArgs(EXTRACT_ARGS, &component);
		break;
	case kSetFloat:
		bExtracted = ExtractArgs(EXTRACT_ARGS, &component, &newFloat);
		break;
	case kSetString:
		bExtracted = ExtractArgs(EXTRACT_ARGS, &component, &newStr);
		break;
	case kSetFormattedString:
		bExtracted = ExtractFormatStringArgs(1, newStr, paramInfo, scriptData, opcodeOffsetPtr, scriptObj, eventList, kCommandInfo_SetUIStringEx.numParams, &component);
		break;
	default:
		DEBUG_PRINT("Error: Invalid action in GetSetUIValue_Execute()");
		return true;
	}

	if (bExtracted)
	{
		Tile::Value* val = InterfaceManager::GetMenuComponentValue(component);
		if (val)
		{
			switch (action)
			{
			case kGetFloat:
				*result = val->num;
				if (IsConsoleMode())
					Console_Print("GetUIFloat >> %.4f", *result);
				break;
			case kSetFloat:
				CALL_MEMBER_FN(val->parent, SetFloatValue)(val->id, newFloat, true);
				break;
			case kSetString:
			case kSetFormattedString:
				CALL_MEMBER_FN(val->parent, SetStringValue)(val->id, newStr, true);
				break;
			}
		}
		else		// trait not found
		{
			if (action == kGetFloat)
				*result = fErrorReturnValue;

			if (IsConsoleMode())
				Console_Print("Trait not found");
		}
	}

	return true;
}

bool Cmd_GetUIFloat_Execute(COMMAND_ARGS)
{
	return GetSetUIValue_Execute(PASS_COMMAND_ARGS, kGetFloat);
}

bool Cmd_SetUIFloat_Execute(COMMAND_ARGS)
{
	return GetSetUIValue_Execute(PASS_COMMAND_ARGS, kSetFloat);
}

bool Cmd_SetUIString_Execute(COMMAND_ARGS)
{
	return GetSetUIValue_Execute(PASS_COMMAND_ARGS, kSetString);
}

bool Cmd_SetUIStringEx_Execute(COMMAND_ARGS)
{
	return GetSetUIValue_Execute(PASS_COMMAND_ARGS, kSetFormattedString);
}

bool Cmd_PrintActiveTile_Execute(COMMAND_ARGS)
{
	InterfaceManager* intfc = InterfaceManager::GetSingleton();
	if (intfc && intfc->activeTile)
	{
		std::string name = intfc->activeTile->GetQualifiedName();
		if (name.length() < 0x200)
			Console_Print("%s", name.c_str());
		else
		{
			Console_Print("Name too long to print in console, sending to fose.log");
			_MESSAGE("%s", name.c_str());
		}
	}
	else
		Console_Print("Could not read active tile");

	return true;
}
