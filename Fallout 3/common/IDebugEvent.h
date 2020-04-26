#pragma once

#include "common/IDebugStringBuffer.h"
#include "common/IDebugSource.h"

class Time;
class IDebugSource;

/**
 *	Information about a debug event
 *	
 *	Most of the members of this class are optional, only specify the fields you need.
 */
class IDebugEvent
{
	public:
						IDebugEvent();
						~IDebugEvent();
		
		void			Clear(void);
		
		void			SetText(char * in)				{ text = in; }
		char *			AllocateText(void);
		void			SetSource(IDebugSource * in)	{ source = in; }
		void			SetTime_Now(void)				{ time.SetToNow(); }
		
		char *			GetText(void)			{ return text; }
		IDebugSource *	GetSource(void)			{ return source; }
		bool			IsTimeSet(void)			{ return time.IsSet(); }
		Time &			GetTime(void)			{ return time; }
		char *			GetSourceFile(void)		{ return sourceFile; }
		UInt32			GetSourceLine(void)		{ return sourceLine; }
	
	private:
		char			* text;
		IDebugSource	* source;
		Time			time;
		char			* sourceFile;
		UInt32			sourceLine;
};
