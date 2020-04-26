#pragma once

typedef void *(__cdecl t_malloc_crt(size_t));
typedef void *(__cdecl t_calloc_crt(size_t, int));

typedef void(__cdecl t_free(void *));

typedef void(__cdecl t_lock(int));
typedef void(__cdecl t_unlock(int));

typedef void(__cdecl t_lock_file(FILE *));
typedef int(__cdecl t_fclose_nolock(FILE *));
typedef void(__cdecl t_unlock_file(FILE *));

typedef void(__cdecl t__SEH_prolog4(int, int));
typedef void(__cdecl t__SEH_epilog4(void));

typedef int(__cdecl t__errno_0(void));
typedef int(__cdecl t_invalid_parameter(int, int, int));

t_malloc_crt* f_malloc_crt = (t_malloc_crt*)0x00ED0CE1;
t_calloc_crt* f_calloc_crt = (t_calloc_crt*)0x00ED0D26;

t_free* f_free = (t_free*)0x00ECD291;

t_lock* f_lock = (t_lock*)0x00EDDF3B;
t_unlock* f_unlock = (t_unlock*)0x00EDDE61;

t_lock_file* f_lock_file = (t_lock_file*)0x00ECE01D;
t_fclose_nolock* f_fclose_nolock = (t_fclose_nolock*)0x00EC9892;
t_unlock_file* f_unlock_file = (t_unlock_file*)0x00ECE090;

t__SEH_prolog4* f__SEH_prolog4 = (t__SEH_prolog4*)0x00ED1714;
t__SEH_epilog4* f__SEH_epilog4 = (t__SEH_epilog4*)0x00ED1759;

t__errno_0* f__errno_0 = (t__errno_0*)0x00EC85E3;
t_invalid_parameter* f_invalid_parameter = (t_invalid_parameter*)0x00EC7C32;

DWORD filePtr = 0x01270A70;
DWORD oldAddy = *(DWORD*)filePtr;
DWORD newAddy = 0x0;
DWORD maxAddy = 0x01271A80;

DWORD getstreamAddy = 0x00ED8501;
DWORD fcloseAddy = 0x00EC9907;
