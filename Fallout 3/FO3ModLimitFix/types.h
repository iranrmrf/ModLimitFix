#pragma once

#define CS(hot, lpcs) EnterCriticalSection(lpcs); hot; LeaveCriticalSection(lpcs)

#define _IOLK 0x8000

struct CFILE
{
	FILE file;
	CRITICAL_SECTION cs;
	CFILE** ref;
};

struct FSS
{
	int size;
	int top;
	int dbg;
	CFILE*** items;
	CRITICAL_SECTION cs;
};

struct Settings
{
	HMODULE hnd;
	HANDLE dbg;
	DWORD iMaxHnd;
	DWORD bDebug;
};

typedef void*(__cdecl t_malloc_crt(size_t));
typedef void*(__cdecl t_calloc_crt(size_t, int));
typedef void(__cdecl t_free(void*));

typedef void(__cdecl t_lock(int));
typedef int(__cdecl t_fclose_nolock(CFILE*));
typedef void(__cdecl t_unlock(int));

typedef CFILE*(__cdecl t_openfile(const char*, const char*, int, CFILE*));
