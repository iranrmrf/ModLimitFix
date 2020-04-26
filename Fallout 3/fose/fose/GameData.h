#pragma once

#include "GameForms.h"
#include "Utilities.h"

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	static const UInt32 _ModInfo_GetNextChunk = 0x00447C80;	// args: none retn: UInt32 subrecordType
	static const UInt32 _ModInfo_GetChunkData = 0x00447210;	// args: void* buf, UInt32 bufSize retn: bool readSucceeded
	static const UInt32 _ModInfo_Read32		  =	0x00447CB0;	// args: void* buf retn: void
	static const UInt32 _ModInfo_HasMoreSubrecords = 0x004464D0;
	static const UInt32 _ModInfo_InitializeForm = 0x004481C0;	// args: TESForm* retn: void

	// addresses of static ModInfo members holding type info about currently loading form
	static const UInt32* s_ModInfo_CurrentChunkTypeCode = (UInt32*)0x0106ACB4;
	static const UInt32* s_ModInfo_CurrentFormTypeEnum = (UInt32*)0x0106ACB0;

	static const UInt8** g_CreatedObjectData = (const UInt8**)0x0106ACA0;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
	static const UInt32* g_CreatedObjectSize = (UInt32*)0x0106ACA4;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	static const UInt32 _ModInfo_GetNextChunk = 0x00448BE0;	// args: none retn: UInt32 subrecordType
	static const UInt32 _ModInfo_GetChunkData = 0x00448170;	// args: void* buf, UInt32 bufSize retn: bool readSucceeded
	static const UInt32 _ModInfo_Read32		  =	0x00448C10;	// args: void* buf retn: void
	static const UInt32 _ModInfo_HasMoreSubrecords = 0x00447430;
	static const UInt32 _ModInfo_InitializeForm = 0x00449120;	// args: TESForm* retn: void

	// addresses of static ModInfo members holding type info about currently loading form
	static const UInt32* s_ModInfo_CurrentChunkTypeCode = (UInt32*)0x0106AA34;
	static const UInt32* s_ModInfo_CurrentFormTypeEnum = (UInt32*)0x0106AA30;

	static const UInt8** g_CreatedObjectData = (const UInt8**)0x0106AA20;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
	static const UInt32* g_CreatedObjectSize = (UInt32*)0x0106AA24;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	static const UInt32 _ModInfo_GetNextChunk = 0x00448740;	// args: none retn: UInt32 subrecordType
	static const UInt32 _ModInfo_GetChunkData = 0x00447CD0;	// args: void* buf, UInt32 bufSize retn: bool readSucceeded
	static const UInt32 _ModInfo_Read32		  =	0x00448770;	// args: void* buf retn: void
	static const UInt32 _ModInfo_HasMoreSubrecords = 0x00446F90;
	static const UInt32 _ModInfo_InitializeForm = 0x00448C80;	// args: TESForm* retn: void

	// addresses of static ModInfo members holding type info about currently loading form
	static const UInt32* s_ModInfo_CurrentChunkTypeCode = (UInt32*)0x0106AB34;
	static const UInt32* s_ModInfo_CurrentFormTypeEnum = (UInt32*)0x0106AB30;

	static const UInt8** g_CreatedObjectData = (const UInt8**)0x0106AB20;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
	static const UInt32* g_CreatedObjectSize = (UInt32*)0x0106AB24;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	static const UInt32 _ModInfo_GetNextChunk = 0x00448950;	// args: none retn: UInt32 subrecordType
	static const UInt32 _ModInfo_GetChunkData = 0x00447EE0;	// args: void* buf, UInt32 bufSize retn: bool readSucceeded
	static const UInt32 _ModInfo_Read32		  =	0x00448980;	// args: void* buf retn: void
	static const UInt32 _ModInfo_HasMoreSubrecords = 0x004471A0;
	static const UInt32 _ModInfo_InitializeForm = 0x00448E90;	// args: TESForm* retn: void

	// addresses of static ModInfo members holding type info about currently loading form
	static const UInt32* s_ModInfo_CurrentChunkTypeCode = (UInt32*)0x0106AB34;
	static const UInt32* s_ModInfo_CurrentFormTypeEnum = (UInt32*)0x0106AB30;

	static const UInt8** g_CreatedObjectData = (const UInt8**)0x0106AB20;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
	static const UInt32* g_CreatedObjectSize = (UInt32*)0x0106AB24;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	static const UInt32 _ModInfo_GetNextChunk = 0x00448840;	// args: none retn: UInt32 subrecordType
	static const UInt32 _ModInfo_GetChunkData = 0x00447DD0;	// args: void* buf, UInt32 bufSize retn: bool readSucceeded
	static const UInt32 _ModInfo_Read32		  =	0x00448870;	// args: void* buf retn: void
	static const UInt32 _ModInfo_HasMoreSubrecords = 0x00447090;
	static const UInt32 _ModInfo_InitializeForm = 0x00448D80;	// args: TESForm* retn: void

	// addresses of static ModInfo members holding type info about currently loading form
	static const UInt32* s_ModInfo_CurrentChunkTypeCode = (UInt32*)0x0106DD34;
	static const UInt32* s_ModInfo_CurrentFormTypeEnum = (UInt32*)0x0106DD30;

	static const UInt8** g_CreatedObjectData = (const UInt8**)0x0106DD20;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
	static const UInt32* g_CreatedObjectSize = (UInt32*)0x0106DD24;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	static const UInt32 _ModInfo_GetNextChunk = 0x00448700;	// args: none retn: UInt32 subrecordType
	static const UInt32 _ModInfo_GetChunkData = 0x00447C90;	// args: void* buf, UInt32 bufSize retn: bool readSucceeded
	static const UInt32 _ModInfo_Read32		  =	0x00448730;	// args: void* buf retn: void
	static const UInt32 _ModInfo_HasMoreSubrecords = 0x00446F50;
	static const UInt32 _ModInfo_InitializeForm = 0x00448C40;	// args: TESForm* retn: void

	// addresses of static ModInfo members holding type info about currently loading form
	static const UInt32* s_ModInfo_CurrentChunkTypeCode = (UInt32*)0x0106DD34;
	static const UInt32* s_ModInfo_CurrentFormTypeEnum = (UInt32*)0x0106DD30;

	static const UInt8** g_CreatedObjectData = (const UInt8**)0x0106DD20;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
	static const UInt32* g_CreatedObjectSize = (UInt32*)0x0106DD24;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	static const UInt32 _ModInfo_GetNextChunk = 0x004487D0;	// args: none retn: UInt32 subrecordType
	static const UInt32 _ModInfo_GetChunkData = 0x00447D60;	// args: void* buf, UInt32 bufSize retn: bool readSucceeded
	static const UInt32 _ModInfo_Read32		  =	0x00448800;	// args: void* buf retn: void
	static const UInt32 _ModInfo_HasMoreSubrecords = 0x00447020;
	static const UInt32 _ModInfo_InitializeForm = 0x00448D10;	// args: TESForm* retn: void

	// addresses of static ModInfo members holding type info about currently loading form
	static const UInt32* s_ModInfo_CurrentChunkTypeCode = (UInt32*)0x0106DD34;
	static const UInt32* s_ModInfo_CurrentFormTypeEnum = (UInt32*)0x0106DD30;

	static const UInt8** g_CreatedObjectData = (const UInt8**)0x0106DD20;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
	static const UInt32* g_CreatedObjectSize = (UInt32*)0x0106DD24;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	static const UInt32 _ModInfo_GetNextChunk = 0x004488B0;	// args: none retn: UInt32 subrecordType
	static const UInt32 _ModInfo_GetChunkData = 0x00447E40;	// args: void* buf, UInt32 bufSize retn: bool readSucceeded
	static const UInt32 _ModInfo_Read32		  =	0x004488E0;	// args: void* buf retn: void
	static const UInt32 _ModInfo_HasMoreSubrecords = 0x00447090;
	static const UInt32 _ModInfo_InitializeForm = 0x00448DF0;	// args: TESForm* retn: void

	// addresses of static ModInfo members holding type info about currently loading form
	static const UInt32* s_ModInfo_CurrentChunkTypeCode = (UInt32*)0x0106AD34;
	static const UInt32* s_ModInfo_CurrentFormTypeEnum = (UInt32*)0x0106AD30;

	static const UInt8** g_CreatedObjectData = (const UInt8**)0x0106AD20;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
	static const UInt32* g_CreatedObjectSize = (UInt32*)0x0106AD24;
