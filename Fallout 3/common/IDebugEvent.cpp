#include "IDebugEvent.h"
#include "IDebugStringBuffer.h"

IDebugEvent::IDebugEvent()
{
	Clear();
}

IDebugEvent::~IDebugEvent()
{
	
}

//! Clears the fields of the event
void IDebugEvent::Clear(void)
{
	text = NULL;
	source = NULL;
	time.Clear();
	sourceFile = NULL;
	sourceLine = 0;
}

/**
 *	Returns a buffer to be used as the event's main text field
 *	
 *	@todo return the size of the buffer
 */
char * IDebugEvent::AllocateText(void)
{
	char	* buf = IDebugStringBuffer::GetSingleton().Alloc();
	
	SetText(buf);
	
	return buf;
}
