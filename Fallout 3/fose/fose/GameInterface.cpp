#include "GameInterface.h"
#include "GameTypes.h"

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0

InterfaceManager** g_interfaceManager = (InterfaceManager**)0x01071AA4;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_0_15

InterfaceManager** g_interfaceManager = (InterfaceManager**)0x01072AA4;
NiTArray<TileMenu*> * g_TileMenuArray = (NiTArray<TileMenu*> *)0x0106772C;
bool * g_MenuVisibilityArray = (bool *)0x0117632B;	// size 3C
const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x00619480;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35

InterfaceManager** g_interfaceManager = (InterfaceManager**)0x01072824;
NiTArray<TileMenu*> * g_TileMenuArray = (NiTArray<TileMenu*> *)0x010674AC;
bool * g_MenuVisibilityArray = (bool *)0x011760DB;	// size 3C
const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x0061BE30;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6

InterfaceManager** g_interfaceManager = (InterfaceManager**)0x01072924;
NiTArray<TileMenu*> * g_TileMenuArray = (NiTArray<TileMenu*> *)0x0106759C;
bool * g_MenuVisibilityArray = (bool *)0x011761DB;	// size 3C
const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x0061BD40;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b

InterfaceManager** g_interfaceManager = (InterfaceManager**)0x01072924;
NiTArray<TileMenu*> * g_TileMenuArray = (NiTArray<TileMenu*> *)0x0106759C;
bool * g_MenuVisibilityArray = (bool *)0x011761DB;	// size 3C
const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x0061C4E0;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22

InterfaceManager** g_interfaceManager = (InterfaceManager**)0x01075B24;
NiTArray<TileMenu*> * g_TileMenuArray = (NiTArray<TileMenu*> *)0x0106A7BC;
bool * g_MenuVisibilityArray = (bool *)0x011793DB;	// size 3C
const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x0061C040;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6

InterfaceManager** g_interfaceManager = (InterfaceManager**)0x01075B24;
NiTArray<TileMenu*> * g_TileMenuArray = (NiTArray<TileMenu*> *)0x0106A7BC;
bool * g_MenuVisibilityArray = (bool *)0x011793DB;	// size 3C
const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x0061B810;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7

InterfaceManager** g_interfaceManager = (InterfaceManager**)0x01075B24;
NiTArray<TileMenu*> * g_TileMenuArray = (NiTArray<TileMenu*> *)0x0106A7BC;
bool * g_MenuVisibilityArray = (bool *)0x011793DB;	// size 3C
const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x0061B850;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng

InterfaceManager** g_interfaceManager = (InterfaceManager**)0x01072B24;
NiTArray<TileMenu*> * g_TileMenuArray = (NiTArray<TileMenu*> *)0x010677BC;
bool * g_MenuVisibilityArray = (bool *)0x011763DB;	// size 3C
const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x0061B980;

#else
#error unsupported runtime version
#endif

InterfaceManager * InterfaceManager::GetSingleton(void)
{
	return *g_interfaceManager;
}

bool InterfaceManager::IsMenuVisible(UInt32 menuType)
{
	if (menuType >= kMenuType_Message)
		menuType -= kMenuType_Message;

	if (menuType < 0x3C)
		return g_MenuVisibilityArray[menuType];

	return false;
}

Menu* InterfaceManager::GetMenuByType(UInt32 menuType)
{
	if (menuType >= kMenuType_Message)
		menuType -= kMenuType_Message;

	if (menuType < 0x3C)
	{
		TileMenu* tileMenu = g_TileMenuArray->Get(menuType);
		if (tileMenu)
			return tileMenu->menu;
	}

	return NULL;
}

Tile::Value* InterfaceManager::GetMenuComponentValue(char* componentPath)
{
	// path is of format "MenuType/tile/tile/.../traitName" following hierarchy defined in menu's xml

	// get menu name - stored by game as "&MENUNAME;" so need to fix it up
	char* slashPos = strpbrk(componentPath, "\\/");
	if (slashPos)
	{
		*slashPos = 0;
		char menuName[0x20];
		UInt32 len = strlen(componentPath);
		strcpy_s(menuName + 1, len + 1, componentPath);
		menuName[len + 1] = ';';
		menuName[0] = '&';
		menuName[len + 2] = '\0';

		UInt32 menuID = Tile::TraitNameToID(menuName);
		if (menuID >= kMenuType_Min && menuID <= kMenuType_Max)
		{
			Menu* menu = GetMenuByType(menuID);
			if (menu)
				return menu->tileMenu->GetComponentValue(slashPos + 1);
		}
	}

	return NULL;
}
