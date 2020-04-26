#include "GameAPI.h"
#include "GameRTTI.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameData.h"

#ifdef RUNTIME

// arg1 = 1, ignored if canCreateNew is false, passed to 'init' function if a new object is created
typedef void * (* _GetSingleton)(bool canCreateNew);

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x00516750;
const _Fallout_DynamicCast Fallout_DynamicCast = (_Fallout_DynamicCast)0x00BFAB0A;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401010;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x00454CC0;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x00629440;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_0_15

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x005157E0;
const _Fallout_DynamicCast Fallout_DynamicCast = (_Fallout_DynamicCast)0x00BFACAA;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401010;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x00454600;
const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x0043C610;

const UInt32* g_TlsIndexPtr = (UInt32*)0x01176A44;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x00629180;

DataHandler ** g_dataHandler = (DataHandler **)0x01069D4C;
TESSaveLoadGame ** g_saveLoadGame = (TESSaveLoadGame **)0x01076BDC;
SaveGameManager ** g_saveGameManager = (SaveGameManager**)0x01076934;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x00518020;
const _Fallout_DynamicCast Fallout_DynamicCast = (_Fallout_DynamicCast)0x00BFF4DA;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401010;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x00455570;
const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x0043D260;

const UInt32* g_TlsIndexPtr = (UInt32*)0x011767F4;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x0062BB80;

DataHandler ** g_dataHandler = (DataHandler **)0x01069ACC;
TESSaveLoadGame ** g_saveLoadGame = (TESSaveLoadGame **)0x010769A4;
SaveGameManager ** g_saveGameManager = (SaveGameManager**)0x010766FC;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x00517A80;
const _Fallout_DynamicCast Fallout_DynamicCast = (_Fallout_DynamicCast)0x00BFFADA;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401010;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x004550F0;
const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x0043CD00;

const UInt32* g_TlsIndexPtr = (UInt32*)0x011768F4;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x0062BB30;

DataHandler ** g_dataHandler = (DataHandler **)0x01069BCC;
TESSaveLoadGame ** g_saveLoadGame = (TESSaveLoadGame **)0x01076AA4;
SaveGameManager ** g_saveGameManager = (SaveGameManager**)0x010767FC;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x00517F90;
const _Fallout_DynamicCast Fallout_DynamicCast = (_Fallout_DynamicCast)0x00BFFA6A;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401010;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x00455350;
const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x0043CFC0;

const UInt32* g_TlsIndexPtr = (UInt32*)0x011768F4;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x0062C230;

DataHandler ** g_dataHandler = (DataHandler **)0x01069BCC;
TESSaveLoadGame ** g_saveLoadGame = (TESSaveLoadGame **)0x01076AA4;
SaveGameManager ** g_saveGameManager = (SaveGameManager**)0x010767FC;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x005181C0;
const _Fallout_DynamicCast Fallout_DynamicCast = (_Fallout_DynamicCast)0x00C0047A;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401010;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x004551F0;
const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x0043CE40;

const UInt32* g_TlsIndexPtr = (UInt32*)0x01179AF4;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x0062BEA0;

DataHandler ** g_dataHandler = (DataHandler **)0x0106CDCC;
TESSaveLoadGame ** g_saveLoadGame = (TESSaveLoadGame **)0x01079CA4;
SaveGameManager ** g_saveGameManager = (SaveGameManager**)0x010799FC;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x00517790;
const _Fallout_DynamicCast Fallout_DynamicCast = (_Fallout_DynamicCast)0x00C004FA;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401010;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x004550C0;
const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x0043CD00;

const UInt32* g_TlsIndexPtr = (UInt32*)0x01179AF4;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x0062B590;

DataHandler ** g_dataHandler = (DataHandler **)0x0106CDCC;
TESSaveLoadGame ** g_saveLoadGame = (TESSaveLoadGame **)0x01079CA4;
SaveGameManager ** g_saveGameManager = (SaveGameManager**)0x010799FC;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x00517950;
const _Fallout_DynamicCast Fallout_DynamicCast = (_Fallout_DynamicCast)0x00C0050A;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401010;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x00455190;
const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x0043CDA0;

const UInt32* g_TlsIndexPtr = (UInt32*)0x01179AF4;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x0062B5D0;

DataHandler ** g_dataHandler = (DataHandler **)0x0106CDCC;
TESSaveLoadGame ** g_saveLoadGame = (TESSaveLoadGame **)0x01079CA4;
SaveGameManager ** g_saveGameManager = (SaveGameManager**)0x010799FC;

