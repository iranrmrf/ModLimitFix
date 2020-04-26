#include <direct.h>
#include "common/IFileStream.h"
#include "Options.h"
#include <string>

// requires recent platform sdk
#ifndef ERROR_ELEVATION_REQUIRED
#define ERROR_ELEVATION_REQUIRED 740
#endif

IDebugLog	gLog("fose_loader.log");

struct ProcHookInfo
{
	UInt32	hookCallAddr;
	UInt32	loadLibAddr;
};

static bool InjectDLL(PROCESS_INFORMATION * info, const char * dllPath, ProcHookInfo * hookInfo);
static bool DoInjectDLL(PROCESS_INFORMATION * info, const char * dllPath, ProcHookInfo * hookInfo);
static bool TestChecksum(const char * procName, std::string * dllSuffix, ProcHookInfo * hookInfo);
static void PrintError(const char * fmt, ...);

int main(int argc, char ** argv)
{
	gLog.SetPrintLevel(IDebugLog::kLevel_FatalError);
	gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

	if(!g_options.Read(argc, argv))
	{
		PrintError("Couldn't read arguments.");
		g_options.PrintUsage();

		return -1;
	}

	if(g_options.m_optionsOnly)
	{
		g_options.PrintUsage();
		return 0;
	}

	if(g_options.m_verbose)
		gLog.SetPrintLevel(IDebugLog::kLevel_VerboseMessage);

	if(g_options.m_launchCS)
		_MESSAGE("launching editor");

	// create the process
	STARTUPINFO			startupInfo = { 0 };
	PROCESS_INFORMATION	procInfo = { 0 };
	bool				dllHasFullPath = false;

	startupInfo.cb = sizeof(startupInfo);

	const char	* procName = g_options.m_launchCS ? "GECK.exe" : "Fallout3.exe";
	const char	* baseDllName = g_options.m_launchCS ? "fose_editor" : "fose";

	char	currentWorkingDirectory[4096];
	ASSERT(_getcwd(currentWorkingDirectory, sizeof(currentWorkingDirectory)));

	std::string procPath = std::string(currentWorkingDirectory) + "\\" + std::string(procName);

	if(g_options.m_altEXE.size())
	{
		procPath = g_options.m_altEXE;
		_MESSAGE("launching alternate exe (%s)", procPath.c_str());
	}
	else if(!g_options.m_launchCS)
	{
		IFileStream	fileCheck;
		if(!fileCheck.Open(procPath.c_str()))
		{
			_MESSAGE("couldn't find %s, trying fallout3ng.exe", procName);

			procName = "fallout3ng.exe";
			procPath = std::string(currentWorkingDirectory) + "\\" + std::string(procName);
		}
	}

	_MESSAGE("launching: %s (%s)", procName, procPath.c_str());

	if(g_options.m_altDLL.size())
	{
		baseDllName = g_options.m_altDLL.c_str();
		_MESSAGE("launching alternate dll (%s)", baseDllName);

		dllHasFullPath = true;
	}

	std::string		dllSuffix;
	ProcHookInfo	procHookInfo;

	if(!TestChecksum(procPath.c_str(), &dllSuffix, &procHookInfo))
	{
		_ERROR("checksum not found");
		return -1;
	}

	_MESSAGE("hook call addr = %08X", procHookInfo.hookCallAddr);
	_MESSAGE("load lib addr = %08X", procHookInfo.loadLibAddr);

	if(g_options.m_crcOnly)
		return 0;

	// build dll path
	std::string	dllPath;
	if(dllHasFullPath)
	{
		dllPath = baseDllName;
	}
	else
	{
		dllPath = std::string(currentWorkingDirectory) + "\\" + baseDllName + "_" + dllSuffix + ".dll";
	}

	_MESSAGE("dll = %s", dllPath.c_str());

	// check to make sure the dll exists
	{
		IFileStream	tempFile;

		if(!tempFile.Open(dllPath.c_str()))
		{
			PrintError("Couldn't find FOSE DLL (%s). Please make sure you have installed FOSE correctly and are running it from your Fallout folder.", dllPath.c_str());
			return -1;
		}
	}

	bool result = CreateProcess(
		procPath.c_str(),
		NULL,	// no args
		NULL,	// default process security
		NULL,	// default thread security
		TRUE,	// don't inherit handles
		CREATE_SUSPENDED,
		NULL,	// no new environment
		NULL,	// no new cwd
		&startupInfo, &procInfo) != 0;

	// check for Vista failing to create the process due to elevation requirements
	if(!result && (GetLastError() == ERROR_ELEVATION_REQUIRED))
	{
		// in theory we could figure out how to UAC-prompt for this process and then run CreateProcess again, but I have no way to test code for that
		PrintError("Vista has decided that launching Fallout requires UAC privilege elevation. There is no good reason for this to happen, but to fix it, right-click on fose_loader.exe, go to Properties, pick the Compatibility tab, then turn on \"Run this program as an administrator\".");
		return -1;
	}
	
	ASSERT_STR_CODE(result, "Launching Fallout failed", GetLastError());

	if(g_options.m_setPriority)
	{
		if(!SetPriorityClass(procInfo.hProcess, g_options.m_priority))
			_WARNING("couldn't set process priority");
	}

	result = InjectDLL(&procInfo, dllPath.c_str(), &procHookInfo);
	
	if(result)
	{
		bool		didFpsLimit = false;
		std::string	limiterDllName = "Limiter_D3D9.dll";
		std::string	limiterDllPath = std::string(currentWorkingDirectory) + "\\" + limiterDllName;

		if(g_options.m_fpsLimit)
		{
			IFileStream	src;

			// check if the file exists
			if(src.Open(limiterDllPath.c_str()))
			{
				src.Close();

				_MESSAGE("injecting FPS limiter DLL (%s)", limiterDllName.c_str());

				didFpsLimit = InjectDLL(&procInfo, limiterDllPath.c_str(), &procHookInfo);
				if(!didFpsLimit)
					_ERROR("failed to inject FPS limiter DLL (%s)", limiterDllPath.c_str());
			}
			else
			{
				_ERROR("couldn't find FPS limiter DLL (%s)", limiterDllName.c_str());
			}
		}

		_MESSAGE("launching");

		// start the process
		ResumeThread(procInfo.hThread);

		// configure fps limiter
		if(didFpsLimit)
		{
			typedef void (__cdecl * LimiterTimerCallback)(UInt32 cmd, UInt32 arg);

			Sleep(1000);

			HMODULE	limiterDll = (HMODULE)LoadLibrary(limiterDllPath.c_str());
			if(limiterDll)
			{
				LimiterTimerCallback	limiterCB = (LimiterTimerCallback)GetProcAddress(limiterDll, "TimerEvent");
				if(limiterCB)
				{
					limiterCB(4, g_options.m_fpsLimit);

					// enable logging
//					limiterCB(5, 0);

					// disable fps display
					limiterCB(8, 0);
				}
				else
				{
					_ERROR("couldn't get FPS limiter callback");
				}

				FreeLibrary(limiterDll);
			}
			else
			{
				_ERROR("couldn't load FPS limiter locally");
			}
		}
	}
	else
	{
		PrintError("Couldn't inject dll.");

		_ERROR("terminating process");

		// kill the partially-created process
		TerminateProcess(procInfo.hProcess, 0);

		g_options.m_waitForClose = false;
	}

	// wait for the process to close if requested
	if(g_options.m_waitForClose)
	{
		WaitForSingleObject(procInfo.hProcess, INFINITE);
	}

	// clean up
	CloseHandle(procInfo.hProcess);
	CloseHandle(procInfo.hThread);

	return 0;
}

