#pragma once

#include "GameTiles.h"

// 28
class Menu
{
public:
	Menu();
	~Menu();

	virtual void	Destroy(bool noDealloc);
	virtual void	Unk_01(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_02(UInt32 arg0, UInt32 arg1);
	virtual void	HandleClick(UInt32 buttonID, Tile* clickedTile);
	virtual void	HandleMouseover(UInt32 buttonID, Tile* tile);		
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_07(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_08(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_09(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0A(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0B(void);
	virtual bool	Unk_0C(UInt32 arg0);				// keyboard handler?
	virtual UInt32	GetTypeID();
	virtual bool	Unk_0E(UInt32 arg0, UInt32 arg1);
	virtual bool	Unk_0F(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_10(UInt32 arg0);
	virtual void	Unk_11(UInt32 arg0);

//	void			** _vtbl;		// 00
	TileMenu		* tileMenu;		// 04
	tList<void*>	list08;			// 08 data = some struct containing char*, some pointers
	UInt32			unk10;			// 10
	UInt32			unk14;			// 14
	UInt32			unk18;			// 18
	UInt8			unk1C;			// 1C init'd to 0
	UInt8			unk1D;			// 1D init'd to 1
	UInt8			pad1E[2];
	UInt32			typeID;			// 20 one of kMenuType_XXX
	UInt32			unk24;			// 24 init'd to 4 (?)
};

// 30
template <typename T>
class ListBox
{
public:
	ListBox();
	~ListBox();

	virtual bool	Unk_00(UInt32 arg0);
	virtual UInt32	GetUnk10(void);
	virtual void	Unk_02(UInt32 arg0);	// handles scrolling?
	virtual bool	Unk_03(UInt32 arg0);
	virtual void	Unk_04(void);
	virtual UInt32	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual void	Destroy(bool noDealloc);
	virtual void	Unk_07(void);			// filter items? iterates over tList, frees selected nodes
	virtual void	Unk_08(UInt32 arg0);	// traverses tList twice

//	void			** _vtbl;		// 00
	tList<T>		list;			// 04 
	Tile			* listBoxTile;	// 0C
	UInt32			unk10;			// 10
	TileImage		* scrollbar;	// 14
	char			* templateName;	// 18
	UInt8			unk1C;			// 1C
	UInt8			pad1D[3];		// 1D
	float			unk20;			// 20
	float			unk24;			// 24
	float			unk28;			// 28
	UInt16			unk2C;			// 2C
	UInt16			pad2E;
};

STATIC_ASSERT(sizeof(ListBox<UInt32>) == 0x30);

// 100
class InventoryMenu : public Menu
{
public:
	InventoryMenu();
	~InventoryMenu();

	// TODO: investigate these structs

	struct ItemInfo {
		void	* unk00;		// points to some struct which sometimes contains pointers to
								// ExtraDataList, Tile::Value
		UInt32	itemCount;
		TESForm	* item;
	};

	struct ItemChange {
		TileImage	* button;
		ItemInfo	* itemInfo;
		UInt32		unk08;		// only seen 1. Possibly bool for whether item is visible or not
	};

	TileRect		* caps;				// 28
	TileRect		* hitpoints;		// 2C
	TileRect		* damageRating;		// 30
	TileRect		* weight;			// 34
	TileImage		* inventoryList;	// 38
	TileRect		* hotkeyWheel;		// 3C
	TileImage		* equipButton;		// 40
	TileImage		* dropButton;		// 44
	TileImage		* repairButton;		// 48
	TileImage		* hotkeyButton;		// 4C
	TileImage		* cancelButton;		// 50
	TileImage		* itemIcon;			// 54
	TileRect		* itemInfo;			// 58
	TileRect		* tabLine;			// 5C
	UInt32			unk60[0x0D];		// 60 seen alternating sequence of (0, -1, 0, ...)
	ListBox<ItemChange>	items;			// 94 ListBox<ItemChange>
	TileRect		* hotkeyWheel_2;	// C4 again?
	TileRect		* hotkeyItems[8];	// C8
	UInt32			unkE8;				// E8
	UInt32			unkEC;				// EC
	UInt32			unkF0;				// F0
	UInt32			unkF4;				// F4
	UInt32			unkF8;				// F8
	UInt32			unkFC;				// FC
};

STATIC_ASSERT(sizeof(InventoryMenu) == 0x100);

// 6C
class MessageMenu : public Menu
{
public:
	MessageMenu();
	~MessageMenu();

	struct ButtonInfo {
		TileImage	* button;
		UInt32		index;
		// possibly one more, if so only seen zero
	};

	TileRect			* mainRect;		// 28
	TileText			* title;		// 2C
	TileImage			* icon;			// 30
	TileText			* text;			// 34
	TileImage			* buttonList;	// 38
	ListBox<ButtonInfo>	buttons;		// 40
};

STATIC_ASSERT(sizeof(MessageMenu) == 0x6C);

enum {
	kMenuType_Audio                 =	0x000003F9,
	kMenuType_Book                  =	0x00000402,
	kMenuType_CharGen               =	0x00000418,
	kMenuType_Container             =	0x000003F0,
	kMenuType_Dialog                =	0x000003F1,
	kMenuType_Gameplay              =	0x000003FC,
	kMenuType_HUDMain               =	0x000003EC,
	kMenuType_Inventory             =	0x000003EA,
	kMenuType_Loading               =	0x000003EF,
	kMenuType_LockPick              =	0x000003F6,
	kMenuType_Map                   =	0x000003FF,
	kMenuType_Message               =	0x000003E9,
	kMenuType_Tutorial              =	0x00000423,
	kMenuType_TextEdit              =	0x0000041B,
	kMenuType_Start                 =	0x000003F5,
	kMenuType_Quantity              =	0x000003F8,
	kMenuType_RaceSex               =	0x0000040C,
	kMenuType_SleepWait             =	0x000003F4,
	kMenuType_Stats                 =	0x000003EB,
	kMenuType_Video                 =	0x000003FA,
	kMenuType_LevelUp               =	0x00000403,
	kMenuType_Repair                =	0x0000040B,
	kMenuType_RepairServices        =	0x00000422,
	kMenuType_Credits               =	0x00000417,
	kMenuType_Barter                =	0x0000041D,
	kMenuType_Surgery               =	0x0000041E,
	kMenuType_Hacking               =	0x0000041F,
	kMenuType_Computers             =	0x00000421,
	kMenuType_VATS                  =	0x00000420,
	kMenuType_SPECIALBook           =	0x00000424,

	kMenuType_Min = kMenuType_Message,
	kMenuType_Max = kMenuType_SPECIALBook
};
