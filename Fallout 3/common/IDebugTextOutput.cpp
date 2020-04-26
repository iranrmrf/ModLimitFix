#include "common/IDebugTextOutput.h"
#include "common/ITypes.h"
#include "common/IErrors.h"
#include <share.h>

IDebugTextOutput::IDebugTextOutput()
{
	
}

/**
 *	Construct the object and open an output file
 */
IDebugTextOutput::IDebugTextOutput(char * fileName)
{
	Open(fileName);
}

/**
 *	The destructor; automatically closes the log file
 */
IDebugTextOutput::~IDebugTextOutput()
{
	Close();
}

/**
 *	Called after the class is registered with the debug manager
 */
void IDebugTextOutput::Register(void)
{
	IDebugOutput::Register();
}

/**
 *	Called to synchronize the state of the file on disk with the local state
 */
void IDebugTextOutput::Flush(void)
{
	if(theFile)
	{
		std::fflush(theFile);
	}
}

/**
 *	Output a debugging event to the file
 */
void IDebugTextOutput::OutputEvent(IDebugEvent * inEvent)
{
	if(inEvent && theFile)
	{
		bool	printDivider = false;
		
		if(inEvent->GetSource())
		{
			fprintf(theFile, "[%08s]", inEvent->GetSource()->GetName());
			printDivider = true;
		}
		
		if(inEvent->IsTimeSet())
		{
			fprintf(theFile, "[%02d:%02d:%02d]",
					inEvent->GetTime().GetHours(),
					inEvent->GetTime().GetMinutes(),
					inEvent->GetTime().GetSeconds());
			printDivider = true;
		}
		
		if(inEvent->GetText())
		{
			if(printDivider)
				fprintf(theFile, " ");
			
			fprintf(theFile, "%s", inEvent->GetText());
		}
		
		if(inEvent->GetSourceFile())
		{
			fprintf(theFile, "\n\t%s (%d)", inEvent->GetSourceFile(), inEvent->GetSourceLine());
		}
		
		fprintf(theFile, "\n");
	}
}

/**
 *	Open a log file
 */
void IDebugTextOutput::Open(char * buf)
{
	ASSERT_STR(!theFile, "IDebugTextOutput::Open: already open");
	
	theFile = _fsopen(buf, "w", _SH_DENYWR);
	
	ASSERT_STR(theFile, "IDebugTextOutput::Open: couldn't create file");
}

/**
 *	Close the log file
 */
void IDebugTextOutput::Close(void)
{
	if(theFile)
	{
		std::fclose(theFile);
		theFile = NULL;
	}
}
