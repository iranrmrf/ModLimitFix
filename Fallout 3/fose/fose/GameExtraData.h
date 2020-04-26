#include "Utilities.h"
#include "GameBSExtraData.h"
#include "GameForms.h"

/*    Class							     vtbl	  Type  Size
 *   ----------------------------		------		--  --
 *	ExtraAction                        00DAEECC		0E	14
 *	ExtraActivateLoopSound             00DAF094		87	18
 *	ExtraActivateRef                   00DAF14C		53	18
 *	ExtraActivateRefChildren           00DAF140		54	18
 *	ExtraAmmo                          00DAD8B4		6E	14
 *	ExtraAnim                          00DAEE90		10	10
 *	ExtraAshPileRef                    00DAEFBC		89	10
 *	ExtraCannotWear                    00DAEF14		3E	0C	// no data
 *	ExtraCell3D                        00DAD734		2	10
 *	ExtraCellAcousticSpace             00DAD6D4		81	10
 *	ExtraCellCanopyShadowMask          00DAD74C		0A	1C
 *	ExtraCellClimate                   00DAD6E0		8	10
 *	ExtraCellImageSpace                00DAD6EC		59	10
 *	ExtraCellMusicType                 00DAD6C8		7	10
 *	ExtraCellWaterType                 00DAD6F8		3	10
 *	ExtraCharge                        00DAD7F4		28	10
 *	ExtraCollisionData                 00DAD920		72	10
 *	ExtraCombatStyle                   00DAD8CC		69	10
 *	ExtraContainerChanges              00DAEED8		15	10
 *	ExtraCount                         00DAD7B8		24	10
 *	ExtraCreatureAwakeSound            00DAF064		7D	18
 *	ExtraCreatureMovementSound         00DAF070		8A	18
 *	ExtraDecalRefs                     00DAF158		57	14
 *	ExtraDetachTime                    00DAD728		0B	10
 *	ExtraDismemberedLimbs              00DAF268		5F	30
 *	ExtraDistantData                   00DAEF8C		13	18
 *	ExtraDroppedItemList               00DAF25C		3A	14
 *	ExtraEditorRefMovedData            00DAF04C		4C	30
 *	ExtraEmittanceSource               00DAEFF8		67	10
 *	ExtraEnableStateChildren           00DAF244		38	14
 *	ExtraEnableStateParent             00DAEF98		37	14
 *	ExtraEncounterZone                 00DAEF68		74	10
 *	ExtraFactionChanges                00DAF194		5E	10
 *	ExtraFollower                      00DAF11C		1D	10
 *	ExtraFollowerSwimBreadcrumbs       00DAF1BC		8B	28
 *	ExtraFriendHits                    00DAF280		45	1C
 *	ExtraGhost                         00DAEEF0		1F	0C	// no data
 *	ExtraGlobal                        00DAD7A0		22	10
 *	ExtraGuardedRefData                00DAF274		7C	1C
 *	ExtraHasNoRumors                   00DAD860		4E	10
 *	ExtraHavok                         00DAD740		1	14
 *	ExtraHeadingTarget                 00DAD854		46	10
 *	ExtraHealth                        00DAD7C4		25	10
 *	ExtraHealthPerc                    00DAD7D0		7A	10
 *	ExtraHotkey                        00DAD818		4A	10
 *	ExtraIgnoredBySandbox              00DAF0B8		80	0C	// no data
 *	ExtraInfoGeneralTopic              00DAEF20		4D	10
 *	ExtraItemDropper                   00DAF01C		39	10
 *	ExtraLastFinishedSequence          00DAEFE0		41	10
 *	ExtraLevCreaModifier               00DAEFD4		1E	10
 *	ExtraLeveledCreature               00DAEEB4		2E	14
 *	ExtraLeveledItem                   00DAD83C		2F	14
 *	ExtraLight                         00DAEEA8		29	10
 *	ExtraLinkedRef                     00DAEFB0		51	10
 *	ExtraLinkedRefChildren             00DAF250		52	14
 *	ExtraLitWaterRefs                  00DADD84		85	14
 *	ExtraLock                          00DAD770		2A	10
 *	ExtraMapMarker                     00DAEEC0		2C	10
 *	ExtraMerchantContainer             00DAEFC8		3C	10
 *	ExtraModelSwap                     00DAD890		5B	14
 *	ExtraMultiBound                    00DAF164		61	10
 *	ExtraMultiBoundData                00DAF010		62	10
 *	ExtraMultiBoundRef                 00DAF004		63	10
 *	ExtraNavMeshPortal                 00DAD884		5A	14
 *	ExtraNorthRotation                 00DAD71C		43	10
 *	ExtraObjectHealth                  00DAD86C		56	10
 *	ExtraOcclusionPlane                00DAF170		71	10
 *	ExtraOcclusionPlaneRefData         00DAD8F0		76	10
 *	ExtraOpenCloseActivateRef          00DAD77C		6C	10
 *	ExtraOriginalReference             00DAEEE4		20	10
 *	ExtraOwnership                     00DAD794		21	10
 *	ExtraPackage                       00DAEF44		19	1C
 *	ExtraPackageData                   00DAD914		70	10
 *	ExtraPackageStartLocation          00DAEF38		18	1C
 *	ExtraPatrolRefData                 00DAD8E4		6F	10
 *	ExtraPatrolRefInUseData            00DAF0C4		88	10
 *	ExtraPersistentCell                00DAEF50		0C	10
 *	ExtraPlayerCrimeList               00DAF128		35	10
 *	ExtraPoison                        00DAD848		3F	10
 *	ExtraPortal                        00DAF17C		78	10
 *	ExtraPortalRefData                 00DAD8FC		77	10
 *	ExtraPrimitive                     00DAD8D8		6B	10
 *	ExtraProcessMiddleLow              00DAD704		9	10
 *	ExtraRadiation                     00DAD8A8		5D	10
 *	ExtraRadioData                     00DAD8C0		68	1C
 *	ExtraRadius                        00DAD89C		5C	10
 *	ExtraRagdollData                   00DAEF5C		14	10
 *	ExtraRandomTeleportMarker          00DAEFA4		3B	10
 *	ExtraRank                          00DAD7AC		23	10
 *	ExtraReferencePointer              00DAD824		1C	10
 *	ExtraReflectedRefs                 00DADD60		65	14
 *	ExtraReflectorRefs                 00DADD6C		66	14
 *	ExtraRefractionProperty            00DAF040		48	10
 *	ExtraRegionList                    00DAD6BC		4	10
 *	ExtraReservedMarkers               00DAEF80		82	10
 *	ExtraRoom                          00DAF188		79	10
 *	ExtraRoomRefData                   00DAD908		7B	10
 *	ExtraRunOncePacks                  00DAF134		1B	10
 *	ExtraSavedAnimation                00DAF028		42	10
 *	ExtraSavedHavokData                00DAF034		3D	10
 *	ExtraSayToTopicInfo                00DAF0AC		75	18
 *	ExtraSayTopicInfoOnceADay          00DAF1A0		73	10
 *	ExtraScale                         00DAD80C		30	10
 *	ExtraScript                        00DAD800		0D	14
 *	ExtraSeed                          00DAEF2C		31	10
 *	ExtraSeenData                      00DAD710		5	10
 *	ExtraSound                         00DAF058		4F	18
 *	ExtraStartingPosition              00DAF110		0F	24
 *	ExtraStartingWorldOrCell           00DAEE9C		49	10
 *	ExtraTalkingActor                  00DAF0A0		55	10
 *	ExtraTeleport                      00DAD788		2B	10
 *	ExtraTerminalState                 00DAD878		50	10
 *	ExtraTimeLeft                      00DAD7E8		27	10
 *	ExtraTrespassPackage               00DAD830		1A	10
 *	ExtraUsedMarkers                   00DAEF74		12	10
 *	ExtraUses                          00DAD7DC		26	10
 *	ExtraWaterLightRefs                00DADD78		84	14
 *	ExtraWaterZoneMap                  00DAF28C		7E	20
 *	ExtraWeaponAttackSound             00DAF088		86	18
 *	ExtraWeaponIdleSound               00DAF07C		83	18
 *	ExtraWorn                          00DAEEFC		16	0C	// no data
 *	ExtraWornLeft                      00DAEF08		17	0C	// no data
 *	ExtraXTarget                       00DAEFEC		44	10
 */

