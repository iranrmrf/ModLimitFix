#pragma once

#include "common/IDebugStream.h"
#include <list>

class IDebugStream;

/**
 *	A source of debug events
 *	
 *	This class is used to get information about debugging sources
 */
class IDebugSource
{
	public:
						IDebugSource();
						~IDebugSource();
		
		virtual void	Register(void);
		
		//! Returns the name of the debugging source
		virtual char *	GetName(void) = 0;
		//! Returns a unique ID number for the source
		virtual UInt32	GetID(void) = 0;
	
	private:
		enum
		{
			kFlag_Attached =	1 << 0	//!< attached to the debug manager
		};
		
		Bitfield32	flags;
};
