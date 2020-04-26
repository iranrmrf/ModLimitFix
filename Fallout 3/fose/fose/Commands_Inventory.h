#pragma once

#include "CommandTable.h"
#include "ParamInfos.h"

// for use with Inventory Objects
#define DEFINE_GET_INV(name, alt, desc) DEFINE_CMD_ALT(name, alt, desc, 0, 1, kParams_OneOptionalInventoryObject);
#define DEFINE_SET_INV_INT(name, alt, desc) DEFINE_CMD_ALT(name, alt, desc, 0, 2, kParams_OneInt_OneOptionalInventoryObject);
#define DEFINE_SET_INV_FLOAT(name, alt, desc) DEFINE_CMD_ALT(name, alt, desc, 0, 2, kParams_OneFloat_OneOptionalInventoryObject);
#define DEFINE_SET_INV_MAGIC(name, alt, desc) DEFINE_CMD_ALT(name, alt, desc, 0, 2, kParams_OneMagicItem_OneOptionalInventoryObject);
// for use with generic objects (anything with 3D) and general Base Forms that could be other types.  Is more inclusive.
#define DEFINE_GET_OBJ(name, alt, desc) DEFINE_CMD_ALT(name, alt, desc, 0, 1, kParams_OneOptionalObject);

#define DEFINE_SET_CUR_FLOAT(name, alt, desc) DEFINE_CMD_ALT(name, alt, desc, 1, 2, kParams_SetEquippedFloat);