/* BaseExtraList methods:
	AddExtra		0x0040A180
	GetByType		0x0040A320, pass typeID
	ItemsInList		0x0040A130
	RemoveExtra		0x0040A250

  ExtraDataList methods:
	DuplicateExtraListForContainer	0x0041B090
*/

enum {
	kExtraData_Havok                    	= 0x01,
	kExtraData_Cell3D                   	= 0x02,
	kExtraData_CellWaterType            	= 0x03,
	kExtraData_RegionList               	= 0x04,
	kExtraData_SeenData                 	= 0x05,
	kExtraData_CellMusicType            	= 0x07,
	kExtraData_CellClimate              	= 0x08,
	kExtraData_ProcessMiddleLow         	= 0x09,
	kExtraData_CellCanopyShadowMask     	= 0x0A,
	kExtraData_DetachTime               	= 0x0B,
	kExtraData_PersistentCell           	= 0x0C,
	kExtraData_Script                   	= 0x0D,
	kExtraData_Action                   	= 0x0E,
	kExtraData_StartingPosition         	= 0x0F,
	kExtraData_Anim                     	= 0x10,
	kExtraData_UsedMarkers              	= 0x12,
	kExtraData_DistantData              	= 0x13,
	kExtraData_RagdollData              	= 0x14,
	kExtraData_ContainerChanges         	= 0x15,
	kExtraData_Worn                     	= 0x16,
	kExtraData_WornLeft                 	= 0x17,
	kExtraData_PackageStartLocation     	= 0x18,
	kExtraData_Package                  	= 0x19,
	kExtraData_TrespassPackage          	= 0x1A,
	kExtraData_RunOncePacks             	= 0x1B,
	kExtraData_ReferencePointer         	= 0x1C,
	kExtraData_Follower                 	= 0x1D,
	kExtraData_LevCreaModifier          	= 0x1E,
	kExtraData_Ghost                    	= 0x1F,
	kExtraData_OriginalReference        	= 0x20,
	kExtraData_Ownership                	= 0x21,
	kExtraData_Global                   	= 0x22,
	kExtraData_Rank                     	= 0x23,
	kExtraData_Count                    	= 0x24,
	kExtraData_Health                   	= 0x25,
	kExtraData_Uses                     	= 0x26,
	kExtraData_TimeLeft                 	= 0x27,
	kExtraData_Charge                   	= 0x28,
	kExtraData_Light                    	= 0x29,
	kExtraData_Lock                     	= 0x2A,
	kExtraData_Teleport                 	= 0x2B,
	kExtraData_MapMarker                	= 0x2C,
	kExtraData_LeveledCreature          	= 0x2E,
	kExtraData_LeveledItem              	= 0x2F,
	kExtraData_Scale                    	= 0x30,
	kExtraData_Seed                     	= 0x31,
	kExtraData_PlayerCrimeList          	= 0x35,
	kExtraData_EnableStateParent        	= 0x37,
	kExtraData_EnableStateChildren      	= 0x38,
	kExtraData_ItemDropper              	= 0x39,
	kExtraData_DroppedItemList          	= 0x3A,
	kExtraData_RandomTeleportMarker     	= 0x3B,
	kExtraData_MerchantContainer        	= 0x3C,
	kExtraData_SavedHavokData           	= 0x3D,
	kExtraData_CannotWear               	= 0x3E,
	kExtraData_Poison                   	= 0x3F,
	kExtraData_LastFinishedSequence     	= 0x41,
	kExtraData_SavedAnimation           	= 0x42,
	kExtraData_NorthRotation            	= 0x43,
	kExtraData_XTarget                  	= 0x44,
	kExtraData_FriendHits               	= 0x45,
	kExtraData_HeadingTarget            	= 0x46,
	kExtraData_RefractionProperty       	= 0x48,
	kExtraData_StartingWorldOrCell      	= 0x49,
	kExtraData_Hotkey                   	= 0x4A,
	kExtraData_EditorRefMovedData       	= 0x4C,
	kExtraData_InfoGeneralTopic         	= 0x4D,
	kExtraData_HasNoRumors              	= 0x4E,
	kExtraData_Sound                    	= 0x4F,
	kExtraData_TerminalState            	= 0x50,
	kExtraData_LinkedRef                	= 0x51,
	kExtraData_LinkedRefChildren        	= 0x52,
	kExtraData_ActivateRef              	= 0x53,
	kExtraData_ActivateRefChildren      	= 0x54,
	kExtraData_TalkingActor             	= 0x55,
	kExtraData_ObjectHealth             	= 0x56,
	kExtraData_DecalRefs                	= 0x57,
	kExtraData_CellImageSpace           	= 0x59,
	kExtraData_NavMeshPortal            	= 0x5A,
	kExtraData_ModelSwap                	= 0x5B,
	kExtraData_Radius                   	= 0x5C,
	kExtraData_Radiation                	= 0x5D,
	kExtraData_FactionChanges           	= 0x5E,
	kExtraData_DismemberedLimbs         	= 0x5F,
	kExtraData_MultiBound               	= 0x61,
	kExtraData_MultiBoundData           	= 0x62,
	kExtraData_MultiBoundRef            	= 0x63,
	kExtraData_ReflectedRefs            	= 0x65,
	kExtraData_ReflectorRefs            	= 0x66,
	kExtraData_EmittanceSource          	= 0x67,
	kExtraData_RadioData                	= 0x68,
	kExtraData_CombatStyle              	= 0x69,
	kExtraData_Primitive                	= 0x6B,
	kExtraData_OpenCloseActivateRef     	= 0x6C,
	kExtraData_Ammo                     	= 0x6E,
	kExtraData_PatrolRefData            	= 0x6F,
	kExtraData_PackageData              	= 0x70,
	kExtraData_OcclusionPlane           	= 0x71,
	kExtraData_CollisionData            	= 0x72,
	kExtraData_SayTopicInfoOnceADay     	= 0x73,
	kExtraData_EncounterZone            	= 0x74,
	kExtraData_SayToTopicInfo           	= 0x75,
	kExtraData_OcclusionPlaneRefData    	= 0x76,
	kExtraData_PortalRefData            	= 0x77,
	kExtraData_Portal                   	= 0x78,
	kExtraData_Room                     	= 0x79,
	kExtraData_HealthPerc               	= 0x7A,
	kExtraData_RoomRefData              	= 0x7B,
	kExtraData_GuardedRefData           	= 0x7C,
	kExtraData_CreatureAwakeSound       	= 0x7D,
	kExtraData_WaterZoneMap             	= 0x7E,
	kExtraData_IgnoredBySandbox         	= 0x80,
	kExtraData_CellAcousticSpace        	= 0x81,
	kExtraData_ReservedMarkers          	= 0x82,
	kExtraData_WeaponIdleSound          	= 0x83,
	kExtraData_WaterLightRefs           	= 0x84,
	kExtraData_LitWaterRefs             	= 0x85,
	kExtraData_WeaponAttackSound        	= 0x86,
	kExtraData_ActivateLoopSound        	= 0x87,
	kExtraData_PatrolRefInUseData       	= 0x88,
	kExtraData_AshPileRef               	= 0x89,
	kExtraData_CreatureMovementSound    	= 0x8A,
	kExtraData_FollowerSwimBreadcrumbs  	= 0x8B,
};

