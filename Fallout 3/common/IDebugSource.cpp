#include "common/IDebugSource.h"
#include "common/IDebugManager.h"

IDebugSource::IDebugSource()
{
	IDebugManager::GetSingleton().RegisterSource(this);
}

IDebugSource::~IDebugSource()
{
	
}

/**
 *	Called after the class is registered with the debug manager
 */
void IDebugSource::Register(void)
{
	ASSERT_STR(flags.IsUnSet(kFlag_Attached), "IDebugSousrce::Register: already registered");
	
	flags.Set(kFlag_Attached);
}
