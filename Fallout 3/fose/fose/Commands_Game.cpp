#include "Commands_Game.h"
#include "GameTypes.h"
#include "GameAPI.h"
#include "Hooks_Gameplay.h"
#include "GameSettings.h"
#include "GameData.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "Hooks_SaveLoad.h"
#include <set>
#include "GameInterface.h"

bool Cmd_GetNumericGameSetting_Execute(COMMAND_ARGS)
{
	char settingName[512] = { 0 };
	*result = -1;

	if (ExtractArgs(EXTRACT_ARGS, &settingName))
	{
		Setting* setting;
		GameSettingCollection* gmsts = GameSettingCollection::GetSingleton();
		if (gmsts && gmsts->GetGameSetting(settingName, &setting))
		{
			double val;
			if (setting->Get(val))
			{
				*result = val;
				if (IsConsoleMode())
					Console_Print("GetNumericGameSetting >> %g", *result);
			}
		}
		else if (IsConsoleMode())
			Console_Print("GetNumericGameSetting >> SETTING NOT FOUND");
	}

	return true;
}

bool Cmd_SetNumericGameSetting_Execute(COMMAND_ARGS)
{
	char settingName[512] = { 0 };
	float newVal = 0;
	*result = 0;

	if (ExtractArgs(EXTRACT_ARGS, &settingName, &newVal))
	{
		Setting* setting;
		GameSettingCollection* gmsts = GameSettingCollection::GetSingleton();
		if (gmsts && gmsts->GetGameSetting(settingName, &setting))
		{
			if (setting->Set(newVal))
				*result = 1;
		}
		else if (IsConsoleMode())
			Console_Print("SetNumericGameSetting >> NOT FOUND");
	}

	return true;
}

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
Cmd_Execute Cmd_AddSpell_Execute = (Cmd_Execute)0x00539480;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
Cmd_Execute Cmd_AddSpell_Execute = (Cmd_Execute)0x0053C1F0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
Cmd_Execute Cmd_AddSpell_Execute = (Cmd_Execute)0x0053BC80;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
Cmd_Execute Cmd_AddSpell_Execute = (Cmd_Execute)0x0053C1F0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
Cmd_Execute Cmd_AddSpell_Execute = (Cmd_Execute)0x0053C530;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
Cmd_Execute Cmd_AddSpell_Execute = (Cmd_Execute)0x0053BAC0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
Cmd_Execute Cmd_AddSpell_Execute = (Cmd_Execute)0x0053BCB0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
Cmd_Execute Cmd_AddSpell_Execute = (Cmd_Execute)0x0053C360;

#else
#error unsupported version of fallout
#endif

bool Cmd_AddSpellNS_Execute(COMMAND_ARGS)
{
	return RunCommand_NS(PASS_COMMAND_ARGS, Cmd_AddSpell_Execute);
}

bool Cmd_GetNumericIniSetting_Execute(COMMAND_ARGS)
{
	char settingName[512] = { 0 };
	*result = -1;

	if (ExtractArgs(EXTRACT_ARGS, &settingName))
	{
		Setting* setting;
		if (GetIniSetting(settingName, &setting))
		{
			double val;
			if (setting->Get(val))
			{
				*result = val;
				if (IsConsoleMode())
					Console_Print("GetNumericIniSetting >> %g", *result);
			}
		}
		else if (IsConsoleMode())
			Console_Print("GetNumericIniSetting >> SETTING NOT FOUND");
	}

	return true;
}

bool Cmd_SetNumericIniSetting_Execute(COMMAND_ARGS)
{
	char settingName[512] = { 0 };
	float newVal = 0;
	*result = 0;

	if (ExtractArgs(EXTRACT_ARGS, &settingName, &newVal))
	{
		Setting* setting;
		if (GetIniSetting(settingName, &setting))
		{
			if (setting->Set(newVal))
				*result = 1;
		}
		else if (IsConsoleMode())
			Console_Print("SetNumericIniSetting >> NOT FOUND");
	}

	return true;
}

bool Cmd_IsModLoaded_Execute(COMMAND_ARGS)
{
	char modName[512];
	*result = 0;

	if (!ExtractArgs(EXTRACT_ARGS, &modName))
		return true;

	const ModInfo* pModInfo = DataHandler::Get()->LookupModByName(modName);
	if (pModInfo && pModInfo->IsLoaded()) {
		*result = 1;
	}
	if (IsConsoleMode())
	{
		if (*result)
			Console_Print("Mod Loaded");
		else
			Console_Print("Mod not loaded");
	}

	return true;
}

bool Cmd_GetModIndex_Execute(COMMAND_ARGS)
{
	char modName[512];
	if (!ExtractArgs(EXTRACT_ARGS, &modName))
		return true;

	UInt32 modIndex = (*g_dataHandler)->GetModIndex(modName);
	*result = modIndex;
	if (IsConsoleMode())
		Console_Print("Mod Index: %02X", modIndex);

	return true;
}

bool Cmd_GetNumLoadedMods_Execute(COMMAND_ARGS)
{
	*result = (*g_dataHandler)->GetActiveModCount();
	return true;
}

bool Cmd_GetSourceModIndex_Execute(COMMAND_ARGS)
{
	TESForm* form = NULL;
	*result = -1;

	if (!ExtractArgsEx(paramInfo, scriptData, opcodeOffsetPtr, scriptObj, eventList, &form))
		return true;

	if (!form)
		form = thisObj;
	
	if (form)
	{
		if (form->IsCloned())
			*result = 0xFF;
		else
			*result = (UInt8)(form->refID >> 24);
	}

	return true;
}

bool Cmd_GetCrosshairRef_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	InterfaceManager* intfc = InterfaceManager::GetSingleton();
	if (intfc && intfc->crosshairRef)
		*refResult = intfc->crosshairRef->refID;

	if (IsConsoleMode())
		Console_Print("GetCrosshairRef >> %08x", *refResult);

	return true;
}
		
bool Cmd_GetGameLoaded_Execute(COMMAND_ARGS)
{
	static std::set<UInt32>	informedScripts;

	*result = 0;

	// was a game loaded?
	if(g_gameLoaded)
	{
		// yes, clear the list of scripts we've informed and reset the 'game loaded' flag
		informedScripts.clear();

		g_gameLoaded = false;
	}

	if(scriptObj)
	{
		// have we returned 'true' to this script yet?
		if(informedScripts.find(scriptObj->refID) == informedScripts.end())
		{
			// no, return true and add to the set
			*result = 1;

			informedScripts.insert(scriptObj->refID);
		}
		if (IsConsoleMode())
			Console_Print("GetGameLoaded >> %.0f", *result);
	}

	return true;
}

bool Cmd_GetGameRestarted_Execute(COMMAND_ARGS)
{
	static std::set<UInt32> regScripts;

	*result = 0;

	if (scriptObj && (regScripts.find(scriptObj->refID) == regScripts.end()))
	{
		*result = 1;
		regScripts.insert(scriptObj->refID);
	}
	
	return true;
}
