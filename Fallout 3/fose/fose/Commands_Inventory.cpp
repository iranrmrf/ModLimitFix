#include "Commands_Inventory.h"

#include "GameRTTI.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameExtraData.h"

// testing conditionals with this
bool Cmd_GetWeight_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;
	TESForm* form = (TESForm*)arg1;
	if (form)
	{
		TESWeightForm* weightForm = DYNAMIC_CAST(form, TESForm, TESWeightForm);
		if (weightForm)
		{
			*result = weightForm->weight;
			if (IsConsoleMode())
				Console_Print("GetWeight >> %.2f", *result);
		}
	}

	return true;
}

bool Cmd_GetWeight_Execute(COMMAND_ARGS)
{
	TESForm* form = NULL;
	*result = 0;

	if (ExtractArgs(EXTRACT_ARGS, &form))
	{
		form = form->TryGetREFRParent();
		if (!form && thisObj)
			form = thisObj->baseForm;

		if (form)
			return Cmd_GetWeight_Eval(thisObj, form, 0, result);
	}

	return true;
}

bool Cmd_GetType_Execute(COMMAND_ARGS)
{
	*result= 0;
	TESForm* form = 0;

	if(!ExtractArgsEx(EXTRACT_ARGS_EX, &form)) return true;
	form = form->TryGetREFRParent();
	if (!form) {
		if (!thisObj) return true;
		form = thisObj->baseForm;
	}

#if _DEBUG
	bool bDump = false;
	if (bDump) {
		DumpClass(form);		
	}
#endif
	*result = form->typeID;	

	return true;
}

bool Cmd_GetHealth_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (!thisObj) return true;
			pForm = thisObj->baseForm;
		}

		TESHealthForm* pHealth = DYNAMIC_CAST(pForm, TESForm, TESHealthForm);
		if (pHealth) {
			*result = pHealth->health;
		}
	}
	return true;
}

bool Cmd_GetRepairList_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = 0;

	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}

	BGSRepairItemList* pRepairList = DYNAMIC_CAST(pForm, TESForm, BGSRepairItemList);
	if (pRepairList) {
		*((UInt32*)result) = pRepairList->listForm->refID;
#if _DEBUG
		Console_Print("repair list: %X", pRepairList->listForm->refID);
#endif
	}
	return true;
}

bool Cmd_GetWeaponAmmo_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = 0;
	
	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}

	BGSAmmoForm* pAmmoForm = DYNAMIC_CAST(pForm, TESForm, BGSAmmoForm);
	if (pAmmoForm && pAmmoForm->ammo) {
		*((UInt32*)result) = pAmmoForm->ammo->refID;
#if _DEBUG
		TESFullName* ammoName = DYNAMIC_CAST(pAmmoForm->ammo, TESAmmo, TESFullName);
		Console_Print("ammo: %X (%s)", pAmmoForm->ammo->refID, ammoName ? ammoName->name.m_data : "unknown ammo");
#endif
	}
	return true;
}

bool Cmd_GetWeaponClipRounds_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = 0;
	
	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}
	BGSClipRoundsForm* pClipRounds = DYNAMIC_CAST(pForm, TESForm, BGSClipRoundsForm);
	if (pClipRounds) {
		*result = pClipRounds->clipRounds;
#if _DEBUG
		Console_Print("clipRounds: %d", pClipRounds->clipRounds);
#endif
	}
	return true;
}

bool Cmd_GetAttackDamage_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = 0;
	
	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}

	TESAttackDamageForm* pDamage = DYNAMIC_CAST(pForm, TESForm, TESAttackDamageForm);
	if (pDamage) {
		*result = pDamage->damage;
#if _DEBUG
		Console_Print("damage: %d", pDamage->damage);
#endif
	}
	return true;
}

enum EWeapValues
{
	eWeap_Type = 0,
	eWeap_MinSpread,
	eWeap_Spread,
	eWeap_Proj,
	eWeap_SightFOV,
	eWeap_MinRange,
	eWeap_Range,
	eWeap_AmmoUse,
	eWeap_APCost,
	eWeap_CritDam,
	eWeap_CritChance,
	eWeap_CritEffect,
	eWeap_FireRate,
	eWeap_AnimAttackMult,
	eWeap_RumbleLeft,
	eWeap_RumbleRight,
	eWeap_RumbleDuration,
	eWeap_RumbleWaveLength,
	eWeap_AnimShotsPerSec,
	eWeap_AnimReloadTime,
	eWeap_AnimJamTime,
	eWeap_Skill,
	eWeap_ResistType,
	eWeap_FireDelayMin,
	eWeap_FireDelayMax,
	eWeap_AnimMult,
	eWeap_Reach,
	eWeap_IsAutomatic,
	eWeap_HandGrip,
	eWeap_ReloadAnim,
	eWeap_VATSChance,
	eWeap_AttackAnim,
	eWeap_NumProj,
	eWeap_AimArc,
	eWeap_LimbDamageMult,
	eWeap_SightUsage,
};

