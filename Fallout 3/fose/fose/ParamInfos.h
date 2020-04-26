#pragma once

#include "CommandTable.h"

static ParamInfo kParams_OneInt[1] =
{
	{	"int", kParamType_Integer, 0 }, 
};

static ParamInfo kParams_TwoInts[2] =
{
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_Integer, 0 },
};

static ParamInfo kParams_OneOptionalInt[1] =
{
	{	"int", kParamType_Integer, 1 }, 
};

static ParamInfo kParams_OneInt_OneOptionalInt[2] =
{
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_Integer, 1 },
};

static ParamInfo kParams_OneFloat[1] =
{
	{	"float", kParamType_Float,	0 },
};

static ParamInfo kParams_OneString[1] =
{
	{	"string",	kParamType_String,	0 },
};

static ParamInfo kParams_OneString_OneFloat[] =
{
	{	"string",	kParamType_String,	0 },
	{	"float",	kParamType_Float,	0 },
};

static ParamInfo kParams_TwoFloats[2] =
{
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
};

static ParamInfo kParams_OneSpellItem[1] =
{
	{	"spell", kParamType_SpellItem, 0 }, 
};

static ParamInfo kParams_OneMagicItem[1] =
{
	{	"spell", kParamType_MagicItem, 0 }, 
};

static ParamInfo kParams_OneMagicEffect[1] =
{
	{	"magic effect", kParamType_MagicEffect, 0 }, 
};

static ParamInfo kParams_OneInventoryObject[1] =
{
	{	"item", kParamType_InventoryObject, 0},
};

static ParamInfo kParams_OneOptionalInventoryObject[1] =
{
	{	"item", kParamType_InventoryObject, 1},
};

static ParamInfo kParams_OneInt_OneOptionalInventoryObject[2] =
{
	{	"path type",	kParamType_Integer,			0	},
	{	"item",			kParamType_InventoryObject,	1	},
};

static ParamInfo kParams_OneInventoryObject_OneInt[2] =
{
	{	"item",		kParamType_InventoryObject,	0	},
	{	"integer",	kParamType_Integer,			0	},
};

static ParamInfo kParams_OneFloat_OneOptionalInventoryObject[2] =
{
	{	"float",		kParamType_Float,			0	},
	{	"item",			kParamType_InventoryObject,	1	},
};

static ParamInfo kParams_OneMagicItem_OneOptionalInventoryObject[2] =
{
	{	"magic item",	kParamType_MagicItem,		0	},
	{	"item",			kParamType_InventoryObject,	1	},
};

static ParamInfo kParams_OneInventoryItem_OneOptionalInventoryObject[2] =
{
	{	"inv item",		kParamType_MagicItem,		0	},
	{	"target item",	kParamType_InventoryObject,	1	},
};

static ParamInfo kParams_OneFormList_OneOptionalInventoryObject[2] =
{
	{	"form list",	kParamType_FormList,		0	},
	{	"target item",	kParamType_InventoryObject,	1	},
};


static ParamInfo kParams_OneActorValue[1] =
{
	{	"actor value", kParamType_ActorValue, 0},
};

#define FORMAT_STRING_PARAMS 	\
	{"format string",	kParamType_String, 0}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1} 

static ParamInfo kParams_FormatString[21] =
{
	FORMAT_STRING_PARAMS
};

#define SIZEOF_FMT_STRING_PARAMS 21
#define NUM_PARAMS(paramInfoName) SIZEOF_ARRAY(paramInfoName, ParamInfo)

static ParamInfo kParams_OneActorRef[1] =
{
	{	"actor reference",	kParamType_Actor,	0	},
};

static ParamInfo kParams_OneOptionalActorRef[1] =
{
	{	"actor reference",	kParamType_Actor,	1	},
};

static ParamInfo kParams_Axis[1] = 
{
	{	"axis",	kParamType_Axis,	0	},
};

static ParamInfo kParams_FormList[1] =
{
	{	"form list", kParamType_FormList,	0		},
};

static ParamInfo kParams_OneString_OneOptionalInventoryObject[2] =
{
	{	"string",		kParamType_String,			0	},
	{	"item",			kParamType_InventoryObject,	1	},
};

static ParamInfo kParams_TwoStrings[2] =
{
	{	"string",	kParamType_String,	0	},
	{	"string",	kParamType_String,	0	},
};

static ParamInfo kParams_OneObject[1] =
{
	{	"target item",	kParamType_TESObject,	0	},
};

static ParamInfo kParams_OneOptionalObject[1] =
{
	{	"target item",	kParamType_TESObject,	1	},
};

static ParamInfo kParams_OneString_OneOptionalObject[2] =
{
	{	"string",		kParamType_String,			0	},
	{	"item",			kParamType_TESObject,	1	},
};

static ParamInfo kParams_OneObject_OneOptionalObject[2] =
{
	{	"target item",	kParamType_TESObject,		0	},
	{	"object",		kParamType_TESObject,		1	},
};

static ParamInfo kParams_OneInt_OneOptionalObject[2] =
{
	{	"int",	kParamType_Integer,			0	},
	{	"item",			kParamType_TESObject,	1	},
};

static ParamInfo kParams_SetEquippedFloat[2] =
{
	{	"val", kParamType_Float, 0 },
	{	"slot", kParamType_Integer, 0 },
};

static ParamInfo kParams_FormListInteger[2] =
{
	{	"form list", kParamType_FormList,	0		},
	{	"index",	 kParamType_Integer,	0		}
};

static ParamInfo kParams_OneQuest[1] =
{
	{	"quest", kParamType_Quest, 0 }, 
};

static ParamInfo kParams_OneNPC[1] =
{
	{	"NPC",	kParamType_NPC,	1	},
};
