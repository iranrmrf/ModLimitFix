#include "Commands_MiscRef.h"

#include "GameForms.h"
#include "GameObjects.h"
#include "GameExtraData.h"
#include "GameRTTI.h"

bool Cmd_GetBaseObject_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	if (thisObj && thisObj->baseForm) {
		*refResult = thisObj->baseForm->refID;
		if (IsConsoleMode())
			Console_Print("GetBaseObject >> %08x (%s)", thisObj->baseForm->refID, GetFullName(thisObj->baseForm));
	}
	return true;
}


bool Cmd_GetParentCell_Execute(COMMAND_ARGS)
{
	UInt32	* refResult = (UInt32 *)result;
	*refResult = 0;

	if(!thisObj) return true;

	if (thisObj->parentCell) {
		*refResult = thisObj->parentCell->refID;
	}

	return true;
}

bool Cmd_GetParentWorldspace_Execute(COMMAND_ARGS)
{
	UInt32	* refResult = (UInt32 *)result;
	*refResult = 0;

	if(!thisObj) return true;

	if (thisObj->parentCell && thisObj->parentCell->worldSpace) {
		*refResult = thisObj->parentCell->worldSpace->refID;
	}

	return true;
}


bool Cmd_GetOpenKey_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	if (!thisObj)	return true;
	
	ExtraLock* xLock = GetByTypeCast(thisObj->extraDataList, Lock);
	if (xLock && xLock->data && xLock->data->key)
		*refResult = xLock->data->key->refID;

	return true;
}

bool Cmd_SetOpenKey_Execute(COMMAND_ARGS)
{
	TESForm* form;
	*result = 0;
	
	if (!thisObj)	
		return true;

	ExtractArgsEx(EXTRACT_ARGS_EX, &form);
	if (!form)	
		return true;

	TESKey* key = DYNAMIC_CAST(form, TESForm, TESKey);
	if (!key)	
		return true;

	ExtraLock* xLock = GetByTypeCast(thisObj->extraDataList, Lock);
	if (!xLock) {
		xLock = ExtraLock::Create();
		if (!thisObj->extraDataList.Add(xLock))
		{
			FormHeap_Free(xLock->data);
			FormHeap_Free(xLock);
			return true;
		}
	}

	if (xLock)
	{
		xLock->data->key = key;
		*result = 1;
	}

	return true;
}

bool Cmd_GetLinkedDoor_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	if (!thisObj)
		return true;

	ExtraTeleport* xTele = GetByTypeCast(thisObj->extraDataList, Teleport);
	if (xTele)
		*refResult = xTele->data->linkedDoor->refID;

	return true;
}

bool Cmd_GetTeleportCell_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	if (!thisObj)
		return true;

	ExtraTeleport* xTele = GetByTypeCast(thisObj->extraDataList, Teleport);
	if (xTele) {
		*refResult = xTele->data->linkedDoor->parentCell->refID;
	}

	return true;
}

struct CellScanInfo
{
	TESObjectCELL::RefList::Iterator	prev;	//last ref returned to script
	const	TESObjectCELL * curCell;					//cell currently being scanned
	const	TESObjectCELL * cell;						//player's current cell
	const	TESWorldSpace * world;
	SInt8	curX;										//offsets of curCell from player's cell
	SInt8	curY;
	UInt8	formType;									//form type to scan for
	UInt8	cellDepth;									//depth of adjacent cells to scan
	bool	includeTakenRefs;

	CellScanInfo() : curCell(NULL), cell(NULL), world(NULL), curX(0), curY(0), formType(0), cellDepth(0), includeTakenRefs(false)
	{	}

	CellScanInfo(UInt8 _cellDepth, UInt8 _formType, bool _includeTaken, TESObjectCELL* _cell) 
					:	curCell(NULL), cell(_cell), world(NULL), curX(0), curY(0), formType(_formType), cellDepth(_cellDepth), includeTakenRefs(_includeTaken)
	{
		world = cell->worldSpace;

		if (world && cellDepth)		//exterior, cell depth > 0
		{
			curX = cell->coords->x - cellDepth;
			curY = cell->coords->y - cellDepth;
			UInt32 key = (curX << 16) + ((curY << 16) >> 16);
			curCell = world->cellMap->Lookup(key);
		}
		else
		{
			cellDepth = 0;
			curCell = cell;
			curX = cell->coords->x;
			curY = cell->coords->y;
		}
	}