bool GetWeaponValue_Execute(COMMAND_ARGS, UInt32 whichVal)
{
	*result = 0;
	TESForm* pForm = 0;
	
	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}

	TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
	if (pWeapon) {
		switch(whichVal) {
			case eWeap_Type: {
				*result = pWeapon->eWeaponType;
				break;
			}
			case eWeap_MinSpread: {
				*result = pWeapon->minSpread;
				break;
			}
			case eWeap_Spread: {
				*result = pWeapon->spread;
				break;
			}
			case eWeap_Proj: {
				BGSProjectile* pProj = pWeapon->projectile;
				if (pProj) {
					*((UInt32*)result) = pProj->refID;
				}
				break;
			}
			case eWeap_SightFOV: {
				*result = pWeapon->sightFOV;
				break;
			}
			case eWeap_MinRange: {
				*result = pWeapon->minRange;
				break;
			}
			case eWeap_Range: {
				*result = pWeapon->maxRange;
				break;
			}
			case eWeap_AmmoUse: {
				*result = pWeapon->ammoUse;
				break;
			}
			case eWeap_APCost: {
				*result = pWeapon->AP;
				break;
			}
			case eWeap_CritDam: {
				*result = pWeapon->criticalDamage;
				break;
			}
			case eWeap_CritChance: {
				*result = pWeapon->criticalPercent;
				break;
			}
			case eWeap_CritEffect: {
				SpellItem* pSpell = pWeapon->criticalEffect;
				if (pSpell) {
					*((UInt32*)result) = pSpell->refID;
				}
				break;
			}
			case eWeap_FireRate : {
				*result = pWeapon->fireRate;
				break;
			}
			case eWeap_AnimAttackMult: {
				*result = pWeapon->animAttackMult;
				break;
			}
			case eWeap_RumbleLeft: {
				*result = pWeapon->rumbleLeftMotor;
				break;
			}
			case eWeap_RumbleRight: {
				*result = pWeapon->rumbleRightMotor;
				break;
			}
			case eWeap_RumbleDuration: {
				*result = pWeapon->rumbleDuration;
				break;
			}
			case eWeap_RumbleWaveLength: {
				*result = pWeapon->rumbleWavelength;
				break;
			}
			case eWeap_AnimShotsPerSec: {
				*result = pWeapon->animShotsPerSec;
				break;
			}
			case eWeap_AnimReloadTime: {
				*result = pWeapon->animReloadTime;
				break;
			}
			case eWeap_AnimJamTime: {
				*result = pWeapon->animJamTime;
				break;
			}
			case eWeap_Skill: {
				*result = pWeapon->weaponSkill;
				break;
			}
			case eWeap_ResistType: {
				*result = pWeapon->resistType;
				break;
			}
			case eWeap_FireDelayMin: {
				*result = pWeapon->semiAutoFireDelayMin;
				break;
			}
			case eWeap_FireDelayMax: {
				*result = pWeapon->semiAutoFireDelayMax;
				break;
			}
			case eWeap_AnimMult: {
				*result = pWeapon->animMult;
				break;
			}
			case eWeap_Reach: {
				*result = pWeapon->reach;
				break;
			}
			case eWeap_IsAutomatic: {
				*result = pWeapon->IsAutomatic() ? 1 : 0;
				break;
			}
			case eWeap_HandGrip: {
				*result = pWeapon->HandGrip();
				break;
			}
			case eWeap_ReloadAnim: {
				*result = pWeapon->reloadAnim;
				break;
			}
			case eWeap_VATSChance: {
				*result = pWeapon->baseVATSChance;
				break;
			}
			case eWeap_AttackAnim: {
				*result = pWeapon->AttackAnimation();
				break;
			}
			case eWeap_NumProj: {
				*result = pWeapon->numProjectiles;
				break;
			}
			case eWeap_AimArc: {
				*result = pWeapon->aimArc;
				break;
			}
			case eWeap_LimbDamageMult: {
				*result = pWeapon->limbDamageMult;
				break;
			}
			case eWeap_SightUsage: {
				*result = pWeapon->sightUsage;
				break;
			}

		}
	}

	return true;
}

bool Cmd_GetWeaponType_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_Type);
}

bool Cmd_GetWeaponMinSpread_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_MinSpread);
}

bool Cmd_GetWeaponSpread_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_Spread);
}

bool Cmd_GetWeaponProjectile_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_Proj);
}

bool Cmd_GetWeaponSightFOV_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_SightFOV);
}

bool Cmd_GetWeaponMinRange_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_MinRange);
}

bool Cmd_GetWeaponMaxRange_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_Range);
}

bool Cmd_GetWeaponAmmoUse_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_AmmoUse);
}

bool Cmd_GetWeaponActionPoints_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_APCost);
}

bool Cmd_GetWeaponCritDamage_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_CritDam);
}

bool Cmd_GetWeaponCritChance_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_CritChance);
}

bool Cmd_GetWeaponCritEffect_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_CritEffect);
}