const _GetActorValueName GetActorValueName = (_GetActorValueName)0x0005A2370;	// See Cmd_GetActorValue_Eval

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x00517F80;
const _Fallout_DynamicCast Fallout_DynamicCast = (_Fallout_DynamicCast)0x00BFD4DA;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401010;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x00455270;
const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x0043CD10;

const UInt32* g_TlsIndexPtr = (UInt32*)0x01176AF4;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x0062B8D0;

DataHandler ** g_dataHandler = (DataHandler **)0x01069DCC;
TESSaveLoadGame ** g_saveLoadGame = (TESSaveLoadGame **)0x01076CA4;
SaveGameManager ** g_saveGameManager = (SaveGameManager**)0x010769FC;

const _GetActorValueName GetActorValueName = (_GetActorValueName)0x005A2CC0;	// See Cmd_GetActorValue_Eval

#else

#error unsupported runtime version

#endif

#endif

UInt32 AddFormToDataHandler(TESForm * form)
{
	return CALL_MEMBER_FN(*g_dataHandler, DoAddForm)(form);
}

UInt32 AddFormToCreatedBaseObjectsList(TESForm* form)
{
	return CALL_MEMBER_FN(*g_saveLoadGame, AddCreatedForm)(form);
}

TESSaveLoadGame* TESSaveLoadGame::GetSingleton()
{
	return *g_saveLoadGame;
}

SaveGameManager* SaveGameManager::GetSingleton()
{
	return *g_saveGameManager;
}

std::string GetSavegamePath()
{
	char path[0x104];
	CALL_MEMBER_FN(SaveGameManager::GetSingleton(), ConstructSavegamePath)(path);
	return path;
}

ConsoleManager * ConsoleManager::GetSingleton(void)
{
	return (ConsoleManager *)ConsoleManager_GetSingleton(true);
}

void Console_Print(const char * fmt, ...)
{
	ConsoleManager	* mgr = ConsoleManager::GetSingleton();
	if(mgr)
	{
		va_list	args;

		va_start(args, fmt);

		CALL_MEMBER_FN(mgr, Print)(fmt, args);

		va_end(args);
	}
}

const char * GetFullName(TESForm * baseForm)
{
	if(baseForm)
	{
		TESFullName* fullName = baseForm->GetFullName();
		if(fullName && fullName->name.m_data)
		{
			if (fullName->name.m_dataLen)
				return fullName->name.m_data;
		}
	}

	return "<no name>";
}

#if 1

void ScriptEventList::Dump(void)
{
	UInt32 nEvents = m_eventList->Count();

	for(SInt32 n = 0; n < nEvents; ++n)
	{
		Event* pEvent = m_eventList->GetNthItem(n);
		if(pEvent)
		{
			Console_Print("%08X (%s) %08X", pEvent->object, GetObjectClassName(pEvent->object), pEvent->eventMask);
		}
	}
}

UInt32 ScriptEventList::ResetAllVariables()
{
	UInt32 numVars = 0;
	for (VarEntry * entry = m_vars; entry; entry = entry->next)
		if (entry->var)
		{
			entry->var->data = 0.0;
			numVars++;
		}

	return numVars;
}

ScriptEventList::Var * ScriptEventList::GetVariable(UInt32 id)
{
	for(VarEntry * entry = m_vars; entry; entry = entry->next)
		if(entry->var && entry->var->id == id)
			return entry->var;

	return NULL;
}


static void ConvertLiteralPercents(std::string* str)
{
	UInt32 idx = 0;
	while ((idx = str->find('%', idx)) != -1)
	{
		str->insert(idx, "%");
		idx += 2;
	}
}

static void SkipArgs(UInt8* &scriptData)
{
	switch (*scriptData)
	{
	case 'z':
		scriptData += sizeof(double) + 1;
		break;
	case 'r':
		scriptData += 6;
		break;
	default:
		scriptData += 3;
		break;
	}
}

static void OmitFormatStringArgs(std::string str, FormatStringArgs& args)
{
	//skip any args omitted by the %{ specifier
	UInt32 strIdx = 0;
	while ((strIdx = str.find('%', strIdx)) != -1 && args.HasMoreArgs())
	{
		switch(str[++strIdx])
		{
		case '%':
		case 'q':
		case 'Q':
		case 'r':
		case 'R':
			break;
		case 'c':
		case 'C':
			args.SkipArgs(2);
			break;
		default:
			args.SkipArgs(1);
		}
		strIdx++;
	}
}

