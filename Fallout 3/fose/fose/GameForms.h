#pragma once

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	static const UInt32 _TESValueForm_SetValue = 0x0045AE80;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	static const UInt32 _TESValueForm_SetValue = 0x0045C180;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	static const UInt32 _TESValueForm_SetValue = 0x0045BD20;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	static const UInt32 _TESValueForm_SetValue = 0x0045BF90;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	static const UInt32 _TESValueForm_SetValue = 0x0045BE30;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	static const UInt32 _TESValueForm_SetValue = 0x0045BD50;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	static const UInt32 _TESValueForm_SetValue = 0x0045BE20;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	static const UInt32 _TESValueForm_SetValue = 0x0045BEB0;
#else
#error unsupported fallout version
#endif

#include "GameTypes.h"
#include "GameAPI.h"
#include "GameBSExtraData.h"

#include "Utilities.h"

/**** form types ****
 *	
 *	id	name	size	class
 *	00	NONE	n/a		n/a
 *	01	TES4	n/a		n/a
 *	02	GRUP	n/a		n/a
 *	03	GMST	n/a		n/a
 *	04	TXST	A0		BGSTextureSet
 *	05	MICN	24		BGSMenuIcon
 *	06	GLOB	28		TESGlobal
 *	07	CLAS	60		TESClass
 *	08	FACT	48		TESFaction
 *	09	HDPT	50		BGSHeadPart
 *	0A	HAIR	4C		TESHair
 *	0B	EYES	34		TESEyes
 *	0C	RACE	4E4		TESRace
 *	0D	SOUN	68		TESSound
 *	0E	ASPC	3C		BGSAcousticSpace
 *	0F	SKIL	60		TESSkill
 *	10	MGEF	B0		EffectSetting
 *	11	SCPT	54		Script
 *	12	LTEX	28		TESLandTexture
 *	13	ENCH	44		EnchantmentItem
 *	14	SPEL	44		SpellItem
 *	15	ACTI	84		TESObjectACTI
 *	16	TACT	8C		BGSTalkingActivator
 *	17	TERM	9C		BGSTerminal
 *	18	ARMO	180		TESObjectARMO
 *	19	BOOK	C4		TESObjectBOOK
 *	1A	CLOT	154		TESObjectCLOT
 *	1B	CONT	98		TESObjectCONT
 *	1C	DOOR	90		TESObjectDOOR
 *	1D	INGR	A4		IngredientItem
 *	1E	LIGH	C8		TESObjectLIGH
 *	1F	MISC	A8		TESObjectMISC
 *	20	STAT	50		TESObjectSTAT
 *	21	SCOL	50		BGSStaticCollection
 *	22	MSTT	6C		BGSMovableStatic
 *	23	PWAT	50		BGSPlaceableWater
 *	24	GRAS	68		TESGrass
 *	25	TREE	94		TESObjectTREE
 *	26	FLOR	90		TESFlora
 *	27	FURN	88		TESFurniture
 *	28	WEAP	20C		TESObjectWEAP
 *	29	AMMO	AC		TESAmmo
 *	2A	NPC_	1EC		TESNPC
 *	2B	CREA	160		TESCreature
 *	2C	LVLC	68		TESLevCreature
 *	2D	LVLN	68		TESLevCharacter
 *	2E	KEYM	A8		TESKey
 *	2F	ALCH	D8		AlchemyItem
 *	30	IDLM	40		BGSIdleMarker
 *	31	NOTE	80		BGSNote
 *	32	COBJ	B0		BGSConstructibleObject
 *	33	PROJ	C0		BGSProjectile
 *	34	LVLI	44		TESLevItem
 *	35	WTHR	2F4		TESWeather
 *	36	CLMT	58		TESClimate
 *	37	REGN	38		TESRegion
 *	38	NAVI	40		NavMeshInfoMap (not loaded via standard code)
 *	39	CELL	E0		TESObjectCELL
 *	3A	REFR	60		TESObjectREFR
 *	3B	ACHR	n/a		n/a - only used on disk
 *	3C	ACRE	n/a		n/a - only used on disk
 *	3D	PMIS	n/a		n/a
 *	3E	PGRE	n/a		n/a
 *	3F	PBEA	n/a		n/a
 *	40	PFLA	n/a		n/a
 *	41	WRLD	E8		TESWorldSpace
 *	42	LAND	2C		TESObjectLAND
 *	43	NAVM	108		NavMesh
 *	44	TLOD	n/a		n/a - custom loader
 *	45	DIAL	n/a		n/a - custom loader
 *	46	INFO	n/a		n/a - custom loader
 *	47	QUST	6C		TESQuest
 *	48	IDLE	54		TESIdleForm
 *	49	PACK	80		TESPackage
 *	4A	CSTY	108		TESCombatStyle
 *	4B	LSCR	3C		TESLoadScreen
 *	4C	LVSP	44		TESLevSpell
 *	4D	ANIO	3C		TESObjectANIO
 *	4E	WATR	190		TESWaterForm
 *				194 after patch 1.5
 *	4F	EFSH	170		TESEffectShader
 *	50	TOFT	n/a		n/a - used by loader
 *	51	EXPL	A4		BGSExplosion
 *	52	DEBR	24		BGSDebris
 *	53	IMGS	B0		TESImageSpace
 *	54	IMAD	728		TESImageSpaceModifier
 *	55	FLST	20		BGSListForm
 *				24 after 1.1
 *	56	PERK	50		BGSPerk
 *	57	BPTD	74		BGSBodyPartData
 *	58	ADDN	60		BGSAddonNode
 *	59	AVIF	C4		ActorValueInfo
 *	5A	RADS	20		BGSRadiationStage
 *	5B	CAMS	78		BGSCameraShot
 *	5C	CPTH	38		BGSCameraPath
 *	5D	VTYP	24		BGSVoiceType
 *	5E	IPCT	78		BGSImpactData
 *	5F	IPDS	4C		BGSImpactDataSet
 *	60	ARMA	180		TESObjectARMA
 *	61	ECZN	30		BGSEncounterZone
 *	62	MESG	40		BGSMessage
 *	63	RGDL	148		BGSRagdoll
 *	64	DOBJ	n/a		n/a
 *	65	LGTM	44		BGSLightingTemplate
 *	66	MUSC	30		BGSMusicType
 *	
 ****/

enum FormType 
{
	kFormType_None = 0,
	kFormType_TES4,
	kFormType_Group,
	kFormType_GMST,
	kFormType_TextureSet,
	kFormType_MenuIcon,
	kFormType_Global,
	kFormType_Class,
	kFormType_Faction,
	kFormType_HeadPart,
	kFormType_Hair,
	kFormType_Eyes,
	kFormType_Race,
	kFormType_Sound,
	kFormType_AcousticSpace,
	kFormType_Skill,
	kFormType_Effect,			// 0x10
	kFormType_Script,
	kFormType_LandTexture,
	kFormType_Enchantment,
	kFormType_Spell,
	kFormType_Activator,
	kFormType_TalkingActivator,
	kFormType_Terminal,
	kFormType_Armor,
	kFormType_Book,
	kFormType_Clothing,
	kFormType_Container,
	kFormType_Door,
	kFormType_Ingredient,
	kFormType_Light,
	kFormType_Misc,
	kFormType_Static,			// 0x20
	kFormType_StaticCollection,
	kFormType_MoveableStatic,
	kFormType_PlaceableWater,
	kFormType_Grass,
	kFormType_Tree,
	kFormType_Flora,
	kFormType_Furniture,
	kFormType_Weapon,
	kFormType_Ammo,
	kFormType_NPC,
	kFormType_Creature,
	kFormType_LeveledCreature,
	kFormType_LeveledCharacter,
	kFormType_Key,
	kFormType_AlchemyItem,
	kFormType_IdleMarker,			// 0x30
	kFormType_Note,
	kFormType_ConstructibleObject,
	kFormType_Projectile,
	kFormType_LeveledItem,
	kFormType_Weather,
	kFormType_Climate,
	kFormType_Region,
	kFormType_NAVI,
	kFormType_Cell,
	kFormType_Reference,
	kFormType_ACHR,
	kFormType_ACRE,
	kFormType_PMIS,
	kFormType_PGRE,
	kFormType_PBEA,
	kFormType_PFLA,					// 0x40
	kFormType_WorldSpace,
	kFormType_Land,
	kFormType_NavMesh,
	kFormType_TLOD,
	kFormType_DIAL,
	kFormType_INFO,
	kFormType_Quest,
	kFormType_Idle,
	kFormType_Package,
	kFormType_CombatStyle,
	kFormType_LoadScreen,
	kFormType_LeveledSpell,
	kFormType_ANIO,
	kFormType_WaterForm,
	kFormType_EffectShader,
	kFormType_TOFT,				// 0x50
	kFormType_Explosion,
	kFormType_Debris,
	kFormType_ImageSpace,
	kFormType_ImageSpaceModifier,
	kFormType_ListForm,
	kFormType_Perk,
	kFormType_BodyPartData,
	kFormType_AddonNode,
	kFormType_ActorValueInfo,
	kFormType_RadiationStage,
	kFormType_CameraShot,
	kFormType_CameraPath,
	kFormType_VoiceType,
	kFormType_ImpactData,
	kFormType_ImpactDataSet,
	kFormType_ARMA,				// 0x60
	kFormType_EncounterZone,
	kFormType_Message,
	kFormType_Ragdoll,
	kFormType_DOBJ,
	kFormType_LightingTemplate,
	kFormType_SoundFile
};

class BoundObjectListHead;
class TESSound;
class BGSImpactDataSet;
class TESObjectSTAT;
class EnchantmentItem;
class TESCombatStyle;
class BGSBodyPartData;
class TESAmmo;
class BGSListForm;
class TESRace;
class BGSProjectile;
class SpellItem;
class TESModel;
class TESQuest;
struct ModInfo;		// in GameData.h 
class TESFullName;
class EffectSetting;
class BSPortalGraph;
class BGSLightingTemplate;
class NiNode;
class TESObjectLAND;
class TESWorldSpace;
class TESImageSpace;
class Character;
class TESWaterForm;
class TESFaction;
class BGSVoiceType;
class FaceGenUndo;

/**** bases ****/

class BaseFormComponent
{
public:
	BaseFormComponent();
	~BaseFormComponent();

	virtual void	Init(void);
	virtual void	Free(void);
	virtual void	CopyFromBase(BaseFormComponent * component);
	virtual bool	CompareWithBase(BaseFormComponent * src);

//	void		** _vtbl;	// 000
};

// 018
class TESForm : public BaseFormComponent
{
public:
	TESForm();
	~TESForm();