#else
#error unsupported fallout version
#endif

class TESRegionManager;
class BSFile;

// 10
class BoundObjectListHead
{
public:
	BoundObjectListHead();
	~BoundObjectListHead();

	UInt32			boundObjectCount;	// 0
	TESBoundObject	* first;			// 4
	TESBoundObject	* last;				// 8
	UInt32			unkC;				// C
};

typedef NiTArray <TESRegion> TESRegionList;

struct FormRecordData
{
	UInt8		typeID;		// corresponds to kFormType_XXX
	UInt32		typeCode;	// i.e. 'GMST', 'FACT'
	UInt32		unk08;		// only seen zero
};

struct ChunkHeader
{
	UInt32	type : 4;	// i.e. 'XGRD', 'DATA'
	UInt16	size : 2;
};

// 42C -> may have grown by 4 bytes after patch 1.1.0.35, doesn't affect known offsets
struct ModInfo		// referred to by game as TESFile
{
	ModInfo();
	~ModInfo();

	// 18 info about currently loading form
	struct FormInfo
	{
		UInt32		recordType;			// 00 i.e. 'FACT', 'GMST'
		UInt32		unk04;				// 04 looks like size of entire record
		UInt32		formFlags;			// 08 copied to TESForm->flags
		UInt32		formID;				// 0C 
		UInt32		unk10;				// 10
		UInt16		unk14;				// 14 always initialized to 0F on SaveForm. 
		UInt16		unk16;
	};

