#include "CommandTable.h"
#include "GameRTTI.h"
#include "Commands_Console.h"
#include "Commands_Game.h"
#include "Commands_Input.h"
#include "Commands_Inventory.h"
#include "Commands_List.h"
#include "Commands_Math.h"
#include "Commands_MiscRef.h"
#include "Commands_Quest.h"
#include "Commands_Script.h"
#include "Commands_UI.h"
#include "Commands_ModelIcon.h"
#include "PluginManager.h"

#include "fose_common/SafeWrite.h"
#include <string>

#ifdef RUNTIME

#include "GameAPI.h"
#include "GameInterface.h"
#include "GameObjects.h"
#include "GameExtraData.h"
#include "GameData.h"
#include "GameForms.h"
#include "Hooks_Script.h"

bool Cmd_GetFOSEVersion_Eval(COMMAND_ARGS_EVAL)
{
	*result = FOSE_VERSION_INTEGER;
	if (IsConsoleMode()) {
		Console_Print("FOSE version: %d", FOSE_VERSION_INTEGER);
	}
	return true;
}

bool Cmd_GetFOSEVersion_Execute(COMMAND_ARGS)
{
	return Cmd_GetFOSEVersion_Eval(thisObj, 0, 0, result);
}

bool Cmd_GetFOSERevision_Eval(COMMAND_ARGS_EVAL)
{
	*result = FOSE_VERSION_INTEGER_MINOR;
	if (IsConsoleMode()) {
		Console_Print("FOSE revision: %d", FOSE_VERSION_INTEGER_MINOR);
	}
	return true;
}

bool Cmd_GetFOSERevision_Execute(COMMAND_ARGS)
{
	return Cmd_GetFOSERevision_Eval(thisObj, 0, 0, result);
}

bool Cmd_GetFOSEBeta_Eval(COMMAND_ARGS_EVAL)
{
	*result = FOSE_VERSION_INTEGER_BETA;
	if (IsConsoleMode()) {
		Console_Print("FOSE revision: %d", FOSE_VERSION_INTEGER_BETA);
	}
	return true;
}

bool Cmd_GetFOSEBeta_Execute(COMMAND_ARGS)
{
	return Cmd_GetFOSEBeta_Eval(thisObj, 0, 0, result);
}


bool Cmd_tcmd_Execute(COMMAND_ARGS)
{
	Console_Print("hello world");

	*result = 0;
	return true;
}

bool Cmd_tcmd2_Execute(COMMAND_ARGS)
{
	UInt32	arg;

	if(ExtractArgs(EXTRACT_ARGS, &arg))
	{
		Console_Print("hello args: %d", arg);
	}
	else
	{
		Console_Print("hello args: failed");
	}

	*result = 0;
	return true;
}

bool Cmd_tcmd3_Execute(COMMAND_ARGS)
{
	PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
	TESQuest* pCurQuest = pPC->quest;
	BGSQuestObjective* pCurObjective = pPC->questObjective;

	Console_Print("Quest: %d (%s)", pCurQuest->refID, GetFullName(pCurQuest));
	Console_Print("Quest Objective: %d (%s)", pCurObjective->objectiveId, pCurObjective->displayText);
	
	//DumpClass(pCurObjective);

	
//	TESObjectCELL* pCell = pPC->parentCell;
//	if (pCell) {
//		Console_Print("%d items in cell %s", pCell->objectList.Count(), pCell->GetFullName());
//		if (pCell->worldSpace) {
//			DumpClass(pCell->worldSpace, 58);
//		}
//	}


	//InterfaceManager* pIM = InterfaceManager::GetSingleton();

	//BSExtraData* pXData = pIM->debugSelection->extraDataList.GetByType(kExtraData_Teleport);
	//if (pXData) {
	//	ExtraTeleport* pExtraTeleport = DYNAMIC_CAST(pXData, BSExtraData, ExtraTeleport);
	//	if (pExtraTeleport) {
	//		int x = 4;
	//	}
	//}


//	MagicTarget* pMagicTarget = DYNAMIC_CAST(*g_thePlayer, TESForm, MagicTarget);
//	if (pMagicTarget) {
//		DumpClass(pMagicTarget, 4);
//	}

	// DumpPlayer
//	void* pToDump = (void*)*g_thePlayer;
//	UInt32 sizeToDump = 1024;
//	_MESSAGE("Dump 0x%08X: %d", pToDump, sizeToDump);
//	DumpClass(pToDump, sizeToDump);

//	TESForm* pBaseForm = pIM->debugSelection->baseForm;
//	_MESSAGE("------------------------------------------");
//	_MESSAGE("Dump 0x%08X: %d", pBaseForm, sizeToDump);
//	DumpClass(pBaseForm, sizeToDump);


//	TESFullName* fullName = DYNAMIC_CAST(pBaseForm, TESForm, TESFullName);
//	if (fullName) {
//		Console_Print("%s", fullName->name.m_data);
//	}

	DataHandler* pDataHandler = DataHandler::Get();
	if (pDataHandler) {
		//BoundObjectListHead* pBoundHead = pDataHandler->boundObjectList;
		//
		//TESBoundObject* pCur = pBoundHead->first;
		//while (pCur != NULL) {
		//	if (pCur->IsArmor()) {
		//		TESBipedModelForm* pBipedModel = DYNAMIC_CAST(pCur, TESForm, TESBipedModelForm);
		//		_MESSAGE("(%X) f:%#x %s:", pCur->refID, pBipedModel->bipedFlags, GetFullName(pCur));
		//	}
		//	pCur = pCur->next;
		//}
		//Console_Print("done dumping weapons!");

		//ModList& modList = pDataHandler->modList;
		//_MESSAGE("mod count: %d modList.list.Count(): %d", modList.modCount, modList.modInfoList.Count());
		//for (UInt32 n = 0; n < modList.modCount; ++n) {
		//	ModInfo* pModInfo = modList.modInfoArray[n];
		//	if (pModInfo) {
		//		_MESSAGE("%d: %s", n, pModInfo->name);
		//		DumpClass(pModInfo, 266);
		//		_MESSAGE("----------");
		//	}
		//}

		//DumpClass(InterfaceManager::GetSingleton(), 300);

		//UInt32 n = 0;
		//tList<TESPackage> * pPackageList = &pDataHandler->packageList;
		//for (tList<TESPackage>::Iterator iter = pPackageList->Begin(); !iter.End(); ++iter)
		//{
		//	_MESSAGE("%d: %#x", n, iter->refID);
		//	DumpClass((void*)*iter, 32);
		//	++n;
		//}


//		UInt32 nQuests = pDataHandler->questList.Count();
//		for (UInt32 n =0; n < nQuests; ++n) {
//			TESQuest* pQuest = pDataHandler->questList.GetNthItem(n);
//			int x = 4;		
//			_MESSAGE("Quest %d %x", n, pQuest->refID);
//			DumpClass(pQuest, 27);
//			_MESSAGE("-----------------------------");
//		}

//		UInt32 nSpells =  pDataHandler->spellItemList.Count();
//		_MESSAGE("Spell count: %d",nSpells);
//
//		for (UInt32 n = 0; n < nSpells; ++n) {
//			SpellItem* pSpell = pDataHandler->spellItemList.GetNthItem(n);
//			TESFullName* pFullName = DYNAMIC_CAST(pSpell, SpellItem, TESFullName);
//			if (pFullName) {
//				_MESSAGE("%d: %s", n, pFullName->name.m_data);
//			}
//		}
	}


//	UInt32 vIds[] = {0x432E, 0x432D, 0x433F, 0x389AF, 0x39550, 0x6b533, 0x6b534, 0x0100726C};
//	UInt32 nIds = 8;
//	for (UInt32 n = 0; n < nIds; ++n) {
//		TESForm* pForm = LookupFormByID(vIds[n]);
//		if (pForm) {
//			TESObjectWEAP* pWeap = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
//			_MESSAGE("(%X) %s:", pWeap->refID, GetFullName(pWeap));
//			DumpClass(pWeap, 131);
//		}
//	}

	//TESForm* pForm = LookupFormByID(0x434F);
	//	if (pForm) {

	//	}
	//}

	return true;
}

bool Cmd_tcmd4_Execute(COMMAND_ARGS)
{
	PlayerCharacter* pPC = PlayerCharacter::GetSingleton();

	ExtraDataList& extraDataList = pPC->extraDataList;
	BSExtraData* extraData = extraDataList.GetByType(kExtraData_ContainerChanges);
	
	_MESSAGE("Dump Player Inventory");
	ExtraContainerChanges* contChanges = DYNAMIC_CAST(extraData, BSExtraData, ExtraContainerChanges);
	if (contChanges) {
		ExtraContainerChanges::EntryDataList* pObjList = contChanges->data->objList;
		UInt32 nEntries = pObjList->Count();
		for (UInt32 n = 0; n < nEntries; ++n) {
			ExtraContainerChanges::EntryData* pEntryData = pObjList->GetNthItem(n);
			if (pEntryData) {
				TESFullName* pFullName = DYNAMIC_CAST(pEntryData->type, TESForm, TESFullName);
				_MESSAGE("%d: %s", n, pFullName ? pFullName->name.m_data : "<unknown>");

				if (pEntryData->extendData) {
					UInt32 xExtends = pEntryData->extendData->Count();
					for (UInt32 x = 0; x < xExtends; ++x) {
						ExtraDataList* pExtraDataList = pEntryData->extendData->GetNthItem(x);
						if (pExtraDataList) {
							BSExtraData* pXData = pExtraDataList->m_data;
							while (pXData != NULL) {
								_MESSAGE("BSXDataType: %X", pXData->type);
								pXData = pXData->next;
							}
						}
					}
				}
			}
			
		}
	}

	BSExtraData* pXData = extraDataList.m_data;
	while (pXData != NULL) {
		_MESSAGE("BSXDataType: %X", pXData->type);
		pXData = pXData->next;
	}


	InterfaceManager* pIM = InterfaceManager::GetSingleton();
	TESObjectREFR* pRef = pIM->debugSelection;
	if (!pRef) return true;

	TESObjectWEAP* pWeapon = DYNAMIC_CAST(pRef->baseForm, TESForm, TESObjectWEAP);
	if (pWeapon) {
		TESAmmo * pAmmo = pWeapon->ammo.ammo;
		Console_Print("%s> Value: %d Weight: %.2f Health: %d \n Damage: %d RateOfFire: %.2f CritPerc: %.2f CritDmg: %d \n AP: %.2f pread: %.2f - %.2f \n ClipRounds: %d Ammo: %s", 
			pWeapon->fullName.name.m_data, pWeapon->value.value, pWeapon->weight.weight,
			pWeapon->health.health, pWeapon->attackDmg.damage, pWeapon->animShotsPerSec, pWeapon->criticalPercent, pWeapon->criticalDamage,
			pWeapon->AP, pWeapon->minSpread, pWeapon->minSpread, pWeapon->clipRounds.clipRounds, (pAmmo) ? pAmmo->fullName.name.m_data : "None");
	} else {
		Console_Print("not a weapon");
	}

	return true;
}

