#include "Commands_Quest.h"
#include "GameForms.h"
#include "GameObjects.h"

bool Cmd_GetCurrentQuest_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
	TESQuest* pCurQuest = pPC->quest;
	if (pCurQuest) {
		*refResult = pCurQuest->refID;
		//if (IsConsoleMode())
		//	Console_Print("CurrentQuest: %x (%s)", pCurQuest->refID, GetFullName(pCurQuest));
	}

	return true;
}

bool Cmd_GetCurrentObjective_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
	BGSQuestObjective* pCurObjective = pPC->questObjective;
	if (pCurObjective) {
		*refResult = pCurObjective->objectiveId;
		//if (IsConsoleMode())
		//	Console_Print("CurrentObjective: %d (%s)", pCurObjective->objectiveId, pCurObjective->displayText.m_data);
	}

	return true;
}

bool Cmd_GetQuestObjectiveCount_Execute(COMMAND_ARGS)
{
	*result = 0;

	TESQuest* pQuest = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &pQuest)) {
		UInt32 count = pQuest->objectives.Count();
		*result = count;
		if (IsConsoleMode())
			Console_Print("%s has %d objectives", GetFullName(pQuest), count);
	}

	return true;
}

bool Cmd_GetNthQuestObjective_Execute(COMMAND_ARGS)
{
	*result = 0;

	TESQuest* pQuest = NULL;
	UInt32 nIndex = 0;
	if (ExtractArgs(EXTRACT_ARGS, &pQuest, &nIndex)) {
		if (!pQuest) return true;

		BGSQuestObjective* pObjective = pQuest->objectives.GetNthItem(nIndex);
		if (pObjective) {
			*result = pObjective->objectiveId;
			//if (IsConsoleMode()) {
			//	UInt32 objectiveId = pObjective->objectiveId;
			//	const char* text = pObjective->displayText.m_data;
			//	Console_Print("%s objective %d: %d %s", GetFullName(pQuest), nIndex, objectiveId, text);
			//}
		}
	}
	return true;
}

bool Cmd_SetCurrentQuest_Execute(COMMAND_ARGS)
{
	*result = 0;

	TESQuest* pQuest = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &pQuest)) {
		PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
		pPC->quest = pQuest;	
	}
	return true;
}
