#include "Commands_Script.h"

#include "GameAPI.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameRTTI.h"

enum EScriptMode {
	eScript_HasScript,
	eScript_Get,
	eScript_Remove,
};

static bool GetScript_Execute(COMMAND_ARGS, EScriptMode eMode)
{
	*result = 0;
	TESForm* form = 0;

	ExtractArgsEx(EXTRACT_ARGS_EX, &form);
	form = form->TryGetREFRParent();
	if (!form) {
		if (!thisObj) return true;
		form = thisObj->baseForm;
	}

	TESScriptableForm* scriptForm = DYNAMIC_CAST(form, TESForm, TESScriptableForm);
	Script* script = (scriptForm) ? scriptForm->script : NULL;

	switch(eMode) {
		case eScript_HasScript: {
			*result = (script != NULL) ? 1 : 0;
			break;
		}
		case eScript_Get: {
			if (script) {
				UInt32* refResult = (UInt32*)result;
				*refResult = script->refID;
			}
			break;
		}
		case eScript_Remove: {
			// simply forget about the script
			if (script) {
				UInt32* refResult = (UInt32*)result;
				*refResult = scriptForm->script->refID;
			}
			if (scriptForm)
				scriptForm->script = NULL;
			break;
		}
	}
	return true;
}

bool Cmd_IsScripted_Execute(COMMAND_ARGS)
{
	return GetScript_Execute(PASS_COMMAND_ARGS, eScript_HasScript);
}

bool Cmd_GetScript_Execute(COMMAND_ARGS)
{
	return GetScript_Execute(PASS_COMMAND_ARGS, eScript_Get);
}

bool Cmd_RemoveScript_Execute(COMMAND_ARGS)
{
	return GetScript_Execute(PASS_COMMAND_ARGS, eScript_Remove);
}

bool Cmd_SetScript_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32* refResult = (UInt32*)result;

	TESForm* form = NULL;
	TESForm* scriptArg = NULL;

	ExtractArgsEx(EXTRACT_ARGS_EX, &scriptArg, &form);
	form = form->TryGetREFRParent();
	if (!form) {
		if (!thisObj) return true;
		form = thisObj->baseForm;
	}

	TESScriptableForm* scriptForm = DYNAMIC_CAST(form, TESForm, TESScriptableForm);
	if (!scriptForm) return true;

	Script* script = DYNAMIC_CAST(scriptArg, TESForm, Script);
	if (!script) return true;

	// we can't get a magic script here or an unknown script here
	if (script->IsMagicScript() || script->IsUnkScript()) return true;


	if ((script->IsQuestScript() && form->typeID == kFormType_Quest) || script->IsObjectScript()) {
		if (scriptForm->script) {
			*refResult = scriptForm->script->refID;
			// clean up event list here?
		}
		scriptForm->script = script;
		// clean up event list here?
	}

	return true;
}

bool Cmd_IsFormValid_Execute(COMMAND_ARGS)
{
	TESForm* pForm = NULL;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (!thisObj) return true;
			pForm = thisObj->baseForm;
		}
		if (pForm) {
			*result = 1;
		}
		if (IsConsoleMode())
			Console_Print(*result == 1.0 ? "Valid Form!" : "Invalid Form");
	}
	return true;
}

bool Cmd_IsReference_Execute(COMMAND_ARGS)
{
	TESObjectREFR* refr = NULL;
	*result = 0;
	if (ExtractArgs(EXTRACT_ARGS, &refr))
		*result = 1;
	if (IsConsoleMode())
		Console_Print(*result == 1.0 ? "IsReference" : "Not reference!");

	return true;
}