	tList<UInt32>						unkList;			// 000
	UInt32 /*NiTPointerMap<TESFile*>*/	* pointerMap;		// 008
	UInt32								unk00C;				// 00C
	BSFile*								unkFile;			// 010
	UInt32								unk014;				// 014 
	void								* unk018;			// 018 seen all zeroes. size unknown
	void								* unk01C;			// 01C as above
	char								name[0x104];		// 020
	char								filepath[0x104];	// 124
	UInt32								unk228;				// 228
	UInt32								unk22C;				// init'd to dword_F469CC (0x2800) same val as BSFile+10?
	UInt32								unk230;				// 230
	UInt32								unk234;				// 234
	UInt32								unk238;				// 238
	UInt32								unk23C;				// 23C
	FormInfo							formInfo;			// 240
	ChunkHeader							subRecord;			// 258
	UInt32								unk260;				// 260
	UInt32								fileOffset;			// 264
	UInt32								dataOffset;			// 268 index into dataBuf
	UInt32								subrecordBytesRead;	// 26C generates error on Read if != expected length
	UInt32						unk268[(0x298-0x270) >> 2];	// 270
	UInt8								unk298;				// 298
	UInt8								bIsBigEndian;		// 299
	UInt8								unk29A;				// 29A
	UInt8								pad29B;
	WIN32_FIND_DATA						fileData;			// 29C
	float								unk3DC;				// 3DC init'd to 0.94
	UInt32								unk3E0;				// 3E0
	UInt32								flags;				// 3E4 init'd to 0x00000800. 4000 and 40000 do stuff
	UInt8								unk3E8;				// 3E8
	UInt8								pad3E9[3];
	UInt32								unk3EC;				// 3EC
	UInt32								unk3F0;				// 3F0
	UInt32								unk3F4;				// 3F4
	UInt32								unk3F8;				// 3F8
	UInt32								numRefMods;			// 3FC related to modindex; see 4472D0
																// formIDs in mod are as saved in GECK, must fix up at runtime
	ModInfo								** refModInfo;		// 400 used to look up modInfo based on fixed mod index, double-check
	UInt32								unk404;				// 404
	UInt32								unk408;				// 408
	UInt8								modIndex;			// 40C init to 0xFF
	UInt8								pad40D[3];
	String								author;				// 410
	String								description;		// 418
	void								* dataBuf;			// 420 
	UInt32								unk424;				// 424 looks like size of entire record
	UInt8								unk428;				// 428
	UInt8								pad429[3];
	
	bool IsLoaded() const { return true; }

	/*** used by TESForm::LoadForm() among others ***/
	MEMBER_FN_PREFIX(ModInfo);
	DEFINE_MEMBER_FN(GetNextChunk, UInt32, _ModInfo_GetNextChunk);	// returns chunk type
	DEFINE_MEMBER_FN(GetChunkData, bool, _ModInfo_GetChunkData, UInt8* buf, UInt32 bufSize); // max size, not num to read
	DEFINE_MEMBER_FN(Read32, void, _ModInfo_Read32, void* out);
	DEFINE_MEMBER_FN(HasMoreSubrecords, bool, _ModInfo_HasMoreSubrecords);
};

STATIC_ASSERT(sizeof(WIN32_FIND_DATA) == 0x140);
STATIC_ASSERT(offsetof(ModInfo, name) == 0x20);
STATIC_ASSERT(offsetof(ModInfo, subRecord) == 0x258);
STATIC_ASSERT(sizeof(ModInfo) == 0x42C);

struct ModList
{
	tList<ModInfo>		modInfoList;
	UInt32				loadedModCount;
	ModInfo*			loadedMods[0xFF];
};
STATIC_ASSERT(sizeof(ModList) == 0x408);

#if RUNTIME
#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	const UInt32 _DataHandler_AddForm = 0x00443CC0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	const UInt32 _DataHandler_AddForm = 0x00444AC0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	const UInt32 _DataHandler_AddForm = 0x004445B0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	const UInt32 _DataHandler_AddForm = 0x004447C0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	const UInt32 _DataHandler_AddForm = 0x004446A0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	const UInt32 _DataHandler_AddForm = 0x00444560;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	const UInt32 _DataHandler_AddForm = 0x00444630;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	const UInt32 _DataHandler_AddForm = 0x004446A0;
#else
	#error unsupported runtime version
