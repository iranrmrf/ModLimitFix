#include "Hooks_CreatedObject.h"
#include "Utilities.h"
#include "GameAPI.h"
#include "GameForms.h"

FakeModInfo::FakeModInfo(FOSESerializationInterface* _intfc)
{
	memset(this, 0, sizeof(FakeModInfo));
	intfc = _intfc;
	modIndex = 0xFF;

	// refModInfo is normally used to fix up formIDs as saved in GECK when referencing forms from other mods
	// for created objects, formIDs represent run-time formIDs, must be fixed up if load order changes
	DataHandler* dataHand = DataHandler::Get();
	numRefMods = dataHand->modList.loadedModCount;
	// TODO: here we need to build an array of mods based on previous load order

	// name, filepath, fileoffset, dataoffset
}

FakeModInfo::~FakeModInfo()
{
	//
}

void SaveCreatedObjects(FOSESerializationInterface* fose)
{
	TESSaveLoadGame* game = TESSaveLoadGame::GetSingleton();
	for (TESSaveLoadGame::CreatedObject* crobj = &game->createdObjectList; crobj; crobj = crobj->next)
	{
		if ((crobj->refID & 0xFF000000) == 0xFF000000)
		{
			TESForm* form = LookupFormByID(crobj->refID);
			if (!form)
			{
				_MESSAGE("SAVE: Unkown Object %08x found in created base object list", crobj->refID);
				continue;
			}
			else
			{
				form->SaveForm();
				fose->OpenRecord('CROB', 0);
				fose->WriteRecordData(*g_CreatedObjectData, *g_CreatedObjectSize);
			}
		}
		else
			_MESSAGE("Save: Non-created object or garbage refID %08x found in created base object list.", crobj->refID);
	}
}

bool LoadCreatedObject(FOSESerializationInterface* fose)
{
	//stub
	return false;
}