//static bool ExtractFormattedString(UInt32 &numArgs, char* buffer, UInt8* &scriptData, Script* scriptObj, ScriptEventList* eventList)
bool ExtractFormattedString(FormatStringArgs& args, char* buffer)
{
	//extracts args based on format string, prints formatted string to buffer
	static const int maxArgs = 20;
	double f[maxArgs] = {0.0};
	UInt32 argIdx = 0;

	std::string fmtString = args.GetFormatString();
	UInt32 strIdx = 0;

	//extract args
	while ((strIdx = fmtString.find('%', strIdx)) != -1)
	{
		char argType = fmtString.at(strIdx+1);
		switch (argType)
		{
		case '%':										//literal %
			strIdx += 2;
			break;
//		case 'z':
//		case 'Z':										//string variable
//			{
//				fmtString.erase(strIdx, 2);
//				double strID = 0;
//				if (!args.Arg(args.kArgType_Float, &strID))
//					return false;
//
//				const char* toInsert = NULL;
//#if OBSE_CORE
//				StringVar* insStr = NULL;
//				insStr = g_StringMap.Get(strID);
//
//				if (insStr)
//					toInsert = insStr->GetCString();
//#else			// called from a plugin command
//				if (s_StringVarInterface)
//					toInsert = s_StringVarInterface->GetString(strID);
//#endif
//				if (toInsert)
//					fmtString.insert(strIdx, toInsert);
//				else
//					fmtString.insert(strIdx, "NULL");
//			}
//			break;
		case 'r':										//newline
		case 'R':
			fmtString.erase(strIdx, 2);
			fmtString.insert(strIdx, "\n");
			break;
		case 'e':
		case 'E':										//workaround for CS not accepting empty strings
			fmtString.erase(strIdx, 2);
			break;
		case 'a':
		case 'A':										//character specified by ASCII code
			{
				fmtString.erase(strIdx, 2);
				double fCharCode = 0;
				if (args.Arg(args.kArgType_Float, &fCharCode))
					fmtString.insert(strIdx, 1, (char)fCharCode);
				else
					return false;
			}
			break;
		case 'n':										// name of obj/ref
		case 'N':
			{
				fmtString.erase(strIdx, 2);
				TESForm* form = NULL;
				if (!args.Arg(args.kArgType_Form, &form))
					return false;

				std::string strName(GetFullName(form));
				ConvertLiteralPercents(&strName);
				fmtString.insert(strIdx, strName);
				strIdx += strName.length();
			}
			break;
		case 'i':											//formID
		case 'I':
			{
				fmtString.erase(strIdx, 2);
				TESForm* form = NULL;
				if (!(args.Arg(args.kArgType_Form, &form)))
					return false;
				else if (!form)
					fmtString.insert(strIdx, "00000000");
				else
				{			
					char formID[9];
					sprintf_s(formID, 9, "%08X", form->refID);
					fmtString.insert(strIdx, formID);
				}
			}
			break;
		case 'c':											//named component of another object
		case 'C':											//2 args - object and index
			{
				TESForm* form = NULL;
				if (!args.Arg(args.kArgType_Form, &form))
					return false;

				fmtString.erase(strIdx, 2);
				if (!form)
					fmtString.insert(strIdx, "NULL");
				else
				{
					double objIdx = 0;
					if (!args.Arg(args.kArgType_Float, &objIdx))
						return false;
					else
					{
						std::string strName("");
						switch (form->typeID)
						{
						case kFormType_Spell:
						case kFormType_Enchantment:
						case kFormType_Ingredient:
						case kFormType_AlchemyItem:
							{
								MagicItem* magItm = DYNAMIC_CAST(form, TESForm, MagicItem);
								if (!magItm)
									strName = "NULL";
								else
								{
									strName = magItm->list.GetNthEIName(objIdx);
									EffectItem* effItem = magItm->list.ItemAt(objIdx);
									//if (effItem && effItem->HasActorValue())
									//{
									//	UInt32 valIdx = strName.find(' ');
									//	if (valIdx != -1)
									//	{
									//		strName.erase(valIdx + 1, strName.length() - valIdx);
									//		strName.insert(valIdx + 1, std::string(GetActorValueString(effItem->actorValueOrOther)));
									//	}
									//}
								}
								break;
							}
						//case kFormType_Faction:
						//	{
						//		TESFaction* fact = DYNAMIC_CAST(form, TESForm, TESFaction);
						//		if (!fact)
						//			strName = "NULL";
						//		else
						//		{
						//			strName = fact->GetNthRankName(objIdx);
						//		}
						//		break;
						//	}
						default:
							strName = "unknown";
						}
						ConvertLiteralPercents(&strName);
						fmtString.insert(strIdx, strName);
						strIdx += strName.length();
					}
				}
				}
				break;
		//case 'k':
		//case 'K':											//DX code
		//	{
		//		double keycode = 0;
		//		fmtString.erase(strIdx, 2);
		//		if (!args.Arg(args.kArgType_Float, &keycode))
		//			return false;

		//		const char* desc = GetDXDescription(keycode);
		//		fmtString.insert(strIdx, desc);

		//	}
		//	break;
		case 'v':
		case 'V':											//actor value
			{
				double actorVal = eActorVal_FalloutMax;
				fmtString.erase(strIdx, 2);
				if (!args.Arg(args.kArgType_Float, &actorVal))
					return false;

				std::string valStr(GetActorValueString(actorVal));
				if (valStr.length())
				{
					for (UInt32 idx = 1; idx < valStr.length(); idx++)
						if (isupper(valStr[idx]))
						{								//insert spaces to make names more presentable
							valStr.insert(idx, " ");
							idx += 2;
						}
				}
				fmtString.insert(strIdx, valStr);
			}
			break;
		case 'p':
		case 'P':											//pronouns
			{
				fmtString.erase(strIdx, 2);
				char pronounType = fmtString[strIdx];
				fmtString.erase(strIdx, 1);
				TESForm* form = NULL;
				if (!args.Arg(args.kArgType_Form, &form))
					return false;

				if (!form)
					fmtString.insert(strIdx, "NULL");
				else
				{			
					TESObjectREFR* refr = DYNAMIC_CAST(form, TESForm, TESObjectREFR);
					if (refr)
						form = refr->baseForm;

					short objType = 0;
					if (form->typeID == kFormType_NPC)
					{
						TESActorBaseData* actorBase = DYNAMIC_CAST(form, TESForm, TESActorBaseData);
						objType = (actorBase->IsFemale()) ? 2 : 1;
					}

					switch (pronounType)
					{
					case 'o':
					case 'O':
						if (objType == 1)
							fmtString.insert(strIdx, "him");
						else if (objType == 2)
							fmtString.insert(strIdx, "her");
						else
							fmtString.insert(strIdx, "it");
						break;
					case 's':
					case 'S':
						if (objType == 1)
							fmtString.insert(strIdx, "he");
						else if (objType == 2)
							fmtString.insert(strIdx, "she");
						else
							fmtString.insert(strIdx, "it");
						break;
					case 'p':
					case 'P':
						if (objType == 1)
							fmtString.insert(strIdx, "his");
						else if (objType == 2)
							fmtString.insert(strIdx, "her");
						else
							fmtString.insert(strIdx, "its");
						break;
					default:
						fmtString.insert(strIdx, "NULL");
					}
				}
			}
			break;
		case 'q':
		case 'Q':											//double quote
			fmtString.erase(strIdx, 2);
			fmtString.insert(strIdx, "\"");
			break;
		case '{':											//omit portion of string based on flag param
			{
				fmtString.erase(strIdx, 2);
				double flag = 0;
				if (!args.Arg(args.kArgType_Float, &flag))
					return false;

				UInt32 omitEnd = fmtString.find("%}", strIdx);
				if (omitEnd == -1)
					omitEnd = fmtString.length();

				if (!flag)
				{
					OmitFormatStringArgs(fmtString.substr(strIdx, omitEnd - strIdx), args);
					fmtString.erase(strIdx, omitEnd - strIdx + 2);
				}
				else
					fmtString.erase(omitEnd, 2);
			}
			break;
		case '}':											//in case someone left a stray closing bracket
			fmtString.erase(strIdx, 2);
			break;
		case 'x':											//hex
		case 'X':
			{
				double data = 0;
				if (!args.Arg(args.kArgType_Float, &data))
					return false;

				UInt64* hexArg = (UInt64*)(&f[argIdx++]);
				*hexArg = data;
				fmtString.erase(strIdx, 2);
				char width = 0;
				if (strIdx < fmtString.length())
				{
					if (isdigit(fmtString[strIdx]))	//single-digit width specifier optionally follows %x
					{
						width = fmtString[strIdx];
						fmtString.erase(strIdx, 1);
					}
				}
				fmtString.insert(strIdx, "%0llX");
				if (width)
					fmtString.insert(strIdx + 2, 1, width);
				strIdx++;
			}
			break;
		default:											//float
			{
				double data = 0;
				if (!args.Arg(args.kArgType_Float, &data))
					return false;

				f[argIdx++] = data;
				strIdx++;
			}
		}
	}

	if (sprintf_s(buffer, kMaxMessageLength - 2, fmtString.c_str(), f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7], f[8], f[9], f[10], f[11], f[12], f[13], f[14], f[15], f[16], f[17], f[18], f[19]) > 0)
	{
		buffer[kMaxMessageLength-1] = '\0';
		return true;
	}
	else if (fmtString.length() == 0)
	{
		buffer[0] = '\0';
		return true;
	}
	else
		return false;
}

