#include "common/IDebugOutput.h"
#include "common/IDebugManager.h"

IDebugOutput::IDebugOutput()
{
	IDebugManager::GetSingleton().RegisterOutput(this);
}

IDebugOutput::~IDebugOutput()
{
	
}

/**
 *	Called after the class is registered with the debug manager
 */
void IDebugOutput::Register(void)
{
	ASSERT_STR(flags.IsUnSet(kFlag_Attached), "IDebugOutput::Register: already registered");
	
	flags.Set(kFlag_Attached);
}

/**
 *	Flushes the output stream if needed
 */
void IDebugOutput::Flush(void)
{
	if(flags.IsSet(kFlag_Dirty))
	{
		DoFlush();
		
		flags.UnSet(kFlag_Dirty);
	}
}
