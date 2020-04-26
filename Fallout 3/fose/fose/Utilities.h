#pragma once

void DumpClass(void * theClassPtr, UInt32 nIntsToDump = 512);
const char * GetObjectClassName(void * obj);
const std::string & GetFalloutDirectory(void);
std::string GetFOSEConfigOption(const char * section, const char * key);
bool GetFOSEConfigOption_UInt32(const char * section, const char * key, UInt32 * dataOut);

// this has been tested to work for non-varargs functions
// varargs functions end up with 'this' passed as the last parameter (ie. probably broken)
// do NOT use with classes that have multiple inheritance

// if many member functions are to be declared, use MEMBER_FN_PREFIX to create a type with a known name
// so it doesn't need to be restated throughout the member list

// all of the weirdness with the _GetType function is because you can't declare a static const pointer
// inside the class definition. inlining automatically makes the function call go away since it's a const

#define MEMBER_FN_PREFIX(className)	\
	typedef className _MEMBER_FN_BASE_TYPE

#define DEFINE_MEMBER_FN_LONG(className, functionName, retnType, address, ...)		\
	typedef retnType (className::* _##functionName##_type)(__VA_ARGS__);			\
																					\
	inline _##functionName##_type * _##functionName##_GetPtr(void)					\
	{																				\
		static const UInt32 _address = address;										\
		return (_##functionName##_type *)&_address;									\
	}

#define DEFINE_MEMBER_FN(functionName, retnType, address, ...)	\
	DEFINE_MEMBER_FN_LONG(_MEMBER_FN_BASE_TYPE, functionName, retnType, address, __VA_ARGS__)

#define CALL_MEMBER_FN(obj, fn)	\
	((*(obj)).*(*((obj)->_##fn##_GetPtr())))

// Macro for debug output to console at runtime
#if RUNTIME
#ifdef _DEBUG
#define DEBUG_PRINT(x, ...) { Console_Print((x), __VA_ARGS__); }
#define DEBUG_MESSAGE(x, ...) { _MESSAGE((x), __VA_ARGS__); }
#else
#define DEBUG_PRINT(x, ...) { }
#define DEBUG_MESSAGE(x, ...) { }
#endif	//_DEBUG
#else
#define DEBUG_PRINT(x, ...) { }
#define DEBUG_MESSAGE(x, ...) { }
#endif	// RUNTIME

class TESForm;

class FormMatcher
{
public:
	virtual bool Matches(TESForm* pForm) const = 0;
};

// alternative to strtok; doesn't modify src string, supports forward/backward iteration
class Tokenizer
{
public:
	Tokenizer(const char* src, const char* delims);
	~Tokenizer();

	// these return the offset of token in src, or -1 if no token
	UInt32 NextToken(std::string& outStr);
	UInt32 PrevToken(std::string& outStr);

private:
	std::string m_delims;
	size_t		m_offset;
	std::string m_data;
};

void CreateTempHook(UInt32 hookAddr, UInt32 jmpAddr);
bool DeleteTempHook(UInt32 hookAddr);

namespace MersenneTwister
{

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s);

/* initialize by an array with array-length */
void init_by_array(unsigned long init_key[], int key_length);

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void);

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void);

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void);

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void);

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void);

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void);

};
