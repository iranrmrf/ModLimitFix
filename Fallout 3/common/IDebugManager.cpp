#include "common/IDebugManager.h"

IDebugTextOutput	gDebugLog("debug.txt");

IDebugManager::IDebugManager()
{
	
}

/**
 *	The destructor; flushes all streams before exiting
 */
IDebugManager::~IDebugManager()
{
	FlushStreams();
}

/**
 *	Registers a stream with the debug manager
 */
void IDebugManager::RegisterStream(IDebugStream * inStream)
{
	if(inStream)
	{
		inStream->Register();
		streamList.push_front(inStream);
	}
}

/**
 *	Registers an event source with the debug manager
 */
void IDebugManager::RegisterSource(IDebugSource * inSource)
{
	if(inSource)
	{
		inSource->Register();
		sourceList.push_front(inSource);
	}
}

/**
 *	Registers an output with the debug manager
 */
void IDebugManager::RegisterOutput(IDebugOutput * inOutput)
{
	if(inOutput)
	{
		inOutput->Register();
		outputList.push_front(inOutput);
	}
}

/**
 *	Flushes all registered streams
 */
void IDebugManager::FlushStreams(void)
{
	for(std::list <IDebugStream *>::iterator iter = streamList.begin(); iter != streamList.end(); iter++)
	{
		(*iter)->Flush();
	}
}
