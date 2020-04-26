#pragma once

#include "GameForms.h"
#include "GameBSExtraData.h"

#if RUNTIME

#if FALLOUT_VERSION == FALLOUT_VERSION_1_7
	static const UInt32 kTESObjectREFR_IsOffLimitsToPlayerAddr = 0x004DEBF0;
	// ### should this be pointing in to the middle of a function?
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	static const UInt32 kTESObjectREFR_IsOffLimitsToPlayerAddr = 0x004DF0E0;
	// ### should this be pointing in to the middle of a function?
#else

	// ### temp build hack
	static const UInt32 kTESObjectREFR_IsOffLimitsToPlayerAddr = 0;
	//#error unsupported runtime version

#endif

#else

static const UInt32 kTESObjectREFR_IsOffLimitsToPlayerAddr = 0;

#endif

class HighProcess;
class bhkRagdollController;
class bhkRagdollPenetrationUtil;
class PlayerMover;
class ImageSpaceModifierInstanceDOF;
class ImageSpaceModifierInstanceDRB;
class NiNode;

class TESObjectCELL;

// 004?
class TESChildCell
{
public:
	TESChildCell();
	~TESChildCell();

	// no virtual destructor
	virtual TESObjectCELL *	GetChildCell(void);
};

class TESObjectREFR : public TESForm
{
public:
	MEMBER_FN_PREFIX(TESObjectREFR);
	DEFINE_MEMBER_FN(IsOffLimitsToPlayer, bool, kTESObjectREFR_IsOffLimitsToPlayerAddr);

	TESObjectREFR();
	~TESObjectREFR();

	enum {
		kFlags_Taken		= 0x00000022,		// 2 bits TODO: which bit does what?
		kFlags_Persistent	= 0x00000400,		//shared bit with kFormFlags_QuestItem
	};

	TESChildCell	childCell;				// 018
	TESForm*		baseForm;				// 01C
	
	float			rotX, rotY, rotZ;		// 020 - either public or accessed via simple inline accessor common to all child classes
	float			posX, posY, posZ;		// 02C - seems to be private
	float			scale;					// 038 

	TESObjectCELL*	parentCell;				// 03C
	ExtraDataList	extraDataList;			// 040
	// 054 ?

	ScriptEventList* GetEventList() const;

	bool IsTaken() const {  return ((flags & kFlags_Taken) == kFlags_Taken) ? true : false; } // Need to implement
	bool IsPersistent() const { return ((flags & kFlags_Persistent) == kFlags_Persistent) ? true : false; }
	void* GetContainerChangesList();
};
STATIC_ASSERT(offsetof(TESObjectREFR, baseForm) == 0x01C);
STATIC_ASSERT(sizeof(TESObjectREFR) == 0x054);

// 080
class MobileObject : public TESObjectREFR
{
public:
	MobileObject();
	~MobileObject();

	UInt32 unk054[3];						// 054
	HighProcess*	 unk60;					// 060
	UInt32 unk064[(0x080 - 0x064) >> 2];	// 064
	// 080
};
STATIC_ASSERT(sizeof(MobileObject) == 0x080);

// 00C
class MagicCaster
{
public:
	MagicCaster();
	~MagicCaster();

	UInt32 vtabl;
	UInt32 unk004[2];	// 004
};

STATIC_ASSERT(sizeof(MagicCaster) == 0x00C);

// 010
class MagicTarget
{
public:
	MagicTarget();
	~MagicTarget();
	
	UInt32 vtabl;
	UInt32 unk004[3];	// 004
};

STATIC_ASSERT(sizeof(MagicTarget) == 0x010);

class Actor : public MobileObject
{
public:
	Actor();
	~Actor();

	MagicCaster			magicCaster;			// 080
	MagicTarget			magicTarget;			// 08C
	ActorValueOwner		avOwner;				// 09C
	CachedValuesOwner	cvOwner;				// 0A0

	void EquipItemAlt(void* itemEntry, bool noUnequip, bool noMessage);
	double GetHealthPercent();
	UInt16 GetLevel();
};

STATIC_ASSERT(offsetof(Actor, cvOwner) == 0x0A0);

class Character : public Actor
{
public:
	Character();
	~Character();
};

// 9BC
class PlayerCharacter : public Character
{
public:
	PlayerCharacter();
	~PlayerCharacter();

	// used to flag controls as disabled in disabledControlFlags
	enum {
		kControlFlag_Movement		= 1 << 0,
		kControlFlag_Look			= 1 << 1,
		kControlFlag_Pipboy			= 1 << 2,
		kControlFlag_Fight			= 1 << 3,
		kControlFlag_POVSwitch		= 1 << 4,
		kControlFlag_RolloverText	= 1 << 5,
		kControlFlag_Sneak			= 1 << 6,
	};

	// lotsa data
	bhkRagdollController				* ragDollController;			// 0A4
	bhkRagdollPenetrationUtil			* ragDollPentrationUtil;		// 0A8
	UInt32								unk0AC[(0x184-0x0AC) >> 2];		// 0AC
	PlayerMover							* playerMover;					// 184
	UInt32								unk188[(0x570-0x188) >> 2];		// 188
	BGSNote								* note;							// 570
	UInt32								unk574;							// 574
	ImageSpaceModifierInstanceDOF		* unk578;						// 578
	ImageSpaceModifierInstanceDOF		* unk57C;						// 57C
	ImageSpaceModifierInstanceDRB		* unk580;						// 580
	UInt32								unk584[(0x5A8 - 0x584) >> 2];	// 584
	bool								bThirdPerson;					// 5A8
	UInt8								unk5A9[3];
	UInt8								unk5AC[3];
	bool								alwaysRun;						// 5AF
	bool								autoMove;						// 5B0
	UInt8								unk5B1[3];
	UInt32								unk5B4[(0x5DC - 0x5B4) >> 2];	// 5B4
	UInt32								disabledControlFlags;			// 5DC
	UInt32								unk5E0;							// 5E0
	UInt32								unk5E4;							// 5E4
	UInt32								unk5E8;							// 5E8
	UInt32								unk5EC;							// 5EC
	NiNode								* unk5F0;						// 5F0
	UInt32								unk5F4[(0x604-0x5F4) >> 2];		// 5F4
	TESTopic							* topic;						// 604
	UInt32								unk608[3];						// 608
	TESQuest							* quest;						// 614
	BGSQuestObjective					* questObjective;				// 618
	UInt8								unk61C[(0x9A4 - 0x61C)];		// 61C
	bool								pcInCombat;						// 9A4
	bool								pcUnseen;						// 9A5
	UInt8								unk9A6[(0x9BC - 0x9A6)];		// 9A6

	static PlayerCharacter*	GetSingleton();
};

STATIC_ASSERT(sizeof(PlayerCharacter) == 0x9BC);
STATIC_ASSERT(offsetof(PlayerCharacter, questObjective) == 0x618);
STATIC_ASSERT(offsetof(PlayerCharacter, bThirdPerson) == 0x5A8);
STATIC_ASSERT(offsetof(PlayerCharacter, disabledControlFlags) == 0x5DC);