bool Cmd_GetWeaponFireRate_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_FireRate);
}

bool Cmd_GetWeaponAnimAttackMult_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_AnimAttackMult);
}

bool Cmd_GetWeaponRumbleLeftMotor_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_RumbleLeft);
}

bool Cmd_GetWeaponRumbleRightMotor_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_RumbleRight);
}

bool Cmd_GetWeaponRumbleDuration_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_RumbleDuration);
}

bool Cmd_GetWeaponRumbleWavelength_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_RumbleWaveLength);
}

bool Cmd_GetWeaponAnimShotsPerSec_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_AnimShotsPerSec);
}

bool Cmd_GetWeaponAnimReloadTime_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_AnimReloadTime);
}

bool Cmd_GetWeaponAnimJamTime_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_AnimJamTime);
}

bool Cmd_GetWeaponSkill_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_Skill);
}

bool Cmd_GetWeaponResistType_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_ResistType);
}

bool Cmd_GetWeaponFireDelayMin_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_FireDelayMin);
}

bool Cmd_GetWeaponFireDelayMax_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_FireDelayMax);
}

bool Cmd_GetWeaponAnimMult_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_AnimMult);
}

bool Cmd_GetWeaponReach_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_Reach);
}

bool Cmd_GetWeaponIsAutomatic_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_IsAutomatic);
}

bool Cmd_GetWeaponHandGrip_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_HandGrip);
}

bool Cmd_GetWeaponReloadAnim_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_ReloadAnim);
}

bool Cmd_GetWeaponBaseVATSChance_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_VATSChance);
}

bool Cmd_GetWeaponAttackAnimation_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_AttackAnim);
}

bool Cmd_GetWeaponNumProjectiles_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_NumProj);
}

bool Cmd_GetWeaponAimArc_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_AimArc);
}

bool Cmd_GetWeaponLimbDamageMult_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_LimbDamageMult);
}

bool Cmd_GetWeaponSightUsage_Execute(COMMAND_ARGS)
{
	return GetWeaponValue_Execute(PASS_COMMAND_ARGS, eWeap_SightUsage);
}

bool Cmd_GetArmorAR_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = NULL;

	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}

	TESObjectARMO* pArmor = DYNAMIC_CAST(pForm, TESForm, TESObjectARMO);
	if (pArmor) {
		*result = pArmor->armorRating;
	}
	return true;
}

bool Cmd_IsPowerArmor_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = NULL;
	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}
	
	TESBipedModelForm* pBiped = DYNAMIC_CAST(pForm, TESForm, TESBipedModelForm);
	if (pBiped) {
		*result = pBiped->IsPowerArmor() ? 1 : 0;
	}
	return true;
}

bool Cmd_GetEquipType_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = 0;
	
	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}

	BGSEquipType* pEquipType = DYNAMIC_CAST(pForm, TESForm, BGSEquipType);
	if (pEquipType) {
		*result = pEquipType->equipType;
	}
	return true;
}

bool Cmd_GetValue_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = 0;
	
	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}

	TESValueForm* pValue = DYNAMIC_CAST(pForm, TESForm, TESValueForm);
	if (pValue) {
		*result = pValue->value;
	}
	return true;
}


TESForm* Extract_IntAndForm(COMMAND_ARGS, UInt32& intVal)
{
	TESForm* pForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &intVal, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (thisObj) {
				pForm = thisObj->baseForm;
			}
		}
	}
	return pForm;
}

TESForm* Extract_FloatAndForm(COMMAND_ARGS, float& floatVal)
{
	TESForm* pForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &floatVal, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (thisObj) {
				pForm = thisObj->baseForm;
			}
		}
	}
	return pForm;
}

TESObjectWEAP* Extract_FloatAndWeapon(COMMAND_ARGS, float& floatVal) {
	TESObjectWEAP* pWeapon = NULL;
	TESForm* pForm = Extract_FloatAndForm(PASS_COMMAND_ARGS, floatVal);
	if (pForm) {
		pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);	
	}
	return pWeapon;
}

bool Cmd_SetWeaponClipRounds_Execute(COMMAND_ARGS) 
{
	*result = 0;
	UInt32 clipRounds = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, clipRounds);
	if (pForm) {
		BGSClipRoundsForm* pClipRounds = DYNAMIC_CAST(pForm, TESForm, BGSClipRoundsForm);
		if (pClipRounds) {
			pClipRounds->clipRounds = clipRounds;
		#if _DEBUG
			Console_Print("clipRounds: %d", pClipRounds->clipRounds);
		#endif
		}
	}
	return true;
}

bool Cmd_SetWeaponMinSpread_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->minSpread = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponSpread_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->spread = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponSightFOV_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->sightFOV = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponMinRange_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->minRange = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponMaxRange_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->maxRange = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponAmmoUse_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm) {
		TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
		if (pWeapon) {
			pWeapon->ammoUse = intVal;
		}
	}
	return true;
}