	bool NextCell()		//advance to next cell in area
	{
		if (!world || !cellDepth)
		{
			curCell = NULL;
			return false;
		}

		do
		{
			if (curX - cell->coords->x == cellDepth)
			{
				if (curY - cell->coords->y == cellDepth)
				{
					curCell = NULL;
					return false;
				}
				else
				{
					curY++;
					curX -= cellDepth * 2;
					UInt32 key = (curX << 16) + ((curY << 16) >> 16);
					curCell = world->cellMap->Lookup(key);
				}
			}
			else
			{
				curX++;
				UInt32 key = (curX << 16) + ((curY << 16) >> 16);
				curCell = world->cellMap->Lookup(key);
			}
		}while (!curCell);
		
		return true;
	}

	void FirstCell()	//init curCell to point to first valid cell
	{
		if (!curCell)
			NextCell();
	}

};

class RefMatcherAnyForm
{
	bool m_includeTaken;
public:
	RefMatcherAnyForm(bool includeTaken) : m_includeTaken(includeTaken)
		{ }

	bool Accept(const TESObjectREFR* refr)
	{
		if (m_includeTaken || !(refr->IsTaken()))
			return true;
		else
			return false;
	}
};

class RefMatcherFormType
{
	UInt32 m_formType;
	bool m_includeTaken;
public:
	RefMatcherFormType(UInt32 formType, bool includeTaken) : m_formType(formType), m_includeTaken(includeTaken)
		{ }

	bool Accept(const TESObjectREFR* refr)
	{
		if (!m_includeTaken && refr->IsTaken())
			return false;
		else if (refr->baseForm->typeID == m_formType && refr->baseForm->refID != 7)	//exclude player for kFormType_NPC
			return true;
		else
			return false;
	}
};

class RefMatcherActor
{
public:
	RefMatcherActor()
		{ }

	bool Accept(const TESObjectREFR* refr)
	{
		if (refr->baseForm->typeID == kFormType_Creature)
			return true;
		else if (refr->baseForm->typeID == kFormType_NPC && refr->baseForm->refID != 7) //exclude the player
			return true;
		else
			return false;
	}
};

class RefMatcherItem
{
	bool m_includeTaken;
public:
	RefMatcherItem(bool includeTaken) : m_includeTaken(includeTaken)
		{ }

	bool Accept(const TESObjectREFR* refr)
	{
		if (!m_includeTaken && refr->IsTaken())
			return false;

		switch (refr->baseForm->typeID)
		{
			case kFormType_Armor:
			case kFormType_Book:
			case kFormType_Clothing:
			case kFormType_Ingredient:
			case kFormType_Misc:
			case kFormType_Weapon:
			case kFormType_Ammo:
			case kFormType_Key:
			case kFormType_AlchemyItem:
			case kFormType_ARMA:
				return true;

			case kFormType_Light:
				TESObjectLIGH* light = DYNAMIC_CAST(refr->baseForm, TESForm, TESObjectLIGH);
				if (light)
					if (light->icon.ddsPath.m_dataLen)	//temp hack until I find canCarry flag on TESObjectLIGH
						return true;
		}
		return false;
	}
};