DEFINE_CMD_COND(GetWeight, returns the weight of the sepcified base form, 0, kParams_OneOptionalInventoryObject);
// DEFINE_GET_INV(GetWeight,  , "returns the weight of the specified base form");
DEFINE_GET_OBJ(GetType, GetObjectType, returns the type of the specified base form);
DEFINE_GET_INV(GetRepairList, grl, returns the repair list for the inventory object);
DEFINE_GET_INV(GetWeaponAmmo, GetAmmo, returns the ammo of a weapon);
DEFINE_GET_INV(GetWeaponClipRounds, GetClipSize, returns the clip size for the weapon);
DEFINE_GET_INV(GetAttackDamage, GetDamage, returns the attack damage for the weapon);
DEFINE_GET_INV(GetWeaponType, GetWeapType, returns the weapon type);
DEFINE_GET_INV(GetWeaponMinSpread, GetMinSpread, returns the minimum spread of the weapon);
DEFINE_GET_INV(GetWeaponSpread, GetSpread, returns the spread of the weapon);
DEFINE_GET_INV(GetWeaponProjectile, GetWeapProj, returns the weapon projectile info);
DEFINE_GET_INV(GetWeaponSightFOV, GetSightFOV, returns the zoom field of view for the weapon);
DEFINE_GET_INV(GetWeaponMinRange, GetMinRange, returns the min range of the weapon);
DEFINE_GET_INV(GetWeaponMaxRange, GetMaxRange, returns the max range of the weapon);
DEFINE_GET_INV(GetWeaponAmmoUse, GetAmmoUse, returns the ammo used per shot of the weapon);
DEFINE_GET_INV(GetWeaponActionPoints, GetAP, returns the number of action points per shot of the weapon);
DEFINE_GET_INV(GetWeaponCritDamage, GetCritDam, returns the critical damage of the weapon);
DEFINE_GET_INV(GetWeaponCritChance, GetCritPerc, returns the chance of a critical shot for the weapon);
DEFINE_GET_INV(GetWeaponCritEffect, GetCritEffect, returns the spell for the critical effect for the weapon);
DEFINE_GET_INV(GetEquipType,  , returns the equipment type of the inventory object);
DEFINE_GET_OBJ(GetHealth, GetBaseHealth, returns the base health of the object or calling reference);
DEFINE_GET_INV(GetValue, GetItemValue, returns the base value of the object or calling reference);
DEFINE_GET_INV(GetWeaponFireRate, GetFireRate, returns the fire rate of the weapon.);
DEFINE_GET_INV(GetWeaponAnimAttackMult, GetAnimAttackMult, returns the animation attack multiplier of the weapon.);
DEFINE_GET_INV(GetWeaponRumbleLeftMotor, GetRumbleLeft, returns the rumble left motor of the weapon.);
DEFINE_GET_INV(GetWeaponRumbleRightMotor, GetRumbleRight, returns the rumble right motor of the weapon.);
DEFINE_GET_INV(GetWeaponRumbleDuration, GetRumbleDuration, returns the rumble duration of the weapon.);
DEFINE_GET_INV(GetWeaponRumbleWavelength, GetRumbleWavelen, returns the rumble wavelegnth for the weapon.);
DEFINE_GET_INV(GetWeaponAnimShotsPerSec, GetAnimShotsPerSec, returns the animation shots per second of the weapon.);
DEFINE_GET_INV(GetWeaponAnimReloadTime, GetAnimReloadTime, retuns the animation reload time for the weapon.);
DEFINE_GET_INV(GetWeaponAnimJamTime, GetAnimJamTime, returns the animation jam time of the weapon.);
DEFINE_GET_INV(GetWeaponSkill,  , returns the skill for the weapon.);
DEFINE_GET_INV(GetWeaponResistType, GetWeaponResist, returns the resist type for the weapon.);
DEFINE_GET_INV(GetWeaponFireDelayMin, GetFireDelayMin, returns the semi-auto min fire delay for the weapon.);
DEFINE_GET_INV(GetWeaponFireDelayMax, GetFireDelayMax, returns the semi-auto max fire delay for the weapon.);
DEFINE_SET_INV_INT(SetWeaponClipRounds, SetClipSize, sets the weapon clip size);
DEFINE_SET_INV_FLOAT(SetWeaponMinSpread, SetMinSpread, sets the weapon min spread);
DEFINE_SET_INV_FLOAT(SetWeaponSpread, SetSpread, sets the weapon spread);
DEFINE_SET_INV_FLOAT(SetWeaponSightFOV, SetSightFOV, sets the weapon xoom field of view);
DEFINE_SET_INV_FLOAT(SetWeaponMinRange, SetMinRange, sets the weapon min range);
DEFINE_SET_INV_FLOAT(SetWeaponMaxRange, SetMaxRange, sets the weapon max range.);
DEFINE_SET_INV_INT(SetWeaponAmmoUse, SetAmmoUse, sets the weapon ammo use);
DEFINE_SET_INV_FLOAT(SetWeaponActionPoints, SetAP, sets the weapon number of action pointer per shot);
DEFINE_SET_INV_INT(SetWeaponCritDamage, SetWeaponCritDamage, sets the weapon critical hit damage.);
DEFINE_SET_INV_FLOAT(SetWeaponCritChance, SetCritPerc, sets the weapon critical hit chance);
DEFINE_SET_INV_MAGIC(SetWeaponCritEffect, SetCritEffect, sets the weapon critical hit effect);
DEFINE_SET_INV_FLOAT(SetWeight, , sets the weight of the object); 
DEFINE_CMD_ALT(SetWeaponAmmo, SetAmmo, sets the ammo of the weapon, 0, 2, kParams_OneInventoryItem_OneOptionalInventoryObject);
DEFINE_CMD_ALT(SetWeaponProjectile, SetProjectile, sets the projectile of the weapon, 0, 2, kParams_OneInventoryItem_OneOptionalInventoryObject);
DEFINE_CMD_ALT(SetRepairList,  , sets the repair list for the specified item., 0, 2, kParams_OneFormList_OneOptionalInventoryObject);
DEFINE_CMD_ALT(CompareNames,  , compares one name to another, 0, 2, kParams_OneObject_OneOptionalObject);
DEFINE_CMD_ALT(GetEquippedObject, GetEqObj, returns the base object of the item in the specified slot, 1, 1, kParams_OneInt);
DEFINE_CMD_ALT(GetEquippedCurrentHealth, GetEqCurHealth, returns the current health of the object equipped in the specified slot, 1, 1, kParams_OneInt);

DEFINE_GET_INV(GetWeaponAnimMult, GetAnimMult, returns the animation multiplier for the weapon);
DEFINE_GET_INV(GetWeaponReach, GetReach,returns the reach of the weapon);
DEFINE_GET_INV(GetWeaponIsAutomatic, GetIsAutomatic, returns 1 if the weapon is an automatic weapon);
DEFINE_GET_INV(GetWeaponHandGrip, GetHandGrip, returns the hand grip of the weapon);
DEFINE_GET_INV(GetWeaponReloadAnim, GetReloadAnim, returns the reload animation of the weapon);
DEFINE_GET_INV(GetWeaponBaseVATSChance, GetVATSChance, returns the base VATS chance of the weapon);
DEFINE_GET_INV(GetWeaponAttackAnimation, GetAttackAnim, returns the attack animation of the weapon);
DEFINE_GET_INV(GetWeaponNumProjectiles, GetNumProj, returns the number of projectiles used in a single shot by the weapon.);
DEFINE_GET_INV(GetWeaponAimArc, GetAimArc, returns the aim arc of the weapon.);
DEFINE_GET_INV(GetWeaponLimbDamageMult, GetLimbDamageMult, returns the limb damage multiplier of the weapon.);
DEFINE_GET_INV(GetWeaponSightUsage, GetSightUsage, returns the sight usage of the weapon.);
DEFINE_GET_OBJ(TempCloneForm, , clones the specified form and returns a new base form which will not be saved in the save game.);
DEFINE_GET_OBJ(IsClonedForm, IsCloned, returns whether the specified form is a created object or not.);
DEFINE_GET_INV(GetObjectEffect, GetEnchantment, returns the object effect of the inventory object.);
DEFINE_CMD_COND(GetWeaponHasScope, returns whether the weapon has a scope or not., 0, kParams_OneOptionalInventoryObject);
DEFINE_GET_INV(GetArmorAR, GetArmorArmorRating, returns the armor rating of the specified armor.);
DEFINE_GET_INV(IsPowerArmor, IsPA, returns whether the biped form is considered power armor.);

