#pragma once

#include "CommandTable.h"
#include "ParamInfos.h"

DEFINE_COMMAND(ModelPathIncludes, 
			   returns 1 if the specified substring exists within the objects model path, 
			   0, 2, kParams_OneString_OneOptionalInventoryObject);