	virtual void *	Destroy(bool noDealloc);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual bool	Unk_07(void);
	virtual bool	LoadForm(ModInfo * modInfo);	
	virtual bool	Unk_09(void);
	virtual void	Unk_0A(void * arg);
	virtual void	SaveForm(void);	// saves in same format as in .esp
									// data buffer and buffer size stored in globals when done, doesn't return anything
	virtual bool	LoadForm2(ModInfo * modInfo);	// just calls LoadForm
	virtual void	Unk_0D(void * arg);	// does some saving stuff, then calls Fn0A
	virtual bool	Unk_0E(void * arg);	// updates current form info ptr, returns
	virtual bool	Sort(TESForm * form);	// returns if the argument is "greater or equal" to this form
	virtual void *	Unk_10(void * arg0, void * arg1);	// makes a new form, 
	virtual void	Unk_11(void * arg);
	virtual void	MarkAsModified(UInt32 flags);	// enable changed flag?
	virtual void	Unk_13(UInt32 flags);	// disable changed flag?
	virtual UInt32	GetSaveSize(UInt32 changedFlags);	// bytes taken by the delta flags for this form
	virtual void	Unk_15(void * arg);	// collect referenced forms?
	virtual void	SaveGame(UInt32 changedFlags);
	virtual void	LoadGame(void * arg);	// load from arg
	virtual void	LoadGame2(UInt32 changedFlags);	// load from TESSaveLoadGame
	virtual void	Unk_19(void * arg);
	virtual void	Unk_1A(void * arg0, void * arg1);
	virtual void	Unk_1B(void * arg0, void * arg1);
	virtual void	Revert(UInt32 changedFlags);		// reset changes in form
	virtual void	Unk_1D(void * arg);
	virtual void	Unk_1E(void * arg);
	virtual bool	Unk_1F(void * arg);
	virtual void	Unk_20(void * arg);
	virtual void	Unk_21(void * arg);
	virtual void	InitItem(void);
	virtual UInt32	GetTypeID(void);
	virtual void	GetDebugName(String * dst);
	virtual bool	IsQuestItem(void);
										// Unk_26 though Unk_36 get or set flag bits
	virtual bool	Unk_26(void);		// 00000040
	virtual bool	Unk_27(void);		// 00010000
	virtual bool	Unk_28(void);		// 00010000
	virtual bool	Unk_29(void);		// 00020000
	virtual bool	Unk_2A(void);		// 00020000
	virtual bool	Unk_2B(void);		// 00080000
	virtual bool	Unk_2C(void);		// 02000000
	virtual bool	Unk_2D(void);		// 40000000
	virtual bool	Unk_2E(void);		// 00000200
	virtual void	Unk_2F(bool set);	// 00000200
	virtual bool	Unk_30(void);		// returns false
	virtual void	Unk_31(bool set);	// 00000020 then calls Fn12
	virtual void	Unk_32(bool set);	// 00000002 with a lot of housekeeping
	virtual void	SetQuestItem(bool set);	// 00000400 then calls Fn12
	virtual void	Unk_34(bool set);	// 00000040 then calls Fn12
	virtual void	Unk_35(bool set);	// 00010000 then calls Fn12
	virtual void	Unk_36(bool set);	// 00020000
	virtual void	Unk_37(void);		// write esp format
	virtual void	Unk_38(ModInfo * modInfo);	// read esp format
	virtual bool	Unk_39(void);
	virtual bool	Unk_3A(void);
	virtual bool	Unk_3B(void);
	virtual bool	Unk_3C(void);	// is REFR
	virtual bool	Unk_3D(void);
	virtual bool	Unk_3E(void);
	virtual bool	Unk_3F(void);
	virtual bool	Unk_40(void);
	virtual UInt32	Unk_41(void);
	virtual void	CopyFrom(const TESForm * form);
	virtual bool	Compare(TESForm * form);
	virtual bool	Unk_44(void * arg);	// does some comparisons against things in the form info list that are always 0
	virtual void	Unk_45(void * dst, void * arg1);	// init dst with info from form info list
	virtual bool	Unk_46(void);
	virtual bool	Unk_47(void);
	virtual bool	Unk_48(UInt32 formType);	// returns if the same FormType is passed in
	virtual bool	Unk_49(void * arg0, void * arg1, void * arg2, void * arg3, void * arg4);
	virtual void	SetRefID(UInt32 refID, bool generateID);
	virtual char *	GetName2(void);
	virtual char *	GetName(void);
	virtual bool	SetEditorID(const char * edid);		// simply returns true at run-time
	// 4E

	enum
	{
		kFormFlags_Initialized	=	0x00000008,	// set by TESForm::InitItem()
		kFormFlags_QuestItem =		0x00000400,
		kFormFlags_DontSaveForm =   0x00004000,	// TODO: investigate
	};

	enum
	{
		kModified_Flags =	0x00000001
		//	UInt32	flags;
	};

	UInt8	typeID;					// 004
	UInt8	typeIDPad[3];			// 005
	UInt32	flags;					// 008
	UInt32	refID;					// 00C
	tList<ModInfo> mods;			// 010 ModReferenceList in Oblivion	
	// 018

	TESForm *		TryGetREFRParent(void);
	UInt8			GetModIndex() const;
	TESFullName*	GetFullName();
	bool			IsCloned() const;

	bool IsWeapon() { return typeID == kFormType_Weapon; }
	bool IsArmor() { return typeID == kFormType_Armor; }

	// return a new base form which is the clone of this form
	TESForm* CloneForm(bool bPersist = true) const;
};

class TESObject : public TESForm
{
public:
	TESObject();
	~TESObject();

	virtual void *	Unk_4E(void);
	virtual bool	Unk_4F(void);
	virtual void *	Unk_50(void);
	virtual bool	Unk_51(void);
	virtual void	Unk_52(void * arg);
	virtual void *	Unk_53(void * arg0, void * arg1);
	virtual void	Unk_54(void * arg);
	virtual bool	IsInternal(void);
	virtual bool	IsInternalMarker(void);
	virtual void	Unk_57(void);
	virtual bool	Unk_58(void);
	virtual bool	Unk_59(void * arg);
	virtual void	Unk_5A(void * arg0, void * arg1);
	virtual bool	Unk_5B(void);
	virtual bool	Unk_5C(void);
	virtual void	Unk_5D(void * arg);
};

// 30
class TESBoundObject : public TESObject
{
public:
	TESBoundObject();
	~TESBoundObject();

	virtual void *	Unk_5E(void * arg);	// calls Fn53
	virtual bool	Unk_5F(void);

	BoundObjectListHead		* head;		// 018
	TESBoundObject			* prev;		// 01C
	TESBoundObject			* next;		// 020
	UInt16					bounds[6];	// 024
};

// C
class TESFullName : public BaseFormComponent
{
public:
	TESFullName();
	~TESFullName();

	String	name;		// 004
};

// 00C
class TESTexture : public BaseFormComponent
{
public:
	TESTexture();
	~TESTexture();

	virtual UInt32	Unk_04(void);
	virtual void	GetNormalMap(String * str);
	virtual char *	GetPathRoot(void);

	String ddsPath;
};

// 00C
class TESIcon : public TESTexture
{
public:
	TESIcon();
	~TESIcon();

	void SetPath(const char* newPath)	{ ddsPath.Set(newPath); }
};

// 010
class BGSMessageIcon : public BaseFormComponent
{
public:
	BGSMessageIcon();
	~BGSMessageIcon();

	TESIcon	icon;		// 004
};

// C
class TESScriptableForm : public BaseFormComponent
{
public:
	TESScriptableForm();
	~TESScriptableForm();

	Script	* script;	// 004
	UInt8	unk1;		// 008
	UInt8	pad[3];		// 009
};

// 008
class TESValueForm : public BaseFormComponent
{
public:
	enum
	{
		kModified_GoldValue =	0x00000008,
			// UInt32	value
	};

	TESValueForm();
	~TESValueForm();

	virtual UInt32	GetSaveSize(UInt32 changedFlags);
	virtual void	Save(UInt32 changedFlags);
	virtual void	Load(UInt32 changedFlags);

	DEFINE_MEMBER_FN_LONG(TESValueForm, SetValue, void, _TESValueForm_SetValue, UInt32 newVal);

	UInt32	value;
	// 008
};

// 10
class TESEnchantableForm : public BaseFormComponent
{
public:
	TESEnchantableForm();
	~TESEnchantableForm();

	virtual UInt32	Unk_04(void);	// returns unk2

	EnchantmentItem* enchantItem;	// 04
	UInt16	enchantment;			// 08
	UInt16	unk1;					// 0A
	UInt32	unk2;					// 0C
	// 010
};

// 08
class TESImageSpaceModifiableForm : public BaseFormComponent
{
public:
	TESImageSpaceModifiableForm();
	~TESImageSpaceModifiableForm();

	UInt32	unk04;	// 04
};

// 008
class TESWeightForm : public BaseFormComponent
{
public:
	TESWeightForm();
	~TESWeightForm();

	float	weight;		// 004
	// 008
};

// 008
class TESHealthForm : public BaseFormComponent
{
public:
	TESHealthForm();
	~TESHealthForm();

	virtual UInt32	GetHealth(void);

	UInt32	health;		// 004
};

// 008
class TESAttackDamageForm : public BaseFormComponent
{
public:
	TESAttackDamageForm();
	~TESAttackDamageForm();

	virtual UInt16	GetDamage(void);

	UInt16	damage;	// 04
	UInt16	unk0;	// 06 - bitmask? perhaps 2 UInt8s?
	// 008
};

// 24
class EffectItem {
public:
	EffectItem();
	~EffectItem();

	enum {
		kRange_Self = 0,
		kRange_Touch,
		kRange_Target,
	};

	struct ScriptEffectInfo
	{
		UInt32 scriptRefID;
		UInt32 school;
		String effectName;
		UInt32 visualEffectCode;
		UInt32 isHostile;

		void SetName(const char* name);
		void SetSchool(UInt32 school);
		void SetVisualEffectCode(UInt32 code);
		void SetIsHostile(bool bIsHostile);
		bool IsHostile() const;
		void SetScriptRefID(UInt32 refID);

		ScriptEffectInfo* Clone() const;
		void CopyFrom(const ScriptEffectInfo* from);
		static ScriptEffectInfo* Create();
	};

	// mising flags
	UInt32	effectCode;			// 00
	UInt32	magnitude;			// 04
	UInt32	area;				// 08
	UInt32	duration;			// 0C
	UInt32	range;				// 10
	UInt32	actorValueOrOther;	// 14
	ScriptEffectInfo	* scriptEffectInfo;	// 18
	EffectSetting	* setting;	// 1C
	float	cost;				// 20 on autocalc items this seems to be the cost

	//bool HasActorValue() const;
	//UInt32 GetActorValue() const;
	//bool IsValidActorValue(UInt32 actorValue) const;
	//void SetActorValue(UInt32 actorValue);

	//bool IsScriptedEffect() const;
	//UInt32 ScriptEffectRefId() const;
	//UInt32 ScriptEffectSchool() const;
	//UInt32 ScriptEffectVisualEffectCode() const;
	//bool IsScriptEffectHostile() const;

	//EffectItem* Clone() const;
	//void CopyFrom(const EffectItem* from);
	//static EffectItem* Create();
	//static EffectItem* ProxyEffectItemFor(UInt32 effectCode);
	//
	//bool operator<(EffectItem*rhs) const;
	//// return the magicka cost of this effect item
	//// adjust for skill level if actorCasting is used
	//float MagickaCost(TESForm* actorCasting = NULL) const;

	//void SetMagnitude(UInt32 magnitude);
	//void ModMagnitude(float modBy);
	//void SetArea(UInt32 area);
	//void ModArea(float modBy);
	//void SetDuration(UInt32 duration);
	//void ModDuration(float modBy);
	//void SetRange(UInt32 range);
	//bool IsHostile() const;
};

// C
class EffectItemList : public BSSimpleList<EffectItem>
{
public:
	EffectItemList();
	~EffectItemList();

	EffectItem* ItemAt(UInt32 whichItem);
	UInt32 CountItems() const;
	const char* GetNthEIName(UInt32 whichEffect) const;

//	bool HasNonHostileItem() const;
//	UInt32 CountHostileItems() const;
//	UInt32 AddItem(EffectItem* effectItem);
//	UInt32 AddItemCopy(EffectItem* effectItem);
//	UInt32 CopyItemFrom(EffectItemList& fromList, UInt32 whichItem);
//	bool RemoveItem(UInt32 whichItem);
};

STATIC_ASSERT(sizeof(EffectItemList) == 0xC);

// 1C
class MagicItem : public TESFullName
{
public:
	MagicItem();
	~MagicItem();