#define GetByTypeCast(xDataList, Type) DYNAMIC_CAST(xDataList.GetByType(kExtraData_ ## Type), BSExtraData, Extra ## Type);
#define GetExtraType(xDataList, Type) (Extra ## Type*)xDataList.GetByType(kExtraData_ ## Type)

// 014
class ExtraHavok : public BSExtraData
{
public:
	ExtraHavok();
	virtual ~ExtraHavok();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 010
class ExtraCell3D : public BSExtraData
{
	ExtraCell3D();
	virtual ~ExtraCell3D();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraCellWaterType : public BSExtraData
{
	ExtraCellWaterType();
	virtual ~ExtraCellWaterType();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraRegionList : public BSExtraData
{
	ExtraRegionList();
	virtual ~ExtraRegionList();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraSeenData : public BSExtraData
{
	ExtraSeenData();
	virtual ~ExtraSeenData();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraCellMusicType : public BSExtraData
{
	ExtraCellMusicType();
	virtual ~ExtraCellMusicType();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraCellClimate : public BSExtraData
{
	ExtraCellClimate();
	virtual ~ExtraCellClimate();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraProcessMiddleLow : public BSExtraData
{
	ExtraProcessMiddleLow();
	virtual ~ExtraProcessMiddleLow();

	UInt32	unk00C;		// 00C
};

// 01C
class ExtraCellCanopyShadowMask : public BSExtraData
{
	ExtraCellCanopyShadowMask();
	virtual ~ExtraCellCanopyShadowMask();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
};

// 010
class ExtraDetachTime : public BSExtraData
{
	ExtraDetachTime();
	virtual ~ExtraDetachTime();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraPersistentCell : public BSExtraData
{
	ExtraPersistentCell();
	virtual ~ExtraPersistentCell();

	UInt32	unk00C;		// 00C
};

// 014
class ExtraScript : public BSExtraData
{
public:
	ExtraScript();
	virtual ~ExtraScript();

	Script			* script;		// 00C
	ScriptEventList	* eventList;	// 010
};

// 014
class ExtraAction : public BSExtraData
{
	ExtraAction();
	virtual ~ExtraAction();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 024
class ExtraStartingPosition : public BSExtraData
{
	ExtraStartingPosition();
	virtual ~ExtraStartingPosition();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
	UInt32	unk01C;		// 01C
	UInt32	unk020;		// 020
};

// 010
class ExtraAnim : public BSExtraData
{
	ExtraAnim();
	virtual ~ExtraAnim();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraUsedMarkers : public BSExtraData
{
	ExtraUsedMarkers();
	virtual ~ExtraUsedMarkers();

	UInt32	unk00C;		// 00C
};

// 018
class ExtraDistantData : public BSExtraData
{
	ExtraDistantData();
	virtual ~ExtraDistantData();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 010
class ExtraRagdollData : public BSExtraData
{
	ExtraRagdollData();
	virtual ~ExtraRagdollData();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraContainerChanges : public BSExtraData
{
public:
	ExtraContainerChanges();
	virtual ~ExtraContainerChanges();

	typedef tList<ExtraDataList> ExtendDataList;


	struct EntryData
	{
		ExtendDataList	* extendData;
		SInt32					countDelta;
		TESForm					* type;
	};

	struct EntryDataList : tList<EntryData> {
		void* FindForItem(TESForm* item);
	};

	struct Data
	{
		EntryDataList	* objList;
		TESObjectREFR		* owner;
		float			totalWgCurrent;
		float			totalWgLast;

		float GetInventoryWeight();
	};

	Data	* data;

	EntryData *	GetByType(TESForm * type);

	// find the equipped item whose form matches the passed matcher
	struct FoundEquipData{
		TESForm* pForm;
		ExtraDataList* pExtraData;
	};
	FoundEquipData FindEquipped(FormMatcher& matcher) const;

	EntryDataList* GetEntryDataList() const {
		return data ? data->objList : NULL;
	}
};
typedef ExtraContainerChanges::FoundEquipData EquipData;
typedef ExtraContainerChanges::EntryData ContChangesEntry;

// 00C
class ExtraWorn : public BSExtraData
{
public:
	ExtraWorn();
	virtual ~ExtraWorn();
};

// 00C
class ExtraWornLeft : public BSExtraData
{
public:
	ExtraWornLeft();
	virtual ~ExtraWornLeft();
};

// 01C
class ExtraPackageStartLocation : public BSExtraData
{
	ExtraPackageStartLocation();
	virtual ~ExtraPackageStartLocation();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
};

// 01C
class ExtraPackage : public BSExtraData
{
	ExtraPackage();
	virtual ~ExtraPackage();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
};

// 010
class ExtraTrespassPackage : public BSExtraData
{
	ExtraTrespassPackage();
	virtual ~ExtraTrespassPackage();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraRunOncePacks : public BSExtraData
{
	ExtraRunOncePacks();
	virtual ~ExtraRunOncePacks();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraReferencePointer : public BSExtraData
{
	ExtraReferencePointer();
	virtual ~ExtraReferencePointer();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraFollower : public BSExtraData
{
	ExtraFollower();
	virtual ~ExtraFollower();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraLevCreaModifier : public BSExtraData
{
	ExtraLevCreaModifier();
	virtual ~ExtraLevCreaModifier();

	UInt32	unk00C;		// 00C
};

// 00C
class ExtraGhost : public BSExtraData
{
public:
	ExtraGhost();
	virtual ~ExtraGhost();
};

// 00C
class ExtraOriginalReference : public BSExtraData
{
public:
	ExtraOriginalReference();
	virtual ~ExtraOriginalReference();
};

// 010
class ExtraOwnership : public BSExtraData
{
public:
	ExtraOwnership();
	virtual ~ExtraOwnership();

	TESForm*	owner;	//maybe this should be a union {TESFaction*; TESNPC*} but it would be more unwieldy to access and modify
};

// 010
class ExtraGlobal : public BSExtraData
{								//ownership data, stored separately from ExtraOwnership
public:
	ExtraGlobal();
	virtual ~ExtraGlobal();

	TESGlobal*	globalVar;	// 00C
};

// 010
class ExtraRank : public BSExtraData
{								//ownership data, stored separately from ExtraOwnership
public:
	ExtraRank();
	virtual ~ExtraRank();

	UInt32	rank; // 00C
};

// 010
class ExtraCount : public BSExtraData
{
public:
	ExtraCount();
	virtual ~ExtraCount();

	SInt16	count;	// 00C
	UInt8	pad[2];	// 00E

	static ExtraCount* Create();	
};

// 010
class ExtraHealth : public BSExtraData
{
public:
	ExtraHealth();
	virtual ~ExtraHealth();
	float health;

	static ExtraHealth* Create();
};

// 010
class ExtraUses : public BSExtraData
{
public:
	ExtraUses();
	~ExtraUses();
	UInt32 unk0;
	static ExtraUses* Create();
};

// 010
class ExtraTimeLeft : public BSExtraData
{
public:
	ExtraTimeLeft();
	virtual ~ExtraTimeLeft();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraCharge : public BSExtraData
{
public:
	ExtraCharge();
	virtual ~ExtraCharge();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraLock : public BSExtraData
{
public:
	ExtraLock();
	virtual ~ExtraLock();

	struct Data
	{
		UInt32	lockLevel;
		TESKey	* key;
		UInt8	flags;
		UInt8	pad[3];
	};

	Data*	data;		// 00C
	static ExtraLock* Create();
};

// 010
class ExtraTeleport : public BSExtraData
{
public:
	ExtraTeleport();
	virtual ~ExtraTeleport();
	struct Data
	{
		TESObjectREFR*	linkedDoor;
		float			x; //x, y, z, zRot refer to teleport marker's position and rotation
		float			y; 
		float			z;
		float			zRot;
		UInt32			unk1;	//looks like flags (have only seen 0x80000000)
		UInt32			unk2;
	};

	Data *	data;	// 00C
};

// 010
class ExtraMapMarker : public BSExtraData
{
public:
	ExtraMapMarker();
	virtual ~ExtraMapMarker();

	UInt32	unk00C;		// 00C
};

// 014
class ExtraLeveledCreature : public BSExtraData
{
	ExtraLeveledCreature();
	virtual ~ExtraLeveledCreature();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 014
class ExtraLeveledItem : public BSExtraData
{
	ExtraLeveledItem();
	virtual ~ExtraLeveledItem();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 010
class ExtraScale : public BSExtraData
{
public:
	ExtraScale();
	virtual ~ExtraScale();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraSeed : public BSExtraData
{
public:
	ExtraSeed();
	virtual ~ExtraSeed();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraPlayerCrimeList : public BSExtraData
{
public:
	ExtraPlayerCrimeList();
	virtual ~ExtraPlayerCrimeList();

	UInt32	unk00C;		// 00C
};

// 014
class ExtraEnableStateParent : public BSExtraData
{
	ExtraEnableStateParent();
	virtual ~ExtraEnableStateParent();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 014
class ExtraEnableStateChildren : public BSExtraData
{
	ExtraEnableStateChildren();
	virtual ~ExtraEnableStateChildren();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 010
class ExtraItemDropper : public BSExtraData
{
public:
	ExtraItemDropper();
	virtual ~ExtraItemDropper();

	UInt32	unk00C;		// 00C
};

// 014
class ExtraDroppedItemList : public BSExtraData
{
	ExtraDroppedItemList();
	virtual ~ExtraDroppedItemList();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 010
class ExtraRandomTeleportMarker : public BSExtraData
{
public:
	ExtraRandomTeleportMarker();
	virtual ~ExtraRandomTeleportMarker();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraMerchantContainer : public BSExtraData
{
public:
	ExtraMerchantContainer();
	virtual ~ExtraMerchantContainer();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraSavedHavokData : public BSExtraData
{
public:
	ExtraSavedHavokData();
	virtual ~ExtraSavedHavokData();

	UInt32	unk00C;		// 00C
};

// 00C
class ExtraCannotWear : public BSExtraData
{
public:
	ExtraCannotWear();
	virtual ~ExtraCannotWear();
};

// 010
class ExtraPoison : public BSExtraData
{
public:
	ExtraPoison();
	virtual ~ExtraPoison();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraLastFinishedSequence : public BSExtraData
{
public:
	ExtraLastFinishedSequence();
	virtual ~ExtraLastFinishedSequence();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraSavedAnimation : public BSExtraData
{
public:
	ExtraSavedAnimation();
	virtual ~ExtraSavedAnimation();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraNorthRotation : public BSExtraData
{
public:
	ExtraNorthRotation();
	virtual ~ExtraNorthRotation();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraXTarget : public BSExtraData
{
public:
	ExtraXTarget();
	virtual ~ExtraXTarget();

	UInt32	unk00C;		// 00C
};

// 01C
class ExtraFriendHits : public BSExtraData
{
	ExtraFriendHits();
	virtual ~ExtraFriendHits();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
};

// 010
class ExtraHeadingTarget : public BSExtraData
{
public:
	ExtraHeadingTarget();
	virtual ~ExtraHeadingTarget();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraRefractionProperty : public BSExtraData
{
public:
	ExtraRefractionProperty();
	virtual ~ExtraRefractionProperty();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraStartingWorldOrCell : public BSExtraData
{
public:
	ExtraStartingWorldOrCell();
	virtual ~ExtraStartingWorldOrCell();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraHotkey : public BSExtraData
{
public:
	ExtraHotkey();
	virtual ~ExtraHotkey();

	UInt8	index;		// 00C (is 0-7)
};

// 030
class ExtraEditorRefMovedData : public BSExtraData
{
	ExtraEditorRefMovedData();
	virtual ~ExtraEditorRefMovedData();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
	UInt32	unk01C;		// 01C
	UInt32	unk020;		// 020
	UInt32	unk024;		// 024
	UInt32	unk028;		// 028
	UInt32	unk02C;		// 02C
};
STATIC_ASSERT(sizeof(ExtraEditorRefMovedData) == 0x30);

// 010
class ExtraInfoGeneralTopic : public BSExtraData
{
public:
	ExtraInfoGeneralTopic();
	virtual ~ExtraInfoGeneralTopic();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraHasNoRumors : public BSExtraData
{
public:
	ExtraHasNoRumors();
	virtual ~ExtraHasNoRumors();

	UInt32	unk00C;		// 00C
};

// 018
class ExtraSound : public BSExtraData
{
	ExtraSound();
	virtual ~ExtraSound();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 010
class ExtraTerminalState : public BSExtraData
{
public:
	ExtraTerminalState();
	virtual ~ExtraTerminalState();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraLinkedRef : public BSExtraData
{
public:
	ExtraLinkedRef();
	virtual ~ExtraLinkedRef();

	UInt32	unk00C;		// 00C
};

// 014
class ExtraLinkedRefChildren : public BSExtraData
{
	ExtraLinkedRefChildren();
	virtual ~ExtraLinkedRefChildren();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 018
class ExtraActivateRef : public BSExtraData
{
	ExtraActivateRef();
	virtual ~ExtraActivateRef();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 018
class ExtraActivateRefChildren : public BSExtraData
{
	ExtraActivateRefChildren();
	virtual ~ExtraActivateRefChildren();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 010
class ExtraTalkingActor : public BSExtraData
{
public:
	ExtraTalkingActor();
	virtual ~ExtraTalkingActor();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraObjectHealth : public BSExtraData
{
public:
	ExtraObjectHealth();
	virtual ~ExtraObjectHealth();

	UInt32	unk00C;		// 00C
};

// 014
class ExtraDecalRefs : public BSExtraData
{
	ExtraDecalRefs();
	virtual ~ExtraDecalRefs();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 010
class ExtraCellImageSpace : public BSExtraData
{
public:
	ExtraCellImageSpace();
	virtual ~ExtraCellImageSpace();

	UInt32	unk00C;		// 00C
};

// 014
class ExtraNavMeshPortal : public BSExtraData
{
	ExtraNavMeshPortal();
	virtual ~ExtraNavMeshPortal();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 014
class ExtraModelSwap : public BSExtraData
{
	ExtraModelSwap();
	virtual ~ExtraModelSwap();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 010
class ExtraRadius : public BSExtraData
{
public:
	ExtraRadius();
	virtual ~ExtraRadius();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraRadiation : public BSExtraData
{
public:
	ExtraRadiation();
	virtual ~ExtraRadiation();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraFactionChanges : public BSExtraData
{
public:
	ExtraFactionChanges();
	virtual ~ExtraFactionChanges();

	UInt32	unk00C;		// 00C
};

// 030
class ExtraDismemberedLimbs : public BSExtraData
{
	ExtraDismemberedLimbs();
	virtual ~ExtraDismemberedLimbs();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
	UInt32	unk01C;		// 01C
	UInt32	unk020;		// 020
	UInt32	unk024;		// 024
	UInt32	unk028;		// 028
	UInt32	unk02C;		// 02C
};
STATIC_ASSERT(sizeof(ExtraDismemberedLimbs) == 0x30);

// 010
class ExtraMultiBound : public BSExtraData
{
public:
	ExtraMultiBound();
	virtual ~ExtraMultiBound();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraMultiBoundData : public BSExtraData
{
public:
	ExtraMultiBoundData();
	virtual ~ExtraMultiBoundData();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraMultiBoundRef : public BSExtraData
{
public:
	ExtraMultiBoundRef();
	virtual ~ExtraMultiBoundRef();

	UInt32	unk00C;		// 00C
};

// 014
class ExtraReflectedRefs : public BSExtraData
{
	ExtraReflectedRefs();
	virtual ~ExtraReflectedRefs();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 014
class ExtraReflectorRefs : public BSExtraData
{
	ExtraReflectorRefs();
	virtual ~ExtraReflectorRefs();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 010
class ExtraEmittanceSource : public BSExtraData
{
public:
	ExtraEmittanceSource();
	virtual ~ExtraEmittanceSource();

	UInt32	unk00C;		// 00C
};

// 01C
class ExtraRadioData : public BSExtraData
{
	ExtraRadioData();
	virtual ~ExtraRadioData();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
};
STATIC_ASSERT(sizeof(ExtraRadioData) == 0x1C);

// 010
class ExtraCombatStyle : public BSExtraData
{
public:
	ExtraCombatStyle();
	virtual ~ExtraCombatStyle();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraPrimitive : public BSExtraData
{
public:
	ExtraPrimitive();
	virtual ~ExtraPrimitive();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraOpenCloseActivateRef : public BSExtraData
{
public:
	ExtraOpenCloseActivateRef();
	virtual ~ExtraOpenCloseActivateRef();

	UInt32	unk00C;		// 00C
};

// 014
class ExtraAmmo : public BSExtraData
{
	ExtraAmmo();
	virtual ~ExtraAmmo();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 010
class ExtraPatrolRefData : public BSExtraData
{
public:
	ExtraPatrolRefData();
	virtual ~ExtraPatrolRefData();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraPackageData : public BSExtraData
{
public:
	ExtraPackageData();
	virtual ~ExtraPackageData();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraOcclusionPlane : public BSExtraData
{
public:
	ExtraOcclusionPlane();
	virtual ~ExtraOcclusionPlane();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraCollisionData : public BSExtraData
{
public:
	ExtraCollisionData();
	virtual ~ExtraCollisionData();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraSayTopicInfoOnceADay : public BSExtraData
{
public:
	ExtraSayTopicInfoOnceADay();
	virtual ~ExtraSayTopicInfoOnceADay();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraEncounterZone : public BSExtraData
{
public:
	ExtraEncounterZone();
	virtual ~ExtraEncounterZone();

	UInt32	unk00C;		// 00C
};

// 018
class ExtraSayToTopicInfo : public BSExtraData
{
	ExtraSayToTopicInfo();
	virtual ~ExtraSayToTopicInfo();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 010
class ExtraOcclusionPlaneRefData : public BSExtraData
{
public:
	ExtraOcclusionPlaneRefData();
	virtual ~ExtraOcclusionPlaneRefData();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraPortalRefData : public BSExtraData
{
public:
	ExtraPortalRefData();
	virtual ~ExtraPortalRefData();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraPortal : public BSExtraData
{
public:
	ExtraPortal();
	virtual ~ExtraPortal();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraRoom : public BSExtraData
{
public:
	ExtraRoom();
	virtual ~ExtraRoom();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraHealthPerc : public BSExtraData
{
public:
	ExtraHealthPerc();
	virtual ~ExtraHealthPerc();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraRoomRefData : public BSExtraData
{
public:
	ExtraRoomRefData();
	virtual ~ExtraRoomRefData();

	UInt32	unk00C;		// 00C
};

// 01C
class ExtraGuardedRefData : public BSExtraData
{
	ExtraGuardedRefData();
	virtual ~ExtraGuardedRefData();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
};

// 018
class ExtraCreatureAwakeSound : public BSExtraData
{
	ExtraCreatureAwakeSound();
	virtual ~ExtraCreatureAwakeSound();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 020
class ExtraWaterZoneMap : public BSExtraData
{
	ExtraWaterZoneMap();
	virtual ~ExtraWaterZoneMap();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
	UInt32	unk01C;		// 01C
};
STATIC_ASSERT(sizeof(ExtraWaterZoneMap) == 0x20);

// 00C
class ExtraIgnoredBySandbox : public BSExtraData
{
public:
	ExtraIgnoredBySandbox();
	virtual ~ExtraIgnoredBySandbox();
};

// 010
class ExtraCellAcousticSpace : public BSExtraData
{
public:
	ExtraCellAcousticSpace();
	virtual ~ExtraCellAcousticSpace();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraReservedMarkers : public BSExtraData
{
public:
	ExtraReservedMarkers();
	virtual ~ExtraReservedMarkers();

	UInt32	unk00C;		// 00C
};

// 018
class ExtraWeaponIdleSound : public BSExtraData
{
	ExtraWeaponIdleSound();
	virtual ~ExtraWeaponIdleSound();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 014
class ExtraWaterLightRefs : public BSExtraData
{
	ExtraWaterLightRefs();
	virtual ~ExtraWaterLightRefs();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 014
class ExtraLitWaterRefs : public BSExtraData
{
	ExtraLitWaterRefs();
	virtual ~ExtraLitWaterRefs();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
};

// 018
class ExtraWeaponAttackSound : public BSExtraData
{
	ExtraWeaponAttackSound();
	virtual ~ExtraWeaponAttackSound();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 018
class ExtraActivateLoopSound : public BSExtraData
{
	ExtraActivateLoopSound();
	virtual ~ExtraActivateLoopSound();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 010
class ExtraPatrolRefInUseData : public BSExtraData
{
public:
	ExtraPatrolRefInUseData();
	virtual ~ExtraPatrolRefInUseData();

	UInt32	unk00C;		// 00C
};

// 010
class ExtraAshPileRef : public BSExtraData
{
public:
	ExtraAshPileRef();
	virtual ~ExtraAshPileRef();

	UInt32	unk00C;		// 00C
};

// 018
class ExtraCreatureMovementSound : public BSExtraData
{
	ExtraCreatureMovementSound();
	virtual ~ExtraCreatureMovementSound();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
};

// 028
class ExtraFollowerSwimBreadcrumbs : public BSExtraData
{
	ExtraFollowerSwimBreadcrumbs();
	virtual ~ExtraFollowerSwimBreadcrumbs();

	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
	UInt32	unk01C;		// 01C
	UInt32	unk020;		// 020
	UInt32	unk024;		// 024
};

STATIC_ASSERT(sizeof(ExtraDismemberedLimbs) == 0x30);