//class ProjectileFinder
//{
//	Actor		* m_owningActor;
//	MagicCaster	* m_magicCaster;
//	TESForm		* m_form;
//	MagicItem	* m_magicItem;
//	UInt32		m_type;
//public:
//	float curLifetime;
//
//	enum {
//		kType_Any,
//		kType_Arrow,
//		kType_Magic
//	};
//
//	ProjectileFinder(UInt32 type, Actor* actor, TESForm* formToMatch)
//		: m_type(type), m_owningActor(actor), m_form(formToMatch)
//	{
//		if (m_form)
//			m_magicItem = DYNAMIC_CAST(m_magicItem, TESForm, MagicItem);
//		
//		m_magicCaster = DYNAMIC_CAST(m_owningActor, Actor, MagicCaster);
//	}
//
//	bool Accept(const TESObjectREFR* refr)
//	{
//		if (refr->baseForm->typeID != kFormType_Ammo)
//			return false;
//		
//		MagicProjectile* magic = DYNAMIC_CAST(refr, TESObjectREFR, MagicProjectile);
//		ArrowProjectile* arrow = DYNAMIC_CAST(refr, TESObjectREFR, ArrowProjectile);
//
//		switch (m_type)
//		{
//		case kType_Arrow:
//			if (m_form && refr->baseForm != m_form)
//				return false;
//			
//			if (!arrow)
//				return false;
//			else if (arrow->shooter != m_owningActor)
//				return false;
//			else
//			{
//				curLifetime = arrow->elapsedTime;
//				return true;	
//			}
//
//		case kType_Magic:
//			if (!magic)
//				return false;
//			else if (magic->caster != m_magicCaster)
//				return false;
//			else if (m_magicItem && magic->magicItem != m_magicItem)
//				return false;
//			else
//			{
//				curLifetime = magic->elapsedTime;
//				return true;
//			}
//		case kType_Any:
//			if (!m_owningActor)
//				return true;
//
//			if (arrow && arrow->shooter == m_owningActor)
//			{
//				curLifetime = arrow->elapsedTime;
//				return true;
//			}
//			
//			if (magic && magic->caster == m_magicCaster)
//			{
//				curLifetime = magic->elapsedTime;
//				return true;
//			}
//
//			return false;
//		default:		// uh-oh
//			return false;
//		}
//	}
//};

static const TESObjectCELL::RefList::Iterator GetCellRefEntry(const TESObjectCELL::RefList& refList, UInt32 formType, TESObjectCELL::RefList::Iterator prev, bool includeTaken /*, ProjectileFinder* projFinder = NULL*/)
{
	TESObjectCELL::RefList::Iterator entry;
	switch(formType)
	{
	case 0:		//Any type
		entry = refList.Find(RefMatcherAnyForm(includeTaken), prev);
		break;
	case 200:	//Actor
		entry = refList.Find(RefMatcherActor(), prev);
		break;
	case 201:	//Inventory Item
		entry = refList.Find(RefMatcherItem(includeTaken), prev);
		break;
	//case 202:	//Owned Projectile
	//	if (projFinder)
	//		entry = visitor.Find(*projFinder, prev);
	//	break;
	default:
		entry = refList.Find(RefMatcherFormType(formType, includeTaken), prev);
	}

	return entry;
}

static TESObjectREFR* CellScan(Script* scriptObj, TESObjectCELL* cellToScan = NULL, UInt32 formType = 0, UInt32 cellDepth = 0, bool getFirst = false, bool includeTaken = false /*, ProjectileFinder* projFinder = NULL*/)
{
	static std::map<UInt32, CellScanInfo> scanScripts;
	UInt32 idx = scriptObj->refID;

	if (getFirst)
		scanScripts.erase(idx);

	if (scanScripts.find(idx) == scanScripts.end())
	{
		scanScripts[idx] = CellScanInfo(cellDepth, formType, includeTaken, cellToScan);
		scanScripts[idx].FirstCell();
	}

	CellScanInfo* info = &(scanScripts[idx]);

	bool bContinue = true;
	while (bContinue)
	{
		info->prev = GetCellRefEntry(info->curCell->objectList, info->formType, info->prev, info->includeTakenRefs /*, projFinder*/);
		if (info->prev.End() || !(*info->prev))				//no ref found
		{
			if (!info->NextCell())			//check next cell if possible
				bContinue = false;
		}
		else
			bContinue = false;			//found a ref
	}

	if ((*info->prev))
		return info->prev.Get();
	else
	{
		scanScripts.erase(idx);
		return NULL;
	}

}

