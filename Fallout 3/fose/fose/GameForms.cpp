#include "GameForms.h"
#include "GameRTTI.h"
#include "GameObjects.h"
#include "GameExtraData.h"

TESForm * TESForm::TryGetREFRParent(void)
{
	TESForm			* result = this;
	if(result) {
		TESObjectREFR	* refr = DYNAMIC_CAST(this, TESForm, TESObjectREFR);
		if(refr && refr->baseForm)
			result = refr->baseForm;
	}
	return result;
}

UInt8 TESForm::GetModIndex() const
{
	return (refID >> 24);
}

TESFullName* TESForm::GetFullName()
{
	TESForm* baseForm = this;
	TESFullName* fullName = NULL;

	if (typeID >= kFormType_Reference && typeID <= kFormType_ACRE)	//handle MapMarkers and references
	{
		TESObjectREFR* refr = DYNAMIC_CAST(this, TESForm, TESObjectREFR);
		//if (refr->baseForm->typeID == kFormType_Static)
		//{
		//	ExtraMapMarker* mapMarker = (ExtraMapMarker*)refr->extraDataList.GetByType(kExtraData_MapMarker);
		//	if (mapMarker && mapMarker->data)
		//		fullName = &mapMarker->data->fullName;
		//}

		if (!fullName)		//if not a mapmarker, use the base form instead
			baseForm = refr->baseForm;
	}
	else if (typeID == kFormType_Cell)		// some exterior cells inherit name of parent worldspace
	{
		TESObjectCELL* cell = DYNAMIC_CAST(this, TESForm, TESObjectCELL);
		if (cell && cell->worldSpace)
			if (!cell->fullName.name.m_data || !cell->fullName.name.m_dataLen)
					baseForm = cell->worldSpace;
	}

	if(!fullName)
		fullName = DYNAMIC_CAST(baseForm, TESForm, TESFullName);

	return fullName;
}

bool TESForm::IsCloned() const
{
	return GetModIndex() == 0xff;
}

TESForm* TESForm::CloneForm(bool bPersist) const
{
	TESForm* clone = NULL;
	clone = (TESForm*)CreateFormInstance(typeID);
	if (clone) {
		clone->CopyFrom(this);
		AddFormToDataHandler(clone);
		if (bPersist) {
			AddFormToCreatedBaseObjectsList(clone);
		}
	}
	return clone;
}


class ScriptVarFinder
{
public:
	const char* m_varName;
	ScriptVarFinder(const char* varName) : m_varName(varName)
		{	}
	bool Accept(Script::VariableInfo* varInfo)
	{
		//_MESSAGE("  cur var: %s to match: %s", varInfo->name.m_data, m_varName);
		if (!_stricmp(m_varName, varInfo->name.m_data))
			return true;
		else
			return false;
	}
};

Script::VariableInfo* Script::GetVariableByName(const char* varName)
{
	VariableInfo* pVariableInfo = vars.Find(ScriptVarFinder(varName));
	return pVariableInfo;
}

Script::RefVariable	* Script::GetVariable(UInt32 reqIdx)
{
	if (reqIdx > 0) reqIdx--;
	RefVariable* pRefVar = refs.GetNthItem(reqIdx);
	return pRefVar;
}

void Script::RefVariable::Resolve(ScriptEventList * eventList)
{
	if(varIdx && eventList)
	{
		ScriptEventList::Var	* var = eventList->GetVariable(varIdx);
		if(var)
		{
			UInt32	refID = *((UInt32 *)&var->data);
			form = LookupFormByID(refID);
		}
	}
}


EffectItem* EffectItemList::ItemAt(UInt32 whichItem)
{
	return list.GetNthItem(whichItem);
}

UInt32 EffectItemList::CountItems() const
{
	return list.Count();
}

const char* EffectItemList::GetNthEIName(UInt32 whichEffect) const
{
	EffectItem* pEffectItem = list.GetNthItem(whichEffect);
	if (pEffectItem) {
		if (pEffectItem->scriptEffectInfo) {
			return pEffectItem->scriptEffectInfo->effectName.m_data;
		} else if (pEffectItem->setting) {
			return GetFullName(pEffectItem->setting);
		}
	}
	return "<no name>";
}

class FindByForm {
	TESForm* m_pForm;
public:
	FindByForm(TESForm* pForm) : m_pForm(pForm) {}
	bool Accept(TESForm* pForm) const {
		return (pForm->refID == m_pForm->refID) ? true : false;
	}
};

SInt32 BGSListForm::GetIndexOf(TESForm* pForm)
{
	return list.GetIndexOf(FindByForm(pForm));
}

SInt32 BGSListForm::RemoveForm(TESForm* pForm)
{
	SInt32 index = GetIndexOf(pForm);
	if (index >= 0) {
		RemoveNthForm(index);
	}
	return index;
}

SInt32 BGSListForm::ReplaceForm(TESForm* pForm, TESForm* pReplaceWith)
{
	SInt32 index = GetIndexOf(pForm);
	if (index >= 0) {
		list.ReplaceNth(index, pReplaceWith);
	}
	return index;
}