class BGSFormList;

bool Cmd_tcmd5_Execute(COMMAND_ARGS)
{
	TESForm* form = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &form)) {
		
		BGSListForm* listForm = DYNAMIC_CAST(form, TESForm, BGSListForm);
		tList<TESForm>& theList = listForm->list;
		UInt32 nItems = theList.Count();
		for (UInt32 n=0; n < nItems; ++n) {
			TESForm* form = theList.GetNthItem(n);
			if (form) {
				TESFullName* fullName = DYNAMIC_CAST(form, TESForm, TESFullName);
				if (fullName) {
					Console_Print("\t%d: refId:0x%X %s", n, form->refID, fullName->name.m_data);
				}
			}
		}
	}
	return true;
}

bool Cmd_DumpDocs_Execute(COMMAND_ARGS)
{
	UInt32 opCodeStart = kFoseOpCodeStart;
	if (ExtractArgs(EXTRACT_ARGS, &opCodeStart)) {
		g_scriptCommands.DumpCommandDocumentation(opCodeStart);
	}
	return true;
}

bool Cmd_sWTF_Execute(COMMAND_ARGS)
{
	TESForm* form = LookupFormByID(0x000270F0);		// Lacy undies
	TESObjectMISC* misc = DYNAMIC_CAST(form, TESForm, TESObjectMISC);
	if (!misc)
		Console_Print("Uhoh, cast failed");
	else
	{
		_MESSAGE("Saving");
		misc->SaveForm();
		FILE * fp;
		fopen_s(&fp, "swtfFormData", "wb");
		fwrite(*g_CreatedObjectData, 1, *g_CreatedObjectSize, fp);
		fclose(fp);
		_MESSAGE("Saved");
		Console_Print("Saved");
	}

	return true;	

	/*
	void* pTib;
	void* pTlsArray;

	__asm {
		mov eax, fs:[2Ch]
		mov [pTlsArray], eax
		mov eax, fs:[18h]
		mov [pTib], eax
	}

	_MESSAGE("pTib: %08x pTlsArray: %08x", pTib, pTlsArray);
	return true;
	*/
}

static const UInt32 kMaxSavedIPs = 0x100;
static const UInt32	kMaxSavedIPStack = 20;	// twice the supposed limit
struct SavedIPInfo
{
	UInt32	ip;
	UInt32	stackDepth;
	UInt32	stack[kMaxSavedIPStack];
};

struct ScriptExecutionState
{
	UInt32	pad[0x20 >> 2];
	UInt32	stackDepth;
	UInt32	stack[1];
};

static SavedIPInfo s_savedIPTable[kMaxSavedIPs] = { { 0 } };

bool Cmd_Label_Execute(COMMAND_ARGS)
{
	UInt32	_esi;

	// ### assume nothing modifies esi before we get here
	// ### MAKE SURE THIS IS THE FIRST CODE TO RUN
	// ### the alternative is a __declspec(naked) and __asm wrapper
	__asm { mov _esi, esi }

	// make sure this is only called from the main execution loop
	ASSERT_STR(scriptData == scriptObj->data, "SaveIP may not be called inside a set or if statement");

	UInt32	idx = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &idx)) return true;

	// this must happen after extractargs updates opcodeOffsetPtr so it points to the next instruction
	if(idx < kMaxSavedIPs)
	{
		SavedIPInfo				* info = &s_savedIPTable[idx];
		ScriptExecutionState	* state = (ScriptExecutionState *)_esi;

		info->ip = *opcodeOffsetPtr;
		info->stackDepth = state->stackDepth;
		ASSERT((info->stackDepth + 1) < kMaxSavedIPStack);
		memcpy(info->stack, state->stack, (info->stackDepth + 1) * sizeof(UInt32));
	}

	return true;
}

bool Cmd_Goto_Execute(COMMAND_ARGS)
{
	UInt32	_esi;

	// ### assume nothing modifies esi before we get here
	__asm { mov _esi, esi }

	// make sure this is only called from the main execution loop
	ASSERT_STR(scriptData == scriptObj->data, "RestoreIP may not be called inside a set or if statement");

	UInt32	idx = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &idx)) return true;

	if(idx < kMaxSavedIPs)
	{
		SavedIPInfo				* info = &s_savedIPTable[idx];
		ScriptExecutionState	* state = (ScriptExecutionState *)_esi;

		*g_ScriptDataBytes += info->ip - opcodeOffsetPtr[0];

		// restore the if/else/endif stack
		state->stackDepth = info->stackDepth;
		memcpy(state->stack, info->stack, (info->stackDepth + 1) * sizeof(UInt32));
	}

	return true;
}

#endif

// nop command handler for script editor
bool Cmd_Default_Execute(COMMAND_ARGS)
{
	return true;
}

bool Cmd_Default_Eval(COMMAND_ARGS_EVAL)
{
	return true;
}

// called from 004F90A5
bool Cmd_Default_Parse(UInt32 numParams, ParamInfo * paramInfo, ScriptLineBuffer * lineBuf, ScriptBuffer * scriptBuf)
{
	#ifdef RUNTIME

	#if FALLOUT_VERSION == FALLOUT_VERSION_1_0
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x00519BB0;
	#elif FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x00518C40;
	#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x0051B5B0;
	#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x0051B010;
	#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x0051B520;
	#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x0051B780;
	#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x0051AD50;
	#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x0051AF10;
	#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x0051B540;
	#else
	#error unsupported version of runtime
	#endif

	#else

	#if CS_VERSION == CS_VERSION_1_1_36
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x005BFE60;
	#elif CS_VERSION == CS_VERSION_1_5_19
	static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x005C01F0;
	#else
	#error unsupported version of editor
	#endif

	#endif

	// arg0 = idx?
	// arg1 = ParamInfo *
	// arg2 = ptr to line to parse, skip UInt32 header first
	// arg3 = ptr to script info? first UInt32 is ptr to script data

	return g_defaultParseCommand(numParams, paramInfo, lineBuf, scriptBuf);
}

CommandTable::CommandTable()
{
	//
}

CommandTable::~CommandTable()
{
	//
}

static ParamInfo kTestArgCommand_Params[] =
{
	{	"int", kParamType_Integer, 0 }
};

