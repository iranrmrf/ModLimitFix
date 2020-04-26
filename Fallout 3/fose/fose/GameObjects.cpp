#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameExtraData.h"

ScriptEventList* TESObjectREFR::GetEventList() const
{
	BSExtraData* xData = extraDataList.GetByType(kExtraData_Script);
	if (xData)
	{
		ExtraScript* xScript = DYNAMIC_CAST(xData, BSExtraData, ExtraScript);
		if (xScript)
			return xScript->eventList;
	}

	return 0;
}

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0
	static PlayerCharacter** g_thePlayer = (PlayerCharacter **)0x01076044;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	static PlayerCharacter ** g_thePlayer = (PlayerCharacter **)0x01077044;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	static PlayerCharacter ** g_thePlayer = (PlayerCharacter **)0x01076E04;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	static PlayerCharacter ** g_thePlayer = (PlayerCharacter **)0x01076F04;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	static PlayerCharacter ** g_thePlayer = (PlayerCharacter **)0x01076F04;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	static PlayerCharacter ** g_thePlayer = (PlayerCharacter **)0x0107A104;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	static PlayerCharacter ** g_thePlayer = (PlayerCharacter **)0x0107A104;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	static PlayerCharacter ** g_thePlayer = (PlayerCharacter **)0x0107A104;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	static PlayerCharacter ** g_thePlayer = (PlayerCharacter **)0x01077104;
#else
#error unsupported fallout version
#endif

PlayerCharacter* PlayerCharacter::GetSingleton()
{
	return *g_thePlayer;
}