bool Cmd_SetWeaponActionPoints_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->AP = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponCritDamage_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm) {
		TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
		if (pWeapon) {
			pWeapon->criticalDamage = intVal;
		}
	}
	return true;
}

bool Cmd_SetWeaponType_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm && intVal < TESObjectWEAP::kWeapType_Last) {
		TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
		if (pWeapon) {
			pWeapon->eWeaponType = intVal;
		}
	}
	return true;
}


bool Cmd_SetWeaponCritChance_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->criticalPercent = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponCritEffect_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = NULL;
	MagicItem* pMagicItem = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &pMagicItem, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (!thisObj) return true;
			pForm = thisObj->baseForm;
		}
		SpellItem* pSpell = DYNAMIC_CAST(pMagicItem, MagicItem, SpellItem);
		if (pForm && pSpell) {
			TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
			if (pWeapon) {
				pWeapon->criticalEffect = pSpell;
			}
		}
	}
	return true;
}

bool Cmd_SetWeight_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESForm* pForm = Extract_FloatAndForm(PASS_COMMAND_ARGS, floatVal);
	if (pForm) {
		TESWeightForm* pWeightForm = DYNAMIC_CAST(pForm, TESForm, TESWeightForm);
		if (pWeightForm) {
			pWeightForm->weight = floatVal;
		}
	}
	return true;
}

bool Cmd_SetAttackDamage_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm) {
		TESAttackDamageForm* pAttackDmg = DYNAMIC_CAST(pForm, TESForm, TESAttackDamageForm);
		if (pAttackDmg) {
			pAttackDmg->damage = intVal;
		}
	}
	return true;
}

bool Cmd_SetWeaponAmmo_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = NULL;
	TESForm* pAmmoForm = NULL;
	bool bExtracted = ExtractArgsEx(EXTRACT_ARGS_EX, &pAmmoForm, &pForm);
	if (bExtracted) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (!thisObj) return true;
			pForm = thisObj->baseForm;
		}
		TESAmmo* pAmmo = DYNAMIC_CAST(pAmmoForm, TESForm, TESAmmo);
		if (pForm && pAmmo) {
			TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
			if (pWeapon) {
				pWeapon->ammo.ammo = pAmmo;
			}
		}
	}
	return true;
}

bool Cmd_SetWeaponProjectile_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = NULL;
	TESForm* pProjectileForm = NULL;
	bool bExtracted = ExtractArgsEx(EXTRACT_ARGS_EX, &pProjectileForm, &pForm);
	if (bExtracted) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (!thisObj) return true;
			pForm = thisObj->baseForm;
		}
		BGSProjectile* pProjectile = DYNAMIC_CAST(pProjectileForm, TESForm, BGSProjectile);
		if (pForm && pProjectile) {
			TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
			if (pWeapon) {
				pWeapon->projectile = pProjectile;
			}
		}
	}
	return true;
}

bool Cmd_SetRepairList_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = NULL;
	BGSListForm* pListForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &pListForm, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (!thisObj) return true;
			pForm = thisObj->baseForm;
		}

		BGSRepairItemList* pRepairList = DYNAMIC_CAST(pForm, TESForm, BGSRepairItemList);
		if (pRepairList && pListForm) {
			pRepairList->listForm = pListForm;
		}
	}
	return true;
}


bool Cmd_SetWeaponAnimMult_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->animMult = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponAnimAttackMult_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->animAttackMult = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponReach_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->reach = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponIsAutomatic_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm) {
		TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
		if (pWeapon) {
			pWeapon->SetIsAutomatic(intVal == 1);
		}
	}
	return true;
}

bool Cmd_SetWeaponHandGrip_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm  && intVal < TESObjectWEAP::eHandGrip_Count) {
		TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
		if (pWeapon) {
			pWeapon->SetHandGrip(intVal);
		}
	}
	return true;
}

bool Cmd_SetWeaponReloadAnim_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm && intVal < TESObjectWEAP::eReload_Count) {
		TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
		if (pWeapon) {
			pWeapon->reloadAnim = intVal;
		}
	}
	return true;
}

bool Cmd_SetWeaponBaseVATSChance_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm && intVal <= 100) {
		TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
		if (pWeapon) {
			pWeapon->baseVATSChance = intVal;
		}
	}
	return true;
}

bool Cmd_SetWeaponAttackAnimation_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm && intVal < TESObjectWEAP::eAttackAnim_Count) {
		TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
		if (pWeapon) {
			pWeapon->SetAttackAnimation(intVal);
		}
	}
	return true;
}

bool Cmd_SetWeaponNumProjectiles_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 intVal = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, intVal);
	if (pForm && intVal <= 255) {
		TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
		if (pWeapon) {
			pWeapon->numProjectiles = intVal;
		}
	}
	return true;
}

bool Cmd_SetWeaponAimArc_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->aimArc = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponLimbDamageMult_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->limbDamageMult = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponSightUsage_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->sightUsage = floatVal;
	}
	return true;
}