DEFINE_CMD_COND(GetFOSEVersion, returns the installed version of FOSE, 0, NULL);
DEFINE_CMD_COND(GetFOSERevision, returns the numbered revision of the installed version of FOSE, 0, NULL);
DEFINE_CMD_COND(GetFOSEBeta, returns the numbered beta of the installed version of FOSE, 0, NULL);
DEFINE_COMMAND(tcmd, test, 0, 0, NULL);
DEFINE_CMD_ALT(tcmd2, testargcmd ,test, 0, 1, kTestArgCommand_Params);
DEFINE_COMMAND(tcmd3, test, 0, 0, NULL);
DEFINE_COMMAND(tcmd4, dump weapon, 0, 0, NULL);
DEFINE_COMMAND(tcmd5, dump form list, 0, 1, kParams_FormList);
DEFINE_COMMAND(Label, set a label, 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND(Goto, branch to a label, 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND(DumpDocs, dump command documentation, 0, 1, kParams_OneOptionalInt);

DEFINE_COMMAND(sWTF, scruggsy test command, 0, 0, NULL);

static CommandInfo kPaddingCommand =
{
	"", "",
	0,
	"command used for padding",
	0,
	0,
	NULL,

	Cmd_Default_Execute,
	Cmd_Default_Parse,
	NULL,
	NULL
};

struct PatchLocation
{
	UInt32	ptr;
	UInt32	offset;
	UInt32	type;
};

#ifdef RUNTIME

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0

// ### possibly incomplete

static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	// 00518790
	{	0x005187C8 + 3,	0x00 },

	// 005187D0
	{	0x00518819 + 1,	0x04 },
	{	0x005188B2 + 3,	0x08 },

	// 00519870
	{	0x005199F9 + 3,	0x00 },

	// 0051BBF0
	{	0x0051C44A + 3,	0x00 },

	// 0053D240
	{	0x0053D40D + 2,	0x0C },
	{	0x0053D425 + 2,	0x00 },
	{	0x0053D43D + 2,	0x04 },
	{	0x0053D459 + 2,	0x0C },
	{	0x0053D475 + 2,	0x04 },
	{	0x0053D491 + 2,	0x00 },
	{	0x0053D4A9 + 2,	0x00 },
	{	0x0053D4C0 + 2,	0x04 },
	{	0x0053D4DD + 2,	0x00 },
	{	0x0053D4F4 + 2,	0x00 },

	// 005AC5D0
	{	0x005AC66E + 3,	0x20 },
	{	0x005AC67F + 2,	0x10 },

	// 005ACA90
	{	0x005ACB5E + 3,	0x20 },
	{	0x005ACC43 + 3,	0x00 },

	// 005ACE30
	{	0x005ACE40 + 4,	0x12 },

	// 005ACE50
	{	0x005ACE81 + 4,	0x12 },
	{	0x005ACE8F + 2,	0x14 },

	// 005ACEB0
	{	0x005ACECB + 3,	0x12 },
	{	0x005ACED7 + 2,	0x14 },

	// 005ACF90
	{	0x005ACFD7 + 4,	0x12 },
	{	0x005AD0CA + 3,	0x14 },
	{	0x005AD169 + 4,	0x12 },
	{	0x005AD17B + 2,	0x14 },

	// 006EED60
	{	0x006EEDAB + 4,	0x12 },
	{	0x006EEDD5 + 2,	0x14 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	// 005187D0
	{	0x00518847 + 2, 0x04 },

	// 00518750 - assert
//	{	0x00518750 + 2,	0x08 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 0050C2A0
	{	0x0050C324 + 3,	1,	1 },

	// 00518790
	{	0x005187B9 + 2,	(UInt32)(-0x1000) + 1 },

	// 00519870
	{	0x005199EB + 1, (UInt32)(-0x1000) + 1 },

	// 0051BBF0
	{	0x0051C43F + 2,	(UInt32)(-0x1000) + 1 },

	// 00518750 - assert
//	{	0x00518750 + 6,	0 },

	// ### 005AC8A0 - investigate this

	{	0 },
};

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_0_15

static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	// 00517820
	{	0x00517858 + 3,	0x00 },

	// 00517860
	{	0x005178A9 + 1,	0x04 },
	{	0x00517942 + 3,	0x08 },

	// 00518900
	{	0x00518A89 + 3,	0x00 },

	// 0051AC80
	{	0x0051B4DA + 3,	0x00 },

	// 0053C260
	{	0x0053C42D + 2,	0x0C },
	{	0x0053C445 + 2,	0x00 },
	{	0x0053C45D + 2,	0x04 },
	{	0x0053C479 + 2,	0x0C },
	{	0x0053C495 + 2,	0x04 },
	{	0x0053C4B1 + 2,	0x00 },
	{	0x0053C4C9 + 2,	0x00 },
	{	0x0053C4E0 + 2,	0x04 },
	{	0x0053C4FD + 2,	0x00 },
	{	0x0053C514 + 2,	0x00 },

	// 005AC2D0
	{	0x005AC36E + 3,	0x20 },
	{	0x005AC37F + 2,	0x10 },

	// 005AC790
	{	0x005AC85E + 3,	0x20 },
	{	0x005AC943 + 3,	0x00 },

	// 005ACB30
	{	0x005ACB40 + 4,	0x12 },

	// 005ACB50
	{	0x005ACB81 + 4,	0x12 },
	{	0x005ACB8F + 2,	0x14 },

	// 005ACBB0
	{	0x005ACBCB + 3,	0x12 },
	{	0x005ACBD7 + 2,	0x14 },

	// 005ACC90
	{	0x005ACCD7 + 4,	0x12 },
	{	0x005ACDCA + 3,	0x14 },
	{	0x005ACE69 + 4,	0x12 },
	{	0x005ACE7B + 2,	0x14 },

	// 006EEC90
	{	0x006EECDB + 4,	0x12 },
	{	0x006EED05 + 2,	0x14 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	// 00517860
	{	0x005178D7 + 2, 0x04 },

	// 005177E0 - assert
//	{	0x005177E0 + 2,	0x08 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 0050B320
	{	0x0050B3A4 + 3,	1,	1 },

	// 00517820
	{	0x00517849 + 2,	(UInt32)(-0x1000) + 1 },

	// 00518900
	{	0x00518A7B + 1, (UInt32)(-0x1000) + 1 },

	// 0051AC80
	{	0x0051B4CF + 2,	(UInt32)(-0x1000) + 1 },

	// 005177E0 - assert
//	{	0x005177E0 + 6,	0 },

	// ### 005AC8A0 - investigate this

	{	0 },
};

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35

static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	// 51A190
	{	0x0051A1C8 + 3,	0x00 },	// 51A190+38	lea eax, g_ScriptCmdOffset[eax*8]

	// 51A1D0
	{	0x0051A219 + 1,	0x04 }, // 51A1D0+49	mov edi, g_ScriptCmdOffset2
	{	0x0051A2B2 + 3,	0x08 }, // 51A1D0+E2	mov eax, dword_F51988[edx*8]

	// 0051B270
	{	0x0051B3F9 + 3,	0x00 }, // 51B270+189	lea eax, g_ScriptCmdOffset[eax*8]

	// 0051D7E0
	{	0x0051E03A + 3,	0x00 }, // 51D7E0+85A	lea ebp, g_ScriptCmdOffset[eax*8]

	// 0053F020
	{	0x0053F1ED + 2,	0x0C }, // 53F020+1CD	mov edx, off_F5198C[esi]
	{	0x0053F205 + 2,	0x00 }, // 53f020+1E5	mov ecx, g_ScriptCommandOffset[esi]
	{	0x0053F21D + 2,	0x04 }, // 53F020+1FD	mov eax, g_ScriptCmdOffset2[esi]
	{	0x0053F239 + 2,	0x0C }, // 53F020+219	mov edi, off_F5198C[esi]
	{	0x0053F255 + 2,	0x04 }, // 53F020+235	mov edx, g_ScriptCmdOffset2[esi]
	{	0x0053F271 + 2,	0x00 }, // 53f020+251	mov ecx, g_ScriptCommandOffset[esi]
	{	0x0053F289 + 2,	0x00 }, // 53f020+269	mov edx, g_ScriptCommandOffset[esi]
	{	0x0053F2A0 + 2,	0x04 }, // 53F020+280	mov edx, g_ScriptCmdOffset2[esi]
	{	0x0053F2BD + 2,	0x00 }, // 53f020+29D	mov eax, g_ScriptCommandOffset[esi]
	{	0x0053F2D4 + 2,	0x00 }, // 53f020+2B4	mov ecx, g_ScriptCommandOffset[esi]

	// 005AEDB0
	{	0x005AEE4E + 3,	0x20 }, // +9E			mov ecx, dword_F519A0[eax+eax]
	{	0x005AEE5F + 2,	0x10 }, // +AF			cmp byte_F51990[eax], 0

	// 005AC790
	{	0x005AF367 + 3,	0x20 },	// 5AF270+F7	cmp dword_F519A0[edx*8], 0
	{	0x005AF44F + 3,	0x00 }, // 5AF270+1DF	mov ecx, g_ScriptCommandOffset[edx*8]

	// 005AF640
	{	0x005AF650 + 4,	0x12 }, // +10			movzx eax, word_F51992[eax*8]

	// 005AF640
	{	0x005AF691 + 4,	0x12 }, // 5AF640+31	movzx esi, word_F51992[ecx+ecx]
	{	0x005AF69F + 2,	0x14 }, // 5AF640+3F	mov eax, dword_F51994[ecx]

	// 005AF6C0
	{	0x005AF6DB + 3,	0x12 }, // 5AF6C0+1B	movzx esi, word_F51992[ecx]
	{	0x005AF6E7 + 2,	0x14 }, // 5AF6C0+27	mov ecx, dword_F51994[ecx]

	// 005AF7A0
	{	0x005AF7E7 + 4,	0x12 }, // 5AF7A0+47	movzx ebp, word_F51992[eax*8]
	{	0x005AF8DA + 3,	0x14 }, // 5AF7A0+13A	mov esx, dword_F51994[ecx*8]
	{	0x005AF979 + 4,	0x12 }, // 5AF7A0+1D9	movzx ebp, word_F51992[eax+eax]
	{	0x005AF98B + 2,	0x14 }, // 5AF7A0+1EB	mov eax, dword_F51994[eax]

	// 006F2A60
	{	0x006F2AAB + 4,	0x12 }, // 6F2A60+4B	movzx ecx, word_F51992[edi+edi]
	{	0x006F2AD5 + 2,	0x14 }, // 6F2A60+75	mov esi, dword_F51994[edi]

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	// 0050DB70
	{	0x0051A247 + 2, 0x04 },	// 51A1D0+77	cmp edi, off_F5721C

	// 0051A150 - assert
//	{	0x0051A150 + 2,	0x08 },	//				cmp dword_F57220, 1237h

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 0050DB70
	{	0x0050DBF4 + 3,	1,	1 },

	// 0051A190
	{	0x0051A1B9 + 2,	(UInt32)(-0x1000) + 1 },

	// 0051B270
	{	0x0051B3EB + 1, (UInt32)(-0x1000) + 1 },

	// 0051D7E0
	{	0x0051E02F + 2,	(UInt32)(-0x1000) + 1 },

	// 0051A150 - assert
//	{	0x0051A150 + 6,	0 },

	// ### 005AC8A0 - investigate this

	{	0 },
};

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6

// 30
static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x00519C2B, 0x00 },
	{	0x00519C7A, 0x04 },
	{	0x00519D15, 0x08 },
	{	0x0051AE5C, 0x00 },
	{	0x0051DA9D, 0x00 },
	{	0x0053EC8F, 0x0C },
	{	0x0053ECA7, 0x00 },
	{	0x0053ECBF, 0x04 },
	{	0x0053ECDB, 0x0C },
	{	0x0053ECF7, 0x04 },
	{	0x0053ED13, 0x00 },
	{	0x0053ED2B, 0x00 },
	{	0x0053ED42, 0x04 },
	{	0x0053ED5F, 0x00 },
	{	0x0053ED76, 0x00 },
	{	0x005AEF81, 0x20 },
	{	0x005AEF91, 0x10 },
	{	0x005AF49A, 0x20 },
	{	0x005AF582, 0x00 },
	{	0x005AF784, 0x12 },
	{	0x005AF7C5, 0x12 },
	{	0x005AF7D1, 0x14 },
	{	0x005AF80E, 0x12 },
	{	0x005AF819, 0x14 },
	{	0x005AF91B, 0x12 },
	{	0x005AFA0D, 0x14 },
	{	0x005AFAAD, 0x12 },
	{	0x005AFABD, 0x14 },
	{	0x006F2A1F, 0x12 },
	{	0x006F2A47, 0x14 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x00519BB2, 0x08 },
	{	0x00519CA9, 0x04 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 0050D5C0
	{	0x0050D644 + 3,	1,	1 },

	// 00519BF0
	{	0x00519C19 + 2,	(UInt32)(-0x1000) + 1 },

	// 0051ACD0
	{	0x0051AE4B + 1, (UInt32)(-0x1000) + 1 },

	// 0051D240
	{	0x0051DA8F + 2,	(UInt32)(-0x1000) + 1 },

	{	0 },
};

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b