static bool InjectDLL(PROCESS_INFORMATION * info, const char * dllPath, ProcHookInfo * hookInfo)
{
	bool	result = false;

	// wrap DLL injection in SEH, if it crashes print a message
	__try {
		result = DoInjectDLL(info, dllPath, hookInfo);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		PrintError("DLL injection failed. In most cases, this is caused by an overly paranoid software firewall or antivirus package. Disabling either of these may solve the problem.");
		result = false;
	}

	return result;
}

#pragma pack (push, 1)

struct HookLayout
{
	enum
	{
		kNumLibs = 16,
		kMaxLibNameLen = MAX_PATH
	};

	struct DoLoadLibrary
	{
		UInt8	push;		// 68
		UInt32	strAddr;	// address
		UInt8	indCall1;	// FF
		UInt8	indCall2;	// 15
		UInt32	callAddr;	// address

		void	Clear(void)
		{
			// nops
			push = 0x90;
			strAddr = 0x90909090;
			indCall1 = 0x90;
			indCall2 = 0x90;
			callAddr = 0x90909090;
		}

		void	Setup(UInt32 _strAddr, UInt32 _callAddr)
		{
			push = 0x68;
			strAddr = _strAddr;
			indCall1 = 0xFF;
			indCall2 = 0x15;
			callAddr = _callAddr;
		}
	};

