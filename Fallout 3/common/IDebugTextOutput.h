#pragma once

#include "common/IDebugOutput.h"
#include <cstdio>

/**
 *	A debug output object supporting output to a text file
 */
class IDebugTextOutput : public IDebugOutput
{
	public:
					IDebugTextOutput();
					IDebugTextOutput(char * fileName);
					~IDebugTextOutput();
		
		void		Register(void);
		
		void		Flush(void);
		void		OutputEvent(IDebugEvent * inEvent);
		
		void		Open(char * buf);
		void		Close(void);
	
	private:
		std::FILE	* theFile;
};
