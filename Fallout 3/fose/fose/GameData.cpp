#include "GameData.h"

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	static const FormRecordData** s_FormRecordData = (const FormRecordData**)0x00F48548;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	static const FormRecordData** s_FormRecordData = (const FormRecordData**)0x00F47568;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	static const FormRecordData** s_FormRecordData = (const FormRecordData**)0x00F47568;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	static const FormRecordData** s_FormRecordData = (const FormRecordData**)0x00F47568;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	static const FormRecordData** s_FormRecordData = (const FormRecordData**)0x00F4A748;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	static const FormRecordData** s_FormRecordData = (const FormRecordData**)0x00F4A748;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	static const FormRecordData** s_FormRecordData = (const FormRecordData**)0x00F4A748;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	static const FormRecordData** s_FormRecordData = (const FormRecordData**)0x00F47748;
#else
#error unsupported version of fallout
#endif

DataHandler* DataHandler::Get() {
	return *g_dataHandler;
}

class LoadedModFinder
{
	const char * m_stringToFind;

public:
	LoadedModFinder(const char * str) : m_stringToFind(str) { }

	bool Accept(ModInfo* modInfo)
	{
		return _stricmp(modInfo->name, m_stringToFind) == 0;
	}
};

#if 1
const ModInfo * DataHandler::LookupModByName(const char * modName)
{
	return modList.modInfoList.Find(LoadedModFinder(modName));
}


//const ModInfo ** DataHandler::GetActiveModList()
//{
//	static const ModInfo* activeModList[0x100] = { 0 };
//
//	if (!(*activeModList))
//	{
//		UInt8 index = 0;
//		for (ModEntry* entry = &(*g_dataHandler)->modList; entry; entry = entry->next)
//		{
//			if (entry->IsLoaded())
//				activeModList[index++] = entry;
//		}
//	}
//
//	return activeModList;
//}

UInt8 DataHandler::GetModIndex(const char* modName)
{
	return modList.modInfoList.GetIndexOf(LoadedModFinder(modName));
}

struct IsModLoaded
{
	bool Accept(ModInfo* pModInfo) const {
		return pModInfo->IsLoaded();
	}
};

UInt8 DataHandler::GetActiveModCount() const
{
	UInt32 count = modList.modInfoList.CountIf(IsModLoaded());
	return count;
}

//const char* DataHandler::GetNthModName(UInt32 modIndex)
//{
//	const ModEntry** activeModList = GetActiveModList();
//	if (modIndex < GetActiveModCount() && activeModList[modIndex]->data)
//		return activeModList[modIndex]->data->name;
//	else
//		return "";
//}
#endif

class QuestNameFinder
{
	const char* name;
public:
	QuestNameFinder(const char* _name) : name(_name)	{	}

	bool Accept(const TESQuest* quest)
	{
		if (!_stricmp(quest->GetEditorName(), name))
			return true;

		return false;
	}
};

TESQuest* DataHandler::GetQuestByName(const char* questName)
{
	return questList.Find(QuestNameFinder(questName));
}

ModInfo::ModInfo()
{
	//
}

ModInfo::~ModInfo()
{
	//
}
