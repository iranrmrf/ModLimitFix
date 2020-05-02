#pragma once

struct CFILE
{
	FILE file;
	CRITICAL_SECTION lpcs;
	CFILE** ref;
};

struct FSS
{
	int size;
	int top;
	int dbg;
	CFILE*** items;
	//CRITICAL_SECTION lock;
};

struct Settings
{
	HMODULE hnd;
	HANDLE dbg;
	DWORD iMaxHnd;
	DWORD bDebugLog;
};

typedef void *(__cdecl t_malloc_crt(size_t));
typedef void *(__cdecl t_calloc_crt(size_t, int));
typedef void(__cdecl t_free(void *));
typedef void(__cdecl t_lock(int));
typedef int(__cdecl t_fclose_nolock(CFILE *));
typedef void(__cdecl t_unlock(int));

t_malloc_crt* f_malloc_crt;
t_calloc_crt* f_calloc_crt;
t_free* f_free;
t_lock* f_lock;
t_fclose_nolock* f_fclose_nolock;
t_unlock* f_unlock;
