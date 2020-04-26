#pragma once

#include "CommandTable.h"
#include "ParamInfos.h"

static ParamInfo kParams_SetUIStringEx[] =
{
	{	"component name",	kParamType_String,	0 },
	FORMAT_STRING_PARAMS,
};

DEFINE_COMMAND(GetUIFloat, returns the value of a float UI trait, 0, 1, kParams_OneString);
DEFINE_COMMAND(SetUIFloat, sets the value of a float UI trait, 0, 2, kParams_OneString_OneFloat);
DEFINE_COMMAND(SetUIString, sets the value of a string UI trait, 0, 2, kParams_TwoStrings);
DEFINE_COMMAND(SetUIStringEx, sets the value of a string UI trait to a formatted string, 0, 22, kParams_SetUIStringEx);
DEFINE_COMMAND(PrintActiveTile, prints name of highlighted UI component for debug purposes, 0, 0, NULL);