bool Cmd_CompareNames_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* form = NULL;
	TESForm* base = NULL;
	ExtractArgsEx(EXTRACT_ARGS_EX, &form, &base);
	form = form->TryGetREFRParent();
	base = base->TryGetREFRParent();

	if (!form)
		return true;
	if (!base)
	{
		if (!thisObj)
			return true;
		base = thisObj->baseForm;
	}

	TESFullName* first = DYNAMIC_CAST(base, TESForm, TESFullName);
	TESFullName* second = DYNAMIC_CAST(form, TESForm, TESFullName);
	if (first && second) 
		*result = first->name.Compare(second->name); 

	return true;
}

// SetName
bool Cmd_SetName_Execute(COMMAND_ARGS)
{
	if (!result) return true;
	
	TESForm* form = NULL;
	char	string[256];

	ExtractArgsEx(EXTRACT_ARGS_EX, &string, &form);
	form = form->TryGetREFRParent();
	if (!form) {
		if (!thisObj) return true;
		form = thisObj->baseForm;
	}

	TESFullName* name = form->GetFullName();
	if (name) {
		name->name.Set(string);
	}
	return true;
}

bool Cmd_SetIsPowerArmor_Execute(COMMAND_ARGS)
{
	TESForm* pForm = NULL;
	UInt32 isPA = 0;

	pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, isPA);
	if (pForm) {
		TESBipedModelForm* pBiped = DYNAMIC_CAST(pForm, TESForm, TESBipedModelForm);
		if (pBiped) {
			pBiped->SetPowerArmor( isPA != 0);
		}
	}
	return true;
}


// Get Equipped Object utility functions
class MatchBySlot : public FormMatcher
{
	UInt32 m_slotMask;
public:
	MatchBySlot(UInt32 slot) : m_slotMask(TESBipedModelForm::MaskForSlot(slot)) {}
	bool Matches(TESForm* pForm) const {
		UInt32 formMask = 0;
		if (pForm) {
			if (pForm->IsWeapon()) {
				formMask = TESBipedModelForm::eSlot_Weapon;
			} else {
				TESBipedModelForm* pBip = DYNAMIC_CAST(pForm, TESForm, TESBipedModelForm);
				if (pBip) {
					formMask = pBip->partMask;
				}
			}
		}
		return (formMask & m_slotMask) != 0;
	}
};

class MatchBySlotMask : public FormMatcher
{
	UInt32 m_targetMask;
	UInt32 m_targetData;
public:
	MatchBySlotMask(UInt32 targetMask, UInt32 targetData) : m_targetMask(targetMask) {}
	bool Matches(TESForm* pForm) const {
		UInt32 slotMask = 0;
		if (pForm) {
			if (pForm->IsWeapon()) {
				slotMask = TESBipedModelForm::ePart_Weapon;
			} else {
				TESBipedModelForm* pBip = DYNAMIC_CAST(pForm, TESForm, TESBipedModelForm);
				if (pBip) {
					slotMask = pBip->partMask;
				}
			}
		}
		return ((slotMask & m_targetMask) == m_targetData); 
	}
};


static EquipData FindEquipped(TESObjectREFR* thisObj, FormMatcher& matcher) {
	ExtraContainerChanges* pContainerChanges = static_cast<ExtraContainerChanges*>(thisObj->extraDataList.GetByType(kExtraData_ContainerChanges));
	return (pContainerChanges) ? pContainerChanges->FindEquipped(matcher) : EquipData();
}



bool Cmd_GetEquippedObject_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32* refResult = ((UInt32*)result);
	
	if (thisObj) {
		UInt32 slotIdx = 0;
		if (ExtractArgs(EXTRACT_ARGS, &slotIdx)) {
			MatchBySlot matcher(slotIdx);
			EquipData equipD = FindEquipped(thisObj, matcher); 
			TESForm* pFound = equipD.pForm;
			if (pFound) {
				*refResult = pFound->refID;
			}
		}
	}
	return true;
}

bool Cmd_GetEquippedCurrentHealth_Execute(COMMAND_ARGS)
{
	*result = 0;
	
	if (thisObj) {
		UInt32 slotIdx = 0;
		if (ExtractArgs(EXTRACT_ARGS, &slotIdx)) {
			MatchBySlot matcher(slotIdx);
			EquipData equipD = FindEquipped(thisObj, matcher);
			if (equipD.pForm) {
				ExtraHealth* pXHealth = equipD.pExtraData ? (ExtraHealth*)equipD.pExtraData->GetByType(kExtraData_Health) : NULL;
				if (pXHealth) {
					*result = pXHealth->health;
					if (IsConsoleMode()) {
						Console_Print("GetEquippedCurrentHealth: %.2f", pXHealth->health);
					}
				} else {
					TESHealthForm* pHealth = DYNAMIC_CAST(equipD.pForm, TESForm, TESHealthForm);
					if (pHealth) {
						*result = pHealth->health;
						if (IsConsoleMode()) {
							Console_Print("GetEquippedCurrentHealth: baseHealth: %d", pHealth->health);
						}
					}
				}
			}
		}
	}
	return true;
}