// 30
static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x0051A13B, 0x00 },
	{	0x0051A18A, 0x04 },
	{	0x0051A225, 0x08 },
	{	0x0051B36C, 0x00 },
	{	0x0051DFAD, 0x00 },
	{	0x0053F19F, 0x0C },
	{	0x0053F1B7, 0x00 },
	{	0x0053F1CF, 0x04 },
	{	0x0053F1EB, 0x0C },
	{	0x0053F207, 0x04 },
	{	0x0053F223, 0x00 },
	{	0x0053F23B, 0x00 },
	{	0x0053F252, 0x04 },
	{	0x0053F26F, 0x00 },
	{	0x0053F286, 0x00 },
	{	0x005AEFB1, 0x20 },
	{	0x005AEFC1, 0x10 },
	{	0x005AF4CA, 0x20 },
	{	0x005AF5B2, 0x00 },
	{	0x005AF7B4, 0x12 },
	{	0x005AF7F5, 0x12 },
	{	0x005AF801, 0x14 },
	{	0x005AF83E, 0x12 },
	{	0x005AF849, 0x14 },
	{	0x005AF94B, 0x12 },
	{	0x005AFA3D, 0x14 },
	{	0x005AFADD, 0x12 },
	{	0x005AFAED, 0x14 },
	{	0x006F308F, 0x12 },
	{	0x006F30B7, 0x14 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x0051A0C2, 0x08 },
	{	0x0051A1B9, 0x04 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 0050DAD0
	{	0x0050DB54 + 3,	1,	1 },

	// 0051A100
	{	0x0051A129 + 2,	(UInt32)(-0x1000) + 1 },

	// 0051B1E0
	{	0x0051B35B + 1, (UInt32)(-0x1000) + 1 },

	// 0051D750
	{	0x0051DF9F + 2,	(UInt32)(-0x1000) + 1 },

	{	0 },
};

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22

// 30
static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x0051A39B, 0x00 },
	{	0x0051A3EA, 0x04 },
	{	0x0051A485, 0x08 },
	{	0x0051B5CC, 0x00 },
	{	0x0051E20D, 0x00 },
	{	0x0053F52F, 0x0C },
	{	0x0053F547, 0x00 },
	{	0x0053F55F, 0x04 },
	{	0x0053F57B, 0x0C },
	{	0x0053F597, 0x04 },
	{	0x0053F5B3, 0x00 },
	{	0x0053F5CB, 0x00 },
	{	0x0053F5E2, 0x04 },
	{	0x0053F5FF, 0x00 },
	{	0x0053F616, 0x00 },
	{	0x005AF371, 0x20 },
	{	0x005AF381, 0x10 },
	{	0x005AF88A, 0x20 },
	{	0x005AF972, 0x00 },
	{	0x005AFB74, 0x12 },
	{	0x005AFBB5, 0x12 },
	{	0x005AFBC1, 0x14 },
	{	0x005AFBFE, 0x12 },
	{	0x005AFC09, 0x14 },
	{	0x005AFD0B, 0x12 },
	{	0x005AFDFD, 0x14 },
	{	0x005AFE9D, 0x12 },
	{	0x005AFEAD, 0x14 },
	{	0x006F2B3F, 0x12 },
	{	0x006F2B67, 0x14 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x0051A322, 0x08 },
	{	0x0051A419, 0x04 },

	{	0 },
};


static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 0050DCF0
	{	0x0050DD74 + 3,	1,	1 },

	// 0051A360
	{	0x0051A389 + 2,	(UInt32)(-0x1000) + 1 },

	// 0051B440
	{	0x0051B5BB + 1, (UInt32)(-0x1000) + 1 },

	// 0051D9B0
	{	0x0051E1FF + 2,	(UInt32)(-0x1000) + 1 },

	{	0 },
};

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6

// 30
static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x0051996B, 0x00 },
	{	0x005199BA, 0x04 },
	{	0x00519A55, 0x08 },
	{	0x0051AB9C, 0x00 },
	{	0x0051D7DD, 0x00 },
	{	0x0053EABF, 0x0C },
	{	0x0053EAD7, 0x00 },
	{	0x0053EAEF, 0x04 },
	{	0x0053EB0B, 0x0C },
	{	0x0053EB27, 0x04 },
	{	0x0053EB43, 0x00 },
	{	0x0053EB5B, 0x00 },
	{	0x0053EB72, 0x04 },
	{	0x0053EB8F, 0x00 },
	{	0x0053EBA6, 0x00 },
	{	0x005AE551, 0x20 },
	{	0x005AE561, 0x10 },
	{	0x005AEA6A, 0x20 },
	{	0x005AEB52, 0x00 },
	{	0x005AED54, 0x12 },
	{	0x005AED95, 0x12 },
	{	0x005AEDA1, 0x14 },
	{	0x005AEDDE, 0x12 },
	{	0x005AEDE9, 0x14 },
	{	0x005AEEEB, 0x12 },
	{	0x005AEFDD, 0x14 },
	{	0x005AF07D, 0x12 },
	{	0x005AF08D, 0x14 },
	{	0x006F213F, 0x12 },
	{	0x006F2167, 0x14 },
	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x005198F2, 0x08 },
	{	0x005199E9, 0x04 },
	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 0050D2E0
	{	0x0050D364 + 3,	1,	1 },

	// 00519930
	{	0x00519959 + 2,	(UInt32)(-0x1000) + 1 },

	// 0051AA10
	{	0x0051AB8B + 1, (UInt32)(-0x1000) + 1 },

	// 0051CF80
	{	0x0051D7CF + 2,	(UInt32)(-0x1000) + 1 },

	{	0 },
};

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7

// 30
static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x00519B2B, 0x00 },
	{	0x00519B7A, 0x04 },
	{	0x00519C15, 0x08 },
	{	0x0051AD5C, 0x00 },
	{	0x0051D99D, 0x00 },
	{	0x0053ECAF, 0x0C },
	{	0x0053ECC7, 0x00 },
	{	0x0053ECDF, 0x04 },
	{	0x0053ECFB, 0x0C },
	{	0x0053ED17, 0x04 },
	{	0x0053ED33, 0x00 },
	{	0x0053ED4B, 0x00 },
	{	0x0053ED62, 0x04 },
	{	0x0053ED7F, 0x00 },
	{	0x0053ED96, 0x00 },
	{	0x005AE5B1, 0x20 },
	{	0x005AE5C1, 0x10 },
	{	0x005AEACA, 0x20 },
	{	0x005AEBB2, 0x00 },
	{	0x005AEDB4, 0x12 },
	{	0x005AEDF5, 0x12 },
	{	0x005AEE01, 0x14 },
	{	0x005AEE3E, 0x12 },
	{	0x005AEE49, 0x14 },
	{	0x005AEF4B, 0x12 },
	{	0x005AF03D, 0x14 },
	{	0x005AF0DD, 0x12 },
	{	0x005AF0ED, 0x14 },
	{	0x006F209F, 0x12 },
	{	0x006F20C7, 0x14 },
	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x00519AB2, 0x08 },
	{	0x00519BA9, 0x04 },
	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 0050D490
	{	0x0050D514 + 3,	1,	1 },

	// 00519AF0
	{	0x00519B19 + 2,	(UInt32)(-0x1000) + 1 },

	// 0051ABD0
	{	0x0051AD4B + 1, (UInt32)(-0x1000) + 1 },

	// 0051D140
	{	0x0051D98F + 2,	(UInt32)(-0x1000) + 1 },

	{	0 },
};

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng

//	00	longName
//	04	shortName
//	08	opcode
//	0C	helpText
//	10	needsParent
//	12	numParams
//	14	params
//	18	execute
//	1C	parse
//	20	eval
//	24	flags

