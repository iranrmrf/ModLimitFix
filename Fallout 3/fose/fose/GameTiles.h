#pragma once
#include "GameTypes.h"

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	const UInt32 kTile_SetStringAddr = 0x00BEBA80;		// valueID, char*, bool <- bool means propagate change to refs?
	const UInt32 kTileValue_SetStringAddr = 0x00BEB7A0;	// char*, bool <- called by Tile::SetStringValue()
	const UInt32 kTile_SetFloatAddr = 0x00BE8A70;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	const UInt32 kTile_SetStringAddr = 0x00BF0340;		// valueID, char*, bool <- bool means propagate change to refs?
	const UInt32 kTileValue_SetStringAddr = 0x00BF0060;	// char*, bool <- called by Tile::SetStringValue()
	const UInt32 kTile_SetFloatAddr = 0x00BED330;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	const UInt32 kTile_SetStringAddr = 0x00BF07E0;		// valueID, char*, bool <- bool means propagate change to refs?
	const UInt32 kTileValue_SetStringAddr = 0x00BF0500;	// char*, bool <- called by Tile::SetStringValue()
	const UInt32 kTile_SetFloatAddr = 0x00BED7D0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	const UInt32 kTile_SetStringAddr = 0x00BF0650;		// valueID, char*, bool <- bool means propagate change to refs?
	const UInt32 kTileValue_SetStringAddr = 0x00BF0370;	// char*, bool <- called by Tile::SetStringValue()
	const UInt32 kTile_SetFloatAddr = 0x00BED640;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	const UInt32 kTile_SetStringAddr = 0x00BF11F0;		// valueID, char*, bool <- bool means propagate change to refs?
	const UInt32 kTileValue_SetStringAddr = 0x00BF0F10;	// char*, bool <- called by Tile::SetStringValue()
	const UInt32 kTile_SetFloatAddr = 0x00BEE1E0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	const UInt32 kTile_SetStringAddr = 0x00BF1220;		// valueID, char*, bool <- bool means propagate change to refs?
	const UInt32 kTileValue_SetStringAddr = 0x00BF0F40;	// char*, bool <- called by Tile::SetStringValue()
	const UInt32 kTile_SetFloatAddr = 0x00BEE210;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	const UInt32 kTile_SetStringAddr = 0x00BF11A0;		// valueID, char*, bool <- bool means propagate change to refs?
	const UInt32 kTileValue_SetStringAddr = 0x00BF0EC0;	// char*, bool <- called by Tile::SetStringValue()
	const UInt32 kTile_SetFloatAddr = 0x00BEE190;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	const UInt32 kTile_SetStringAddr = 0x00BEE1B0;		// valueID, char*, bool <- bool means propagate change to refs?
	const UInt32 kTileValue_SetStringAddr = 0x00BEDED0;	// char*, bool <- called by Tile::SetStringValue()
	const UInt32 kTile_SetFloatAddr = 0x00BEB1A0;
#else
#error unsupported fallout version
#endif

class NiNode;
class Menu;
class Action_Tile;

// 38
class Tile
{
public:
	Tile();
	~Tile();

	MEMBER_FN_PREFIX(Tile);
	DEFINE_MEMBER_FN(SetStringValue, void, kTile_SetStringAddr, UInt32 valueID, const char* str, bool bPropagate);
	DEFINE_MEMBER_FN(SetFloatValue, void, kTile_SetFloatAddr, UInt32 valueID, float num, bool bPropagate);

	virtual void	Destroy(bool noDealloc);
	virtual void	Init(Tile* parent, const char* name, UInt32 arg2);
	virtual void	Unk_02(void);
	virtual UInt32	GetType(void);		// returns one of kTileValue_XXX
	virtual UInt32	GetTypeID(void);	// returns 4-byte id, e.g. 'IMGE', 'TILE', 'MENU'
	virtual void	UpdateValue(UInt32 valueID, float num, UInt32 arg2);	// arg2 probably string
																			// e.g. pass in FA3 to toggle menu visibility
																			// only handles valueIDs for which it has code
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual UInt16	Unk_08(UInt32 arg0, UInt32 arg1, UInt32 arg2);

	enum { kTypeID = 'TILE' };

	enum {
		kModified_Text			= 0x02,		// set when changing TileText justify, font, wrap, etc
		kModified_Dimensions	= 0x80,		// set when changing TileImage height, width, crop, cropoffset
	};

	// 14
	struct Value
	{
		UInt32		id;			// 00
		Tile		* parent;	// 04
		float		num;		// 08
		char		* str;		// 0C
		Action_Tile	* action;	// 10
	};