	// code (entry point)
	UInt8			infLoop1;		// EB
	UInt8			infLoop2;		// FF
	DoLoadLibrary	loadLib[kNumLibs];
	UInt8			callMain1;		// FF
	UInt8			callMain2;		// 25
	UInt32			callMainAddr;	// address

	// data
	char			libNames[kMaxLibNameLen * kNumLibs];
	UInt32			mainAddr;

	void	Init(ProcHookInfo * hookInfo)
	{
#if 0
		infLoop1 = 0xEB;
		infLoop2 = 0xFE;
#else
		infLoop1 = 0x90;
		infLoop2 = 0x90;
#endif

		for(UInt32 i = 0; i < kNumLibs; i++)
			loadLib[i].Clear();

		callMain1 = 0xFF;
		callMain2 = 0x25;
		callMainAddr = 0;

		memset(libNames, 0, sizeof(libNames));

		mainAddr = 0;
	}
};

#pragma pack (pop, 1)

struct HookSetup
{
	HookLayout	m_data;

	HANDLE	m_proc;
	UInt32	m_base;
	UInt32	m_loadLib;

	UInt32	m_libIdx;
	UInt32	m_strOffset;
	
	bool	m_isInit;

	HookSetup()
	{
		m_proc = NULL;
		m_base = 0;
		m_loadLib = 0;

		m_libIdx = 0;
		m_strOffset = 0;

		m_isInit = false;
	}