static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x0051A15B, 0x00 },
	{	0x0051A1AA, 0x04 },
	{	0x0051A245, 0x08 },
	{	0x0051B38C, 0x00 },
	{	0x0051DFCD, 0x00 },
	{	0x0053F35F, 0x0C },
	{	0x0053F377, 0x00 },
	{	0x0053F38F, 0x04 },
	{	0x0053F3AB, 0x0C },
	{	0x0053F3C7, 0x04 },
	{	0x0053F3E3, 0x00 },
	{	0x0053F3FB, 0x00 },
	{	0x0053F412, 0x04 },
	{	0x0053F42F, 0x00 },
	{	0x0053F446, 0x00 },
	{	0x005AEEC1, 0x20 },
	{	0x005AEED1, 0x10 },
	{	0x005AF3DA, 0x20 },
	{	0x005AF4C2, 0x00 },
	{	0x005AF6C4, 0x12 },
	{	0x005AF705, 0x12 },
	{	0x005AF711, 0x14 },
	{	0x005AF74E, 0x12 },
	{	0x005AF759, 0x14 },
	{	0x005AF85B, 0x12 },
	{	0x005AF94D, 0x14 },
	{	0x005AF9ED, 0x12 },
	{	0x005AF9FD, 0x14 },
	{	0x006F217F, 0x12 },
	{	0x006F21A7, 0x14 },
	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x0051A0E2, 0x08 },
	{	0x0051A1D9, 0x04 },
	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 0050DAF0
	{	0x0050DB74 + 3,	1,	1 },

	// 0051A120
	{	0x0051A149 + 2,	(UInt32)(-0x1000) + 1 },

	// 0051ABD0
	{	0x0051B37B + 1, (UInt32)(-0x1000) + 1 },

	// 0051D770
	{	0x0051DFBF + 2,	(UInt32)(-0x1000) + 1 },

	{	0 },
};

#else

#error unsupported runtime version

#endif

#else // RUNTIME (CS stuff goes here)

#if CS_VERSION == CS_VERSION_1_1_36

//	00	longName
//	04	shortName
//	08	opcode
//	0C	helpText
//	10	needsParent
//	12	numParams
//	14	params
//	18	execute
//	1C	parse
//	20	eval
//	24	flags

static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	// 00406E10
	{	0x00406ED9 + 3,	0x00 },

	// 00406F70
	{	0x00407037 + 3,	0x00 },

	// 004A3AC0
	{	0x004A3B83 + 3,	0x24 },
	{	0x004A3BE0 + 3,	0x24 },

	// 004A4270
	{	0x004A43C8 + 3,	0x00 },

	// 004A5550
	{	0x004A55C1 + 3,	0x20 },
	{	0x004A55D2 + 2,	0x12 },

	// 004A5BE0
	{	0x004A5BF9 + 1,	0x00 },

	// 004A5F30
	{	0x004A6027 + 3,	0x20 },
	{	0x004A6152 + 3,	0x00 },

	// 004A66C0
	{	0x004A675F + 3,	0x00 },

	// 004A6910
	{	0x004A69A3 + 3,	0x00 },

	// 004A7160
	{	0x004A7170 + 4, 0x12 },

	// 004A7180
	{	0x004A71B1 + 4,	0x12 },
	{	0x004A71BF + 2,	0x14 },

	// 004A71E0
	{	0x004A71FB + 3,	0x12 },
	{	0x004A7207 + 2,	0x14 },

	// 004A72C0
	{	0x004A72E2 + 4,	0x12 },
	{	0x004A7329 + 4,	0x12 },
	{	0x004A7337 + 2,	0x14 },

	// 004A7380
	{	0x004A73A2 + 4,	0x12 },
	{	0x004A73E9 + 4,	0x12 },
	{	0x004A73F7 + 2,	0x14 },

	// 004A7440
	{	0x004A7458 + 4,	0x12 },

	// 004A74A0
	{	0x004A74B5 + 4,	0x12 },
	{	0x004A7504 + 4,	0x12 },
	{	0x004A7512 + 2,	0x14 },

	// 004A78D0
	{	0x004A78F0 + 3,	0x14 },
	{	0x004A7E45 + 3,	0x14 },

	// 004A7F50
	{	0x004A7FA0 + 4,	0x12 },
	{	0x004A7FE5 + 4,	0x12 },
	{	0x004A7FF3 + 2,	0x14 },

	// 004A80A0
	{	0x004A80E7 + 4,	0x12 },
	{	0x004A8324 + 4,	0x12 },
	{	0x004A8336 + 2,	0x14 },

	// 004A8420
	{	0x004A844B + 4,	0x12 },
	{	0x004A85E1 + 3,	0x14 },
	{	0x004A859D + 3, 0x14 },	

	// 004A8870
	{	0x004A88AA + 4,	0x12 },

	// 004A89A0
	{	0x004A89E9 + 4,	0x12 },
	{	0x004A8A32 + 3,	0x14 },
	{	0x004A8AE7 + 3,	0x14 },

	// 004A8BA0
	{	0x004A8BE6 + 4,	0x12 },

	// 004A8C10
	{	0x004A8DB9 + 3,	0x14 },

	// 005A3600
	{	0x005A36DD + 2,	0x20 },
	{	0x005A36E6 + 2,	0x24 },
	{	0x005A385B + 1,	0x24 },

	// 005BE960
	{	0x005BE9A9 + 1,	0x04 },
	{	0x005BEA42 + 3,	0x08 },

	// 005BFB20
	{	0x005BFCA9 + 3,	0x00 },

	// 005C20F0
	{	0x005C291B + 3,	0x00 },

	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	// 004A5BE0
	{	0x004A5C1B + 2,	0x00 },

	// 005A3600
	{	0x005A38AD + 2,	0x24 },

	// assert at 005BE920

	// 005BE960
	{	0x005BE9D7 + 2,	0x04 },

	{	0 },
};

// 1CB console cmds, 236 script cmds
// checked 0236
static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 002A4270
	{	0x004A43B7 + 2,	(UInt32)(-0x1000) + 1 },

	// 004A5C70
	{	0x004A5C7A + 2,	(UInt32)(-0x1000) + 1 },
	{	0x004A5C8D + 1,	(UInt32)(-0x1000) + 1 },
	{	0x004A5C99 + 2,	(UInt32)(-0x1000) + 1 },

	// 005A3600
	{	0x005A3721 + 2, (UInt32)(-0x1000) + 1 },

	// 005B3820
	{	0x005B68A4 + 3,	1, 1 },

	// assert at 005BE920

	// 005BFB20
	{	0x005BFC9B + 1,	(UInt32)(-0x1000) + 1 },

	// 005C20F0
	{	0x005C2910 + 2,	(UInt32)(-0x1000) + 1 },

	{	0 },
};

#elif CS_VERSION == CS_VERSION_1_5_19

//	00	longName
//	04	shortName
//	08	opcode
//	0C	helpText
//	10	needsParent
//	12	numParams
//	14	params
//	18	execute
//	1C	parse
//	20	eval
//	24	flags

static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x00406D4C, 0x00 },
	{	0x00406EAA, 0x00 },
	{	0x004A3814, 0x24 },
	{	0x004A3888, 0x24 },
	{	0x004A40FB, 0x00 },
	{	0x004A52F4, 0x20 },
	{	0x004A5304, 0x10 },
	{	0x004A592A, 0x00 },
	{	0x004A5D5A, 0x20 },
	{	0x004A5E85, 0x00 },
	{	0x004A6492, 0x00 },
	{	0x004A66D6, 0x00 },
	{	0x004A6EA4, 0x12 },
	{	0x004A6EE5, 0x12 },
	{	0x004A6EF1, 0x14 },
	{	0x004A6F2E, 0x12 },
	{	0x004A6F39, 0x14 },
	{	0x004A7016, 0x12 },
	{	0x004A705D, 0x12 },
	{	0x004A7069, 0x14 },
	{	0x004A70D6, 0x12 },
	{	0x004A711D, 0x12 },
	{	0x004A7129, 0x14 },
	{	0x004A718C, 0x12 },
	{	0x004A71E9, 0x12 },
	{	0x004A7238, 0x12 },
	{	0x004A7244, 0x14 },
	{	0x004A7623, 0x14 },
	{	0x004A7B78, 0x14 },
	{	0x004A7CD4, 0x12 },
	{	0x004A7D19, 0x12 },
	{	0x004A7D25, 0x14 },
	{	0x004A7E1B, 0x12 },
	{	0x004A8058, 0x12 },
	{	0x004A8068, 0x14 },
	{	0x004A817F, 0x12 },
	{	0x004A82D0, 0x14 },
	{	0x004A8314, 0x14 },
	{	0x004A85DE, 0x12 },
	{	0x004A871D, 0x12 },
	{	0x004A8765, 0x14 },
	{	0x004A881A, 0x14 },
	{	0x004A891A, 0x12 },
	{	0x004A8AEC, 0x14 },
	{	0x005A38BF, 0x20 },
	{	0x005A38C8, 0x24 },
	{	0x005A3A47, 0x24 },
	{	0x005BED3A, 0x04 },
	{	0x005BEDD5, 0x08 },
	{	0x005C003C, 0x00 },
	{	0x005C2CAE, 0x00 },
	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x004A594D, 0x00 },
	{	0x005A3AA2, 0x24 },
//	{	0x005BECB2, 0x08 },
	{	0x005BED69, 0x04 },
	{	0 },
};

// 1CB console cmds, 236 script cmds
// checked 0236
static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	// 004A3FA0
	{	0x004A40E7 + 2,	(UInt32)(-0x1000) + 1 },

	// 004A59A0
	{	0x004A59AA + 2,	(UInt32)(-0x1000) + 1 },
	{	0x004A59BD + 1,	(UInt32)(-0x1000) + 1 },
	{	0x004A59C9 + 2,	(UInt32)(-0x1000) + 1 },

	// 005A37E0
	{	0x005A3905 + 2, (UInt32)(-0x1000) + 1 },

	// 005B6CB0
	{	0x005B6D34 + 3,	1, 1 },

	// assert at 005BE920

	// 005BFB20
	{	0x005C002B + 1,	(UInt32)(-0x1000) + 1 },

	// 005C2480
	{	0x005C2CA0 + 2,	(UInt32)(-0x1000) + 1 },

	{	0 },
};

#else

#error unsupported cs version

#endif

#endif

static void ApplyPatch(const PatchLocation * patch, UInt32 newData)
{
	for(; patch->ptr; ++patch)
	{
		switch(patch->type)
		{
			case 0:
				SafeWrite32(patch->ptr, newData + patch->offset);
				break;

			case 1:
				SafeWrite16(patch->ptr, newData + patch->offset);
				break;
		}
	}
}

