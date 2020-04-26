#include "Serialization.h"
#include "Core_Serialization.h"
#include "GameData.h"
#include "Hooks_CreatedObject.h"
#include <string>

/*************************
Save file format:
	Header
		MODS				// stored in order of modIndex when game was saved
			UInt8 numMods
				UInt16	nameLen
				char	modName[nameLen]
		CROB				// a created base object
			void * objectData		// recorded by TESForm::SaveForm() in mod file format


**************************/					

static ModInfo** s_ModFixupTable = NULL;
bool LoadModList(FOSESerializationInterface* fose);	// reads saved mod order, builds table mapping changed mod indexes
bool BuildFixedModIndexTable();

/*******************************
*	Callbacks
*******************************/
void Core_SaveCallback(void * reserved)
{
	FOSESerializationInterface* fose = &g_FOSESerializationInterface;
	DataHandler* dhand = DataHandler::Get();
	ModInfo** mods = dhand->modList.loadedMods;
	UInt8 modCount = dhand->modList.loadedModCount;

	// save the mod list
	fose->OpenRecord('MODS', 0);
	fose->WriteRecordData(&modCount, sizeof(modCount));
	for (UInt32 i = 0; i < modCount; i++)
	{
		UInt16 nameLen = strlen(mods[i]->name);
		fose->WriteRecordData(&nameLen, sizeof(nameLen));
		fose->WriteRecordData(mods[i]->name, nameLen);
	}

	SaveCreatedObjects(fose);
}

void Core_LoadCallback(void * reserved)
{
	FOSESerializationInterface* fose = &g_FOSESerializationInterface;
	UInt32 type, version, length;

	while (fose->GetNextRecordInfo(&type, &version, &length))
	{
		Serialization::ignoreNextChunk = false;
		switch (type)
		{
		case 'MODS':
			if (!LoadModList(fose))
				_MESSAGE("LOAD: Error occurred while loading mod list");
			else if (!BuildFixedModIndexTable())
				_MESSAGE("LOAD: Failed to build fixed mod index table");

			break;
		case 'CROB':
			LoadCreatedObject(fose);	// if this fails it is handled internally so no need to check return val
			break;
		default:
			_MESSAGE("LOAD: Unhandled chunk type in LoadCallback: %08x", type);
			continue;
		}
	}
}

void Core_NewGameCallback(void * reserved)
{
	// reset mod indexes to match current load order
	if (s_ModFixupTable)
	{
		delete s_ModFixupTable;
		s_ModFixupTable = NULL;
	}

	DataHandler* dhand = DataHandler::Get();
	UInt8 modCount = dhand->modList.loadedModCount;
	ModInfo** mods = dhand->modList.loadedMods;

	s_ModFixupTable = new ModInfo*[modCount];
	for (UInt32 i = 0; i < modCount; i++)
		s_ModFixupTable[i] = mods[i];
}

void Core_PostLoadCallback(bool bLoadSucceeded)
{
	// Currently a stub
}

void Core_PreLoadCallback(void * reserved)
{
	// Currently a stub
}


void Init_CoreSerialization_Callbacks()
{
	Serialization::InternalSetSaveCallback(0, Core_SaveCallback);
	Serialization::InternalSetLoadCallback(0, Core_LoadCallback);
	Serialization::InternalSetNewGameCallback(0, Core_NewGameCallback);
	Serialization::InternalSetPreLoadCallback(0, Core_PreLoadCallback);
}

bool LoadModList(FOSESerializationInterface* fose)
{
	//stub
	return true;
}

bool BuildFixedModIndexTable()
{
	//stub
	return true;
}