// functions for argument extraction
ScriptEventList* ResolveExternalVar(ScriptEventList* in_EventList, Script* in_Script, UInt8* &scriptData)
{
	ScriptEventList* refEventList = NULL;
	UInt16 varIdx = *((UInt16*)++scriptData);
	scriptData += 2;

	Script::RefVariable* refVar = in_Script->GetVariable(varIdx);
	if (refVar)
	{
		refVar->Resolve(in_EventList);
		TESForm* refObj = refVar->form;
		if (refObj)
		{
			if (refObj->typeID == kFormType_Reference)
			{
				TESObjectREFR* refr = DYNAMIC_CAST(refObj, TESForm, TESObjectREFR);
				if (refr)
					refEventList = refr->GetEventList();
			}
			else if (refObj->typeID == kFormType_Quest)
			{
				TESQuest* quest = DYNAMIC_CAST(refObj, TESForm, TESQuest);
				if (quest)
					refEventList = quest->scriptEventList;
			}
		}
	}

	return refEventList;
}

TESGlobal* ResolveGlobalVar(ScriptEventList* in_EventList, Script* in_Script, UInt8* &scriptData)
{
	TESGlobal* global = NULL;
	UInt16 varIdx = *((UInt16*)++scriptData);
	scriptData += 2;

	Script::RefVariable* globalRef = in_Script->GetVariable(varIdx);
	if (globalRef)
		global = (TESGlobal*)DYNAMIC_CAST(globalRef->form, TESForm, TESGlobal);

	return global;
}