	struct ChildNode {
		ChildNode	* next;
		ChildNode	* prev;
		Tile		* child;
	};

	// void	**	_vtbl
	tList<ChildNode>		childList;		// 04
	UInt32					unk0C;			// 0C looks like childcount
	BSSimpleArray<Value*>	values;			// 10
	String					name;			// 20
	Tile					* parent;		// 28
	NiNode					* niNode;		// 2C
	UInt32					flags;			// 30 often modified when modifying traits
	UInt8					unk34;			// 34
	UInt8					pad35[3];

	static UInt32 TraitNameToID(const char* traitName);
	Value* GetValue(UInt32 typeID);
	Value* GetValue(const char* valueName);
	Tile* GetChild(const char* childName);
	Tile::Value* GetComponentValue(const char* componentPath);
	std::string GetQualifiedName();
};

// 0C
// technically a template class Action<T> but only used as Action<Tile>
// used to manage references in Tile::Value to other Tile::Values
class Action_Tile
{
public:
	Action_Tile();
	~Action_Tile();

	virtual float			GetValue();
	virtual Tile::Value*	GetParent();

	// void	** vtbl
	UInt32		opcode;			// 04 one of kTileValue_XXX, usually 7D0 ("copy")
	Action_Tile	* nextAction;	// 08
};

// 10
class RefValueAction : public Action_Tile
{
public:
	RefValueAction();
	~RefValueAction();

	// GetValue() returns float value of parent tile::value
	// GetParent() returns parent

	Tile::Value	* value;
};

// 10
class FloatAction : public Action_Tile
{
public:
	FloatAction();
	~FloatAction();

	// GetValue() returns value
	// GetParent returns NULL

	float	value;
};

// 44
class TileMenu : public Tile
{
public:
	TileMenu();
	~TileMenu();

	enum { kTypeID = 'MENU' };

	UInt32		unk38;		// 38
	Menu		* menu;		// 3C
	UInt32		unk40;		// 40
};

class TileRect;
class TileImage;
class TileText;

