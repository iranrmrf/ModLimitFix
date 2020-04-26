#pragma once

#include "GameTiles.h"
#include "GameMenus.h"

class NiNode;
class NiObject;
class NiTriStrips;
class NiSourceTexture;
class NiScreenElements;
class NiPointLight;
class TESObjectREFR;
class SceneGraph;

// can be passed to QueueUIMessage to determine Vaultboy icon displayed
enum eEmotion {
	happy	= 0,
	sad		= 1,
	neutral = 2,
	pain	= 3
};

typedef bool (* _QueueUIMessage)(const char* msg, UInt32 emotion, const char* ddsPath, const char* soundName, float msgTime);
extern const _QueueUIMessage QueueUIMessage;

// 170
class FOPipboyManager
{
public:
	FOPipboyManager();
	~FOPipboyManager();

	virtual void	Destroy(bool noDealloc);			
	virtual bool	Unk_01(void);				
	virtual NiObject* GetNiNode08(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual float	Unk_0B(void);		// returns 1.0
	virtual void	Unk_0C(void);		// plays UIPipboyHum sound - open pipboy?
	virtual void	Unk_0D(void);		// plays UIPipboyAccessDown - close pipboy?
	virtual void	Unk_0E(float);
	virtual void	Unk_0F(float);
	virtual void	Unk_10(float);
	virtual void	Unk_11(float);
	virtual void	Unk_12(float);
	virtual void	Unk_13(float);
	virtual void	Unk_14(UInt32 arg0, UInt32 arg1, UInt32 arg2);

	// void	** vtbl
	NiTriStrips			* unk004;		// 004 
	NiNode				* unk008;		// 008
	NiScreenElements	* unk00C;		// 00C
	NiSourceTexture		* unk010;		// 010
	SceneGraph			* sceneGraph;	// 014
	UInt32				unk018;			// 018
	NiPointLight		* unk01C;		// 01C
	void				* unk020;		// 020
	UInt32				unk024;			// 024
	UInt8				unk028;			// 028 not initialized
	UInt8				unk029;			// 029 not initialized
	UInt8				unk02A;			// 02A init'd to 1
	UInt8				unk02B;			// 02B not initialized
	float				unk02C[0x24];	// 02C
	NiSourceTexture		* unk0BC;		// 0BC
	float				unk0C0[5];		// 0C0
	void				* unk0D4;		// 0D4
	void				* unk0D8;		// 0D8
	NiNode				* unk0DC;		// 0DC
	NiTriStrips			* unk0E0;		// 0E0
	UInt32				unk0E4;			// 0E4
	NiTriStrips			* unk0E8[3];	// 0E8
	NiNode				* unk0F4[3];	// 0F4
	NiTriStrips			* unk100;		// 100
	NiNode				* unk104;		// 104
	NiNode				* unk108;		// 108
	float				unk10C[0x0E];	// 10C
	UInt8				unk144;			// 144
	UInt8				pad145[3];		// 145
	UInt32				unk148;			// 148 UInt8? uninitialized
	UInt32				unk14C;			// 14C uninitialized
	UInt8				unk150;			// 150
	UInt8				pad151[3];		// 151
	UInt32				unk154;			// 154 uninitialized
	UInt8				unk158;			// 158
	UInt8				pad159[3];		// 159
	UInt32				unk15C;			// 15C uninitialized
	UInt8				unk160;			// 160
	UInt8				unk161;
	UInt8				unk162;
	UInt8				pad163;
	UInt32				unk164;			// 164 uninitialized
	UInt32				unk168;			// 168 uninitialized
	UInt32				unk16C;			// 16C uninitialized
};

STATIC_ASSERT(sizeof(FOPipboyManager) == 0x170);

// 484
class InterfaceManager
{
public:
	InterfaceManager();
	~InterfaceManager();

	static InterfaceManager * GetSingleton(void);
	static bool	IsMenuVisible(UInt32 menuType);
	static Menu* GetMenuByType(UInt32 menuType);
	static Tile::Value* GetMenuComponentValue(char* componentPath);

	UInt32				flags;							// 000
	SceneGraph			* sceneGraph004;				// 004
	SceneGraph			* sceneGraph008;				// 008
	UInt32				currentMode;
	UInt32				unk010[(0x028 - 0x010) >> 2];	// 00C
	Tile				* cursor;						// 028
	UInt32				unk02C[(0x070 - 0x02C) >> 2];	// 02C
	TESObjectREFR		* debugSelection;				// 070
	UInt32				unk074;							// 074
	UInt32				unk078;							// 078
	UInt32				unk07C;							// 07C
	NiNode				* niNode080;					// 080
	NiNode				* niNode084;					// 084
	UInt32				unk088[(0x09C - 0x088) >> 2];	// 088
	Tile				* menuRoot;						// 09C
	Tile				* unk0A0;						// 0A0 seen "Strings"
	void				* unk0A4;						// 0A4 saw Tile? seen NiNode
	UInt32				unk0A8;							// 0A8
	NiObject			* unk0AC;						// 0AC seen NiAlphaProperty
	UInt32				unk0B0[(0x0CC - 0x0B0) >> 2];	// 0B0
	Tile				* activeTile;					// 0CC
	UInt32				unk0D0[(0x0E4 - 0x0D0) >> 2];	// 0D0
	UInt8				msgBoxButton;					// 0E4 -1 if no button pressed
	UInt8				pad0E5[3];
	UInt32				unk0E8;							// 0E8
	UInt32				unk0EC;							// 0EC
	UInt32				unk0F0;							// 0F0
	UInt32				unk0F4;							// 0F4
	UInt32				unk0F8;							// 0F8
	TESObjectREFR		* crosshairRef;					// 0FC
	UInt32				unk100[(0x174 - 0x100) >> 2];	// 100
	FOPipboyManager		* pipboyManager;				// 174
	UInt32				unk178;							// 178
	NiTArray<UInt32>	array17C;						// 17C NiTPrimitiveArray@PackedMenu@BGSMenuPacker
	UInt32				unk18C[(0x394 - 0x18C) >> 2];	// 18C
	NiObject			* unk394;						// 394 seen NiSourceTexture
	UInt32				unk398[(0x454 - 0x398) >> 2];	// 398
	NiTArray<UInt32>	array454;						// 454 NiTPrimitiveArray@TextureType@BSTextureManager
	NiTArray<UInt32>	array464;						// 464 NiTPrimitiveArray@FilterMode@NiTexturingProperty
	UInt32				unk468[(0x4BC - 0x474) >> 2];	// 474
	UInt32				pipBoyMode;						// 4BC
};

STATIC_ASSERT(sizeof(InterfaceManager) == 0x4C0);
STATIC_ASSERT(offsetof(InterfaceManager, debugSelection) == 0x070);
