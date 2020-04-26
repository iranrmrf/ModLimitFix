#pragma once

#include "CommandTable.h"
#include "ParamInfos.h"

DEFINE_CMD_ALT(GetBaseObject, gbo, returns the base object id of the reference, 1, 0, NULL);
DEFINE_CMD_ALT(GetParentCell, gpc, returns the parent cell of the reference, 1, 0, NULL);
DEFINE_CMD_ALT(GetParentWorldspace, gpw, returns the parent worldspace of the reference, 1, 0, NULL);
DEFINE_CMD_ALT(GetOpenKey, GetKey, returns the key associated with a lockable object, 1, 0, NULL);
DEFINE_CMD_ALT(SetOpenKey, SetKey, sets the key uesd to unlock the calling object, 1, 1, kParams_OneInventoryObject);
DEFINE_CMD_ALT(GetTeleportCell, , returns the cell to which the calling door reference teleports, 1, 0, NULL);
DEFINE_CMD_ALT(GetLinkedDoor, , returns the door to which the calling reference is linked, 1, 0, NULL);

static ParamInfo kParams_GetFirstRef[3] =
{
	{	"form type",			kParamType_Integer,	1	},
	{	"cell depth",			kParamType_Integer,	1	},
	{	"include taken refs",	kParamType_Integer,	1	},
};

DEFINE_COMMAND(GetFirstRef, returns the first reference of the specified type in the current cell, 0, 3, kParams_GetFirstRef);
DEFINE_COMMAND(GetNextRef, returns the next reference of a given type in the  current cell, 0, 0, NULL);
DEFINE_COMMAND(GetNumRefs, returns the number of references of a given type in the current cell, 0, 3, kParams_GetFirstRef);

static ParamInfo kParams_GetFirstRefInCell[4] =
{
	{	"cell",					kParamType_Cell,	0	},
	{	"form type",			kParamType_Integer,	1	},
	{	"cell depth",			kParamType_Integer,	1	},
	{	"include taken refs",	kParamType_Integer,	1	},
};

DEFINE_COMMAND(GetFirstRefInCell, returns the first reference of the specified type in the specified cell, 0, 4, kParams_GetFirstRefInCell);
DEFINE_COMMAND(GetNumRefsInCell, returns the number of references of a given type in the specified cell, 0, 4, kParams_GetFirstRefInCell);
DEFINE_COMMAND(GetRefCount, returns the count in a stacked reference, 1, 0, NULL);
DEFINE_COMMAND(SetRefCount, sets the count on a stacked reference, 1, 1, kParams_OneInt);

static ParamInfo kParams_OneActor[1] =
{
	{	"NPC",	kParamType_Actor,	0	},
};

DEFINE_CMD_ALT(IsOffLimits, IsIllegal, returns true if activating the calling reference would result in a crime for the actor, 1, 1, kParams_OneActor);
DEFINE_CMD_ALT(GetParentCellOwner, GetCellOwner, returns the owner of the cell of the calling reference, 1, 0, NULL);
DEFINE_COMMAND(GetOwner, returns the owner of the calling reference, 1, 0, NULL);
DEFINE_CMD_ALT(GetOwningFactionRequiredRank, GetOwningFactionRank, returns the required rank for ownership of the calling reference, 1, 0, NULL);
DEFINE_CMD_ALT(GetParentCellOwningFactionRequiredRank, CetCellFactionRank, returns the required rank for ownership of the cell of the calling reference, 1, 0, NULL);
DEFINE_COMMAND(IsPersistent, returns true if the calling reference is persistent, 1, 0, NULL);

static ParamInfo kParams_SetNPCBodyData[2] =
{
	{	"body data",	kParamType_InventoryObject,	0	},
	{	"base NPC",		kParamType_NPC,				1	},
};

static ParamInfo kParams_SetHairLength[2] =
{
	{	"hair length",	kParamType_Float,	0	},
	{	"base NPC",		kParamType_NPC,		1	},
};

DEFINE_COMMAND(SetEyes, set an NPCs eyes, false, 2, kParams_SetNPCBodyData);
DEFINE_COMMAND(GetEyes, get an NPCs eyes, false, 1, kParams_OneNPC);
DEFINE_COMMAND(SetHair, set an NPCs hair, false, 2, kParams_SetNPCBodyData);
DEFINE_COMMAND(GetHair, set an NPCs hair, false, 1, kParams_OneNPC);
DEFINE_COMMAND(SetHairLength, set an NPCs hair length, false, 2, kParams_SetHairLength);
DEFINE_COMMAND(GetHairLength, get an NPCs hair length, false, 1, kParams_OneNPC);
