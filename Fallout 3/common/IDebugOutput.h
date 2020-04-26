#pragma once

#include "common/IDebugEvent.h"

class IDebugEvent;

/**
 *	Base class for objects that can output debugging events
 */
class IDebugOutput
{
	public:
						IDebugOutput();
						~IDebugOutput();
		
		virtual void	Register(void);
		
		void			Flush(void);
		//! Outputs a debug event to the stream
		virtual void	OutputEvent(IDebugEvent * event) = 0;
		
		//! Marks the output stream as dirty
		void			Dirty(void)	{ flags.Set(kFlag_Dirty); }
		
	protected:
		//! Flushes the output stream
		virtual void	DoFlush(void) { }
		
		enum
		{
			kFlag_Dirty =		1 << 0,	//!< the stream may be out-of-date
			kFlag_Attached =	1 << 1	//!< attached to the debug manager
		};
		
		Bitfield32	flags;
};