	// pure virtual args/return values unknown
	virtual void	Unk_04(void); // pure virtual
	virtual void	Unk_05(void); // pure virtual
	virtual void	Unk_06(void); // pure virtual
	virtual bool	Unk_07(void);
	virtual bool	Unk_08(void);
	virtual void	Unk_09(void); // pure virtual
	virtual void	Unk_0A(void); // pure virtual
	virtual void	Unk_0B(void); // pure virtual
	virtual void	Unk_0C(void); // pure virtual
	virtual void	Unk_0D(void); // pure virtual
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void); // pure virtual

	EffectItemList	list;	// 00C
	UInt32	unk018;			// 018
	// perhaps types are no longer correct!
	enum EType{
		kType_None = 0,
		kType_Spell = 1,
		kType_Enchantment = 2,
		kType_Alchemy = 3,
		kType_Ingredient = 4,
	};
	EType Type() const;
};

STATIC_ASSERT(sizeof(MagicItem) == 0x1C);

// 034
class MagicItemForm : public TESForm
{
public:
	MagicItemForm();
	~MagicItemForm();

	virtual void	ByteSwap(void); // pure virtual

	// base
	MagicItem	magicItem;	// 018
};

STATIC_ASSERT(sizeof(MagicItemForm) == 0x34);

// 18
class TESModel : public BaseFormComponent
{
public:
	TESModel();
	~TESModel();

	enum
	{
		kFacegenFlag_Head =			0x01,
		kFacegenFlag_Torso =		0x02,
		kFacegenFlag_RightHand =	0x04,
		kFacegenFlag_LeftHand =		0x08,
	};

	virtual void *	Destroy(bool noDealloc);	// 04
	virtual char *	GetPath(void);
	virtual void	SetPath(char * path);		// 06

	String	nifPath;		// 04
	UInt32	unk0C;			// 0C
	void	* unk10;		// 10
	UInt8	facegenFlags;	// 14
	UInt8	pad15[3];		// 15

	void SetPath(const char* newPath)	{ nifPath.Set(newPath); }
};

// 18
class BGSTextureModel : public TESModel
{
public:
	BGSTextureModel();
	~BGSTextureModel();
};

// 020
class TESModelTextureSwap : public TESModel
{
public:
	TESModelTextureSwap();
	~TESModelTextureSwap();

	virtual void *	Destroy(bool noDealloc);
	virtual char *	GetPath(void);
	virtual void	SetPath(char * path);
	virtual void *	Unk_07(void);

	UInt32 unk018;		// 018
	UInt32 unk01C;		// 01C
};


// 008
class BGSClipRoundsForm : public BaseFormComponent
{
public:
	BGSClipRoundsForm();
	~BGSClipRoundsForm();

	UInt8	clipRounds;
	UInt8	padding[3];
	// 008
};

// 008
class BGSDestructibleObjectForm : public BaseFormComponent
{
public:
	BGSDestructibleObjectForm();
	~BGSDestructibleObjectForm();

	void	* unk004;
};

// 00C
class BGSPickupPutdownSounds : public BaseFormComponent
{
public:
	BGSPickupPutdownSounds();
	~BGSPickupPutdownSounds();

	TESSound	* unk004;		// 004
	TESSound	* unk008;		// 008
};

// 008
class BGSAmmoForm : public BaseFormComponent
{
public:
	BGSAmmoForm();
	~BGSAmmoForm();

	TESAmmo	* ammo;	// 04
};

// 008
class BGSRepairItemList : public BaseFormComponent
{
public:
	BGSRepairItemList();
	~BGSRepairItemList();

	BGSListForm	* listForm;	// 04
};

// 008
class BGSEquipType : public BaseFormComponent
{
public:
	BGSEquipType();
	~BGSEquipType();

	UInt32	equipType;	// 08
};

// 004
class BGSPreloadable : public BaseFormComponent
{
public:
	BGSPreloadable();
	~BGSPreloadable();

	virtual void	Fn_04(void); // pure virtual
};

// 008
class BGSBipedModelList : public BaseFormComponent
{
public:
	BGSBipedModelList();
	~BGSBipedModelList();
	UInt32	unk004;		// 004
	// 008
};

// 018
class TESModelRDT : public TESModel
{
public:
	TESModelRDT();
	~TESModelRDT();

	virtual UInt32	Fn_07(void);
};

// 0DC
class TESBipedModelForm : public BaseFormComponent
{
public:
	TESBipedModelForm();
	~TESBipedModelForm();

	// bit indices starting from lsb
	enum EPartBit {
		ePart_Head = 0,
		ePart_Hair,
		ePart_UpperBody,
		ePart_LeftHand,
		ePart_RightHand,
		ePart_Weapon,
		ePart_PipBoy,
		ePart_Backpack,
		ePart_Necklace,
		ePart_Headband,
		ePart_Hat,
		ePart_Eyeglasses,
		ePart_Nosering,
		ePart_Earrings,
		ePart_Mask,
		ePart_Choker,
		ePart_MouthObject,
		ePart_BodyAddon1,
		ePart_BodyAddon2,
		ePart_BodyAddon3
	};

	enum ESlot {
		eSlot_Head =		0x1 << ePart_Head,
		eSlot_Hair =		0x1 << ePart_Hair,
		eSlot_UpperBody =	0x1 << ePart_UpperBody,
		eSlot_LeftHand =	0x1 << ePart_LeftHand,
		eSlot_RightHand =	0x1 << ePart_RightHand,
		eSlot_Weapon =		0x1 << ePart_Weapon,
		eSlot_PipBoy =		0x1 << ePart_PipBoy,
		eSlot_Backpack =	0x1 << ePart_Backpack,
		eSlot_Necklace =	0x1 << ePart_Necklace,
		eSlot_Headband =	0x1 << ePart_Headband,
		eSlot_Hat =			0x1 << ePart_Hat,
		eSlot_Eyeglasses =	0x1 << ePart_Eyeglasses,
		eSlot_Nosering =	0x1 << ePart_Nosering,
		eSlot_Earrings =	0x1 << ePart_Earrings,
		eSlot_Mask =		0x1 << ePart_Mask,
		eSlot_Choker =		0x1 << ePart_Choker,
		eSlot_MouthObject=	0x1 << ePart_MouthObject,
		eSlot_BodyAddon1 =	0x1 << ePart_BodyAddon1,
		eSlot_BodyAddon2 =	0x1 << ePart_BodyAddon2,
		eSlot_BodyAddon3 =	0x1 << ePart_BodyAddon3
	};

	enum EBipedFlags {
		eBipedFlag_PowerArmor = 0x20
	};

	// missing part mask and flags
	UInt32					partMask;			// 004
	UInt32					bipedFlags;			// 008
	TESModelTextureSwap		bipedModel[2];		// 00C
	TESModelTextureSwap		groundModel[2];		// 04C
	TESIcon					icon[2];			// 08C
	BGSMessageIcon			messageIcon[2];		// 0A4
	TESModelRDT				modelRDT;			// 0C4
	// 0DC

	static UInt32 MaskForSlot(UInt32 mask);

	bool IsPowerArmor() const { return (bipedFlags & eBipedFlag_PowerArmor) == eBipedFlag_PowerArmor; }
	void SetPowerArmor(bool bPA) {
		if (bPA) {
			bipedFlags |= eBipedFlag_PowerArmor;
		} else {
			bipedFlags &= ~eBipedFlag_PowerArmor;
		}
	}
};

STATIC_ASSERT(sizeof(TESBipedModelForm) == 0x0DC);

// 30
class TESBoundAnimObject : public TESBoundObject
{
public:
	TESBoundAnimObject();
	~TESBoundAnimObject();
};

// 00C
class TESContainer : public BaseFormComponent
{
public:
	TESContainer();
	~TESContainer();

	struct FormCount
	{
		SInt32 count;
		TESForm* form;
	};

	tList<FormCount> formCountList;	// 004
	// 00C
};

// 00C
class BGSTouchSpellForm : public BaseFormComponent
{
public:
	BGSTouchSpellForm();
	~BGSTouchSpellForm();

	UInt32	unk04;		// 04
	UInt16	unk08;		// 08
	UInt16	pad0A;		// 0A
};

// 034
class TESActorBaseData : public BaseFormComponent
{
public:
	TESActorBaseData();
	~TESActorBaseData();

	virtual void			Fn_04(void * arg);
											// flags access
	virtual bool			Fn_05(void);	// 00100000
	virtual bool			Fn_06(void);	// 00200000
	virtual bool			Fn_07(void);	// 10000000
	virtual bool			Fn_08(void);	// 20000000
	virtual bool			Fn_09(void);	// 80000000
	virtual bool			Fn_0A(void);	// 00400000
	virtual bool			Fn_0B(void);	// 00400000
	virtual bool			Fn_0C(void);	// 00800000
	virtual bool			Fn_0D(void);
	virtual bool			Fn_0E(void);
	virtual bool			Fn_0F(void);
	virtual bool			Fn_10(void);
	virtual bool			Fn_11(void);
	virtual bool			Fn_12(void);
	virtual void			Fn_13(void * arg);
	virtual bool			Fn_14(void);
	virtual void			Fn_15(void * arg);
	virtual UInt32			Fn_16(void);
	virtual void			Fn_17(void * arg);
	virtual UInt32			Fn_18(void);	// return unk08
	virtual float			Fn_19(void);	// return unk14
	virtual BGSVoiceType *	GetVoiceType(void);

	enum {
		kFlags_Female		= 1 << 0,
	};

	struct FactionListData
	{
		TESFaction	* faction;
		UInt8		rank;
		UInt8		pad[3];
	};

	UInt32			flags;		// 04
	UInt16			unk08;		// 08
	UInt16			unk0A;		// 0A
	UInt16			unk0C;		// 0C
	UInt16			unk0E;		// 0E
	UInt16			unk10;		// 10
	UInt16			unk12;		// 08
	float			unk14;		// 14
	UInt16			unk18;		// 18
	UInt16			unk1A;		// 1A
	UInt32			unk1C;		// 1C
	BGSVoiceType	* voiceType;// 20
	UInt32			unk24;		// 24
	UInt32			unk28;		// 28
	tList<FactionListData>	factionList;	// 2C

	SInt8 GetFactionRank(TESFaction* faction);

	bool IsFemale() { return flags & kFlags_Female ? true : false; }	// place holder until GECK 
};

// 14
class TESSpellList : public BaseFormComponent
{
public:
	enum
	{
		kModified_BaseSpellList =	0x00000020,
			// CHANGE_ACTOR_BASE_SPELLLIST
			//	UInt16	numSpells;
			//	UInt32	spells[numSpells];
	};

	TESSpellList();
	~TESSpellList();

	virtual UInt32	GetSaveSize(UInt32 changedFlags);
	virtual void	Save(UInt32 changedFlags);
	virtual void	Load(UInt32 changedFlags);

	tList<SpellItem>	spellList;	// 004
	UInt32	unk2;					// 00C
	UInt32	unk3;					// 010

	UInt32	GetSpellCount() const {
		return spellList.Count();
	}

	// return the nth spell
	SpellItem* GetNthSpell(SInt32 whichSpell) const
	{
		return spellList.GetNthItem(whichSpell);
	}

	// removes all spells and returns how many spells were removed
	//UInt32 RemoveAllSpells();
};

// 020
class TESAIForm : public BaseFormComponent
{
public:
	TESAIForm();
	~TESAIForm();

	virtual UInt32	GetSaveSize(UInt32 changedFlags);
	virtual void	Save(UInt32 changedFlags);
	virtual void	Load(UInt32 changedFlags);

	UInt8	unk04;		// 04
	UInt8	unk05;		// 05
	UInt8	unk06;		// 06
	UInt8	unk07;		// 07
	UInt8	unk08;		// 08
	UInt8	pad09[3];	// 09