void ImportConsoleCommand(const char * name)
{
	CommandInfo	* info = g_consoleCommands.GetByName(name);
	if(info)
	{
		CommandInfo	infoCopy = *info;

		std::string	newName;

		newName = std::string("con_") + name;

		infoCopy.shortName = "";
		infoCopy.longName = _strdup(newName.c_str());	// this leaks but meh

		g_scriptCommands.Add(&infoCopy);

//		_MESSAGE("imported console command %s", name);
	}
	else
	{
		_WARNING("couldn't find console command (%s)", name);

		// pad it
		g_scriptCommands.Add(&kPaddingCommand);
	}
}

#define ADD_CMD(command) g_scriptCommands.Add(&kCommandInfo_ ## command )

void CommandTable::Init(void)
{
	g_consoleCommands.SetBaseID(0x0100);
	g_scriptCommands.SetBaseID(0x1000);

#ifdef RUNTIME

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0

	g_consoleCommands.Read((CommandInfo *)0x00F4F810, (CommandInfo *)0x00F517F0);
	g_scriptCommands.Read((CommandInfo *)0x00F51818, (CommandInfo *)0x00F57010);

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_0_15

	g_consoleCommands.Read((CommandInfo *)0x00F50810, (CommandInfo *)0x00F527F0);
	g_scriptCommands.Read((CommandInfo *)0x00F52818, (CommandInfo *)0x00F58010);

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35

	g_consoleCommands.Read((CommandInfo *)0x00F4F978, (CommandInfo *)0x00F51958);
	g_scriptCommands.Read((CommandInfo *)0x00F51980, (CommandInfo *)0x00F57218);

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6

	// yes, they ended up in the same place
	g_consoleCommands.Read((CommandInfo *)0x00F4F978, (CommandInfo *)0x00F51958);
	g_scriptCommands.Read((CommandInfo *)0x00F51980, (CommandInfo *)0x00F57218);

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b

	// yes, they ended up in the same place (again)
	g_consoleCommands.Read((CommandInfo *)0x00F4F978, (CommandInfo *)0x00F51958);
	g_scriptCommands.Read((CommandInfo *)0x00F51980, (CommandInfo *)0x00F57218);

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22

	g_consoleCommands.Read((CommandInfo *)0x00F52B70, (CommandInfo *)0x00F54B50);
	g_scriptCommands.Read((CommandInfo *)0x00F54B78, (CommandInfo *)0x00F5A438);

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6

	g_consoleCommands.Read((CommandInfo *)0x00F52B70, (CommandInfo *)0x00F54B50);
	g_scriptCommands.Read((CommandInfo *)0x00F54B78, (CommandInfo *)0x00F5A438);

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7

	g_consoleCommands.Read((CommandInfo *)0x00F52B70, (CommandInfo *)0x00F54B50);
	g_scriptCommands.Read((CommandInfo *)0x00F54B78, (CommandInfo *)0x00F5A438);

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng

	g_consoleCommands.Read((CommandInfo *)0x00F4FB70, (CommandInfo *)0x00F51B50);
	g_scriptCommands.Read((CommandInfo *)0x00F51B78, (CommandInfo *)0x00F57438);

#else

#error unsupported runtime version

#endif

#else

#if CS_VERSION == CS_VERSION_1_1_36

	g_consoleCommands.Read((CommandInfo *)0x00EAE440, (CommandInfo *)0x00EB0420);
	g_scriptCommands.Read((CommandInfo *)0x00EB0448, (CommandInfo *)0x00EB5CE0);

#elif CS_VERSION == CS_VERSION_1_5_19

	g_consoleCommands.Read((CommandInfo *)0x00EB04D0, (CommandInfo *)0x00EB24B0);
	g_scriptCommands.Read((CommandInfo *)0x00EB24D8, (CommandInfo *)0x00EB7D98);

#else

#error unsupported cs version

#endif

#endif

	// pad to opcode 0x1400 to give Bethesda lots of room
	g_scriptCommands.PadTo(kFoseOpCodeStart);

	// added in v1: 189 from 0x1400 to 0x14bd
	ADD_CMD(GetFOSEVersion);
	ADD_CMD(GetFOSERevision);
	ADD_CMD(tcmd);
	ADD_CMD(tcmd2);
	ADD_CMD(GetWeight);
	ADD_CMD(GetRepairList);
	ADD_CMD(GetWeaponAmmo);
	ADD_CMD(GetWeaponClipRounds);
	ADD_CMD(GetAttackDamage);
	ADD_CMD(GetWeaponType);
	ADD_CMD(GetWeaponMinSpread);
	ADD_CMD(GetWeaponSpread);
	ADD_CMD(GetWeaponProjectile);
	ADD_CMD(GetWeaponSightFOV);
	ADD_CMD(GetWeaponMinRange);
	ADD_CMD(GetWeaponMaxRange);
	ADD_CMD(GetWeaponAmmoUse);
	ADD_CMD(GetWeaponActionPoints);
	ADD_CMD(GetWeaponCritDamage);
	ADD_CMD(GetWeaponCritChance);
	ADD_CMD(GetWeaponCritEffect);
	ADD_CMD(GetEquipType);
	ADD_CMD(GetBaseObject);
	ADD_CMD(GetHealth);
	ADD_CMD(GetValue);
	ADD_CMD(GetWeaponFireRate);
	ADD_CMD(GetWeaponAnimAttackMult);
	ADD_CMD(GetWeaponRumbleLeftMotor);
	ADD_CMD(GetWeaponRumbleRightMotor);
	ADD_CMD(GetWeaponRumbleDuration);
	ADD_CMD(GetWeaponRumbleWavelength);
	ADD_CMD(GetWeaponAnimShotsPerSec);
	ADD_CMD(GetWeaponAnimReloadTime);
	ADD_CMD(GetWeaponAnimJamTime);
	ADD_CMD(GetWeaponSkill);
	ADD_CMD(GetWeaponResistType);
	ADD_CMD(GetWeaponFireDelayMin);
	ADD_CMD(GetWeaponFireDelayMax);
	ADD_CMD(ListGetCount);
	ADD_CMD(ListGetNthForm);
	ADD_CMD(ListAddForm);
	ADD_CMD(ListGetFormIndex);
	ADD_CMD(ListAddReference);
	ADD_CMD(SetWeaponClipRounds);
	ADD_CMD(SetWeaponMinSpread);
	ADD_CMD(SetWeaponSpread);
	ADD_CMD(SetWeaponSightFOV);
	ADD_CMD(SetWeaponMinRange);
	ADD_CMD(SetWeaponMaxRange);
	ADD_CMD(SetWeaponAmmoUse);	
	ADD_CMD(SetWeaponActionPoints);
	ADD_CMD(SetWeaponCritDamage);
	ADD_CMD(SetWeaponCritChance);
	ADD_CMD(SetWeaponCritEffect);
	ADD_CMD(SetWeight);
	ADD_CMD(PrintToConsole);
	ADD_CMD(DebugPrint);
	ADD_CMD(SetDebugMode);
	ADD_CMD(IsKeyPressed);
	ADD_CMD(TapKey);
	ADD_CMD(HoldKey);
	ADD_CMD(ReleaseKey);
	ADD_CMD(DisableKey);
	ADD_CMD(EnableKey);
	ADD_CMD(GetNumKeysPressed);
	ADD_CMD(GetKeyPress);
	ADD_CMD(GetNumMouseButtonsPressed);
	ADD_CMD(GetMouseButtonPress);
	ImportConsoleCommand("SetGameSetting");
	ImportConsoleCommand("SetINISetting");
	ImportConsoleCommand("GetINISetting");
	ImportConsoleCommand("SetCameraFOV");
	ImportConsoleCommand("RefreshINI");
	ImportConsoleCommand("Save");
	ImportConsoleCommand("SaveINI");
	ImportConsoleCommand("QuitGame");
	ImportConsoleCommand("LoadGame");
	ImportConsoleCommand("CloseAllMenus");
	ADD_CMD(GetControl);
	ADD_CMD(GetAltControl);
	ADD_CMD(SetWeaponAmmo);
	ADD_CMD(SetWeaponProjectile);
	ADD_CMD(SetRepairList);
	ADD_CMD(GetNumericGameSetting);
	ADD_CMD(SetNumericGameSetting);
	ADD_CMD(Label);
	ADD_CMD(Goto);
	ADD_CMD(CompareNames);
	ImportConsoleCommand("SetVel");
	ADD_CMD(GetEquippedObject);
	ADD_CMD(MenuTapKey);
	ADD_CMD(MenuReleaseKey);
	ADD_CMD(MenuHoldKey);
	ADD_CMD(DisableControl);
	ADD_CMD(EnableControl);
	ADD_CMD(TapControl);
	ADD_CMD(SetControl);
	ADD_CMD(SetAltControl);
	ADD_CMD(SetIsControl);
	ADD_CMD(IsControl);
	ADD_CMD(IsKeyDisabled);
	ADD_CMD(IsControlDisabled);
	ADD_CMD(AddSpellNS);
	ADD_CMD(GetWeaponAnimMult);
	ADD_CMD(GetWeaponReach);
	ADD_CMD(GetWeaponIsAutomatic);
	ADD_CMD(GetWeaponHandGrip);
	ADD_CMD(GetWeaponReloadAnim);
	ADD_CMD(GetWeaponBaseVATSChance);
	ADD_CMD(GetWeaponAttackAnimation);
	ADD_CMD(GetWeaponNumProjectiles);
	ADD_CMD(GetWeaponAimArc);
	ADD_CMD(GetWeaponLimbDamageMult);
	ADD_CMD(GetWeaponSightUsage);
	ADD_CMD(SetAttackDamage);
	ADD_CMD(SetWeaponAnimMult);
	ADD_CMD(SetWeaponReach);
	ADD_CMD(SetWeaponIsAutomatic);
	ADD_CMD(SetWeaponHandGrip);
	ADD_CMD(SetWeaponReloadAnim);
	ADD_CMD(SetWeaponBaseVATSChance);
	ADD_CMD(SetWeaponAttackAnimation);
	ADD_CMD(SetWeaponNumProjectiles);
	ADD_CMD(SetWeaponAimArc);
	ADD_CMD(SetWeaponLimbDamageMult);
	ADD_CMD(SetWeaponSightUsage);
	ADD_CMD(GetNumericIniSetting);
	ADD_CMD(SetNumericIniSetting);
	ADD_CMD(GetModIndex);
	ADD_CMD(GetNumLoadedMods);
	ADD_CMD(GetSourceModIndex);
	ADD_CMD(IsModLoaded);
	ADD_CMD(GetCrosshairRef);
	ADD_CMD(SetName);
	ADD_CMD(TempCloneForm);
	ADD_CMD(IsClonedForm);
	ADD_CMD(IsScripted);
	ADD_CMD(GetScript);
	ADD_CMD(RemoveScript);
	ADD_CMD(SetScript);
	ADD_CMD(GetObjectEffect);
	ADD_CMD(GetWeaponHasScope);
	ADD_CMD(IsControlPressed);
	ADD_CMD(ListRemoveNthForm);
	ADD_CMD(ListRemoveForm);
	ADD_CMD(GetEquippedCurrentHealth);
	ADD_CMD(SetEquippedCurrentHealth);
	ADD_CMD(GetType);
	ADD_CMD(GetDebugMode);
	ADD_CMD(GetParentCell);
	ADD_CMD(Exp);
	ADD_CMD(Log10);
	ADD_CMD(Floor);
	ADD_CMD(Ceil);
	ADD_CMD(LeftShift);
	ADD_CMD(RightShift);
	ADD_CMD(LogicalAnd);
	ADD_CMD(LogicalOr);
	ADD_CMD(LogicalXor);
	ADD_CMD(LogicalNot);
	ADD_CMD(fmod);
	ADD_CMD(GetArmorAR);
	ADD_CMD(IsFormValid);
	ADD_CMD(IsReference);
	ADD_CMD(IsPowerArmor);
	ADD_CMD(SetIsPowerArmor);
	ADD_CMD(GetOpenKey);
	ADD_CMD(SetOpenKey);
	ADD_CMD(GetGameLoaded);
	ADD_CMD(GetGameRestarted);
	ADD_CMD(SetWeaponType);
	ADD_CMD(SetWeaponAnimAttackMult);
	ADD_CMD(GetHotkeyItem);
	ADD_CMD(GetTeleportCell);
	ADD_CMD(GetLinkedDoor);
	ADD_CMD(GetFirstRef);
	ADD_CMD(GetNextRef);
	ADD_CMD(GetNumRefs);
	ADD_CMD(GetFirstRefInCell);
	ADD_CMD(GetNumRefsInCell);
	ADD_CMD(GetUIFloat);
	ADD_CMD(SetUIFloat);
	ADD_CMD(SetUIString);
	ADD_CMD(ListReplaceNthForm);
	ADD_CMD(ListReplaceForm);
	ADD_CMD(GetParentWorldspace);
	ADD_CMD(PrintActiveTile);
	ADD_CMD(SetBaseItemValue);
	ADD_CMD(SetHealth);
	ADD_CMD(GetFOSEBeta);

	// v2 - starts at 0x14be
	ADD_CMD(GetCurrentHealth);
	ADD_CMD(SetCurrentHealth);
	ADD_CMD(Rand);
	ADD_CMD(GetNumItems);
	ADD_CMD(GetInventoryObject);
	ADD_CMD(GetRefCount);
	ADD_CMD(SetRefCount);
	ADD_CMD(Pow);
	ADD_CMD(IsQuestItem);
	ADD_CMD(SetQuestItem);
	ADD_CMD(IsOffLimits);
	ADD_CMD(GetParentCellOwner);
	ADD_CMD(GetOwner);
	ADD_CMD(GetOwningFactionRequiredRank);
	ADD_CMD(GetParentCellOwningFactionRequiredRank);
	ADD_CMD(GetCurrentQuest);
	ADD_CMD(GetCurrentObjective);
	ADD_CMD(GetQuestObjectiveCount);
	ADD_CMD(GetNthQuestObjective);
	ADD_CMD(SetCurrentQuest);
	ADD_CMD(IsPersistent);
	ADD_CMD(SetEyes);
	ADD_CMD(SetHair);
	ADD_CMD(SetHairLength);
	ADD_CMD(GetEyes);
	ADD_CMD(GetHair);
	ADD_CMD(GetHairLength);

#ifdef _DEBUG
//	ADD_CMD(CloneForm);
	ADD_CMD(ModelPathIncludes);
	/*
	ImportConsoleCommand("SetFog");
	ImportConsoleCommand("SetClipDist");
	ImportConsoleCommand("SetImageSpaceGlow");
	ImportConsoleCommand("ToggleDetection");
	ImportConsoleCommand("SexChange");
	ImportConsoleCommand("HairTint");
	ImportConsoleCommand("SetTargetRefraction");
	ImportConsoleCommand("SetTargetRefractionFire");
	ImportConsoleCommand("SetSkyParam");
	ImportConsoleCommand("RunMemoryPass");
	ImportConsoleCommand("ModWaterShader");
	ImportConsoleCommand("WaterShallowColor");
	ImportConsoleCommand("WaterDeepColor");
	ImportConsoleCommand("WaterReflectionColor");
	ImportConsoleCommand("SetGamma");
	ImportConsoleCommand("SetHDRParam");
	ImportConsoleCommand("TCL");
	ImportConsoleCommand("ToggleAI");
	ImportConsoleCommand("ToggleCombatAI");
	ImportConsoleCommand("ToggleMenus");
	ImportConsoleCommand("CAL");
	ImportConsoleCommand("TGM");
	ImportConsoleCommand("TFC");
	ImportConsoleCommand("PlayerSpellBook");
	ImportConsoleCommand("ToggleMapMarkers");
	ImportConsoleCommand("Show1stPerson");
	ImportConsoleCommand("ToggleFreeCamera");
*/
#endif

#ifdef _DEBUG
	ADD_CMD(sWTF);
	ADD_CMD(tcmd3);
	ADD_CMD(tcmd4);
	ADD_CMD(tcmd5);
	ADD_CMD(DumpDocs);
#endif

	// register plugins
	g_pluginManager.Init();

	// patch the code
	ApplyPatch(kPatch_ScriptCommands_Start, (UInt32)g_scriptCommands.GetStart());
	ApplyPatch(kPatch_ScriptCommands_End, (UInt32)g_scriptCommands.GetEnd());
	ApplyPatch(kPatch_ScriptCommands_MaxIdx, g_scriptCommands.GetMaxID());

	_MESSAGE("max id = %08X", g_scriptCommands.GetMaxID());

	_MESSAGE("console commands");
	g_consoleCommands.Dump();
	_MESSAGE("script commands");
	g_scriptCommands.Dump();

	_MESSAGE("patched");
}