static bool AdjustHealth(TESHealthForm* pHealth, ExtraDataList* pExtraData, float nuHealth)
{
	ExtraHealth* pXHealth = (ExtraHealth*)pExtraData->GetByType(kExtraData_Health);
	if (nuHealth < 0) nuHealth = 0;
	if (nuHealth >= pHealth->health) {
		if (pXHealth) {
			pExtraData->Remove(pXHealth);
			FormHeap_Free(pXHealth);
			pXHealth = NULL;
		}
	} else if (pXHealth) {
		pXHealth->health = nuHealth;
	} else {
		// need to create a new pXHealth
		pXHealth = ExtraHealth::Create();
		if (pXHealth) {
			pXHealth->health = nuHealth;
			if (!pExtraData->Add(pXHealth)) {
				FormHeap_Free(pXHealth);
				pXHealth = NULL;
			}
		}
	}
	return true;
}

bool Cmd_SetEquippedCurrentHealth_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (!thisObj) return true;


	UInt32 slotIdx = 0;
	float health = 0;
	if (!ExtractArgs(EXTRACT_ARGS, &health, &slotIdx)) return true;
	MatchBySlot matcher(slotIdx);
	EquipData equipD = FindEquipped(thisObj, matcher);
	if (equipD.pForm && equipD.pExtraData) {
		TESHealthForm* pHealth = DYNAMIC_CAST(equipD.pForm, TESForm, TESHealthForm);
		if (pHealth) {
			float nuHealth = health;
			AdjustHealth(pHealth, equipD.pExtraData, nuHealth);
		}
	}
	return true;
}

bool Cmd_IsClonedForm_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* form = NULL;

	ExtractArgsEx(EXTRACT_ARGS_EX, &form);
	form = form->TryGetREFRParent(); 
	if (!form) {
		if (!thisObj) return true;
		form = thisObj->baseForm;
	}

	*result = form->IsCloned() ? 1 : 0;
	return true;
}

bool CloneForm_Execute(COMMAND_ARGS, bool bPersist)
{
	*result = 0;
	UInt32* refResult = (UInt32*)result;
	TESForm* form = NULL;
	ExtractArgsEx(EXTRACT_ARGS_EX, &form);
	if (!form) {
		if (!thisObj) return true;
		form = thisObj->baseForm;
	}

	TESForm* clonedForm = form->CloneForm(bPersist); 
	if (clonedForm) {
		*refResult = clonedForm->refID;
		if (IsConsoleMode())
			Console_Print("Created cloned form: %08x", *refResult);
	}

	return true;
}

bool Cmd_TempCloneForm_Execute(COMMAND_ARGS)
{
	return CloneForm_Execute(PASS_COMMAND_ARGS, false);
}

bool Cmd_CloneForm_Execute(COMMAND_ARGS)
{
	return CloneForm_Execute(PASS_COMMAND_ARGS, true);
}

// testing conditionals with this
bool Cmd_GetWeaponHasScope_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;
	TESForm* form = (TESForm*)arg1;
	if (form)
	{
		TESObjectWEAP* weapon = DYNAMIC_CAST(form, TESForm, TESObjectWEAP);
		if (weapon)
		{
			*result = weapon->HasScope() ? 1 : 0;
		}
	}

	return true;
}

bool Cmd_GetWeaponHasScope_Execute(COMMAND_ARGS)
{
	TESForm* form = NULL;
	*result = 0;

	if (ExtractArgs(EXTRACT_ARGS, &form))
	{
		form = form->TryGetREFRParent();
		if (!form && thisObj)
			form = thisObj->baseForm;

		if (form)
			return Cmd_GetWeaponHasScope_Eval(thisObj, form, 0, result);
	}

	return true;
}

bool Cmd_GetObjectEffect_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32* refResult = (UInt32*)result;
	TESForm* form = NULL;
	ExtractArgsEx(EXTRACT_ARGS_EX, &form);
	if (!form) {
		if (!thisObj) return true;
		form = thisObj->baseForm;
	}
	
	TESEnchantableForm* enchantable = DYNAMIC_CAST(form, TESForm, TESEnchantableForm);

	if (enchantable && enchantable->enchantItem) {
		*refResult = enchantable->enchantItem->refID;
	}

	return true;
}