	bool	Init(PROCESS_INFORMATION * info, ProcHookInfo * hookInfo)
	{
		bool	result = false;

		if(m_isInit) return true;

		m_loadLib =				hookInfo->loadLibAddr;
		UInt32 hookBaseAddr =	hookInfo->hookCallAddr;

		m_data.Init(hookInfo);

		m_proc = OpenProcess(
			PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, info->dwProcessId);
		if(m_proc)
		{
			m_base = (UInt32)VirtualAllocEx(m_proc, NULL, sizeof(m_data), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if(m_base)
			{
				UInt32	hookBaseCallAddr;
				UInt32	bytesTransferred = 0;

				_MESSAGE("remote memory = %08X", m_base);

				// update the call
				if(	ReadProcessMemory(m_proc, (void *)(hookBaseAddr + 1), &hookBaseCallAddr, sizeof(hookBaseCallAddr), &bytesTransferred) &&
					(bytesTransferred == sizeof(hookBaseCallAddr)))
				{
					// adjust for relcall
					hookBaseCallAddr += 5 + hookBaseAddr;

					_MESSAGE("old winmain = %08X", hookBaseCallAddr);

					m_data.mainAddr =			hookBaseCallAddr;
					m_data.callMainAddr =		GetRemoteOffset(&m_data.mainAddr);

					UInt32	newHookDst = m_base - hookBaseAddr - 5;
					if(	WriteProcessMemory(m_proc, (void *)(hookBaseAddr + 1), &newHookDst, sizeof(newHookDst), &bytesTransferred) &&
						(bytesTransferred == sizeof(newHookDst)))
					{
						m_isInit = true;
						result = true;
					}
					else
					{
						_ERROR("couldn't write memory (update winmain)");
					}
				}
				else
				{
					_ERROR("couldn't read memory (update winmain)");
				}
			}
			else
			{
				_ERROR("couldn't allocate memory in remote process");
			}
		}
		else
		{
			_ERROR("couldn't open process");
		}

		return result;
	}

	bool	AddLoadLibrary(const char * dllPath)
	{
		bool	result = false;

		if(m_libIdx < HookLayout::kNumLibs)
		{
			HookLayout::DoLoadLibrary	* lib = &m_data.loadLib[m_libIdx];
			char						* strDst = &m_data.libNames[m_strOffset];
			m_libIdx++;

#pragma warning (push)
#pragma warning (disable : 4996)
			strcpy(strDst, dllPath);
#pragma warning (pop)

			m_strOffset += strlen(dllPath) + 1;

			lib->Setup(
				GetRemoteOffset(strDst),
				m_loadLib);

			if(UpdateRemoteProc())
			{
				result = true;
			}
		}

		return result;
	}

	UInt32	GetRemoteOffset(void * data)
	{
		return m_base + ((UInt32)data) - ((UInt32)&m_data);
	}

	bool	UpdateRemoteProc(void)
	{
		UInt32	bytesTransferred;
		return	WriteProcessMemory(m_proc, (void *)m_base, &m_data, sizeof(m_data), &bytesTransferred) &&
				(bytesTransferred == sizeof(m_data));
	}
};

HookSetup	g_hookData;

static bool DoInjectDLL(PROCESS_INFORMATION * info, const char * dllPath, ProcHookInfo * hookInfo)
{
	bool	result = false;

	if(g_hookData.Init(info, hookInfo))
	{
		if(g_hookData.AddLoadLibrary(dllPath))
		{
			result = true;
		}
		else
		{
			_ERROR("couldn't add library to list");
		}
	}
	else
	{
		_ERROR("couldn't init hook");
	}

	return result;
}

// based on some code from wikipedia
static UInt32 Adler32(UInt8 * buf, UInt32 len)
{
	static const UInt32 kModAdler = 65521;

	UInt32 a = 1, b = 0;

	while (len) {
		unsigned tlen = len > 5550 ? 5550 : len;
		len -= tlen;

		do {
			a += *buf++;
			b += a;
		} while (--tlen);

		a = (a & 0xffff) + (a >> 16) * (65536-kModAdler);
		b = (b & 0xffff) + (b >> 16) * (65536-kModAdler);
	}

	/* It can be shown that a <= 0x1013a here, so a single subtract will do. */
	if (a >= kModAdler) a -= kModAdler;

	/* It can be shown that b can reach 0xffef1 here. */
	b = (b & 0xffff) + (b >> 16) * (65536-kModAdler);
	if (b >= kModAdler) b -= kModAdler;

	return (b << 16) | a;
}

static UInt32 CalcEXEChecksum(UInt8 * buf, UInt32 length, UInt32 checksumOffset)
{
	// from pefile

	UInt64	checksum = 0;
	UInt32	* buf32 = (UInt32 *)buf;

	checksumOffset /= 4;

	for(UInt32 i = 0; i < length / 4; i++)
	{
		if(i == checksumOffset) continue;	// checksum field ignored

		checksum = (checksum & 0xFFFFFFFF) + buf32[i] + (checksum >> 32);
		checksum = (checksum & 0xFFFFFFFF) + (checksum >> 32);
	}

	checksum = (checksum & 0xFFFF) + (checksum >> 16);
	checksum = checksum + (checksum >> 16);
	checksum = checksum & 0xFFFF;

	checksum = checksum + length;

	return checksum;
}

static bool TestChecksum(const char * procName, std::string * dllSuffix, ProcHookInfo * hookInfo)
{
	bool		result = false;
	IFileStream	src;

	if(src.Open(procName))
	{
		UInt8	* buf = new UInt8[src.GetLength()];
		ASSERT(buf);
		src.ReadBuf(buf, src.GetLength());

		// *really* clear 2GB+ address-aware flag
		if(src.GetLength() > 0x40)
		{
			UInt32	headerOffset = *((UInt32 *)(buf + 0x3C)) + 4;	// +4 to skip 'PE\0\0'
			UInt32	flagsOffset = headerOffset + 0x12;
			UInt32	checksumOffset = headerOffset + 0x14 + 0x40;	// +14 to skip COFF header

			if(src.GetLength() > checksumOffset + 2)
			{
				UInt16	* flagsPtr = (UInt16 *)(buf + flagsOffset);
				UInt32	* checksumPtr = (UInt32 *)(buf + checksumOffset);

				if(*flagsPtr & 0x0020)
				{
					_MESSAGE("clearing large-address-aware flag");

					// clear it, recalculate the exe checksum
					*flagsPtr &= ~0x0020;

					UInt32	newChecksum = CalcEXEChecksum(buf, src.GetLength(), checksumOffset);

					// did the tool fix up the checksum?
					if(*checksumPtr != newChecksum)
					{
						if(!g_options.m_launchCS)
						{
							// yes, set it back
							_MESSAGE("recorrecting exe checksum (%08X -> %08X)", *checksumPtr, newChecksum);

							*checksumPtr = newChecksum;
						}
						else
						{
							// ok, this is just stupid
							// bethesda ships the cs with 0x00000000 in the PE checksum field
							// honestly, why would you do that?
							// at least it's only the cs so we can work around it

							_MESSAGE("using broken cs checksum (was %08X, should be %08X, setting to 0)", *checksumPtr, newChecksum);

							*checksumPtr = 0;
						}
					}
				}
			}
		}

		UInt32	crc = Adler32(buf, src.GetLength());

		delete [] buf;

		// make sure the crc shows up in the console when run with -crconly
		if(g_options.m_crcOnly)
			_FATALERROR("crc = %08X", crc);
		else
			_MESSAGE("crc = %08X", crc);

		if(g_options.m_launchCS)
		{
			switch(crc)
			{
				case 0x535CA534:	// 1.1.0.36
					*dllSuffix = "1_1";
					hookInfo->hookCallAddr = 0x00BC1338;
					hookInfo->loadLibAddr = 0x00D0317C;
					result = true;
					break;

				case 0x59F00F32:	// 1.5.0.19
					*dllSuffix = "1_5";
					hookInfo->hookCallAddr = 0x00BC2108;
					hookInfo->loadLibAddr = 0x00D0417C;
					result = true;
					break;

				default:	// unknown checksum
					PrintError("You have an unknown version of the CS. Please check http://fose.silverlock.org to make sure you're using the latest version of FOSE, then send an email to the contact addresses listed in fose_readme.txt if this version is not supported in the latest release. (CRC = %08X)", crc);
					break;
			}
		}
		else
		{
			switch(crc)
			{
				case 0x4614F449:	// 1.0.0.12 english retail
				case 0x4768F4C0:	// 1.0.0.12 english no-dvd
					PrintError("You have the original retail version of Fallout. Please patch it to the latest version available from www.bethsoft.com.");
					break;

				case 0xDBFCD417:	// 1.0.0.12 russian no-dvd (trivium)
					// ### this may actually work with the same offsets as us retail, needs testing
					PrintError("You have the Russian version of Fallout with a no-dvd patch applied. Since it is based on 1.0.0.12, which is unsupported, we cannot support this version. Please update to a supported version.");
					break;

				case 0xBC803CAC:	// 1.0.0.12 russian retail (starforce)
				case 0x00EB9C06:	// 1.0.0.15 polish with safedisc
				case 0xD448DD39:	// 1.1.0.35 hungarian (safedisc)
				case 0xDE69B7F2:	// 1.7.0.3 polish (safedisc)
					PrintError("You have a copy-protected version of Fallout. It cannot be supported by FOSE.");
					break;

				case 0xC23120CF:	// 1.0.0.12 german no-gore
					PrintError("You have an old version of the German censored version of Fallout. Currently due to the additional support load required, no censored version works with FOSE. If this changes, only the latest patch will be supported, so you will need to upgrade to 1.7.");
					break;

				// ### find out what the CRCs are for the intermediate versions

				case 0x30CD08E2:	// 1.0.0.15 english patch
					*dllSuffix = "1_0";
					hookInfo->hookCallAddr = 0x00C004B1;
					hookInfo->loadLibAddr = 0x00D940EC;
					result = true;
					break;

				case 0x2FF4640D:	// 1.1.0.35 english patch
					// ### deprecate this now that 1.4.0.6 is out?
					// broke VATS
					*dllSuffix = "1_1";
					hookInfo->hookCallAddr = 0x00C04F31;
					hookInfo->loadLibAddr = 0x00D990F0;
					result = true;
					break;

				case 0x03ABCAA0:	// 1.4.0.6 english patch
					*dllSuffix = "1_4";
					hookInfo->hookCallAddr = 0x00C05531;
					hookInfo->loadLibAddr = 0x00D990F0;
					result = true;
					break;

				case 0x56492499:	// 1.4.0.6 austrian/german/steam patch - same version number, but built at different times
					*dllSuffix = "1_4b";
					hookInfo->hookCallAddr = 0x00C054C1;
					hookInfo->loadLibAddr = 0x00D990F0;
					result = true;
					break;

				case 0xAA4933DF:	// 1.5.0.22 uk patch (hopefully all the other regions as well)
					// broke .esp-based mods
					*dllSuffix = "1_5";
					hookInfo->hookCallAddr = 0x00C05ED1;
					hookInfo->loadLibAddr = 0x00D9B0F0;
					result = true;
					break;

				case 0x36009C19:	// 1.6.0.3 english patch
					// may have fixed .esp-based mods?
					*dllSuffix = "1_6";
					hookInfo->hookCallAddr = 0x00C05F51;
					hookInfo->loadLibAddr = 0x00D9B0F0;
					result = true;
					break;

				case 0xFE5B82AE:	// 1.7.0.3 english patch
					*dllSuffix = "1_7";
					hookInfo->hookCallAddr = 0x00C05F61;
					hookInfo->loadLibAddr = 0x00D9B0F0;
					result = true;
					break;

				case 0x3FA1DF9C:	// 1.7.0.3 german no-gore
					*dllSuffix = "1_7ng";
					hookInfo->hookCallAddr = 0x00C02F31;
					hookInfo->loadLibAddr = 0x00D980F0;
					result = true;
					break;

				default:	// unknown checksum
					PrintError("You have an unknown version of Fallout. Please check http://fose.silverlock.org to make sure you're using the latest version of FOSE, then send an email to the contact addresses listed in fose_readme.txt if this version is not supported in the latest release. (CRC = %08X)", crc);
					break;
			}
		}
	}
	else
	{
		PrintError("Couldn't find %s, make sure you're running this from the same folder as fallout3.exe.", procName);
	}

	return result;
}

static void PrintError(const char * fmt, ...)
{
	va_list	args;

	va_start(args, fmt);

	gLog.Log(IDebugLog::kLevel_FatalError, fmt, args);

	char	buf[4096];
	vsprintf_s(buf, sizeof(buf), fmt, args);

	MessageBox(NULL, buf, "FOSE Loader", MB_OK | MB_ICONEXCLAMATION);

	va_end(args);
}