static bool ExtractFloat(double& out, UInt8* &scriptData, Script* scriptObj, ScriptEventList* eventList)
{
	//extracts one float arg

	bool ret = false;
	if (*scriptData == 'r')		//reference to var in another script
	{
		eventList = ResolveExternalVar(eventList, scriptObj, scriptData);
		if (!eventList)			//couldn't resolve script ref
			return false;
	}	

	switch (*scriptData)
	{
	case 'G':		//global var
	{
		TESGlobal* global = ResolveGlobalVar(eventList, scriptObj, scriptData);
		if (global)
		{
			out = global->data;
			ret = true;
		}
		break;
	}
	case 'z':		//literal double
	{
		out = *((double*)++scriptData);
		scriptData += sizeof(double);
		ret = true;
		break;
	}
	case 'f':
	case 's':		//local var
	{
		UInt16 varIdx = *((UInt16*)++scriptData);
		scriptData += 2;
		ScriptEventList::Var* var = eventList->GetVariable(varIdx);
		if (var)
		{
			out = var->data;
			ret = true;
		}
		break;
	}
	}
	return ret;
}

TESForm* ExtractFormFromFloat(UInt8* &scriptData, Script* scriptObj, ScriptEventList* eventList)
{
	TESForm* outForm = NULL;
	if (*scriptData == 'r')		//doesn't work as intended yet so refs must be local vars
	{
		eventList = ResolveExternalVar(eventList, scriptObj, scriptData);
		if (!eventList)
			return NULL;
	}

	UInt16 varIdx = *(UInt16*)++scriptData;
	scriptData += 2;

	ScriptEventList::Var* var = eventList->GetVariable(varIdx);
	if (var)
		outForm = LookupFormByID(*((UInt64 *)&var->data));

	return outForm;
}

TESForm* ResolveForm(UInt8* &scriptData, Script* scriptObj, ScriptEventList* eventList)
{
	TESForm* outForm = NULL;
	char argType = *scriptData;
	UInt16	varIdx = *((UInt16 *)(scriptData+1));
//	scriptData += 2;

	switch (argType)
	{
	case 'r':
		{
			Script::RefVariable	* var = scriptObj->GetVariable(varIdx);
			if(var)
			{
				var->Resolve(eventList);
				outForm = var->form;
				scriptData += 3;
			}
		}
		break;
	case 'f':
			outForm = ExtractFormFromFloat(scriptData, scriptObj, eventList);
			break;
	}
	return outForm;
}