DEFINE_SET_INV_INT(SetAttackDamage, SetDamage, sets the attack damage of the form);
DEFINE_SET_INV_FLOAT(SetWeaponAnimMult, SetAnimMult, sets the animiation multiple of the weapon.);
DEFINE_SET_INV_FLOAT(SetWeaponReach, SetReach, sets the reach of the weapon.);
DEFINE_SET_INV_INT(SetWeaponIsAutomatic, SetIsAutomatic, sets whether the weapon is an automatic weapon or not.);
DEFINE_SET_INV_INT(SetWeaponHandGrip, SetHandGrip, sets the hand grip of the weapon.);
DEFINE_SET_INV_INT(SetWeaponReloadAnim, SetReloadAnim, sets the reload animation of the weapon.);
DEFINE_SET_INV_INT(SetWeaponBaseVATSChance, SetVATSChance, sets the base VATS chance for the weapon.);
DEFINE_SET_INV_INT(SetWeaponAttackAnimation, SetAttackAnim, sets the attack animation for the weapon.);
DEFINE_SET_INV_INT(SetWeaponNumProjectiles, SetNumProj, sets the number of projectiles the weapon fires each time it is shot.);
DEFINE_SET_INV_FLOAT(SetWeaponAimArc, SetAimArc, sets the aim arc of the weapon.);
DEFINE_SET_INV_FLOAT(SetWeaponLimbDamageMult, SetLimbDamageMult, sets the limb damage multiplier for the weapon.);
DEFINE_SET_INV_FLOAT(SetWeaponSightUsage, SetSightUsage, sets the sight usage for the weapon.);
DEFINE_CMD_ALT(SetName,  , sets the name of the object., 0, 2, kParams_OneString_OneOptionalObject);
DEFINE_SET_CUR_FLOAT(SetEquippedCurrentHealth, SetEqCurHealth, sets the current health of the equipped object at the given slot.);
DEFINE_SET_INV_INT(SetIsPowerArmor, SetIsPA, sets whether the armor is power armor or not.);
DEFINE_SET_INV_INT(SetWeaponType, , sets the weapon type of the weapon.);
DEFINE_SET_INV_FLOAT(SetWeaponAnimAttackMult, SetAnimAttackMult, sets the anim attack multiplier.);

DEFINE_COMMAND(GetHotkeyItem, returns the item assigned to the specified hotkey from 1 to 8, 0, 1, kParams_OneInt);
DEFINE_CMD_ALT(SetBaseItemValue, SetValue, sets the monetary value of a base object, 0, 2, kParams_OneInventoryObject_OneInt);
DEFINE_CMD_ALT(SetHealth, SetObjectHealth, sets the base health of the specified base form, 0, 2, kParams_OneInt_OneOptionalObject);

DEFINE_GET_OBJ(CloneForm, , clones the specified form and returns a new base form which will be saved in the save game.);

DEFINE_COMMAND(GetCurrentHealth, returns the current health of the calling ref, 1, 0, NULL);
DEFINE_COMMAND(SetCurrentHealth, sets the current health of the calling ref, 1, 1, kParams_OneFloat);
DEFINE_CMD_ALT(GetNumItems, GetNumObjects, returns the number of items contained by the calling ref, 1, 0, NULL);
DEFINE_CMD_ALT(GetInventoryObject, GetNthObject, returns the base object of the specified index contained in the calling ref, 1, 1, kParams_OneInt);
DEFINE_GET_INV(IsQuestItem, , returns 1 if the object or calling reference is a quest item);
DEFINE_SET_INV_INT(SetQuestItem, , Sets whether the specified object or object reference is a quest item);