#include "Commands_List.h"
#include "GameForms.h"
#include "GameRTTI.h"
#include "GameObjects.h"

bool Cmd_ListGetCount_Execute(COMMAND_ARGS)
{
	*result = 0;
	BGSListForm* pListForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &pListForm)) {
		if (pListForm) {
			*result = pListForm->Count();
#if _DEBUG
			Console_Print("count: %d", pListForm->Count());
#endif
		}
	}
	return true;
}

bool Cmd_ListGetNthForm_Execute(COMMAND_ARGS)
{
	*result = 0;
	BGSListForm* pListForm = NULL;
	UInt32 n = 0;
	if (ExtractArgs(EXTRACT_ARGS, &pListForm, &n)) {
		if (pListForm) {
			TESForm* pForm = pListForm->GetNthForm(n);
			if (pForm) {
				*((UInt32 *)result) = pForm->refID;
#if _DEBUG
				TESFullName* listName = DYNAMIC_CAST(pListForm, BGSListForm, TESFullName);
				TESFullName* formName = DYNAMIC_CAST(pForm, TESForm, TESFullName);

				Console_Print("%s item %d: %X %s", listName ? listName->name.m_data : "unknown list", n, pForm->refID, formName ? formName->name.m_data : "unknown item");
#endif
			}
		}
	}
	return true;
}

bool Cmd_ListAddForm_Execute(COMMAND_ARGS)
{
	*result = eListInvalid;
	BGSListForm* pListForm = NULL;
	TESForm* pForm = NULL;
	UInt32 n = eListEnd;

	ExtractArgsEx(EXTRACT_ARGS_EX, &pListForm, &pForm, &n);
	if (pListForm && pForm) {
		UInt32 index = pListForm->AddAt(pForm, n);
		if (index != eListInvalid) {
			*result = index;
		}
		if (IsConsoleMode()) {
			Console_Print("Index: %d", index);
		}
	}

	return true;
}

bool Cmd_ListAddReference_Execute(COMMAND_ARGS)
{
	*result = eListInvalid;
	BGSListForm* pListForm = NULL;
	UInt32 n = eListEnd;

	if (ExtractArgs(EXTRACT_ARGS, &pListForm, &n)) {
		if (!pListForm || !thisObj) return true;

		UInt32 index = pListForm->AddAt(thisObj, n);
		if (index != eListInvalid) {
			*result = index;
		}
		if (IsConsoleMode()) {
			Console_Print("Index: %d", index);
		}
	}
	return true;
}

bool Cmd_ListRemoveNthForm_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	BGSListForm* pListForm = NULL;
	UInt32 n = eListEnd;

	if (ExtractArgs(EXTRACT_ARGS, &pListForm, &n)) {
		if (pListForm) {
			TESForm* pRemoved = pListForm->RemoveNthForm(n);
			if (pRemoved) {
				*refResult = pRemoved->refID;
			}
		}
	}
	return true;
}

bool Cmd_ListReplaceNthForm_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	BGSListForm* pListForm = NULL;
	TESForm* pReplaceWith = NULL;
	UInt32 n = eListEnd;

	if (ExtractArgs(EXTRACT_ARGS, &pListForm, &pReplaceWith, &n)) {
		if (pListForm && pReplaceWith) {
			TESForm* pReplaced = pListForm->ReplaceNthForm(n, pReplaceWith);
			if (pReplaced) {
				*refResult = pReplaced->refID;
			}
		}
	}
	return true;
}

bool Cmd_ListRemoveForm_Execute(COMMAND_ARGS)
{
	*result = 0;
	BGSListForm* pListForm = NULL;
	TESForm* pForm = NULL;

	ExtractArgsEx(EXTRACT_ARGS_EX, &pListForm, &pForm);
	if (pListForm && pForm) {
		SInt32 index = pListForm->RemoveForm(pForm);
		*result = index;
	}
	return true;
}

bool Cmd_ListReplaceForm_Execute(COMMAND_ARGS)
{
	*result = 0;
	BGSListForm* pListForm = NULL;
	TESForm* pForm = NULL;
	TESForm* pReplaceWith = NULL;

	ExtractArgsEx(EXTRACT_ARGS_EX, &pListForm, &pReplaceWith, &pForm);
	if (pListForm && pForm && pReplaceWith) {
		SInt32 index = pListForm->ReplaceForm(pForm, pReplaceWith);
		*result = index;
	}
	return true;
}


bool Cmd_ListClear_Execute(COMMAND_ARGS)
{
	*result = 0;
	BGSListForm* pListForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &pListForm)) {
		//pListForm->list.RemoveAll();
	}
	return true;
}

bool Cmd_ListGetFormIndex_Execute(COMMAND_ARGS)
{
	*result = -1;
	BGSListForm* pListForm = NULL;
	TESForm* pForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &pListForm, &pForm)) {
		if (pListForm && pForm) {
			SInt32 index = pListForm->GetIndexOf(pForm); 
			*result = index;
			if (IsConsoleMode()) {
				Console_Print("Index: %d", index);
			}
		}
	}
	return true;
}
