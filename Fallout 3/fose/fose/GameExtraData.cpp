#include "GameExtraData.h"
#include "GameBSExtraData.h"

struct GetMatchingEquipped {
	FormMatcher& m_matcher;
	EquipData m_found;

	GetMatchingEquipped(FormMatcher& matcher) : m_matcher(matcher) {
		m_found.pForm = NULL;
		m_found.pExtraData = NULL;
	}

	bool Accept(ExtraContainerChanges::EntryData* pEntryData) {
		if (pEntryData) {
			// quick check - needs an extendData or can't be equipped
			ExtraContainerChanges::ExtendDataList* pExtendList = pEntryData->extendData;
			if (pExtendList && m_matcher.Matches(pEntryData->type)) { 
				SInt32 n = 0;
				ExtraDataList* pExtraDataList = pExtendList->GetNthItem(n);
				while (pExtraDataList) {
					if (pExtraDataList->HasType(kExtraData_Worn) || pExtraDataList->HasType(kExtraData_WornLeft)) {
						m_found.pForm = pEntryData->type;
						m_found.pExtraData = pExtraDataList;
						return false;
					}
					n++;
					pExtraDataList = pExtendList->GetNthItem(n);
				}
			}
		}
		return true;
	}

	EquipData Found() {
		return m_found;
	}
};


EquipData ExtraContainerChanges::FindEquipped(FormMatcher& matcher) const
{
	FoundEquipData equipData;
	if (data && data->objList) {
		GetMatchingEquipped getEquipped(matcher);
		data->objList->Visit(getEquipped);
		equipData = getEquipped.Found();
	}
	return equipData;
};


#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15

static const UInt32 s_ExtraHealthVtbl = 0x00DAD7C4;
static const UInt32 s_ExtraLockVtbl = 0x00DAD770;
static const UInt32 s_ExtraCountVtbl = 0x00DAD7B8;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35

static const UInt32 s_ExtraHealthVtbl = 0x00DB3808;
static const UInt32 s_ExtraLockVtbl = 0x00DB37B4;
static const UInt32 s_ExtraCountVtbl = 0x00DB37FC;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6

static const UInt32 s_ExtraHealthVtbl = 0x00DB3808;
static const UInt32 s_ExtraLockVtbl = 0x00DB37B4;
static const UInt32 s_ExtraCountVtbl = 0x00DB37FC;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b

static const UInt32 s_ExtraHealthVtbl = 0x00DB3808;
static const UInt32 s_ExtraLockVtbl = 0x00DB37B4;
static const UInt32 s_ExtraCountVtbl = 0x00DB37FC;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22

static const UInt32 s_ExtraHealthVtbl = 0x00DB5888;
static const UInt32 s_ExtraLockVtbl = 0x00DB5834;
static const UInt32 s_ExtraCountVtbl = 0x00DB587C;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6

static const UInt32 s_ExtraHealthVtbl = 0x00DB5880;
static const UInt32 s_ExtraLockVtbl = 0x00DB582C;
static const UInt32 s_ExtraCountVtbl = 0x00DB5874;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7

static const UInt32 s_ExtraHealthVtbl = 0x00DB5880;
static const UInt32 s_ExtraLockVtbl = 0x00DB582C;
static const UInt32 s_ExtraCountVtbl = 0x00DB5874;

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng

static const UInt32 s_ExtraHealthVtbl = 0x00DB2880;
static const UInt32 s_ExtraLockVtbl = 0x00DB282C;
static const UInt32 s_ExtraCountVtbl = 0x00DB2874;

#else

#error unsupported runtime version

#endif

STATIC_ASSERT(sizeof(ExtraHealth) == 0x10);
STATIC_ASSERT(sizeof(ExtraLock) == 0x10);
STATIC_ASSERT(sizeof(ExtraCount) == 0x10);

// static
BSExtraData* BSExtraData::Create(UInt8 xType, UInt32 size, UInt32 vtbl)
{
	void* memory = FormHeap_Allocate(size);
	memset(memory, 0, size);
	((UInt32*)memory)[0] = vtbl;
	BSExtraData* xData = (BSExtraData*)memory;
	xData->type = xType;
	return xData;
}

ExtraHealth* ExtraHealth::Create() 
{
	ExtraHealth* xHealth = (ExtraHealth*)BSExtraData::Create(kExtraData_Health, sizeof(ExtraHealth), s_ExtraHealthVtbl);
	return xHealth;
}

ExtraLock* ExtraLock::Create()
{
	ExtraLock* xLock = (ExtraLock*)BSExtraData::Create(kExtraData_Lock, sizeof(ExtraLock), s_ExtraLockVtbl);
	ExtraLock::Data* lockData = (ExtraLock::Data*)FormHeap_Allocate(sizeof(ExtraLock::Data));
	memset(lockData, 0, sizeof(ExtraLock::Data));
	xLock->data = lockData;
	return xLock;
}

ExtraCount* ExtraCount::Create()
{
	ExtraCount* xCount = (ExtraCount*)BSExtraData::Create(kExtraData_Count, sizeof(ExtraCount), s_ExtraCountVtbl);
	xCount->count = 0;
	return xCount;
}