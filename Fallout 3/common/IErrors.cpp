#include "common/IErrors.h"
#include "common/IDebugLog.h"
#include <cstdlib>

/**
 *	Report a failed assertion and exit the program
 *	
 *	@param file the file where the error occured
 *	@param line the line number where the error occured
 *	@param desc an error message
 */
void _AssertionFailed(const char * file, UInt32 line, const char * desc)
{
	_FATALERROR("Assertion failed in %s (%d): %s", file, line, desc);
	exit(1);
}

/**
 *	Report a failed assertion and exit the program
 *	
 *	@param file the file where the error occured
 *	@param line the line number where the error occured
 *	@param desc an error message
 *	@param code the error code
 */
void _AssertionFailed_ErrCode(const char * file, UInt32 line, const char * desc, UInt64 code)
{
	if(code & 0xFFFFFFFF00000000)
		_FATALERROR("Assertion failed in %s (%d): %s (code = %16I64X (%I64d))", file, line, desc, code, code);
	else
	{
		UInt32	code32 = code;
		_FATALERROR("Assertion failed in %s (%d): %s (code = %08X (%d))", file, line, desc, code32, code32);
	}
	
	exit(1);
}

/**
 *	Report a failed assertion and exit the program
 *	
 *	@param file the file where the error occured
 *	@param line the line number where the error occured
 *	@param desc an error message
 *	@param code the error code
 */
void _AssertionFailed_ErrCode(const char * file, UInt32 line, const char * desc, const char * code)
{
	_FATALERROR("Assertion failed in %s (%d): %s (code = %s)", file, line, desc, code);
	exit(1);
}