void CommandTable::Read(CommandInfo * start, CommandInfo * end)
{
	UInt32	numCommands = end - start;
	m_commands.reserve(m_commands.size() + numCommands);

	for(; start != end; ++start)
		Add(start);
}

void CommandTable::Add(CommandInfo * info, CommandReturnType retnType, UInt32 parentPluginOpcodeBase)
{
	UInt32	backCommandID = m_baseID + m_commands.size();	// opcode of the next command to add

	info->opcode = m_curID;

	if(m_curID == backCommandID)
	{
		// adding at the end?
		m_commands.push_back(*info);
	}
	else if(m_curID < backCommandID)
	{
		// adding to existing data?
		ASSERT(m_curID >= m_baseID);

		m_commands[m_curID - m_baseID] = *info;
	}
	else
	{
		HALT("CommandTable::Add: adding past the end");
	}

	m_curID++;

	CommandMetadata * metadata = &m_metadata[info->opcode];

	metadata->parentPlugin = parentPluginOpcodeBase;
	metadata->returnType = retnType;
}

bool CommandTable::Replace(UInt32 opcodeToReplace, CommandInfo* replaceWith)
{
	for (CommandList::iterator iter = m_commands.begin(); iter != m_commands.end(); ++iter)
	{
		if (iter->opcode == opcodeToReplace)
		{
			*iter = *replaceWith;
			iter->opcode = opcodeToReplace;
			return true;
		}
	}

	return false;
}


void CommandTable::PadTo(UInt32 id, CommandInfo * info)
{
	if(!info) info = &kPaddingCommand;

	while(m_baseID + m_commands.size() < id)
	{
		info->opcode = m_baseID + m_commands.size();
		m_commands.push_back(*info);
	}

	m_curID = id;
}

void CommandTable::Dump(void)
{
	for(CommandList::iterator iter = m_commands.begin(); iter != m_commands.end(); ++iter)
	{
		_MESSAGE("%08X %04X %s %s", iter->opcode, iter->needsParent, iter->longName, iter->shortName);
//		_MESSAGE("\t%08X %08X %08X %08X %08X %s", iter->params, iter->execute, iter->parse, iter->eval, iter->flags, iter->longName);
		gLog.Indent();

#if 0
		for(UInt32 i = 0; i < iter->numParams; i++)
		{
			ParamInfo	* param = &iter->params[i];
			_MESSAGE("%08X %08X %s", param->typeID, param->isOptional, param->typeStr);
		}
#endif

		gLog.Outdent();
	}
}