static bool v_ExtractArgsEx(UInt32 numArgs, ParamInfo * paramInfo, UInt8* &scriptData, Script * scriptObj, ScriptEventList * eventList, va_list args)
{
	for(UInt32 i = 0; i < numArgs; i++)
	{
		ParamInfo	* info = &paramInfo[i];

		//DEBUG_PRINT("ParamType: %d Type: %d Param: %s scriptData: %08x", info->typeID, *scriptData, info->typeStr, scriptData);	

		switch(info->typeID)
		{
			case kParamType_String:
			{
				char	* out = va_arg(args, char *);

				UInt16	len = *((UInt16 *)scriptData);
				scriptData += 2;

				memcpy(out, scriptData, len);
				scriptData += len;

				out[len] = 0;
			}
			break;

			case kParamType_Integer:
			{
				UInt32	* out = va_arg(args, UInt32 *);
				UInt8   type = *scriptData;
				switch(type)
				{
					case 0x6E: // "n"
						*out = *((UInt32 *)++scriptData);
						scriptData += sizeof(UInt32);
						break;
					case 0x7A: // "z"
						*out = *((double *)++scriptData);
						scriptData += sizeof(double);
						break;					
					case 0x66: // "f"
					case 0x72: // "r"
					case 0x73: // "s"
					case 0x47: // "G"
					{
						double data = 0;
						if (ExtractFloat(data, scriptData, scriptObj, eventList))
							*out = data;
						else
							return false;

						break;
					}

					default:
						return false;
				}
			}
			break;

			case kParamType_Float:
			{
				float	* out = va_arg(args, float *);
				UInt8	type = *scriptData;
				switch(type)
				{
					case 0x7A: // "z"
						*out = *((double *)++scriptData);
						scriptData += sizeof(double);
						break;

					case 0x72: // "r"
					case 0x66: // "f"
					case 0x73: // "s"
					case 0x47: // "G"
					{
						double data = 0;
						if (ExtractFloat(data, scriptData, scriptObj, eventList))
							*out = data;
						else
							return false;
						
						break;
					}

					default:
						return false;
				}
			}
			break;

			// Need to adjust list based on FO3 types
			case kParamType_InventoryObject:
			case kParamType_ObjectRef:
			case kParamType_Actor:
			case kParamType_SpellItem:
			case kParamType_Cell:
			case kParamType_MagicItem:
			case kParamType_Sound:
			case kParamType_Topic:
			case kParamType_Quest:
			case kParamType_Race:
			case kParamType_Class:
			case kParamType_Faction:
			case kParamType_Global:
			case kParamType_Furniture:
			case kParamType_TESObject:
			case kParamType_MapMarker:
			case kParamType_ActorBase:
			case kParamType_Container:
			case kParamType_WorldSpace:
			case kParamType_AIPackage:
			case kParamType_CombatStyle:
			case kParamType_MagicEffect:
			case kParamType_WeatherID:
			case kParamType_NPC:
			case kParamType_Owner:
			case kParamType_EffectShader:
			case kParamType_FormList:
			case kParamType_Perk:
			case kParamType_Message:
			{
				TESForm	** out = va_arg(args, TESForm **);
				TESForm* form = ResolveForm(scriptData, scriptObj, eventList);
				if (!form)
					return false;

				*out = form;
			}
			break;

			case kParamType_ActorValue:
			case kParamType_AnimationGroup:
			case kParamType_Sex:
			case kParamType_CrimeType:
			{
				UInt32	* out = va_arg(args, UInt32 *);

				*out = *((UInt16 *)scriptData);
				scriptData += 2;
			}
			break;

			default:
				_MESSAGE("Unhandled type encountered. Arg #%d numArgs = %d paramType = %d paramStr = %s",
					i, numArgs, info->typeID, info->typeStr);
				HALT("unhandled type");
				break;
		}
	}

	return true;
}

bool ExtractArgsEx(ParamInfo * paramInfo, void * scriptDataIn, UInt32 * scriptDataOffset, Script * scriptObj, ScriptEventList * eventList, ...)
{
	va_list	args;
	va_start(args, eventList);

	UInt8	* scriptData = ((UInt8 *)scriptDataIn) + *scriptDataOffset;
	UInt32	numArgs = *((UInt16 *)scriptData);
	scriptData += 2;

	bool bExtracted = v_ExtractArgsEx(numArgs, paramInfo, scriptData, scriptObj, eventList, args);
	va_end(args);
	return bExtracted;
}


