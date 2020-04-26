#pragma once

#include "CommandTable.h"
#include "ParamInfos.h"

DEFINE_CMD_ALT(Exp, , calculates the exponential of a value, 0, 1, kParams_OneFloat);
DEFINE_CMD_ALT(Log10, , calculates the base 10 log of a value, 0, 1, kParams_OneFloat);
DEFINE_CMD_ALT(Floor, flr, Returns the nearest whole number that is less than a float, 0, 1, kParams_OneFloat);
DEFINE_CMD_ALT(Ceil, , Returns the nearest whole number that is greater than a float, 0, 1, kParams_OneFloat);
DEFINE_CMD_ALT(LeftShift, , Shifts a 32-bit integer left the specified number of bits, 0, 2, kParams_TwoInts);
DEFINE_CMD_ALT(RightShift, , Shifts a 32-bit integer right the specified number of bits, 0, 2, kParams_TwoInts);
DEFINE_CMD_ALT(LogicalAnd, , Performs a logical AND between two 32-bit integers., 0, 2, kParams_TwoInts);
DEFINE_CMD_ALT(LogicalOr, , Performs a logical OR between two 32-bit integers., 0, 2, kParams_TwoInts);
DEFINE_CMD_ALT(LogicalXor, , Performs a logical XOR between two 32-bit integers., 0, 2, kParams_TwoInts);
DEFINE_CMD_ALT(LogicalNot, , Performs a logical NOT on a 32-bit integer., 0, 1, kParams_OneInt);
DEFINE_CMD_ALT(Pow, , Calculates one value raised to the power of another, 0, 2, kParams_TwoFloats);

static ParamInfo kParams_Fmod[3] =
{
	{	"x",	kParamType_Float,	0 },
	{	"n",	kParamType_Float,	0 },
	{	"offset",	kParamType_Float,	1 },
};
DEFINE_CMD_ALT(fmod, , returns the result of a floating point modulous of the passed floats, 0, 3, kParams_Fmod);

DEFINE_CMD_ALT(Rand, r, Returns a float between min and max, 0, 2, kParams_TwoFloats);