bool Cmd_GetHotkeyItem_Execute(COMMAND_ARGS)
{
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;

	UInt32 hotkeyNum;	// passed as 1 - 8, stored by game as 0-7
	if (ExtractArgs(EXTRACT_ARGS, &hotkeyNum) && --hotkeyNum < 8)
	{
		BSExtraData* xData = PlayerCharacter::GetSingleton()->extraDataList.GetByType(kExtraData_ContainerChanges);
		ExtraContainerChanges* xChanges = (ExtraContainerChanges *)xData;
		if (xChanges)
		{
			for (ExtraContainerChanges::EntryDataList::Iterator itemIter = xChanges->data->objList->Begin();
				!itemIter.End();
				++itemIter)
			{
				for (ExtraContainerChanges::ExtendDataList::Iterator iter = itemIter->extendData->Begin();
					!iter.End();
					++iter)
				{
					ExtraHotkey* xHotKey = (ExtraHotkey*)iter->GetByType(kExtraData_Hotkey);
					if (xHotKey && xHotKey->index == hotkeyNum)
					{
						*refResult = itemIter->type->refID;
						if (IsConsoleMode())
							Console_Print("GetHotkeyItem >> %08x (%s)", *refResult, GetFullName(itemIter->type));

						return true;
					}
				}
			}
		}
	}

	// not found
	if (IsConsoleMode())
		Console_Print("GetHotkeyItem >> Hotkey not assigned");

	return true;
}

bool Cmd_SetBaseItemValue_Execute(COMMAND_ARGS)
{
	TESForm* form = NULL;
	UInt32 newVal = 0;

	if (ExtractArgs(EXTRACT_ARGS, &form, &newVal))
	{
		TESValueForm* valForm = DYNAMIC_CAST(form, TESForm, TESValueForm);
		if (valForm)
			CALL_MEMBER_FN(valForm, SetValue)(newVal);
	}

	return true;
}

bool Cmd_SetHealth_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 health = 0;
	TESForm* pForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &health, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (!thisObj) return true;
			pForm = thisObj->baseForm;
		}

		TESHealthForm* pHealth = DYNAMIC_CAST(pForm, TESForm, TESHealthForm);
		if (pHealth) {
			pHealth->health = health;
		}
	}
	return true;
}

bool Cmd_GetCurrentHealth_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (!thisObj) return true;
	TESHealthForm* pHealth = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESHealthForm);
	if (!pHealth) return true;
	ExtraHealth* pXHealth = (ExtraHealth*)thisObj->extraDataList.GetByType(kExtraData_Health);
	*result = pXHealth ? pXHealth->health : pHealth->health;
	return true;
}

bool Cmd_SetCurrentHealth_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (!thisObj) return true;

	TESHealthForm* pHealth = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESHealthForm);
	if (!pHealth) return true;

	float nuHealth = 0.0;

	if (ExtractArgs(EXTRACT_ARGS, &nuHealth)) {
		if (nuHealth < 0.0) nuHealth = 0.0;
		AdjustHealth(pHealth, &thisObj->extraDataList, nuHealth);
	}
	return true;
}

static void PrintItemType(TESForm * form)
{
	Console_Print("%s (%s)", GetFullName(form), GetObjectClassName(form));
}


typedef std::vector<ExtraContainerChanges::EntryData*> ExtraDataVec;
typedef std::map<TESForm*, UInt32> ExtraContainerMap;

class ExtraContainerInfo
{
	ExtraDataVec	m_vec;
	ExtraContainerMap m_map;
public:
	ExtraContainerInfo(ExtraContainerChanges::EntryDataList * entryList) : m_map(), m_vec()
	{
		m_vec.reserve(128);
		if (entryList) {
			entryList->Visit(*this);
		}
	}

	bool Accept(ExtraContainerChanges::EntryData* data) 
	{
		if (data) {
			m_vec.push_back(data);
			m_map[data->type] = m_vec.size()-1;
		}
		return true;
	}

	bool IsValidFormCount(TESContainer::FormCount* formCount, SInt32& numObjects)
	{
		if (formCount) {
			numObjects = formCount->count;
			TESForm* pForm = formCount->form;

			if (DYNAMIC_CAST(pForm, TESForm, TESLevItem))
				return false;

			ExtraContainerMap::iterator it = m_map.find(pForm);
			ExtraContainerMap::iterator itEnd = m_map.end();
			if (it != itEnd) {
				UInt32 index = it->second;
				ExtraContainerChanges::EntryData* pXData = m_vec[index];
				if (pXData) {
					numObjects += pXData->countDelta;
				}
				// clear the object from the vector so we don't bother to look for it
				// in the second step
				m_vec[index] = NULL;
			}

			if (numObjects > 0) {
				if (IsConsoleMode()) {
					PrintItemType(pForm);
				}
				return true;
			}
		}
		return false;
	}

	// returns the count of items left in the vector
	UInt32 CountItems() {
		UInt32 count = 0;
		ExtraDataVec::iterator itEnd = m_vec.end();
		ExtraDataVec::iterator it = m_vec.begin();
		while (it != itEnd) {
			ExtraContainerChanges::EntryData* extraData = (*it);
			if (extraData && (extraData->countDelta > 0)) {
				count++;
				if (IsConsoleMode()) {
					PrintItemType(extraData->type);
				}
			}
			++it;
		}
		return count;
	}