	UInt32	unk0C;		// 0C
	UInt8	unk10;		// 10
	UInt8	unk11;		// 11
	UInt8	unk12;		// 12
	UInt8	unk13;		// 13
	UInt32	unk14;		// 14

	UInt32 packageList[(0x020-0x018) >> 2];	// 18 (tList?)
};

// 00C
class TESAttributes : public BaseFormComponent
{
public:
	TESAttributes();
	~TESAttributes();

	enum
	{
		kStrength = 0,
		kPerception,
		kEndurance,
		kCharisma,
		kIntelligence,
		kAgility,
		kLuck,
	};

	UInt8	attributes[7];	// 4
	UInt8	padB;			// B
};

// 00C
class TESAnimation : public BaseFormComponent
{
public:
	TESAnimation();
	~TESAnimation();

	UInt32	unk004;
	UInt32	unk008;
	// 00C
};

class ActorValueOwner
{
public:
	ActorValueOwner();
	~ActorValueOwner();

	virtual UInt32	GetBaseActorValue(UInt32 avCode);		// GetBaseActorValue (used from Eval) result in EAX
	virtual float	GetBaseAVFloat(UInt32 avCode);			// GetBaseActorValue internal, result in st
	virtual float	Fn_02(UInt32 avCode);					// GetActorValue internal, result in EAX
	virtual float	GetActorValue(UInt32 avCode);			// GetActorValue (used from Eval) result in EAX
	virtual float	Fn_04(UInt32 avCode);					// GetBaseActorValue04 (internal) result in st
	virtual float	GetActorValueDamage(UInt32 avCode);
	virtual float	Fn_06(UInt32 avCode);					// GetDamageActorValue or GetModifiedActorValue		called from Fn_08, result in st, added to Fn_01
	virtual UInt32	Fn_07(UInt32 avCode);					// Manipulate GetPermanentActorValue, maybe convert to integer.
	virtual float	GetPermanentActorValue(UInt32 avCode);	// GetPermanentActorValue (used from Eval) result in EAX
	virtual void* Fn_09(void);							// GetActorBase (= this - 0x100) or GetActorBase (= this - 0x0A4)
	virtual UInt16	GetLevel();								// GetLevel (from ActorBase)

};

STATIC_ASSERT(sizeof(ActorValueOwner) == 0x004);

class CachedValuesOwner
{
public:
	CachedValuesOwner();
	~CachedValuesOwner();

	virtual float	Fn_00(void);
	virtual float	Fn_01(void);
	virtual float	Fn_02(void);
	virtual float	Fn_03(void);
	virtual float	Fn_04(void);
	virtual float	Fn_05(void);
	virtual float	Fn_06(void);
	virtual float	Fn_07(void);
	virtual float	Fn_08(void);
	virtual float	Fn_09(void);
	virtual float	Fn_0A(void);
	virtual UInt32	Fn_0B(void);
	virtual UInt32	Fn_0C(void);
	virtual float	Fn_0D(void);
	virtual float	Fn_0E(void);
	virtual bool	Fn_0F(void);
};

STATIC_ASSERT(sizeof(CachedValuesOwner) == 0x004);

// 10C
class TESActorBase : public TESBoundAnimObject
{
public:
	TESActorBase();
	~TESActorBase();

	virtual BGSBodyPartData *	GetBodyPartData(void);
	virtual void				Fn_61(void * arg);
	virtual UInt32				Fn_62(void);
	virtual void				SetCombatStyle(void * arg);
	virtual void				SetAttr(UInt32 idx, float value);	// calls Fn65
	virtual void				SetAttr(UInt32 idx, UInt32 value);
	virtual void				Fn_66(void * arg0, float arg1);		// mod actor value?
	virtual void				Fn_67(void * arg0, UInt32 arg1);	// mod actor value?

	// bases
	TESActorBaseData			baseData;		// 030
	TESContainer				container;		// 064
	BGSTouchSpellForm			touchSpell;		// 070
	TESSpellList				spellList;		// 07C
	TESAIForm					ai;				// 090
	TESHealthForm				health;			// 0B0
	TESAttributes				attributes;		// 0B8
	TESAnimation				animation;		// 0C4
	TESFullName					fullName;		// 0D0
	TESModel					model;			// 0DC
	TESScriptableForm			scriptable;		// 0F4
	ActorValueOwner				avOwner;		// 100
	BGSDestructibleObjectForm	destructible;	// 104
	// 10C
};

STATIC_ASSERT(offsetof(TESActorBase, avOwner) == 0x100);
STATIC_ASSERT(sizeof(TESActorBase) == 0x10C);

// 14
class TESModelList : public BaseFormComponent
{
public:
	TESModelList();
	~TESModelList();

	void	* unk04;	// 04
	void	* first;	// 08
	void	* next;		// 0C
	UInt32	count;		// 10
};

// 008
class TESDescription : public BaseFormComponent
{
public:
	TESDescription();
	~TESDescription();

	virtual char *	Get(TESForm * overrideForm, UInt32 chunkID);

	UInt32	formDiskOffset;	// 4 - how does this work for descriptions in mods?
							// maybe extracts the mod ID then uses that to find the src file?
};

// 10
class TESReactionForm : public BaseFormComponent
{
public:
	TESReactionForm();
	~TESReactionForm();

	struct Reaction
	{
		enum
		{
			kNeutral = 0,
			kEnemy,
			kAlly,
			kFriend
		};

		TESFaction	* faction;
		SInt32		modifier;
		UInt32		reaction;
	};

	tList <Reaction>	reactions;	// 4
	UInt8	unkC;		// C
	UInt8	padD[3];	// D
};

// 08
class TESRaceForm : public BaseFormComponent
{
public:
	TESRaceForm();
	~TESRaceForm();

	TESRace	* race;	// 04
};

// 8
// ### derives from NiObject
class BSTextureSet
{
public:
	BSTextureSet();
	~BSTextureSet();

	void	* _vtbl;	// 0
	UInt32	unk04;		// 4
};

// C?
class TESSoundFile : public BaseFormComponent
{
public:
	TESSoundFile();
	~TESSoundFile();

	virtual void	Set(const char * str);

	String	path;	// 4
};

// 4+
class BGSQuestObjective
{
public:
	BGSQuestObjective();
	~BGSQuestObjective();

	UInt32		objectiveId;	// 004 Objective Index in the GECK
	String		displayText;	// 008
	TESQuest*	quest;			// 010
	UInt32		unk014;			// 014
	UInt32		unk018;			// 018
	UInt32		unk01C;			// 01C
	UInt32		unk020;			// 020

	virtual void *	Destroy(bool noDealloc);
};

class BGSOpenCloseForm
{
public:
	virtual void	Unk_00(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_01(UInt32 arg0, UInt32 arg1);
	virtual bool	Unk_02(void);

	BGSOpenCloseForm();
	~BGSOpenCloseForm();
};

/**** forms ****/

// 40
class TESTopic : public TESForm
{
public:
	TESTopic();
	~TESTopic();

	TESFullName		fullName;	// 18

	UInt8			unk24;		// 24
	UInt8			pad25[3];	// 25
	float			unk28;		// 28
	UInt32			unk2C;		// 2C
	UInt32			unk30;		// 30
	UInt32			unk34;		// 34
	UInt32			unk38;		// 38
	UInt16			unk3C;		// 3C
	UInt16			unk3E;		// 3E
};

STATIC_ASSERT(offsetof(TESTopic, fullName) == 0x018);

// A0
class BGSTextureSet : public TESBoundObject
{
public:
	BGSTextureSet();
	~BGSTextureSet();

	enum	// texture types
	{
		kDiffuse = 0,
		kNormal,
		kEnvMask,
		kGlow,
		kParallax,
		kEnv
	};

	enum
	{
		kTexFlag_NoSpecMap = 0x0001,
	};

	// 24
	struct DecalInfo
	{
		enum
		{
			kFlag_Parallax =	0x01,
			kFlag_AlphaBlend =	0x02,
			kFlag_AlphaTest =	0x04,
		};

		float	minWidth;		// 00
		float	maxWidth;		// 04
		float	minHeight;		// 08
		float	maxHeight;		// 0C
		float	depth;			// 10
		float	shininess;		// 14
		float	parallaxScale;	// 18
		UInt8	parallaxPasses;	// 1C
		UInt8	flags;			// 1D
		UInt8	pad1E[2];		// 1E
		UInt32	color;			// 20
	};

	BSTextureSet	bsTexSet;		// 30

	TESTexture		textures[6];	// 38
	DecalInfo		* decalInfo;	// 80
	UInt16			texFlags;		// 84
	UInt8			pad86[2];		// 86
	UInt32			unk88;			// 88
	UInt32			unk8C;			// 8C
	UInt32			unk90;			// 90
	UInt32			unk94;			// 94
	UInt32			unk98;			// 98
	UInt32			unk9C;			// 9C
};

STATIC_ASSERT(sizeof(BGSTextureSet) == 0xA0);

// 24
class BGSMenuIcon : public TESForm
{
public:
	BGSMenuIcon();
	~BGSMenuIcon();

	TESIcon	icon;	// 18
};

STATIC_ASSERT(sizeof(BGSMenuIcon) == 0x24);

// 28
class TESGlobal : public TESForm
{
public:
	TESGlobal();
	~TESGlobal();

	enum
	{
		kType_Short =	's',
		kType_Long =	'l',
		kType_Float =	'f'
	};

	String	name;		// 18
	UInt8	type;		// 20
	UInt8	pad21[3];	// 21
	float	data;		// 24
};

STATIC_ASSERT(sizeof(TESGlobal) == 0x28);

// 60
class TESClass : public TESForm
{
public:
	TESClass();
	~TESClass();

	enum
	{
		kFlag_Playable =	0x00000001,
		kFlag_Guard =		0x00000002,
	};

	enum
	{
		kService_Weapons =		0x00000001,
		kService_Armor =		0x00000002,
		kService_Clothing =		0x00000004,
		kService_Books =		0x00000008,
		kService_Food =			0x00000010,
		kService_Chems =		0x00000020,
		kService_Stimpacks =	0x00000040,
		kService_Lights =		0x00000080,	// ??
		kService_Misc =			0x00000400,
		kService_Potions =		0x00002000,	// probably deprecated
		kService_Training =		0x00004000,
		kService_Recharge =		0x00010000,
		kService_Repair =		0x00020000,
	};

	TESFullName		fullName;		// 18
	TESDescription	description;	// 24
	TESTexture		texture;		// 2C
	TESAttributes	attributes;		// 38

	// corresponds to DATA chunk
	UInt32			tagSkills[4];	// 44
	UInt32			classFlags;		// 54
	UInt32			services;		// 58
	UInt8			teaches;		// 5C
	UInt8			trainingLevel;	// 5D
	UInt8			pad5E[2];		// 5E
};

STATIC_ASSERT(sizeof(TESClass) == 0x60);

// 48
class TESFaction : public TESForm
{
public:
	TESFaction();
	~TESFaction();
	enum
	{
		// TESForm flags

		// TESReactionForm flags

		kModified_FactionFlags =	0x00000004
			// CHANGE_FACTION_FLAGS
			// UInt8	flags;
	};

	enum
	{
		kFlag_HiddenFromPC =	0x00000001,
		kFlag_Evil =			0x00000002,
		kFlag_SpecialCombat =	0x00000004,

		kFlag_TrackCrime =		0x00000100,
		kFlag_AllowSell =		0x00000200,
	};

	// 1C
	struct Rank
	{
		String		name;		// 00
		String		femaleName;	// 08
		TESTexture	insignia;	// 10 - effectively unused, can be set but there is no faction UI
	};