enum {
	kTileValue_false                     =	0x00000000,
	kTileValue_console                   =	0x00000000,
	kTileValue_nosystemcolor             =	0x00000000,
	kTileValue_true                      =	0x00000001,
	kTileValue_left                      =	0x00000001,
	kTileValue_center                    =	0x00000002,
	kTileValue_right                     =	0x00000004,
	kTileValue_up                        =	0x00000005,
	kTileValue_down                      =	0x00000006,
	kTileValue_default_accept            =	0x00000009,
	kTileValue_xbuttona                  =	0x00000009,
	kTileValue_xbuttonb                  =	0x0000000A,
	kTileValue_xbuttonx                  =	0x0000000B,
	kTileValue_xbuttony                  =	0x0000000C,
	kTileValue_xbuttonlt                 =	0x0000000D,
	kTileValue_xbuttonrt                 =	0x0000000E,
	kTileValue_xbuttonlb                 =	0x0000000F,
	kTileValue_xbuttonrb                 =	0x00000010,
	kTileValue_xbuttonls                 =	0x00000011,
	kTileValue_xbuttonrs                 =	0x00000012,
	kTileValue_click_past                =	0x00000065,
	kTileValue_no_click_past             =	0x00000066,
	kTileValue_mixed_menu                =	0x00000067,
	kTileValue_glow_branch               =	0x0000006E,
	kTileValue_noglow_branch             =	0x0000006F,
	kTileValue_pipboymenu                =	0x00000070,
	kTileValue_rect                      =	0x00000385,
	kTileValue_image                     =	0x00000386,
	kTileValue_text                      =	0x00000387,
	kTileValue_3d                        =	0x00000388,
	kTileValue_nif                       =	0x00000388,
	kTileValue_menu                      =	0x00000389,
	kTileValue_hotrect                   =	0x0000038A,
	kTileValue_window                    =	0x0000038B,
	kTileValue_template                  =	0x000003E7,
	kTileValue_MessageMenu               =	0x000003E9,
	kTileValue_InventoryMenu             =	0x000003EA,
	kTileValue_StatsMenu                 =	0x000003EB,
	kTileValue_HUDMainMenu               =	0x000003EC,
	kTileValue_LoadingMenu               =	0x000003EF,
	kTileValue_ContainerMenu             =	0x000003F0,
	kTileValue_DialogMenu                =	0x000003F1,
	kTileValue_SleepWaitMenu             =	0x000003F4,
	kTileValue_StartMenu                 =	0x000003F5,
	kTileValue_LockPickMenu              =	0x000003F6,
	kTileValue_QuantityMenu              =	0x000003F8,
	kTileValue_AudioMenu                 =	0x000003F9,
	kTileValue_VideoMenu                 =	0x000003FA,
	kTileValue_GameplayMenu              =	0x000003FC,
	kTileValue_MapMenu                   =	0x000003FF,
	kTileValue_BookMenu                  =	0x00000402,
	kTileValue_LevelUpMenu               =	0x00000403,
	kTileValue_RepairMenu                =	0x0000040B,
	kTileValue_RaceSexMenu               =	0x0000040C,
	kTileValue_CreditsMenu               =	0x00000417,
	kTileValue_CharGenMenu               =	0x00000418,
	kTileValue_TextEditMenu              =	0x0000041B,
	kTileValue_BarterMenu                =	0x0000041D,
	kTileValue_SurgeryMenu               =	0x0000041E,
	kTileValue_HackingMenu               =	0x0000041F,
	kTileValue_VATSMenu                  =	0x00000420,
	kTileValue_ComputersMenu             =	0x00000421,
	kTileValue_RepairServicesMenu        =	0x00000422,
	kTileValue_TutorialMenu              =	0x00000423,
	kTileValue_SPECIALBookMenu           =	0x00000424,
	kTileValue_copy                      =	0x000007D0,
	kTileValue_add                       =	0x000007D1,
	kTileValue_sub                       =	0x000007D2,
	kTileValue_mul                       =	0x000007D3,
	kTileValue_mult                      =	0x000007D3,
	kTileValue_div                       =	0x000007D4,
	kTileValue_min                       =	0x000007D5,
	kTileValue_max                       =	0x000007D6,
	kTileValue_mod                       =	0x000007D7,
	kTileValue_floor                     =	0x000007D8,
	kTileValue_ceil                      =	0x000007D9,
	kTileValue_abs                       =	0x000007DA,
	kTileValue_round                     =	0x000007DB,
	kTileValue_gt                        =	0x000007DC,
	kTileValue_gte                       =	0x000007DD,
	kTileValue_eq                        =	0x000007DE,
	kTileValue_neq                       =	0x000007DF,
	kTileValue_lt                        =	0x000007E0,
	kTileValue_lte                       =	0x000007E1,
	kTileValue_and                       =	0x000007E2,
	kTileValue_or                        =	0x000007E3,
	kTileValue_not                       =	0x000007E4,
	kTileValue_onlyif                    =	0x000007E5,
	kTileValue_onlyifnot                 =	0x000007E6,
	kTileValue_ref                       =	0x000007E7,
	kTileValue_value                     =	0x00000BB9,
	kTileValue_name                      =	0x00000BBA,
	kTileValue_src                       =	0x00000BBB,
	kTileValue_trait                     =	0x00000BBC,
	kTileValue_x                         =	0x00000FA1,
	kTileValue_y                         =	0x00000FA2,
	kTileValue_visible                   =	0x00000FA3,
	kTileValue_class                     =	0x00000FA4,
	kTileValue_clipwindow                =	0x00000FA6,
	kTileValue_stackingtype              =	0x00000FA7,
	kTileValue_locus                     =	0x00000FA8,
	kTileValue_alpha                     =	0x00000FA9,
	kTileValue_id                        =	0x00000FAA,
	kTileValue_disablefade               =	0x00000FAB,
	kTileValue_listindex                 =	0x00000FAC,
	kTileValue_depth                     =	0x00000FAD,
	kTileValue_clips                     =	0x00000FAE,
	kTileValue_target                    =	0x00000FAF,
	kTileValue_height                    =	0x00000FB0,
	kTileValue_width                     =	0x00000FB1,
	kTileValue_red                       =	0x00000FB2,
	kTileValue_green                     =	0x00000FB3,
	kTileValue_blue                      =	0x00000FB4,
	kTileValue_tile                      =	0x00000FB5,
	kTileValue_child_count               =	0x00000FB6,
	kTileValue_childcount                =	0x00000FB6,
	kTileValue_justify                   =	0x00000FB7,
	kTileValue_zoom                      =	0x00000FB8,
	kTileValue_font                      =	0x00000FB9,
	kTileValue_wrapwidth                 =	0x00000FBA,
	kTileValue_wraplimit                 =	0x00000FBB,
	kTileValue_wraplines                 =	0x00000FBC,
	kTileValue_pagenum                   =	0x00000FBD,
	kTileValue_ishtml                    =	0x00000FBE,
	kTileValue_cropoffsety               =	0x00000FBF,
	kTileValue_cropy                     =	0x00000FBF,
	kTileValue_cropoffsetx               =	0x00000FC0,
	kTileValue_cropx                     =	0x00000FC0,
	kTileValue_menufade                  =	0x00000FC1,
	kTileValue_explorefade               =	0x00000FC2,
	kTileValue_mouseover                 =	0x00000FC3,
	kTileValue_string                    =	0x00000FC4,
	kTileValue_shiftclicked              =	0x00000FC5,
	kTileValue_clicked                   =	0x00000FC7,
	kTileValue_clicksound                =	0x00000FCB,
	kTileValue_filename                  =	0x00000FCC,
	kTileValue_filewidth                 =	0x00000FCD,
	kTileValue_fileheight                =	0x00000FCE,
	kTileValue_repeatvertical            =	0x00000FCF,
	kTileValue_repeathorizontal          =	0x00000FD0,
	kTileValue_animation                 =	0x00000FD2,
	kTileValue_linecount                 =	0x00000FD4,
	kTileValue_pagecount                 =	0x00000FD5,
	kTileValue_xdefault                  =	0x00000FD6,
	kTileValue_xup                       =	0x00000FD7,
	kTileValue_xdown                     =	0x00000FD8,
	kTileValue_xleft                     =	0x00000FD9,
	kTileValue_xright                    =	0x00000FDA,

