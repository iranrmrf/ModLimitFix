#include "common/IDebugStream.h"
#include "common/IDebugManager.h"

IDebugStream::IDebugStream()
{
	IDebugManager::GetSingleton().RegisterStream(this);
}

/**
 *	Construct the class and attach an output
 */
IDebugStream::IDebugStream(IDebugOutput * inOutput)
{
	IDebugManager::GetSingleton().RegisterStream(this);
	AttachOutput(inOutput);
}

IDebugStream::~IDebugStream()
{
	
}

/**
 *	Attach an output to the stream
 */
void IDebugStream::AttachOutput(IDebugOutput * inOutput)
{
	outputList.push_front(inOutput);
}

/**
 *	Called after the class is registered with the debug manager
 */
void IDebugStream::Register(void)
{
	ASSERT_STR(flags.IsUnSet(kFlag_Attached), "IDebugStream::Register: already registered");
	
	flags.Set(kFlag_Attached);
}

/**
 *	Flush all attached streams if needed
 */
void IDebugStream::Flush(void)
{
	if(flags.IsSet(kFlag_Dirty))
	{
		for(std::list <IDebugOutput *>::iterator iter = outputList.begin(); iter != outputList.end(); iter++)
		{
			(*iter)->Flush();
		}
		
		flags.UnSet(kFlag_Dirty);
	}
}

/**
 *	Send a debug event to all attached streams
 */
void IDebugStream::OutputEvent(IDebugEvent * inEvent)
{
	for(std::list <IDebugOutput *>::iterator iter = outputList.begin(); iter != outputList.end(); iter++)
	{
		(*iter)->OutputEvent(inEvent);
	}
	
	Dirty();
}