	TESFullName		fullName;	// 18
	TESReactionForm	reaction;	// 24

	UInt32			factionFlags;	// 34
	tList <Rank>	ranks;			// 38
	UInt32			crimeCount40;	// 40
	UInt32			crimeCount44;	// 44


	bool IsFlagSet(UInt32 flag) {
		return (factionFlags & flag) != 0;
	}
	void SetFlag(UInt32 flag, bool bMod) {
		factionFlags = bMod ? (factionFlags | flag) : (factionFlags & ~flag);
		MarkAsModified(kModified_FactionFlags);
	}
	bool IsHidden()
		{	return IsFlagSet(kFlag_HiddenFromPC);	}
	bool IsEvil()
		{	return IsFlagSet(kFlag_Evil);	}
	bool HasSpecialCombat()
		{	return IsFlagSet(kFlag_SpecialCombat);	}
	void SetHidden(bool bHidden)
		{	SetFlag(kFlag_HiddenFromPC, bHidden);	}
	void SetEvil(bool bEvil)
		{	SetFlag(kFlag_Evil, bEvil);	}
	void SetSpecialCombat(bool bSpec)
		{	SetFlag(kFlag_SpecialCombat, bSpec);	}
};

STATIC_ASSERT(sizeof(TESFaction) == 0x48);

// 50
class BGSHeadPart : public TESForm
{
public:
	BGSHeadPart();
	~BGSHeadPart();

	enum
	{
		kFlag_Playable =	0x01,
	};

	TESFullName			fullName;	// 18
	TESModelTextureSwap	texSwap;	// 24
	
	UInt8				headFlags;	// 44
	UInt8				pad45[3];	// 45
	UInt32				unk48;		// 48
	UInt32				unk4C;		// 4C
};

STATIC_ASSERT(sizeof(BGSHeadPart) == 0x50);

// 4C
class TESHair : public TESForm
{
public:
	TESHair();
	~TESHair();

	enum
	{
		kFlag_Playable =	0x01,
		kFlag_NotMale =		0x02,
		kFlag_NotFemale =	0x04,
		kFlag_Fixed =		0x08,
	};

	TESFullName		fullName;	// 18
	TESModel		model;		// 24
	TESTexture		texture;	// 3C
	
	UInt8			hairFlags;	// 48
	UInt8			pad49[3];	// 49
};

STATIC_ASSERT(sizeof(TESHair) == 0x4C);

// 34
class TESEyes : public TESForm
{
public:
	TESEyes();
	~TESEyes();

	enum
	{
		kFlag_Playable =	0x01,
		kFlag_NotMale =		0x02,
		kFlag_NotFemale =	0x04,
	};

	TESFullName		fullName;	// 18
	TESTexture		texture;	// 24

	UInt8			eyeFlags;	// 30
	UInt8			pad31[3];	// 31
};

STATIC_ASSERT(sizeof(TESEyes) == 0x34);

// 4E4 - incomplete
class TESRace : public TESForm
{
public:
	// 18
	struct Unk1
	{
		UInt32	unk00;
		UInt32	unk04;
		UInt32	unk08;
		UInt32	unk0C;
		UInt32	unk10;
		UInt32	unk14;
	};

	// 2
	struct SkillMod
	{
		UInt8	actorValue;
		SInt8	mod;
	};

	enum
	{
		kFlag_Playable =	0x00000001,
		kFlag_Child =		0x00000004,
	};

	TESRace();
	~TESRace();

	TESFullName		fullName;	// 018
	TESDescription	desc;		// 024
	TESSpellList	spells;		// 02C
	TESReactionForm	reaction;	// 040

	SkillMod		skillMods[7];	// 050
	UInt8			pad05E[2];		// 05E
	float			maleHeight;		// 060
	float			femaleHeight;	// 064
	float			maleWeight;		// 068
	float			femaleWeight;	// 06C
	UInt32			raceFlags;		// 070

	TESAttributes	unk074;		// 074
	TESAttributes	unk080;		// 080
	UInt32			unk08C;		// 08C
	UInt32			unk090;		// 090

	UInt32			unk094[(0xA8 - 0x94) >> 2];	// 0A8 - uninitialized

	UInt32			unk0A8;		// 0A8
	UInt32			unk0AC;		// 0AC

	TESModel		models0B0[0x10];	// 0B0
	TESTexture		textures230[0x10];	// 230
	TESTexture		textures2F0[6];		// 2F0
	TESModel		models338[6];		// 338
	BGSTextureModel	textures3C8[2];		// 3C8
	Unk1			unk3F8[4];			// 3F8
	Unk1			unk458[4];			// 458

	UInt32			unk4B8[(0x4CC - 0x4B8) >> 2]; // 4B8

	String				name;			// 4CC
	NiTArray <void *>	faceGenUndo;	// 4D4 - NiTPrimitiveArray<FaceGenUndo *>
};

// 68
class TESSound : public TESBoundAnimObject
{
public:
	TESSound();
	~TESSound();

	TESSoundFile	soundFile;	// 30

	UInt32			unk3C;	// 3C
	UInt16			unk40;	// 40
	UInt16			unk42;	// 42
	UInt8			unk44;	// 44
	UInt8			unk45;	// 45
	UInt8			unk46;	// 46
	UInt8			unk47;	// 47
	UInt32			unk48;	// 48
	UInt16			unk4C;	// 4C
	UInt16			unk4E;	// 4E
	UInt16			unk50;	// 50
	UInt16			unk52;	// 52
	UInt16			unk54;	// 54
	UInt16			unk56;	// 56
	UInt16			unk58;	// 58
	UInt16			unk5A;	// 5A
	UInt32			unk5C;	// 5C
	UInt32			unk60;	// 60
	UInt32			unk64;	// 64
};

STATIC_ASSERT(sizeof(TESSound) == 0x68);

// 3C
class BGSAcousticSpace : public TESBoundObject
{
public:
	BGSAcousticSpace();
	~BGSAcousticSpace();

	UInt32	unk30;	// 30
	UInt32	unk34;	// 34
	UInt32	unk38;	// 38
};

STATIC_ASSERT(sizeof(BGSAcousticSpace) == 0x3C);

// 60
class TESSkill : public TESForm
{
public:
	TESSkill();
	~TESSkill();

	TESDescription	description;	// 18
	TESTexture		texture;		// 20

	UInt32			unk2C;			// 2C
	UInt32			unk30;			// 30
	UInt32			unk34;			// 34
	float			unk38;			// 38
	float			unk3C;			// 3C
	TESDescription	desc2[3];		// 40
	UInt32			unk58[(0x60 - 0x58) >> 2];	// 58
};

STATIC_ASSERT(sizeof(TESSkill) == 0x60);

// B0
class EffectSetting : public TESForm
{
public:
	EffectSetting();
	~EffectSetting();

	TESModel		model;			// 18
	TESDescription	description;	// 30
	TESFullName		fullName;		// 38
	TESIcon			icon;			// 44
	UInt32			unk50;			// 50
	UInt32			unk54;			// 54
	UInt32			unk58;			// 58
	float			unk5C;			// 5C
	UInt32			unk60;			// 60
	UInt32			unk64;			// 64
	UInt32			unk68;			// 68
	UInt16			unk6C;			// 6C
	UInt8			pad6E[2];		// 6E
	UInt32			unk70;			// 70
	float			unk74;			// 74
	UInt32			unk78;			// 78
	UInt32			unk7C;			// 7C
	UInt32			unk80;			// 80
	UInt32			unk84;			// 84
	UInt32			unk88;			// 88
	UInt32			unk8C;			// 8C
	float			unk90;			// 90 - fMagicDefaultCEEnchantFactor
	float			unk94;			// 94 - fMagicDefaultCEBarterFactor
	UInt32			unk98;			// 98
	UInt32			unk9C;			// 9C
	UInt32			unkA0;			// A0
	UInt32			unkA4;			// A4
	UInt32			unkA8;			// A8
	UInt32			unkAC;			// AC
};

STATIC_ASSERT(sizeof(EffectSetting) == 0xB0);

// 54
class Script : public TESForm
{
public:
	Script();
	~Script();

	enum {
		eVarType_Float = 0,			//ref is also zero
		eVarType_Integer,
	};

	struct RefVariable
	{
		UInt32	unk0;				// 00
		UInt32	unk1;				// 04
		TESForm	* form;				// 08
		UInt32	varIdx;				// 0C

		void	Resolve(ScriptEventList * eventList);
	};

	struct VariableInfo
	{
		UInt32			idx;		// 00
		UInt32			pad04;		// 04
		double			data;		// 08
		UInt8			type;		// 10
		UInt8			pad11[3];	// 11
		UInt32			unk14;		// 14
		String			name;		// 18
	};

	struct ScriptInfo
	{
		UInt32	unk0;		// 00 (18)
		UInt32	numRefs;	// 04 (1C)
		UInt32	dataLength;	// 08 (20)
		UInt32	varCount;	// 0C (24)
		UInt16	type;		// 10 (28)
		UInt16	unk12;		// 12 (2A)
	};

	enum {
		eType_Object = 0,
		eType_Quest = 1,
		eType_Magic = 0x100,
		eType_Unk = 0x10000,
	};

	ScriptInfo			info;					// 018
	UInt32				unk2C;					// 02C
	void*				data;					// 030
	UInt32				unk34;					// 034
	float				questDelayTimeCounter;	// 038
	float				secondsPassed;			// 03C
	TESQuest*			quest;					// 040
	
	tList<RefVariable>	refs;					// 044
	tList<VariableInfo>	vars;					// 04C

	Script::VariableInfo* GetVariableByName(const char* name);
	Script::RefVariable* GetVariable(UInt32 reqIdx);

	UInt32 AddVariable(TESForm* form);
	void CleanupVariables();

	UInt32			Type() const { return info.type; }
	bool			IsObjectScript() const {return info.type == eType_Object; }
	bool			IsQuestScript() const { return info.type == eType_Quest; }
	bool			IsMagicScript() const { return info.type == eType_Magic; }
	bool			IsUnkScript() const { return info.type == eType_Unk; }
};

STATIC_ASSERT(sizeof(Script) == 0x54);

// 28
class TESLandTexture : public TESForm
{
public:
	TESLandTexture();
	~TESLandTexture();

	UInt32	unk18;	// 18
	UInt8	unk1C;	// 1C
	UInt8	unk1D;	// 1D
	UInt8	unk1E;	// 1E
	UInt8	unk1F;	// 1F
	UInt32	unk20;	// 20
	UInt32	unk24;	// 24
};

STATIC_ASSERT(sizeof(TESLandTexture) == 0x28);

// 44
class EnchantmentItem : public MagicItemForm
{
public:
	EnchantmentItem();
	~EnchantmentItem();

	virtual void	ByteSwap(void);

	UInt32	unk34;		// 34
	UInt32	unk38;		// 38
	UInt32	unk3C;		// 3C
	UInt8	unk40;		// 40
	UInt8	pad41[3];	// 41
};

STATIC_ASSERT(offsetof(EnchantmentItem, unk34) == 0x34);
STATIC_ASSERT(sizeof(EnchantmentItem) == 0x44);

// 44
class SpellItem : public MagicItemForm
{
public:
	SpellItem();
	~SpellItem();

	virtual void	ByteSwap(void);

	UInt32	unk34;		// 34
	UInt32	unk38;		// 38
	UInt32	unk3C;		// 3C
	UInt8	unk40;		// 40
	UInt8	pad41[3];	// 41
};

STATIC_ASSERT(sizeof(SpellItem) == 0x44);

// TESObjectACTI (84)
class TESObjectACTI : public TESBoundAnimObject
{
public:
	TESObjectACTI();
	~TESObjectACTI();

