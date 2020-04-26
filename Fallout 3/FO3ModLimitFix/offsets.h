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

t_malloc_crt* f_malloc_crt = (t_malloc_crt*)0x00C0AB3F;
t_calloc_crt* f_calloc_crt = (t_calloc_crt*)0x00C0AB7F;

t_free* f_free = (t_free*)0x00C064B8;

t_lock* f_lock = (t_lock*)0x00C16621;
t_unlock* f_unlock = (t_unlock*)0x00C16549;

t_lock_file* f_lock_file = (t_lock_file*)0x00C07B90;
t_fclose_nolock* f_fclose_nolock = (t_fclose_nolock*)0x00C03D19;
t_unlock_file* f_unlock_file = (t_unlock_file*)0x00C07BFA;

t__SEH_prolog4* f__SEH_prolog4 = (t__SEH_prolog4*)0x00C0CB08;
t__SEH_epilog4* f__SEH_epilog4 = (t__SEH_epilog4*)0x00C0CB4D;

t__errno_0* f__errno_0 = (t__errno_0*)0x00C02A76;
t_invalid_parameter* f_invalid_parameter = (t_invalid_parameter*)0x00C01E67;

DWORD filePtr = 0x0117A770;
DWORD oldAddy = *(DWORD*)filePtr;
DWORD newAddy = 0x0;
DWORD maxAddy = 0x0117B780;

DWORD getstreamAddy = 0x00C12DA8;
DWORD fcloseAddy = 0x00C03D8B;