	/* these are defined twice, why?
	kTileValue_xbuttona                  =	0x00000FDD,
	kTileValue_xbuttonb                  =	0x00000FDE,
	kTileValue_xbuttonx                  =	0x00000FDF,
	kTileValue_xbuttony                  =	0x00000FE0,
	kTileValue_xbuttonlt                 =	0x00000FE1,
	kTileValue_xbuttonrt                 =	0x00000FE2,
	kTileValue_xbuttonlb                 =	0x00000FE3,
	kTileValue_xbuttonrb                 =	0x00000FE4,
	*/

	kTileValue_xbuttonstart              =	0x00000FE7,
	kTileValue_mouseoversound            =	0x00000FE8,
	kTileValue_draggable                 =	0x00000FE9,
	kTileValue_dragstartx                =	0x00000FEA,
	kTileValue_dragstarty                =	0x00000FEB,
	kTileValue_dragoffsetx               =	0x00000FEC,
	kTileValue_dragoffsety               =	0x00000FED,
	kTileValue_dragdeltax                =	0x00000FEE,
	kTileValue_dragdeltay                =	0x00000FEF,
	kTileValue_dragx                     =	0x00000FF0,
	kTileValue_dragy                     =	0x00000FF1,
	kTileValue_wheelable                 =	0x00000FF2,
	kTileValue_wheelmoved                =	0x00000FF3,
	kTileValue_systemcolor               =	0x00000FF4,
	kTileValue_brightness                =	0x00000FF5,
	kTileValue_linegap                   =	0x00000FF7,
	kTileValue_resolutionconverter       =	0x00000FF8,
	kTileValue_texatlas                  =	0x00000FF9,
	kTileValue_rotateangle               =	0x00000FFA,
	kTileValue_rotateaxisx               =	0x00000FFB,
	kTileValue_rotateaxisy               =	0x00000FFC,
	kTileValue_user0                     =	0x00001004,
	kTileValue_user1                     =	0x00001005,
	kTileValue_user2                     =	0x00001006,
	kTileValue_user3                     =	0x00001007,
	kTileValue_user4                     =	0x00001008,
	kTileValue_user5                     =	0x00001009,
	kTileValue_user6                     =	0x0000100A,
	kTileValue_user7                     =	0x0000100B,
	kTileValue_user8                     =	0x0000100C,
	kTileValue_user9                     =	0x0000100D,
	kTileValue_user10                    =	0x0000100E,
	kTileValue_user11                    =	0x0000100F,
	kTileValue_user12                    =	0x00001010,
	kTileValue_user13                    =	0x00001011,
	kTileValue_user14                    =	0x00001012,
	kTileValue_user15                    =	0x00001013,
	kTileValue_user16                    =	0x00001014,
	kTileValue_parent                    =	0x00001389,
	kTileValue_me                        =	0x0000138A,
	kTileValue_sibling                   =	0x0000138C,
	kTileValue_child                     =	0x0000138D,
	kTileValue_screen                    =	0x0000138E,
	kTileValue_globals                   =	0x0000138F,
	kTileValue_io                        =	0x00001390,
	kTileValue_grandparent               =	0x00001391,
	kTileValue_does_not_stack            =	0x00001778,
	kTileValue_generic                   =	0xFFFFFFFF,
	kTileValue_scale                     =	0xFFFFFFFF,
	kTileValue_uselocalcolor             =	0xFFFFFFFF,
	kTileValue_nosound                   =	0xFFFFFFFF,
};