	// bases
	TESFullName					fullName;			// 30
	TESModelTextureSwap			modelTextureSwap;	// 3C
	TESScriptableForm			scriptable;			// 5C
	BGSDestructibleObjectForm	destructible;		// 68
	BGSOpenCloseForm			openClose;			// 70

	UInt32		unk74;			// 74
	UInt32		unk78;			// 78
	UInt32		unk7C;			// 7C
	UInt32		unk80;			// 80
};

STATIC_ASSERT(sizeof(TESObjectACTI) == 0x84);

// BGSTalkingActivator (8C)
class BGSTalkingActivator;

// BGSTerminal (9C)
class BGSTerminal;

// 180
class TESObjectARMO : public TESBoundObject
{
public:
	TESObjectARMO();
	~TESObjectARMO();

	// children
	TESFullName					fullName;		// 030
	TESScriptableForm			scriptable;		// 03C
	TESEnchantableForm			enchantable;	// 048
	TESValueForm				value;			// 058
	TESWeightForm				weight;			// 060
	TESHealthForm				health;			// 068
	TESBipedModelForm			bipedModel;		// 070
	BGSDestructibleObjectForm	destuctible;	// 14C
	BGSEquipType				equipType;		// 154
	BGSRepairItemList			repairItemList;	// 15C
	BGSBipedModelList			bipedModelList; // 164
	BGSPickupPutdownSounds		unk16C;			// 16C
	UInt16						armorRating;	// 178
	UInt16						modifiesVoice;	// 180
	UInt32						armorFlags;		// 17C
	// 180
};
STATIC_ASSERT(sizeof(TESObjectARMO) == 0x180);

// TESObjectBOOK (C4)
class TESObjectBOOK : public TESBoundObject
{
public:
	TESObjectBOOK();
	~TESObjectBOOK();

	enum BookFlags {
		IsScroll = 1,
		CanBeTaken = 2
	};

	TESFullName					fullName;		// 30
	TESModelTextureSwap			model;			// 3C
	TESIcon						icon;			// 5C
	TESScriptableForm			scriptable;		// 68
	TESEnchantableForm			enchantable;	// 74
	TESValueForm				value;			// 84
	TESWeightForm				weight;			// 8C
	TESDescription				description;	// 94
	BGSDestructibleObjectForm	destuctible;	// 9C
	BGSMessageIcon				messageIcon;	// A4
	BGSPickupPutdownSounds		sounds;			// B4

	UInt8						bookFlags;		// C0
	UInt8						skillCode;		// C1
	UInt8						padC2[2];		// C2
};
STATIC_ASSERT(sizeof(TESObjectBOOK) == 0xC4);

// 154
class TESObjectCLOT : public TESBoundObject
{
public:
	TESObjectCLOT();
	~TESObjectCLOT();

	// bases
	TESFullName					fullName;		// 030
	TESScriptableForm			scriptable;		// 03C
	TESEnchantableForm			enchantable;	// 048
	TESValueForm				value;			// 058
	TESWeightForm				weight;			// 060
	TESBipedModelForm			bipedModel;		// 068
	BGSDestructibleObjectForm	destuctible;	// 144
	BGSEquipType				equipType;		// 14C
	// unk data
};

// TESObjectCONT (98)
class TESObjectCONT;

// TESObjectDOOR (90)
class TESObjectDOOR;

// IngredientItem (A4)
class IngredientItem;

// TESObjectLIGH (C8)
class TESObjectLIGH : public TESBoundAnimObject
{
public:
	TESObjectLIGH();
	~TESObjectLIGH();

	TESFullName					fullName;		// 030
	TESModelTextureSwap			modelSwap;		// 03C
	TESIcon						icon;			// 05C
	BGSMessageIcon				messageIcon;	// 068
	TESScriptableForm			scriptable;		// 078
	TESWeightForm				weight;			// 084
	TESValueForm				value;			// 08C
	BGSDestructibleObjectForm	destructible;	// 094
	
	UInt32	unk09C[11];

};
STATIC_ASSERT(sizeof(TESObjectLIGH) == 0x0C8);

// TESObjectMISC (A8)
class TESObjectMISC : public TESBoundObject
{
public:
	TESObjectMISC();
	~TESObjectMISC();
};

// 50
class TESObjectSTAT : public TESBoundObject
{
public:
	TESObjectSTAT();
	~TESObjectSTAT();

	// children
	TESModel	model;	// 
};

// BGSStaticCollection (50)
class BGSStaticCollection;

// BGSMovableStatic (6C)
class BGSMovableStatic;

// BGSPlaceableWater (50)
class BGSPlaceableWater;

// TESGrass (68)
class TESGrass;

// TESObjectTREE (94)
class TESObjectTREE;

// TESFlora (90)
class TESFlora;

// TESFurniture (88)
class TESFurniture;

// 20C
class TESObjectWEAP : public TESBoundObject
{
public:
	TESObjectWEAP();
	~TESObjectWEAP();

	enum EWeaponType {
		kWeapType_HandToHandMelee = 0,
		kWeapType_OneHandMelee,
		kWeapType_TwoHandMelee,
		kWeapType_OneHandPistol,
		kWeapType_OneHandPistolEnergy,
		kWeapType_TwoHandRifle,
		kWeapType_TwoHandAutomatic,
		kWeapType_TwoHandRifleEnergy,
		kWeapType_TwoHandHandle,
		kWeapType_TwoHandLauncher,
		kWeapType_OneHandGrenade,
		kWeapType_OneHandMine,
		kWeapType_OneHandLunchboxMine,
		kWeapType_Last
	};

	enum EWeaponSounds {
		kWeapSound_Shoot3D = 0,
		kWeapSound_Shoot2D,
		kWeapSound_Shoot3DLooping,
		kWeapSound_NoAmmo,
		kWeapSound_Swing = kWeapSound_NoAmmo,
		kWeapSound_Block,
		kWeapSound_Idle,
		kWeapSound_Equip,
		kWeapSound_Unequip
	};

	enum EHandGrip {
		eHandGrip_Default	= 0xff,	// 11111111
		eHandGrip_1			= 0xab,	// 10101011
		eHandGrip_2			= 0xac,	// 10101100
		eHandGrip_3			= 0xad,	// 10101101
		eHandGrip_Count		= 4,
	};

	enum EAttackAnimations {
		eAttackAnim_Default			= 0xff,	// 11111111
		eAttackAnim_Attack3			= 0x26,	// 00100110
		eAttackAnim_Attack4			= 0x2c, // 00101100
		eAttackAnim_Attack5			= 0x32,	// 00110010
		eAttackAnim_Attack6			= 0x38, // 
		eAttackAnim_Attack7			= 0x3e,
		eAttackAnim_Attack8			= 0x44,
		eAttackAnim_AttackLeft		= 0x1a,
		eAttackAnim_AttackLoop		= 0x4a,
		eAttackAnim_AttackRight		= 0x20,
		eAttackAnim_AttackSpin		= 0x50,
		eAttackAnim_AttackSpin2		= 0x56,
		eAttackAnim_AttackThrow		= 0x6d,
		eAttackAnim_AttackThrow2	= 0x73,
		eAttackAnim_AttackThrow3	= 0x79,
		eAttackAnim_AttackThrow4	= 0x7F,
		eAttackAnim_AttackThrow5	= 0x85,
		eAttackAnim_PlaceMine		= 0x61,
		eAttackAnim_PlaceMine2		= 0x67,
		eAttackAnim_Count			= 19,
	};

	enum ReloadAnim {
		eReload_A = 0,
		eReload_B,
		eReload_C,
		eReload_D,
		eReload_E,
		eReload_F,
		eReload_G,
		eReload_H,
		eReload_I,
		eReload_J,
		eReload_K,
		eReload_Count = 11,
	};

	enum EWeaponFlags1 {
		eFlag_IgnoresNormalWeapResist	= 0x1,
		eFlag_IsAutomatic				= 0x2,
		eFlag_HasScope					= 0x4,
		eFlag_CantDrop					= 0x8,
		eFlag_HideBackpack				= 0x10,
		eFlag_EmbeddedWeapon			= 0x20,
		eFlag_No1stPersonISAnims		= 0x40,
		Eflag_NonPlayable				= 0x80
	};

	enum EWeaponFlags2 {
		eFlag_PlayerOnly				= 0x1,
		eFlag_NPCsUseAmmo				= 0x2,
		eFlag_NoJamAfterReload			= 0x4,
		eFlag_ActionPointOverride		= 0x8,
		eFlag_MinorCrime				= 0x10,
		eFlag_FixedRange				= 0x20,
		eFlag_NotUsedNormalCombat		= 0x40,
		eFlag_DamageToWeaponOverride	= 0x80,
		eFlag_No3rdPersonISAnims		= 0x100,
		eFlag_BurstShot					= 0x200,
		eFlag_RumbleAlternate			= 0x400,
		eFlag_LongBurst					= 0x800,
	};

	enum EEmbedWeapAV {
		eEmbedAV_Perception				= 0,
		eEmbedAV_Endurance,
		eEmbedAV_LeftAttack,
		eEmbedAV_RightAttack,
		eEmbedAV_LeftMobility,
		eEmbedAV_RightMobility,
		eEmbedAV_Brain,
	};

	enum EOnHit {
		eOnHit_Normal					= 0,
		eOnHit_DismemberOnly,
		eOnHit_ExplodeOnly,
		eOnHit_NoDismemberOrExplode,
	};

	enum ERumblePattern {
		eRumblePattern_Constant			= 0,
		eRumblePattern_Square,
		eRumblePattern_Triangle,
		eRumblePattern_Sawtooth
	};

	enum ECritDamageFlags {
		eCritDamage_OnDeath				= 0x1
	};

	// bases
	TESFullName					fullName;			// 030
	TESModelTextureSwap			textureSwap;		// 03C
	TESIcon						icon;				// 05C
	TESScriptableForm			scritpable;			// 068
	TESEnchantableForm			enchantable;		// 074
	TESValueForm				value;				// 084
	TESWeightForm				weight;				// 08C
	TESHealthForm				health;				// 094
	TESAttackDamageForm			attackDmg;			// 09C
	BGSAmmoForm					ammo;				// 0A4
	BGSClipRoundsForm			clipRounds;			// 0AC
	BGSDestructibleObjectForm	destructible;		// 0B4
	BGSRepairItemList			repairItemList;		// 0BC
	BGSEquipType				equipType;			// 0C4
	BGSPreloadable				preloadable;		// 0CC
	BGSMessageIcon				messageIcon;		// 0D0
	BGSBipedModelList			bipedModelList;		// 0E0
	BGSPickupPutdownSounds		pickupPutdownSounds;// 0E8

