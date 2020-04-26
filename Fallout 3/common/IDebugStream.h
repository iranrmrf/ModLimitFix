#pragma once

#include "common/IDebugOutput.h"
#include "common/IDebugEvent.h"
#include <list>

class IDebugOutput;
class IDebugEvent;

/**
 *	A debug event stream
 *	
 *	This class relays debug events to output objects.
 */
class IDebugStream
{
	public:
				IDebugStream();
				IDebugStream(IDebugOutput * inOutput);
				~IDebugStream();
		
		void	AttachOutput(IDebugOutput * inOutput);
		
		void	Register(void);
		
		void	Flush(void);
		void	OutputEvent(IDebugEvent * inEvent);
		
		//! Mark the stream as possibly dirty
		void	Dirty(void)	{ flags.Set(kFlag_Dirty); }
	
	private:
		enum
		{
			kFlag_Dirty =		1 << 0,	//!< the stream is possibly out-of-sync
			kFlag_Attached =	1 << 1	//!< attached to the debug manager
		};
		
		Bitfield32					flags;
		
		std::list <IDebugOutput *>	outputList;	//!< the output objects attached
};