//fmtStringPos is index of fmtString param in paramInfo, with first param = 0
bool ExtractFormatStringArgs(UInt32 fmtStringPos, char* buffer, ParamInfo * paramInfo, void * scriptDataIn, UInt32 * scriptDataOffset, Script * scriptObj, ScriptEventList * eventList, UInt32 maxParams, ...)
{
	va_list args;
	va_start(args, maxParams);

	UInt8	* scriptData = ((UInt8 *)scriptDataIn) + *scriptDataOffset;
	UInt32	numArgs = *((UInt16 *)scriptData);
	numArgs -= fmtStringPos + 1;
	scriptData += 2;

	bool bExtracted = false;
	if (fmtStringPos > 0)
	{
		bExtracted = v_ExtractArgsEx(fmtStringPos, paramInfo, scriptData, scriptObj, eventList, args);
		if (!bExtracted)
			return false;
	}

	ScriptFormatStringArgs scriptArgs(numArgs, scriptData, scriptObj, eventList);
	bExtracted = ExtractFormattedString(scriptArgs, buffer);

	numArgs = scriptArgs.GetNumArgs();
	scriptData = scriptArgs.GetScriptData();
	//NOTE: if v_ExtractArgsEx was called above, passing args again in second call below = undefined behavior. Needs fixing.
	if (bExtracted && numArgs > 0)			//some optional normal params following format string params
	{
		if ((numArgs + fmtStringPos + 21) > maxParams)		//scripter included too many optional params - adjust to prevent crash
			numArgs = (maxParams - fmtStringPos - 21);

		bExtracted = v_ExtractArgsEx(numArgs, &(paramInfo[fmtStringPos + 21]), scriptData, scriptObj, eventList, args);
	}

	va_end(args);
	return bExtracted;
}

// g_baseActorValueNames is only filled in after oblivion's global initializers run
const char* GetActorValueString(UInt32 actorValue)
{
	char* name = 0;
	if (actorValue <= eActorVal_FalloutMax)
		name = GetActorValueName(actorValue);
	if (!name)
		name = "unknown";

	return name;
}

#else
bool ExtractFormatStringArgs(UInt32 fmtStringPos, char* buffer, ParamInfo * paramInfo, void * scriptDataIn, UInt32 * scriptDataOffset, Script * scriptObj, ScriptEventList * eventList, UInt32 maxParams, ...)
{
	return false;
}
#endif

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15

// not sure how much of this changed, zeroed out struct until confirmed
struct TLSData
{
	// thread local storage

	UInt32			unk000[(0x24C - 0x000) >> 2]; 	// 000
	bool			bConsoleMode;					// 250 was executing command called from console?
};

STATIC_ASSERT(offsetof(TLSData, bConsoleMode) == 0x24C);

#elif FALLOUT_VERSION >= FALLOUT_VERSION_1_1_35

// 2A4
struct TLSData
{
	// thread local storage

	UInt32			unk00;							// 000
	UInt32			unk04;							// 004
	void			* unk08;						// 008 Seen ExtraDataList*
	UInt32			unk0C[(0x044 - 0x00C) >> 2]; 	// 00C
	void			* unk44;						// 044 Seen ExtraScript*
	UInt32			unk048[(0x244 - 0x048) >> 2];	// 048
	UInt32			unk244;							// 244
	UInt32			unk248;							// 248
	UInt32			unk24C;							// 24C 
	bool			bConsoleMode;					// 250 was executing command called from console?
	UInt8			unk24D[3];
	UInt32			unk250[(0x278 - 0x254) >> 2];	// 254
	UInt32			unk278;							// 278
	UInt32			unk27C[(0x294 - 0x27C) >> 2];	// 27C
	UInt32			unk294;							// 294 often retrieved & modified before alloc'ing mem for some large object
	UInt32			unk298[(0x2A4 - 0x298) >> 2];	// 298
};

STATIC_ASSERT(sizeof(TLSData) == 0x2A4);
STATIC_ASSERT(offsetof(TLSData, bConsoleMode) == 0x250);	// 1.1.35 patch changed offset from 0x24C

#else

#warning unsupported runtime version

#endif

static TLSData* GetTLSData()
{
	UInt32 TlsIndex = *g_TlsIndexPtr;
	TLSData* data = NULL;

	__asm {
		mov     ecx,	[TlsIndex]   
		mov     edx,	fs:[2Ch]	// linear address of thread local storage array
		mov     eax,	[edx+ecx*4]
		mov		[data], eax
	}

	return data;
}