	UInt8				eWeaponType;		// 0F4
	UInt8				pad[3];
	float				animMult;			// 0F8
	float				reach;				// 0FC
	UInt8				weaponFlags1;		// 100
	UInt8				handGrip;			// 100
	UInt8				ammoUse;			// 100
	UInt8				reloadAnim;			// 100
	float				minSpread;			// 104
	float				spread;				// 108
	UInt32				unk10C;				// 10C
	float				sightFOV;			// 110
	UInt32				unk114;				// 114
	BGSProjectile		* projectile;		// 118
	UInt8				baseVATSChance;		// 11C
	UInt8				attackAnim;			// 11D
	UInt8				numProjectiles;		// 11E
	UInt8				embedWeaponAV;		// 11F
	float				minRange;			// 120
	float				maxRange;			// 124
	UInt32				onHit;				// 128
	UInt32				weaponFlags2;		// 12C
	float				animAttackMult;		// 130
	float				fireRate;			// 134
	float				AP;					// 138
	float				rumbleLeftMotor;	// 13C
	float				rumbleRightMotor;	// 140
	float				rumbleDuration;		// 144
	float				damageToWeaponMult;	// 148
	float				animShotsPerSec;	// 14C
	float				animReloadTime;		// 150
	float				animJamTime;		// 154		
	float				aimArc;				// 158
	UInt32				weaponSkill;		// 15C - actor value
	UInt32				rumblePattern;		// 160 - reload anim?
	float				rumbleWavelength;	// 164
	float				limbDamageMult;		// 168
	UInt32				resistType;			// 16c - actor value
	float				sightUsage;			// 170
	float				semiAutoFireDelayMin;	// 174
	float				semiAutoFireDelayMax;	// 178
	UInt32				criticalDamage;		// 17C
	float				criticalPercent;	// 180
	UInt8				critDamageFlags;	// 184
	UInt8				pad185[3];			// 185
	SpellItem			* criticalEffect;	// 188
	TESModel			shellCasingModel;	// 18C
	TESModel			model1A4;			// 1A4
	TESModel			model1BC;			// 1BC
	UInt32				unk1D4;				// 1D4
	TESSound			* sounds[8];		// 1D8
	BGSImpactDataSet	* impactDataSet;	// 1F8
	TESObjectSTAT		* worldStatic;		// 1FC
	UInt32				unk200;				// 200 - sound level?
	UInt32				unk204;				// 204
	UInt32				unk208;				// 208
	// 20C

	bool IsFlag1Set(UInt8 flag) const {
		return (weaponFlags1 & flag) == flag;
	}

	void SetFlag1(UInt8 flag) {
		weaponFlags1 |= flag;
	}

	void ClearFlag1(UInt8 flag) {
		weaponFlags1 &= ~flag;
	}

	bool IsAutomatic() const { return IsFlag1Set(eFlag_IsAutomatic); }
	void SetIsAutomatic(bool bAuto) {
		(bAuto) ? SetFlag1(eFlag_IsAutomatic) : ClearFlag1(eFlag_IsAutomatic);
		
	}

	bool HasScope() const { return IsFlag1Set(eFlag_HasScope);}
	UInt8 HandGrip() const;
	void SetHandGrip(UInt8 handGrip);
	UInt8 AttackAnimation() const;
	void SetAttackAnimation(UInt8 attackAnim);
};

STATIC_ASSERT(offsetof(TESObjectWEAP, fullName) == 0x030);
STATIC_ASSERT(offsetof(TESObjectWEAP, icon) == 0x5C);
STATIC_ASSERT(offsetof(TESObjectWEAP, ammo) == 0xA4);
STATIC_ASSERT(offsetof(TESObjectWEAP, projectile) == 0x118);
STATIC_ASSERT(offsetof(TESObjectWEAP, animShotsPerSec) == 0x14C);
STATIC_ASSERT(offsetof(TESObjectWEAP, unk200) == 0x200);
STATIC_ASSERT(sizeof(TESObjectWEAP) == 0x20C);

// AC
class TESAmmo : public TESBoundObject
{
public:
	TESAmmo();
	~TESAmmo();

	// bases
	TESFullName					fullName;		// 030
	TESModelTextureSwap			model;			// 03C
	TESIcon						icon;			// 05C
	BGSMessageIcon				messageIcon;	// 068	
	TESValueForm				value;			// 078
	BGSClipRoundsForm			clipRounds;		// 080
	BGSDestructibleObjectForm	destructible;	// 088
	BGSPickupPutdownSounds		unk090;			// 090
};

// 1EC
class TESNPC : public TESActorBase
{
public:
	TESNPC();
	~TESNPC();

	// 18 - facegen data?
	struct Unk134
	{
		UInt32	unk00;
		void	* unk04;
		UInt32	unk08;
		UInt32	unk0C;
		UInt32	unk10;
		UInt32	unk14;
	};

	TESRaceForm	race;							// 10C
	UInt8		skillValues[0x0E];				// 114
	UInt8		skillOffsets[0x0E];				// 122
	UInt32		classID;						// 130
	Unk134		unk134[4];						// 134
	UInt32		pad194;							// 194
	TESHair		* hair;							// 198
	float		hairLength;						// 19C
	TESEyes		* eyes;							// 1A0
	UInt32		unk1A4;
	UInt32		unk1A8;
	UInt32		unk1AC;
	UInt32		pad1B0[(0x1BC - 0x1B0) >> 2];	// 1B0
	tList <BGSHeadPart>	headPart;				// 1BC
	UInt32		impactMaterialType;				// 1C4
	UInt32		pad1C8[(0x1D4 - 0x1C8) >> 2];	// 1C8
	float		height;							// 1D4
	float		weight;							// 1D8
	NiTArray <FaceGenUndo *>	faceGenUndo;	// 1DC
};

STATIC_ASSERT(sizeof(TESNPC) == 0x1EC);

// 160
class TESCreature : public TESActorBase
{
public:
	TESCreature();
	~TESCreature();

	TESAttackDamageForm			attackDmg;		// 10C
	TESModelList				modelList;		// 114

	// data
	TESCreature*				creatureTemplate;	// 128
	UInt8						type;				// 12C
	UInt32						unk12D;				// 12D
	UInt8						combatSkill;		// 12E
	UInt8						stealthSkill;		// 12F
	UInt32						attackReach;		// 130
	float						turningSpeed;		// 134
	float						footWeight;			// 138
	float						baseScale;			// 13C
	TESCombatStyle*				combatStyle;		// 140
	BGSBodyPartData*			bodyPartData;		// 144
	UInt32						materialType;		// 148
	BGSImpactDataSet*			impactDataSet;		// 14C
	UInt32						unk150;				// 150
	UInt32						soundLevel;			// 154
	BGSListForm*				meleeWeaponList;	// 158
};

STATIC_ASSERT(offsetof(TESCreature, modelList) == 0x114);
STATIC_ASSERT(offsetof(TESCreature, creatureTemplate) == 0x128);

// TESLevCreature (68)
class TESLevCreature;

// TESLevCharacter (68)
class TESLevCharacter;

// TESKey (A8)
class TESKey : public TESObjectMISC
{
public:
	TESKey();
	~TESKey();
};

// AlchemyItem (D8)
class AlchemyItem;

// BGSIdleMarker (40)
class BGSIdleMarker;

// BGSNote (80)
class BGSNote : public TESBoundObject
{
public:
	BGSNote();
	~BGSNote();

	// bases
	TESModel					model;					// 030
	TESFullName					fullName;				// 048
	TESIcon						icon;					// 054
	BGSPickupPutdownSounds		pickupPutdownSounds;	// 060
	UInt32	unk06C[(0x80-0x6C) >> 2];						// 06C
};

STATIC_ASSERT(offsetof(BGSNote, pickupPutdownSounds) == 0x60);
STATIC_ASSERT(offsetof(BGSNote, unk06C) == 0x06C);
STATIC_ASSERT(sizeof(BGSNote) == 0x80);

// BGSConstructibleObject (B0)
class BGSConstructibleObject;

// 0C0
class BGSProjectile : public TESBoundObject
{
public:
	BGSProjectile();
	~BGSProjectile();

	// bases
	TESFullName					fullName;		// 030
	TESModel					model;			// 03C
	BGSPreloadable				preloadable;	// 054
	BGSDestructibleObjectForm	destructible;	// 058
	// ???
};

// TESLevItem (44)
class TESLevItem;

// TESWeather (2F4)
class TESWeather;

// TESClimate (58)
class TESClimate : public TESForm
{
public:
	TESClimate();
	~TESClimate();

	UInt32 unk018[(0x58-0x18) >> 2];		// 018
};

STATIC_ASSERT(sizeof(TESClimate) == 0x58);

// TESRegion (38)
class TESRegion;

// NavMeshInfoMap (40)
class NavMeshInfoMap;

// TESObjectCELL (E0)
class TESObjectCELL : public TESForm
{
public:
	TESObjectCELL();
	~TESObjectCELL();

	typedef tList<TESObjectREFR> RefList;
	struct CellCoordinates
	{
		UInt32	x;
		UInt32	y;
	};

	TESFullName				fullName;			// 018
	UInt32					unk024;				// 024
	ExtraDataList			extraDataList;		// 028
	UInt32					unk03C;				// 03C
	UInt32					unk040;				// 040
	CellCoordinates			* coords;			// 044
	TESObjectLAND			* land;				// 048
	UInt32					unk04C;				// 04C
	UInt32					unk050;				// 050
	TESTexture				texture054;			// 054
	void					* NavMeshArray;		// 060	?$BSSimpleArray@VNavMeshPtr@@$0EAA@@@
	UInt32					unk064[(0x0AC-0x064) >> 2];	// 064
	RefList					objectList;			// 0AC
	NiNode					* niNode0B4;			// 0B4
	NiNode					* niNode0B8;			// 0B8
	UInt32					unk0BC;				// 0BC
	TESWorldSpace			* worldSpace;			// 0C0
	void					* unk0C4;				// 0C4
	float					unk0C8;				// 0C8
	UInt32					unk0CC;				// 0CC
	UInt32					unk0D0;				// 0D)
	BSPortalGraph			* portalGraph;		// 0D4
	BGSLightingTemplate		* lightingTemplate;	// 0D8
	UInt32					unk0DC;				// 0DC

	bool IsInterior() { return worldSpace == NULL; }
};
STATIC_ASSERT(offsetof(TESObjectCELL, NavMeshArray) == 0x060);
STATIC_ASSERT(sizeof(TESObjectCELL) == 0xE0);

// TESObjectREFR (60) - see GameObjects.h

// TESWorldSpace (E8)
class TESWorldSpace : public TESForm
{
public:
	TESWorldSpace();
	~TESWorldSpace();

	TESFullName			fullName;			// 018
	TESTexture			texture;			// 024

	typedef NiTPointerMap<BSSimpleList<TESObjectREFR> > RefListPointerMap;
	typedef NiTPointerMap<TESObjectCELL> CellPointerMap;

	CellPointerMap		* cellMap;			// 030 
	TESObjectCELL		* cell;				// 034
	UInt32				unk038;				// 038
	UInt32				unk03C;				// 03C
	TESClimate			* climate;			// 040
	TESImageSpace		* imageSpace;		// 044
	UInt32				unk048;				// 048
	RefListPointerMap	pointerMap;			// 04C
	Character			* character;		// 05C
	UInt32				unk060;				// 060
	RefListPointerMap	* pointerMap064;	// 064 
	BSPortalGraph		* portalGraph;		// 068
	UInt32				unk06C;				// 06C
	TESWaterForm		* waterFormFirst;	// 070
	TESWaterForm		* waterFormLast;	// 074
	float				unk078;				// 078
	UInt32				unk07C;				// 07C
	UInt32				unk080;				// 080
	UInt32				unk084;				// 084
	UInt32				unk088;				// 088
	float				unk08C;				// 08C
	UInt32				unk090;				// 090
	UInt32				unk094;				// 094
	UInt32				unk098;				// 098
	float				unk09C;				// 09C
	float				unk0A0;				// 0A0
	float				unk0A4;				// 0A4
	float				unk0A8;				// 0A8
	UInt32				unk0AC[6];			// 0AC	?$NiTMap@PAVTESFile@@PAUOFFSET_DATA@TESWorldSpace@@@@ (embedded)
	float				unk0C4;				// 0C4
	float				unk0C8;				// 0C8
	UInt32				unk0CC;				// 0CC
	TESTexture			tex0D0;				// 0D0
	TESTexture			tex0DC;				// 0DC
};

STATIC_ASSERT(sizeof(TESWorldSpace) == 0xE8);
STATIC_ASSERT(offsetof(TESWorldSpace, unk0A8) == 0x0A8);

// TESObjectLAND (2C)
class TESObjectLAND;

// NavMesh (108)
class NavMesh;

// TESQuest (6C)
class TESQuest : public TESForm
{
public:
	TESQuest();
	~TESQuest();