// static
UInt32 TESBipedModelForm::MaskForSlot(UInt32 slot)
{
	switch(slot) {
		case ePart_Head:		return eSlot_Head;
		case ePart_Hair:		return eSlot_Hair;
		case ePart_UpperBody:	return eSlot_UpperBody;
		case ePart_LeftHand:	return eSlot_LeftHand;
		case ePart_RightHand:	return eSlot_RightHand;
		case ePart_Weapon:		return eSlot_Weapon;
		case ePart_PipBoy:		return eSlot_PipBoy;
		case ePart_Backpack:	return eSlot_Backpack;
		case ePart_Necklace:	return eSlot_Necklace;
		case ePart_Headband:	return eSlot_Headband;
		case ePart_Hat:			return eSlot_Hat;
		case ePart_Eyeglasses:	return eSlot_Eyeglasses;
		case ePart_Nosering:	return eSlot_Nosering;
		case ePart_Earrings:	return eSlot_Earrings;
		case ePart_Mask:		return eSlot_Mask;
		case ePart_Choker:		return eSlot_Choker;
		case ePart_MouthObject:	return eSlot_MouthObject;
		case ePart_BodyAddon1:	return eSlot_BodyAddon1;
		case ePart_BodyAddon2:	return eSlot_BodyAddon2;
		case ePart_BodyAddon3:	return eSlot_BodyAddon3;
		default:				return -1;
	}
}

UInt8 TESObjectWEAP::HandGrip() const
{
	switch(handGrip) {
		case eHandGrip_1:	return 1;
		case eHandGrip_2:	return 2;
		case eHandGrip_3:	return 3;

		case eHandGrip_Default:
		default:
			return 0;
	}
}

void TESObjectWEAP::SetHandGrip(UInt8 _handGrip)
{
	switch(_handGrip) {
		case 0:	{
			handGrip = eHandGrip_Default;
			break;
		}
		case 1:	{
			handGrip = eHandGrip_1;
			break;
		}
		case 2:	{
			handGrip = eHandGrip_2;
			break;
		}
		case 3:	{
			handGrip = eHandGrip_3;
			break;
		}
		default:	// not a real value, so don't set it
			break;
	}
}

UInt8 TESObjectWEAP::AttackAnimation() const
{
	switch(attackAnim) {
		case eAttackAnim_Default:		return 0;
		case eAttackAnim_Attack3:		return 1;
		case eAttackAnim_Attack4:		return 2;
		case eAttackAnim_Attack5:		return 3;
		case eAttackAnim_Attack6:		return 4;
		case eAttackAnim_Attack7:		return 5;
		case eAttackAnim_Attack8:		return 6;
		case eAttackAnim_AttackLeft:	return 7;
		case eAttackAnim_AttackLoop:	return 8;
		case eAttackAnim_AttackRight:	return 9;
		case eAttackAnim_AttackSpin:	return 10;
		case eAttackAnim_AttackSpin2:	return 11;
		case eAttackAnim_AttackThrow:	return 12;
		case eAttackAnim_AttackThrow2:	return 13;
		case eAttackAnim_AttackThrow3:	return 14;
		case eAttackAnim_AttackThrow4:	return 15;
		case eAttackAnim_AttackThrow5:	return 16;
		case eAttackAnim_PlaceMine:		return 17;
		case eAttackAnim_PlaceMine2:	return 18;

		default:
			return -1;
	}
}

void TESObjectWEAP::SetAttackAnimation(UInt8 _attackAnim)
{
	switch(_attackAnim) {
		case 0: {
			attackAnim = eAttackAnim_Default; 
			break;
		}
		case 1: {
			attackAnim = eAttackAnim_Attack3; 
			break;
		}
		case 2: {
			attackAnim = eAttackAnim_Attack4;
			break;
		}
		case 3: {
			attackAnim = eAttackAnim_Attack5;
			break;
		}
		case 4: {
			attackAnim = eAttackAnim_Attack6;
			break;
		}
		case 5: {
			attackAnim = eAttackAnim_Attack7;
			break;
		}
		case 6: {
			attackAnim = eAttackAnim_Attack8;
			break;
		}
		
		case 7: {
			attackAnim = eAttackAnim_AttackLeft;
			break;
		}
		case 8: {
			attackAnim = eAttackAnim_AttackLoop;
			break;
		}
		case 9: {
			attackAnim = eAttackAnim_AttackRight;
			break;
		}
		case 10: {
			attackAnim = eAttackAnim_AttackSpin;
			break;
		}
		case 11: {
			attackAnim = eAttackAnim_AttackSpin2;
			break;
		}
		case 12: {
			attackAnim = eAttackAnim_AttackThrow;
			break;
		}
		case 13: {
			eAttackAnim_AttackThrow2;
			break;
		}
		case 14: {
			attackAnim = eAttackAnim_AttackThrow3;
			break;
		}
		case 15: {
			attackAnim = eAttackAnim_AttackThrow4;
			break;
		}
		case 16: {
			attackAnim = eAttackAnim_AttackThrow5;
			break;
		}
		case 17: {
			attackAnim = eAttackAnim_PlaceMine;
			break;
		}
		case 18: {
			attackAnim = eAttackAnim_PlaceMine2;
			break;
		}
		default:
			break;
	}
}

class FactionMatcher
{
	TESFaction* pFaction;
public:
	FactionMatcher(TESFaction* faction) : pFaction(faction) {}
	bool Accept(TESActorBaseData::FactionListData* data) {
		return (data->faction == pFaction) ? true : false;
	}
};

SInt8 TESActorBaseData::GetFactionRank(TESFaction* faction)
{
	FactionMatcher matcher(faction);
	FactionListData* pData = factionList.Find(matcher);
	return (pData) ? pData->rank : -1;
}