static bool GetFirstRef_Execute(COMMAND_ARGS, bool bUsePlayerCell = true)
{
	UInt32 formType = 0;
	UInt32 cellDepth = -1;
	UInt32 bIncludeTakenRefs = 0;
	UInt32* refResult = (UInt32*)result;
	TESObjectCELL* cell = NULL;
	*refResult = 0;
	
	PlayerCharacter* pc = PlayerCharacter::GetSingleton();
	if (!pc)
		return true;						//avoid crash when these functions called in main menu before parentCell instantiated

	if (bUsePlayerCell)
	{
		if (ExtractArgs(EXTRACT_ARGS, &formType, &cellDepth, &bIncludeTakenRefs))
			cell = pc->parentCell;
		else
			return true;
	}
	else
		if (!ExtractArgs(EXTRACT_ARGS, &cell, &formType, &cellDepth, &bIncludeTakenRefs))
			return true;

	if (!cell)
		return true;

	if (cellDepth == -1)
		cellDepth = 0;

	TESObjectREFR* refr = CellScan(scriptObj, cell, formType, cellDepth, true, bIncludeTakenRefs ? true : false);
	if (refr)
		*refResult = refr->refID;

	if (IsConsoleMode())
		Console_Print("GetFirstRef >> %08x", *refResult);

	return true;
}

bool Cmd_GetFirstRef_Execute(COMMAND_ARGS)
{
	GetFirstRef_Execute(PASS_COMMAND_ARGS, true);
	return true;
}

bool Cmd_GetFirstRefInCell_Execute(COMMAND_ARGS)
{
	GetFirstRef_Execute(PASS_COMMAND_ARGS, false);
	return true;
}

bool Cmd_GetNextRef_Execute(COMMAND_ARGS)
{
	
	PlayerCharacter* pc = PlayerCharacter::GetSingleton();
	if (!pc || !(pc->parentCell))
		return true;						//avoid crash when these functions called in main menu before parentCell instantiated

	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	TESObjectREFR* refr = CellScan(scriptObj);
	if (refr)
		*refResult = refr->refID;

	return true;
}

static bool GetNumRefs_Execute(COMMAND_ARGS, bool bUsePlayerCell = true)
{
	*result = 0;
	UInt32 formType = 0;
	UInt32 cellDepth = -1;
	UInt32 includeTakenRefs = 0;

	PlayerCharacter* pc = PlayerCharacter::GetSingleton();
	if (!pc || !(pc->parentCell))
		return true;						//avoid crash when these functions called in main menu before parentCell instantiated

	TESObjectCELL* cell = NULL;
	if (bUsePlayerCell)
		if (ExtractArgs(EXTRACT_ARGS, &formType, &cellDepth, &includeTakenRefs))
			cell = pc->parentCell;
		else
			return true;
	else
		if (!ExtractArgs(EXTRACT_ARGS, &cell, &formType, &cellDepth, &includeTakenRefs))
			return true;

	if (!cell)
		return true;

	bool bIncludeTakenRefs = includeTakenRefs ? true : false;
	if (cellDepth == -1)
		cellDepth = 0;

	CellScanInfo info(cellDepth, formType, bIncludeTakenRefs, cell);
	info.FirstCell();

	while (info.curCell)
	{
		const TESObjectCELL::RefList& refList = info.curCell->objectList;
		switch (formType)
		{
		case 0:
			*result += refList.CountIf(RefMatcherAnyForm(bIncludeTakenRefs));
			break;
		case 69:
			*result += refList.CountIf(RefMatcherActor());
			break;
		case 70:
			*result += refList.CountIf(RefMatcherItem(bIncludeTakenRefs));
			break;
		default:
			*result += refList.CountIf(RefMatcherFormType(formType, bIncludeTakenRefs));
		}
		info.NextCell();
	}

	return true;
}

bool Cmd_GetNumRefs_Execute(COMMAND_ARGS)
{
	return GetNumRefs_Execute(PASS_COMMAND_ARGS, true);
}

bool Cmd_GetNumRefsInCell_Execute(COMMAND_ARGS)
{
	return GetNumRefs_Execute(PASS_COMMAND_ARGS, false);
}

bool Cmd_GetRefCount_Execute(COMMAND_ARGS)
{
	if (!thisObj)
		return true;

	*result = 1;

	ExtraCount* pXCount = GetByTypeCast(thisObj->extraDataList, Count);
	if (pXCount) {
		*result = pXCount->count;
		if (IsConsoleMode())
			Console_Print("%s: %d", GetFullName(thisObj->baseForm), pXCount->count);
	}
	return true;
}