	ExtraContainerChanges::EntryData* GetNth(UInt32 n, UInt32 count) {
		ExtraDataVec::iterator itEnd = m_vec.end();
		ExtraDataVec::iterator it = m_vec.begin();
		while (it != itEnd) {
			ExtraContainerChanges::EntryData* extraData = (*it);
			if (extraData && (extraData->countDelta > 0)) {
				if(count == n)
				{
					return extraData;
				}
				count++;
			}
			++it;
		}
		return NULL;
	}

};

class ContainerCountIf
{
	ExtraContainerInfo& m_info;
public:
	ContainerCountIf(ExtraContainerInfo& info) : m_info(info) { }

	bool Accept(TESContainer::FormCount* formCount) const
	{
		SInt32 numObjects = 0; // not needed in this count
		return m_info.IsValidFormCount(formCount, numObjects);
	}
};

class ContainerFindNth
{
	ExtraContainerInfo& m_info;
	UInt32 m_findIndex;
	UInt32 m_curIndex;
public:
	ContainerFindNth(ExtraContainerInfo& info, UInt32 findIndex) : m_info(info), m_findIndex(findIndex), m_curIndex(0) { }

	bool Accept(TESContainer::FormCount* formCount)
	{
		SInt32 numObjects = 0;
		if (m_info.IsValidFormCount(formCount, numObjects)) {
			if (m_curIndex == m_findIndex) {
				return true;
			}
			m_curIndex++;
		}
		return false;
	}

	UInt32 GetCurIdx() { return m_curIndex; }
};

bool Cmd_GetNumItems_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (!thisObj) return true;

	// handle critical section?

	UInt32 count = 0;

	ExtraContainerChanges* pXContainerChanges = static_cast<ExtraContainerChanges*>(thisObj->extraDataList.GetByType(kExtraData_ContainerChanges));
	ExtraContainerInfo info(pXContainerChanges ? pXContainerChanges->GetEntryDataList() : NULL);
	
	TESContainer* pContainer = NULL;
	TESForm* pBaseForm = thisObj->baseForm;
	if (pBaseForm) {
		pContainer = DYNAMIC_CAST(pBaseForm, TESForm, TESContainer);
	}

	// first walk the base container
	if (pContainer) {
		ContainerCountIf counter(info);
		count = pContainer->formCountList.CountIf(counter);
	}
	
	// now count the remaining items
	count += info.CountItems();
	
	*result = count;

	// handle leave critical section
	
	if(IsConsoleMode())
		Console_Print("item count: %d", count);

	return true;
}

static TESForm* GetItemByIdx(TESObjectREFR* thisObj, UInt32 objIdx, SInt32* outNumItems)
{
	if (!thisObj) return NULL;
	if(outNumItems) *outNumItems = 0;

	UInt32 count = 0;

	ExtraContainerChanges* pXContainerChanges = static_cast<ExtraContainerChanges*>(thisObj->extraDataList.GetByType(kExtraData_ContainerChanges));
	ExtraContainerInfo info(pXContainerChanges ? pXContainerChanges->GetEntryDataList() : NULL);

	TESContainer* pContainer = NULL;
	TESForm* pBaseForm = thisObj->baseForm;
	if (pBaseForm) {
		pContainer = DYNAMIC_CAST(pBaseForm, TESForm, TESContainer);
	}

	// first look in the base container
	if (pContainer) {
		ContainerFindNth finder(info, objIdx);
		TESContainer::FormCount* pFound = pContainer->formCountList.Find(finder);
		if (pFound) {
			if (outNumItems) *outNumItems = pFound->count;
			return pFound->form;
		} else {
			count = finder.GetCurIdx();
		}
	}

	// now walk the remaining items in the map
	ExtraContainerChanges::EntryData* pEntryData = info.GetNth(objIdx, count);
	if (pEntryData) {
		if (outNumItems) *outNumItems = pEntryData->countDelta;
		return pEntryData->type;
	}
	return NULL;
}


bool Cmd_GetInventoryObject_Execute(COMMAND_ARGS)
{
	*result = 0;

	if (!thisObj) return true;

	UInt32 objIdx = 0;
	if (!ExtractArgs(EXTRACT_ARGS, &objIdx))
		return true;

	// enter critical section

	TESForm* pForm = GetItemByIdx(thisObj, objIdx, NULL);
	if (pForm) {
		UInt32 id = pForm->refID;
		*((UInt32*)result) = id;
		if (IsConsoleMode()) {
			Console_Print("%d: %s (%s)", objIdx, GetFullName(pForm), GetObjectClassName(pForm));
		}
	}

	// leave critical section

	return true;
}

bool Cmd_IsQuestItem_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (!thisObj) return true;
			pForm = thisObj->baseForm;
		}
		
		*result = pForm->IsQuestItem();
	}
	return true;
}

bool Cmd_SetQuestItem_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = NULL;
	UInt32 nSetQuest = 0;
	if (ExtractArgs(EXTRACT_ARGS, &nSetQuest, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (!thisObj) return true;
			pForm = thisObj->baseForm;
		}

		pForm->SetQuestItem(nSetQuest == 1);
	}
	return true;
}
