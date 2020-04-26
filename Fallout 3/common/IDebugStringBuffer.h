#pragma once

#include "common/IObjectPool.h"
#include "common/ISingleton.h"

/**
 *	A pool of strings for temporary use
 */
class IDebugStringBuffer : public IObjectPool<char[1024], 32>, public ISingleton<IDebugStringBuffer>
{
	public:
		IDebugStringBuffer()	{ }
		~IDebugStringBuffer()	{ }
};