bool Cmd_SetRefCount_Execute(COMMAND_ARGS)
{
	UInt32 newCount = 0;
	if (!ExtractArgs(EXTRACT_ARGS, &newCount))
		return true;
	else if (!thisObj || newCount > 32767 || newCount < 1)
		return true;

	ExtraCount* pXCount = GetByTypeCast(thisObj->extraDataList, Count);
	if (!pXCount) {
		pXCount = ExtraCount::Create();
		if (!thisObj->extraDataList.Add(pXCount)) {
			FormHeap_Free(pXCount);
			return true;
		}
	}
	pXCount->count = newCount;

	return true;
}


static TESForm* GetOwner(BaseExtraList& xDataList)
{
	TESForm* owner = NULL;
	ExtraOwnership* xOwner = GetByTypeCast(xDataList, Ownership);
	if (xOwner)
		owner = xOwner->owner;

	return owner;
}

static UInt32 GetOwningFactionRequiredRank(BaseExtraList& xDataList)
{
	ExtraRank* xRank = GetByTypeCast(xDataList, Rank);
	if (xRank)
		return xRank->rank;

	return 0;
}

bool Cmd_GetParentCellOwner_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	if (!thisObj)
		return true;

	TESForm* owner = GetOwner(thisObj->parentCell->extraDataList);
	if (owner)
		*refResult = owner->refID;

	return true;
}

bool Cmd_GetOwner_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	if (!thisObj)
		return true;

	TESForm* owner = GetOwner(thisObj->extraDataList);
	if (owner)
		*refResult = owner->refID;

	return true;
}

bool Cmd_GetOwningFactionRequiredRank_Execute(COMMAND_ARGS)
{
	*result = 0;

	if (!thisObj)
		return true;

	*result = GetOwningFactionRequiredRank(thisObj->extraDataList);

	return true;
}

bool Cmd_GetParentCellOwningFactionRequiredRank_Execute(COMMAND_ARGS)
{
	*result = 0;

	if (!thisObj)
		return true;

	*result = GetOwningFactionRequiredRank(thisObj->parentCell->extraDataList);

	return true;
}


static SInt8 IsOffLimits(BaseExtraList& xDataList, TESNPC* actor)
{
	SInt8 offLimits = -1;					//return -1 if ownership is ambiguous

	TESForm* owner = GetOwner(xDataList);
	if (owner)
	{
		if (owner->typeID == kFormType_NPC)			
		{
			if (owner->refID == actor->refID)			//owned by this actor
				offLimits = 0;
			else
			{
				ExtraGlobal* xGlobal = GetByTypeCast(xDataList, Global);

				if (xGlobal && xGlobal->globalVar->data) {
					offLimits = 0;
				} else {
					offLimits = 1;
				}
			}
		}
		else if (owner->typeID == kFormType_Faction)
		{
			TESFaction* owningFaction = DYNAMIC_CAST(owner, TESForm, TESFaction);
			if (owningFaction && !(owningFaction->IsEvil()))		//no crime to steal from evil factions
			{
				SInt8 reqRank = 0;
				ExtraRank* xRank = GetByTypeCast(xDataList, Rank);
				if (xRank)					// ExtraRank only present if required rank > 0
				{
					reqRank = xRank->rank;
				}
				if (actor->baseData.GetFactionRank((TESFaction*)owner) >= reqRank)
					offLimits = 0;
				else
					offLimits = 1;
			}
		}
	}
	return offLimits;
}

bool Cmd_IsOffLimits_Execute(COMMAND_ARGS)
{
	TESNPC* actor = NULL;
	*result = 0;

	if (!thisObj)
		return true;
	else if (!ExtractArgs(EXTRACT_ARGS, &actor))
		return true;

#if FALLOUT_VERSION >= FALLOUT_VERSION_1_7
	//PlayerCharacter* pc = PlayerCharacter::GetSingleton();
	//if (actor->refID == PlayerCharacter::GetSingleton()->refID)		// let the game do the work if it's the player
	//{
	//	*result = CALL_MEMBER_FN(thisObj, IsOffLimitsToPlayer)() ? 1 : 0;
	//	Console_Print("IsOffLimits player >> %.0f", *result);
	//	return true;
	//}
#endif

	TESObjectREFR* refObj = thisObj;
	if (refObj->parentCell && !refObj->parentCell->IsInterior() && refObj->baseForm->typeID == kFormType_Door)
	{
		// ownership data for doors in exteriors stored on linked door
		
		ExtraTeleport* xTele = GetByTypeCast(thisObj->extraDataList, Teleport);
		if (xTele) {
			refObj = xTele->data->linkedDoor;
		}
	}

	if (!refObj)
		return true;

	SInt8 offLimits = IsOffLimits(refObj->extraDataList, actor);
	if (offLimits != -1)
		*result = offLimits;
	else
	{
		offLimits = IsOffLimits(refObj->parentCell->extraDataList, actor);
		if (offLimits == 1)
			*result = 1;
	}

	return true;
}

