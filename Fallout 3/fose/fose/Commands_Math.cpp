#include "Commands_Math.h"

#include "GameAPI.h"

bool Cmd_Exp_Execute(COMMAND_ARGS)
{
	*result = 0;

	float arg = 0;
	if(!ExtractArgs(EXTRACT_ARGS, &arg))
		return true;

	*result = exp(arg);

	return true;
}

bool Cmd_Log10_Execute(COMMAND_ARGS)
{
	*result = 0;

	float arg = 0;
	if(!ExtractArgs(EXTRACT_ARGS, &arg))
		return true;

	*result = log10(arg);

	return true;
}

bool Cmd_Floor_Execute(COMMAND_ARGS)
{
	*result = 0;

	float arg = 0;
	if(!ExtractArgs(EXTRACT_ARGS, &arg))
		return true;

	*result = floor(arg);

	return true;
}
bool Cmd_Ceil_Execute(COMMAND_ARGS)
{
	*result = 0;

	float arg = 0;
	if(!ExtractArgs(EXTRACT_ARGS, &arg))
		return true;

	*result = ceil(arg);

	return true;
}

bool Cmd_LeftShift_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32	lhs = 0;
	UInt32	rhs = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &lhs, &rhs))
		return true;

	if(rhs >= 32)
		*result = 0;
	else
		*result = lhs << rhs;

	return true;
}

bool Cmd_RightShift_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32	lhs = 0;
	UInt32	rhs = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &lhs, &rhs))
		return true;

	if(rhs >= 32)
		*result = 0;
	else
		*result = lhs >> rhs;

	return true;
}

bool Cmd_LogicalAnd_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32	lhs = 0;
	UInt32	rhs = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &lhs, &rhs))
		return true;

	*result = lhs & rhs;

	return true;
}

bool Cmd_LogicalOr_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32	lhs = 0;
	UInt32	rhs = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &lhs, &rhs))
		return true;

	*result = lhs | rhs;

	return true;
}

bool Cmd_LogicalXor_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32	lhs = 0;
	UInt32	rhs = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &lhs, &rhs))
		return true;

	*result = lhs ^ rhs;

	return true;
}

#pragma warning (push)
#pragma warning (disable : 4319)

bool Cmd_LogicalNot_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32	lhs = 0;

	if(!ExtractArgs(EXTRACT_ARGS, eventList, &lhs))
		return true;

	*result = (double)(~lhs);

	return true;
}

#pragma warning (pop)

bool Cmd_fmod_Execute(COMMAND_ARGS)
{
	*result = 0;
	float x = 0.0;
	float n = 0.0;
	float offset = 0.0;

	ExtractArgs(EXTRACT_ARGS, &x, &n, &offset);

	float answer = x - n * floor(x/n);
	if (offset != 0) {
		float bump = n * floor(offset/n);
		float bound = offset - bump;
		answer += bump;
		bool bBigger = (n > 0);
		if ( (bBigger && answer < bound) || (!bBigger && answer > bound) ) {
			answer += n;
		}
	}
	*result = answer;

	return true;
}

bool Cmd_Rand_Execute(COMMAND_ARGS)
{
	*result = 0;

	float rangeMin = 0;
	float rangeMax = 0;
	if(!ExtractArgs(EXTRACT_ARGS, &rangeMin, &rangeMax)) return true;

	if(rangeMax < rangeMin)
	{
		float	temp = rangeMin;
		rangeMin = rangeMax;
		rangeMax = temp;
	}

	float	range = rangeMax - rangeMin;

	double	value = MersenneTwister::genrand_real2() * range;
	value += rangeMin;

	*result = value;

	return true;
}

bool Cmd_Pow_Execute(COMMAND_ARGS)
{
	*result = 0;

	float f1 = 0;
	float f2 = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &f1, &f2)) return true;

	*result = pow(f1,f2);

	return true;
}