void CommandTable::DumpAlternateCommandNames(void)
{
	for (CommandList::iterator iter= m_commands.begin(); iter != m_commands.end(); ++iter)
	{
		if (iter->shortName)
			_MESSAGE("%s", iter->shortName);
	}
}

const char* StringForParamType(UInt32 paramType)
{
	switch(paramType) {
		case kParamType_String: return "String";
		case kParamType_Integer: return "Integer";
		case kParamType_Float: return "Float";
		case kParamType_InventoryObject: return "InventoryObject";
		case kParamType_ObjectRef: return "ObjectRef";
		case kParamType_ActorValue: return "ActorValue";
		case kParamType_Actor: return "Actor";
		case kParamType_SpellItem: return "SpellItem";
		case kParamType_Axis: return "Axis";
		case kParamType_Cell: return "Cell";
		case kParamType_AnimationGroup: return "AnimationGroup";
		case kParamType_MagicItem: return "MagicItem";
		case kParamType_Sound: return "Sound";
		case kParamType_Topic: return "Topic";
		case kParamType_Quest: return "Quest";
		case kParamType_Race: return "Race";
		case kParamType_Class: return "Class";
		case kParamType_Faction: return "Faction";
		case kParamType_Sex: return "Sex";
		case kParamType_Global: return "Global";
		case kParamType_Furniture: return "Furniture";
		case kParamType_TESObject: return "Object";
		case kParamType_VariableName: return "VariableName";
		case kParamType_QuestStage: return "QuestStage";
		case kParamType_MapMarker: return "MapMarker";
		case kParamType_ActorBase: return "ActorBase";
		case kParamType_Container: return "Container";
		case kParamType_WorldSpace: return "WorldSpace";
		case kParamType_CrimeType: return "CrimeType";
		case kParamType_AIPackage: return "AIPackage";
		case kParamType_CombatStyle: return "CombatStyle";
		case kParamType_MagicEffect: return "MagicEffect";
		case kParamType_FormType: return "FormType";
		case kParamType_WeatherID: return "WeatherID";
		case kParamType_NPC: return "NPC";
		case kParamType_Owner: return "Owner";
		case kParamType_EffectShader: return "EffectShader";
		case kParamType_FormList: return "FormList";
		case kParamType_MenuIcon: return "MenuIcon";
		case kParamType_Perk: return "Perk";
		case kParamType_Note: return "Note";
		case kParamType_MiscellaneousStat: return "MiscStat";
		case kParamType_IdleForm: return "IdleForm";
		case kParamType_Message: return "Message";
		case kParamType_InvObjOrFormList: return "InvObjOrFormList";
		case kParamType_Alignment: return "Alignment";
		case kParamType_EquipType: return "EquipType";
		case kParamType_NonInvObjOrFormList: return "NonInvObjOrFormList";
		case kParamType_Music: return "Music";
		case kParamType_CriticalStage: return "CriticalStage";
		default: return "<unknown>";
	}
}

void CommandTable::DumpCommandDocumentation(UInt32 startWithID)
{
	_MESSAGE("FOSE Commands from: %#x", startWithID);

	_MESSAGE("<br><b>Function Quick Reference</b>");
	CommandList::iterator itEnd = m_commands.end();
	for (CommandList::iterator iter = m_commands.begin();iter != itEnd; ++iter) {
		if (iter->opcode >= startWithID) {
			iter->DumpFunctionDef();
		}
	}

	_MESSAGE("<hr><br><b>Functions In Detail</b>");
	for (CommandList::iterator iter = m_commands.begin();iter != itEnd; ++iter) {
		if (iter->opcode >= startWithID) {
			iter->DumpDocs();
		}
	}
}

CommandInfo * CommandTable::GetByName(const char * name)
{
	for(CommandList::iterator iter = m_commands.begin(); iter != m_commands.end(); ++iter)
		if(!_stricmp(name, iter->longName) || (iter->shortName && !_stricmp(name, iter->shortName)))
			return &(*iter);

	return NULL;
}

CommandTable	g_consoleCommands;
CommandTable	g_scriptCommands;
//CommandTable	g_tokenCommands;

void CommandInfo::DumpDocs() const
{
	_MESSAGE("<p><a name=\"%s\"></a><b>%s</b> ", longName, longName);
	_MESSAGE("<br><b>Alias:</b> %s<br><b>Parameters:</b>%d", (strlen(shortName) != 0) ? shortName : "none", numParams);
	if (numParams > 0) {
		for(UInt32 i = 0; i < numParams; i++)
		{
			ParamInfo	* param = &params[i];
			const char* paramTypeName = StringForParamType(param->typeID);
			if (param->isOptional != 0) {
				_MESSAGE("<br>&nbsp;&nbsp;&nbsp;<i>%s:%s</i> ", param->typeStr, paramTypeName);
			} else {
				_MESSAGE("<br>&nbsp;&nbsp;&nbsp;%s:%s ", param->typeStr, paramTypeName);
			}
		}
	}
	_MESSAGE("<br><b>Return Type:</b> FixMe<br><b>Opcode:</b> %#4x (%d)<br><b>Condition Function:</b> %s<br><b>Description:</b> %s</p>", opcode, opcode, eval ? "Yes" : "No",helpText);
}

void CommandInfo::DumpFunctionDef() const
{
	_MESSAGE("<br>(FixMe) %s<a href=\"#%s\">%s</a> ", needsParent > 0 ? "reference." : "", longName, longName);
	if (numParams > 0) {
		for(UInt32 i = 0; i < numParams; i++)
		{
			ParamInfo	* param = &params[i];
			const char* paramTypeName = StringForParamType(param->typeID);
			if (param->isOptional != 0) {
				_MESSAGE("<i>%s:%s</i> ", param->typeStr, paramTypeName);
			} else {
				_MESSAGE("%s:%s ", param->typeStr, paramTypeName);
			}
		}
	}
}

CommandInfo* CommandTable::GetByOpcode(UInt32 opcode)
{
	// could do binary search here but padding command has opcode 0
	for (CommandList::iterator iter = m_commands.begin(); iter != m_commands.end(); ++iter)
		if (iter->opcode == opcode)
			return &(*iter);

	return NULL;
}

CommandReturnType CommandTable::GetReturnType(const CommandInfo* cmd)
{
	CommandMetadata * metadata = NULL;
	if (cmd)
		metadata = &m_metadata[cmd->opcode];
	if (metadata)
		return metadata->returnType;
	return kRetnType_Default;
}

void CommandTable::SetReturnType(UInt32 opcode, CommandReturnType retnType)
{
	CommandInfo* cmdInfo = GetByOpcode(opcode);
	if (!cmdInfo)
		_MESSAGE("CommandTable::SetReturnType() - cannot locate command with opcode %04X", opcode);
	else {
		CommandMetadata * metadata = &m_metadata[opcode];
		if (metadata)
			metadata->returnType = retnType;
	}
}

void CommandTable::RecordReleaseVersion(void)
{
	m_opcodesByRelease.push_back(GetCurID());
}

UInt32 CommandTable::GetRequiredFOSEVersion(const CommandInfo* cmd)
{
	UInt32  ver = 0;
	if (cmd) {
		if (cmd->opcode < m_opcodesByRelease[0])	// vanilla cmd
			ver = 0;
		else if (cmd->opcode >= kFoseOpCodeTest)	// plugin cmd, we have no way of knowing
			ver = -1;
		else {
			for (UInt32 i = 0; i < m_opcodesByRelease.size(); i++) {
				if (cmd->opcode >= m_opcodesByRelease[i]) {
					ver = i;
				}
				else {
					break;
				}
			}
		}
	}

	return ver;
}

void CommandTable::RemoveDisabledPlugins(void)
{
	for (CommandList::iterator iter = m_commands.begin(); iter != m_commands.end(); ++iter)
	{
		CommandMetadata * metadata = &m_metadata[iter->opcode];
		if (metadata)
			// plugin failed to load but still registered some commands?
			// realistically the game is going to go down hard if this happens anyway
			if(g_pluginManager.LookupHandleFromBaseOpcode(metadata->parentPlugin) == kPluginHandle_Invalid)
				Replace(iter->opcode, &kPaddingCommand);
	}
}

static char * kFOSEname = "NVSE";

static PluginInfo g_FOSEPluginInfo =
{
	PluginInfo::kInfoVersion,
	kFOSEname,
	FOSE_VERSION_INTEGER,
};

PluginInfo * CommandTable::GetParentPlugin(const CommandInfo * cmd)
{
	if (!cmd->opcode || cmd->opcode<kFoseOpCodeStart)
		return NULL;

	if (cmd->opcode < kFoseOpCodeTest)
		return &g_FOSEPluginInfo;

	CommandMetadata * metadata = &m_metadata[cmd->opcode];
	if (metadata) {
		PluginInfo	* info = g_pluginManager.GetInfoFromBase(metadata->parentPlugin);
		if (info)
			return info;
	}
	return NULL;
}


namespace PluginAPI {
	const CommandInfo* GetCmdTblStart() { return g_scriptCommands.GetStart(); }
	const CommandInfo* GetCmdTblEnd() { return g_scriptCommands.GetEnd(); }
	const CommandInfo* GetCmdByOpcode(UInt32 opcode) { return g_scriptCommands.GetByOpcode(opcode); }
	const CommandInfo* GetCmdByName(const char* name) { return g_scriptCommands.GetByName(name); }
	UInt32 GetCmdRetnType(const CommandInfo* cmd) { return g_scriptCommands.GetReturnType(cmd); }
	UInt32 GetReqVersion(const CommandInfo* cmd) { return g_scriptCommands.GetRequiredFOSEVersion(cmd); }
	const PluginInfo* GetCmdParentPlugin(const CommandInfo* cmd) { return g_scriptCommands.GetParentPlugin(cmd); }
}