bool Cmd_IsPersistent_Execute(COMMAND_ARGS)
{
	*result = 0;

	if (thisObj)
		*result = (thisObj->IsPersistent() ? 1 : 0);

	return true;
}

bool Cmd_SetEyes_Execute(COMMAND_ARGS)
{
	TESForm	* part = NULL;
	TESForm	* target = NULL;

	*result = 0;

	if(!ExtractArgsEx(EXTRACT_ARGS_EX, &part, &target))
		return true;

	TESEyes	* eyes = DYNAMIC_CAST(part, TESForm, TESEyes);
	if(!eyes)
		return true;

	if(!target)
	{
		if(!thisObj)
			return true;
		target = thisObj->baseForm;
	}

	if(!target)
		return true;

	TESNPC	* npc = DYNAMIC_CAST(target, TESForm, TESNPC);
	if(!npc)
		return true;

	npc->eyes = eyes;

	*result = 1;

	return true;
}

bool Cmd_SetHair_Execute(COMMAND_ARGS)
{
	TESForm	* part = NULL;
	TESForm	* target = NULL;

	*result = 0;

	if(!ExtractArgsEx(EXTRACT_ARGS_EX, &part, &target))
		return true;

	TESHair	* hair = DYNAMIC_CAST(part, TESForm, TESHair);
	if(!hair)
		return true;

	if(!target)
	{
		if(!thisObj)
			return true;
		target = thisObj->baseForm;
	}

	if(!target)
		return true;

	TESNPC	* npc = DYNAMIC_CAST(target, TESForm, TESNPC);
	if(!npc)
		return true;

	npc->hair = hair;

	*result = 1;

	return true;
}

bool Cmd_SetHairLength_Execute(COMMAND_ARGS)
{
	float	length = 0;
	TESForm	* target = NULL;

	*result = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &length, &target))
		return true;

	if(!target)
	{
		if(!thisObj)
			return true;
		target = thisObj->baseForm;
	}

	if(!target)
		return true;

	TESNPC	* npc = DYNAMIC_CAST(target, TESForm, TESNPC);
	if(!npc)
		return true;

	npc->hairLength = length;

	*result = 1;

	return true;
}

bool Cmd_GetEyes_Execute(COMMAND_ARGS)
{
	TESNPC	* npc = 0;
	UInt32	* refResult = (UInt32 *)result;

	*refResult = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &npc))
		return true;

	if(!npc && thisObj)
		npc = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESNPC);

	if(npc && npc->eyes)
	{
		if(IsConsoleMode())
			Console_Print("GetEyes: %08X", npc->eyes->refID);

		*refResult = npc->eyes->refID;
	}

	return true;
}

bool Cmd_GetHair_Execute(COMMAND_ARGS)
{
	TESNPC	* npc = 0;
	UInt32	* refResult = (UInt32 *)result;

	*refResult = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &npc))
		return true;

	if(!npc && thisObj)
		npc = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESNPC);

	if(npc && npc->hair)
	{
		if(IsConsoleMode())
			Console_Print("GetHair: %08X", npc->hair->refID);

		*refResult = npc->hair->refID;
	}

	return true;
}

bool Cmd_GetHairLength_Execute(COMMAND_ARGS)
{
	TESNPC	* npc = 0;

	*result = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &npc))
		return true;

	if(!npc && thisObj)
		npc = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESNPC);

	if(npc)
	{
		if(IsConsoleMode())
			Console_Print("GetHairLength: %f", npc->hairLength);

		*result = npc->hairLength;
	}

	return true;
}
