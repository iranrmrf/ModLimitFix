#pragma once

#include "CommandTable.h"
#include "ParamInfos.h"

DEFINE_COMMAND(IsScripted, returns 1 if the object or reference has a script attached to it., 0, 1, kParams_OneOptionalObject);
DEFINE_COMMAND(GetScript, returns the script of the reference or passed object., 0, 1, kParams_OneOptionalObject);
DEFINE_COMMAND(RemoveScript, removes the script of the reference or passed object., 0, 1, kParams_OneOptionalObject);
DEFINE_COMMAND(SetScript, sets the script of the reference or passed object., 0, 2, kParams_OneObject_OneOptionalObject);
DEFINE_COMMAND(IsFormValid, returns 1 if the reference or passed object is valid., 0, 1, kParams_OneOptionalObject);

static ParamInfo kParams_OneReference[1] =
{
	{	"reference",	kParamType_ObjectRef,	0	},
};

DEFINE_COMMAND(IsReference, returns 1 if the passed refVar is a reference., 0, 1, kParams_OneReference);