void DumpTLSData()
{
	TLSData* data = GetTLSData();
	DumpClass(data, sizeof(TLSData)/4);
}

bool IsConsoleMode()
{
	TLSData* tlsData = GetTLSData();
	if (tlsData)
		return tlsData->bConsoleMode;

	return false;
}

ScriptFormatStringArgs::ScriptFormatStringArgs(UInt32 _numArgs, UInt8* _scriptData, Script* _scriptObj, ScriptEventList* _eventList)
	: numArgs(_numArgs), scriptData(_scriptData), scriptObj(_scriptObj), eventList(_eventList)
{
	//extract format string
	UInt16 len = *((UInt16*)scriptData);
	char* szFmt = new char[len+1];
	scriptData += 2;
	memcpy(szFmt, scriptData, len);
	szFmt[len] = '\0';

	scriptData += len;
	fmtString = std::string(szFmt);
	delete szFmt;
}

std::string ScriptFormatStringArgs::GetFormatString()
{
	return fmtString;
}

bool ScriptFormatStringArgs::HasMoreArgs()
{
	return (numArgs > 0);
}

UInt32 ScriptFormatStringArgs::GetNumArgs()
{
	return numArgs;
}

UInt8* ScriptFormatStringArgs::GetScriptData()
{
	return scriptData;
}

bool ScriptFormatStringArgs::SkipArgs(UInt32 numToSkip)
{
	while (numToSkip--)
	{
		switch (*scriptData)
		{
		case 'z':
			scriptData += sizeof(double) + 1;
			break;
		case 'r':
			scriptData += 6;
			break;
		default:
			scriptData += 3;
			break;
		}

		numArgs--;
	}

	return true;
}

//Generate a game messagebox
void MessageBoxAlert(const char * msg)
{
//	*ShowMessageBox_button = 0xFF;
//	*ShowMessageBox_pScriptRefID = 0;
//	ShowMessageBox(msg, ShowMessageBox_Callback, 0, "Ok", 0);
}

//Log error if expression evaluates to false
bool SCRIPT_ASSERT(bool expr, Script* script, const char * errorMsg, ...)
{
//	static bool bAlerted = false;			//only alert user on first error
//	static std::set<UInt32> naughtyScripts;	//one error per script to avoid thrashing
//
//	if (!expr && naughtyScripts.find(script->refID) == naughtyScripts.end())
//	{
//		const ModEntry ** activeMods = (*g_dataHandler)->GetActiveModList();
//		UInt8 modIndex = script->GetModIndex();
//		const ModEntry * modEntry = activeMods[modIndex];
//
//		const char * modName;
//		if (modIndex != 0xFF && modEntry && modEntry->data && modEntry->data->name)
//			modName = modEntry->data->name;
//		else
//			modName = "Unknown";
//
////		sprintf_s(errorHeader, sizeof(errorHeader) - 1, "** Error: Script %08X in file \"%s\" **", script->refID, modName);
////		_MESSAGE("%s", errorHeader);
//		_MESSAGE("** Script Error: Script %08x in file \"%s\" **", script->refID, modName);
//
//		va_list args;
//		va_start(args, errorMsg);
//
//		char errorBuf[512];
//		vsprintf_s(errorBuf, sizeof(errorBuf) - 1, errorMsg, args);
//		va_end(args);
//
//		gLog.Indent();
//		_MESSAGE("%s", errorBuf);
//		gLog.Outdent();
//
//		if (!bAlerted)
//		{
//			MessageBoxAlert("OBSE has detected a script error. \n\nPlease check obse.log for details.");
//			bAlerted = true;
//		}
//
//		naughtyScripts.insert(script->refID);
//	}
	return expr;
}

bool ScriptFormatStringArgs::Arg(FormatStringArgs::argType asType, void * outResult)
{
	if (!SCRIPT_ASSERT((numArgs > 0), scriptObj, "Too few args for format specifier"))
		return false;

	numArgs--;

	switch (asType)
	{
	case kArgType_Float:
		{
			double data = 0;
			if (ExtractFloat(data, scriptData, scriptObj, eventList))
			{
				*((double*)outResult) = data;
				return true;
			}
		}
		break;
	case kArgType_Form:
		{
			TESForm* form = ExtractFormFromFloat(scriptData, scriptObj, eventList);
			*((TESForm**)outResult) = form;
			return true;
		}
	}

	return false;
}