#endif
#else
	const UInt32 _DataHandler_AddForm = 0;
#endif


// 5B8
class DataHandler
{
public:
	DataHandler();
	~DataHandler();

	BoundObjectListHead				* boundObjectList;		// 000
	tList<TESPackage>				packageList;			// 004
	tList<TESWorldSpace>			worldSpaceList;			// 00C
	tList<TESClimate>				climateList;			// 014
	tList<TESImageSpace>			imageSpaceList;			// 01C
	tList<TESImageSpaceModifier>	imageSpaceModList;		// 024
	tList<TESWeather>				weatherList;			// 02C
	tList<EnchantmentItem>			enchantmentItemList;	// 034
	tList<SpellItem>				spellItemList;			// 03C
	tList<BGSHeadPart>				headPartList;			// 044
	tList<TESHair>					hairList;				// 04C
	tList<TESEyes>					eyeList;				// 054
	tList<TESRace>					raceList;				// 05C
	tList<BGSEncounterZone>			encounterZoneList;		// 066
	tList<TESLandTexture>			landTextureList;		// 06C
	tList<BGSCameraShot>			cameraShotList;			// 074
	tList<TESClass>					classList;				// 07C
	tList<TESFaction>				factionList;			// 084
	tList<Script>					scriptList;				// 08C
	tList<TESSound>					soundList;				// 094
	tList<BGSAcousticSpace>			acousticSpaceList;		// 09C
	tList<BGSRagdoll>				ragdollList;			// 0A4
	tList<TESGlobal>				globalList;				// 0AC
	tList<BGSVoiceType>				voiceTypeList;			// 0B4
	tList<BGSImpactData>			impactDataList;			// 0BC
	tList<BGSImpactDataSet>			impactDataSetList;		// 0C4
	tList<TESTopic>					topicList;				// 0CC
	tList<TESQuest>					questList;				// 0D4
	tList<TESCombatStyle>			combatStyleList;		// 0DC
	tList<TESLoadScreen>			loadScreenList;			// 0E4
	tList<TESWaterForm>				waterFormList;			// 0EC
	tList<TESEffectShader>			effectShaderList;		// 0F4
	tList<BGSProjectile>			projectileList;			// 0FC
	tList<BGSExplosion>				explosionList;			// 104
	tList<BGSRadiationStage>		radiationStageList;		// 10C
	tList<BGSDebris>				debrisList;				// 114
	tList<BGSPerk>					perkList;				// 11C
	tList<BGSBodyPartData>			bodyPartDataList;		// 124
	tList<BGSNote>					noteList;				// 12C
	tList<BGSListForm>				listFormList;			// 134
	tList<BGSMenuIcon>				menuIconList;			// 13C
	tList<TESObjectANIO>			anioList;				// 144
	tList<BGSMessage>				messageList;			// 14C
	tList<BGSLightingTemplate>		lightninghTemplateList;	// 154
	tList<BGSMusicType>				musicTypeList;			// 15C
	TESRegionList					* regionList;			// 164
	NiTArray<TESObjectCELL*>		cellArray;				// 168
	NiTArray<BGSAddonNode*>			addonArray;				// 178
	UInt32	unk188[0x5];									// 188
	ModList							modList;				// 19C
	UInt32							unk5A4;					// 5A4
	UInt32							unk5A8;					// 5A8
	UInt32							unk5AC;					// 5AC
	TESRegionManager				* regionManager;		// 5B0
	UInt32							unk5B4;					// 5B4
	
	static DataHandler* Get();
	const ModInfo* LookupModByName(const char* modName);
	UInt8 GetModIndex(const char* modName);
	UInt8 GetActiveModCount() const;

	MEMBER_FN_PREFIX(DataHandler);
	DEFINE_MEMBER_FN(DoAddForm, UInt32, _DataHandler_AddForm, TESForm * pForm);	// stupid name is because AddForm is redefined in windows header files

	TESQuest* GetQuestByName(const char* questName);
};

STATIC_ASSERT((0x5A8-0x19C) == 0x40C);
STATIC_ASSERT(sizeof(NiTArray<TESObjectCELL*>) == 0x10);
STATIC_ASSERT(offsetof(DataHandler, listFormList) == 0x134);
STATIC_ASSERT(offsetof(DataHandler, regionList) == 0x164);
STATIC_ASSERT(offsetof(DataHandler, modList) == 0x19C);
STATIC_ASSERT(offsetof(DataHandler, regionManager) == 0x5B0);
STATIC_ASSERT(sizeof(DataHandler) == 0x5B8);