	virtual char * GetEditorName() const;			// 4E

	// bases
	TESScriptableForm			scriptable;			// 018
	TESIcon						icon;				// 024
	TESFullName					fullName;			// 030
	
	struct StageInfo {
		UInt8 stage;
		UInt8 pad[3];
	};

	struct Unk54 {
		UInt8 unk;
		UInt8 pad[3];
	};

	UInt8						running;			// 03C
	UInt8						priority;			// 03D
	UInt8						pad03E[2];			// 03E
	float						questDelayTime;		// 040
	tList<StageInfo>			stages;				// 044
	tList<BGSQuestObjective>	objectives;			// 04C
	tList<Unk54>				conditions;			// 054	
	ScriptEventList*			scriptEventList;	// 05C
	UInt32						unk60;				// 060
	String						editorName;			// 064
};

STATIC_ASSERT(offsetof(TESQuest, running) == 0x03C);
STATIC_ASSERT(offsetof(TESQuest, objectives) == 0x04C);
STATIC_ASSERT(offsetof(TESQuest, conditions) == 0x54);
STATIC_ASSERT(sizeof(TESQuest) == 0x6C);

// TESIdleForm (54)
class TESIdleForm;

// TESPackage (80)
class TESPackage : public TESForm
{
public:
	TESPackage();
	~TESPackage();

	UInt32 unk018[(0x80 - 0x18) >> 2];		// 018
};

STATIC_ASSERT(sizeof(TESPackage) == 0x80);

// TESCombatStyle (108)
class TESCombatStyle : public TESForm
{
public:
	TESCombatStyle();
	~TESCombatStyle();

	UInt32 unk018[(0x106 - 0x18) >> 2];		// 018
};

// TESLoadScreen (3C)
class TESLoadScreen : public TESForm
{
public:
	TESLoadScreen();
	~TESLoadScreen();

	TESTexture		texture;			// 018
	TESDescription	description;		// 024
	UInt32	unk2C[(0x3C - 0x2C) >> 2];	// 02C
};

// TESLevSpell (44)
class TESLevSpell;

// TESObjectANIO (3C)
class TESObjectANIO : public TESForm
{
public:
	TESObjectANIO();
	~TESObjectANIO();

	TESModelTextureSwap	modelSwap;		// 18
	UInt32	unk38;						// 38
};

// TESWaterForm (190, 194 in 1.5)
class TESWaterForm : public TESForm
{
public:
	TESWaterForm();
	~TESWaterForm();

	TESFullName				fullName;		// 018
	TESAttackDamageForm		attackDamage;	// 024

	UInt32 unk2C[(0x190 - 0x2C) >> 2];		// 02C

	// 080 has a TESWaterForm * added in patch 1.5
};

// TESEffectShader (170)
class TESEffectShader : public TESForm
{
public:
	TESEffectShader();
	~TESEffectShader();

	UInt32 unk018[(0x170 - 0x18) >> 2];
};

// BGSExplosion (A4)
class BGSExplosion : public TESBoundObject
{
public:
	BGSExplosion();
	~BGSExplosion();

	TESFullName					fullName;			// 030
	TESModel					model;				// 03C
	TESEnchantableForm			enchantable;		// 054
	BGSPreloadable				preloadable;		// 064
	TESImageSpaceModifiableForm	imageSpaceModForm;	// 068

	UInt32		unk06C[(0xA4 - 0x70) >> 2];
};

STATIC_ASSERT(sizeof(BGSExplosion) == 0xA4);

// BGSDebris (24)
class BGSDebris : public TESForm
{
	BGSDebris();
	~BGSDebris();

	BGSPreloadable				preloadable;	// 018
	UInt32	unk01C;
	UInt32	unk020;
};

// TESImageSpace (B0)
class TESImageSpace : public TESForm
{
public:
	TESImageSpace();
	~TESImageSpace();

	UInt32 unk018[(0xB0-0x18) >> 2];		// 018
};

STATIC_ASSERT(sizeof(TESImageSpace) == 0xB0);

// TESImageSpaceModifier (728)
class TESImageSpaceModifier : public TESForm
{
public:
	TESImageSpaceModifier();
	~TESImageSpaceModifier();

	UInt32 unk018[(0x728-0x18) >> 2];		// 018
};

STATIC_ASSERT(sizeof(TESImageSpaceModifier) == 0x728);

// 20 / 24 in 1.1 and after
class BGSListForm : public TESForm
{
public:
	BGSListForm();
	~BGSListForm();
	
	tList<TESForm> list;			// 018

#if FALLOUT_VERSION >= FALLOUT_VERSION_1_1_35
	UInt32	numAddedObjects;	// number of objects added via script - assumed to be at the start of the list
#endif

	UInt32 Count() const {
		return list.Count();
	}

	TESForm* GetNthForm(SInt32 n) const {
		return list.GetNthItem(n);
	}

	UInt32 AddAt(TESForm* pForm, SInt32 n) {
		SInt32	result = list.AddAt(pForm, n);

#if FALLOUT_VERSION >= FALLOUT_VERSION_1_1_35
		if(result >= 0 && IsAddedObject(n))
			numAddedObjects++;
#endif

		return result;
	}

	SInt32 GetIndexOf(TESForm* pForm);

	TESForm* RemoveNthForm(SInt32 n) {
		TESForm	* form = list.RemoveNth(n);

#if FALLOUT_VERSION >= FALLOUT_VERSION_1_1_35
		if(form && IsAddedObject(n))
		{
			if(numAddedObjects == 0)
			{
				_MESSAGE("BGSListForm::RemoveNthForm: numAddedObjects = 0");
			}
			else
			{
				numAddedObjects--;
			}
		}
#endif

		return form;
	}

	TESForm* ReplaceNthForm(SInt32 n, TESForm* pReplaceWith) {
		return list.ReplaceNth(n, pReplaceWith);
	}

	SInt32 RemoveForm(TESForm* pForm);
	SInt32 ReplaceForm(TESForm* pForm, TESForm* pReplaceWith);

#if FALLOUT_VERSION >= FALLOUT_VERSION_1_1_35
	bool IsAddedObject(SInt32 idx)
	{
		return (idx >= 0) && (idx < numAddedObjects);
	}
#endif
};

#if FALLOUT_VERSION < FALLOUT_VERSION_1_1_35
STATIC_ASSERT(sizeof(BGSListForm) == 0x020);
#else
STATIC_ASSERT(sizeof(BGSListForm) == 0x024);
#endif

// BGSPerk (50)
class BGSPerk : public TESForm
{
	BGSPerk();
	~BGSPerk();

	TESFullName		fullName;			// 018
	TESDescription	description;		// 024
	TESIcon			icon;				// 02C
	UInt32	unk38[(0x50 - 0x38) >>2];	// 038
};

// BGSBodyPartData (74)
class BGSBodyPartData : public TESForm
{
public:
	BGSBodyPartData();
	~BGSBodyPartData();

	TESModel		model;				// 018
	BGSPreloadable	preloadable;		// 030
	UInt32 unk34[(0x74 - 0x34) >> 2];	// 034
};

// BGSAddonNode (60)
class BGSAddonNode : public TESBoundObject
{
public:
	BGSAddonNode();
	~BGSAddonNode();

	TESModel	model;				// 030
	UInt32 unk48[(0x60-0x48) >> 2]; // 048
};

STATIC_ASSERT(sizeof(BGSAddonNode) == 0x60);

// ActorValueInfo (C4)
class ActorValueInfo;

// BGSRadiationStage (20)
class BGSRadiationStage : public TESForm
{
public:
	BGSRadiationStage();
	~BGSRadiationStage();

	UInt32	unk018;			// 018
	UInt32	unk01C;			// 01C
};

// BGSCameraShot (78)
class BGSCameraShot : public TESForm
{
	BGSCameraShot();
	~BGSCameraShot();

	TESModel	model;								// 018
//	TESImageSpaceModifiableForm imageSpaceModForm;	// 024
	
	UInt32 unk024[(0x78-0x24) >> 2];	// 024
};

// BGSCameraPath (38)
class BGSCameraPath;

// BGSVoiceType (24)
class BGSVoiceType : public TESForm
{
public:
	BGSVoiceType();
	~BGSVoiceType();

	UInt32		unk018;		// 018
	UInt32		unk01C;		// 01C
	UInt32		unk020;		// 020
};

// BGSImpactData (78)
class BGSImpactData : public TESForm
{
public:
	BGSImpactData();
	~BGSImpactData();

	BGSPreloadable		preloadable;		// 018
	UInt32	unk01C[(0x78 - 0x1C) >> 2];		// 01C
};

STATIC_ASSERT(sizeof(BGSImpactData) == 0x078);
	
// 4C
class BGSImpactDataSet : public TESForm
{
public:
	BGSImpactDataSet();
	~BGSImpactDataSet();

	BGSPreloadable	preloadable;		// 018
	UInt32 unk01C[(0x4C - 0x1C) >> 2];	// 01C
};

STATIC_ASSERT(offsetof(BGSImpactDataSet, preloadable) == 0x018);
STATIC_ASSERT(sizeof(BGSImpactDataSet) == 0x4C);

// TESObjectARMA (180)
class TESObjectARMA : public TESBoundObject
{
public:
	TESObjectARMA();
	~TESObjectARMA();

	TESFullName					fullName;				// 030
	TESScriptableForm			scriptable;				// 03C
	TESEnchantableForm			enchantable;			// 048
	TESValueForm				value;					// 058
	TESWeightForm				weight;					// 060
	TESHealthForm				health;					// 068
	TESBipedModelForm			bipedModelForm;			// 070
	BGSDestructibleObjectForm	destructible;			// 14C
	BGSEquipType				equipType;				// 154
	BGSRepairItemList			repairList;				// 15C
	BGSBipedModelList			bipedModelList;			// 164
	BGSPickupPutdownSounds		pickupPutdownSounds;	// 16C
	UInt32						unk178;					// 178			
	UInt32						unk17C;					// 17C
};

STATIC_ASSERT(sizeof(TESObjectARMA) == 0x180);

// BGSEncounterZone (30)
class BGSEncounterZone : public TESForm
{
	BGSEncounterZone();
	~BGSEncounterZone();

	UInt32 unk018[(0x30-0x18) >> 2];	// 018
};

// BGSMessage (40)
class BGSMessage : public TESForm
{
public:
	BGSMessage();
	~BGSMessage();

	TESFullName		fullName;			// 018
	TESDescription	description;		// 024

	UInt32	unk02C[(0x40-0x2C) >> 2];	// 02C
};

STATIC_ASSERT(sizeof(BGSMessage) == 0x040);

// BGSRagdoll (148)
class BGSRagdoll : public TESForm
{
public:
	BGSRagdoll();
	~BGSRagdoll();

	TESModel	model;					// 018
	UInt32	unk030[(0x148-0x30) >> 2];	// 030
};

STATIC_ASSERT(sizeof(BGSRagdoll) == 0x148);

// BGSLightingTemplate (44)
class BGSLightingTemplate : public TESForm
{
public:
	BGSLightingTemplate();
	~BGSLightingTemplate();

	UInt32	unk018[(0x44 - 0x18) >> 2];
};

STATIC_ASSERT(sizeof(BGSLightingTemplate) == 0x44);

// BGSMusicType (30)
class BGSMusicType : public TESForm
{
public:
	BGSMusicType();
	~BGSMusicType();

	TESSoundFile		soundFile;	// 018
	UInt32	unk024;
	UInt32	unk028;
	UInt32	unk02C;
};

STATIC_ASSERT(sizeof(BGSMusicType) == 0x30);
