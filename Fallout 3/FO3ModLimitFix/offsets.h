#pragma once

#pragma once

#include <types.h>

CFILE*** filePtr;
DWORD* maxAddy;

void* getstreamAddy;
void* fcloseAddy;
void* openfileAddy;

t_malloc_crt* f_malloc_crt;
t_calloc_crt* f_calloc_crt;
t_free* f_free;

t_lock* f_lock;
t_fclose_nolock* f_fclose_nolock;
t_unlock* f_unlock;

t_openfile* f_openfile;

void InitOffsets()
{
	f_malloc_crt = (t_malloc_crt*)0x00C0AB3F;
	f_calloc_crt = (t_calloc_crt*)0x00C0AB7F;
	f_free = (t_free*)0x00C064B8;

	f_lock = (t_lock*)0x00C16621;
	f_fclose_nolock = (t_fclose_nolock*)0x00C03D19;
	f_unlock = (t_unlock*)0x00C16549;

	f_openfile = (t_openfile*)0x00C12B08;

	filePtr = (CFILE***)0x0117A770;
	maxAddy = (DWORD*)0x0117B780;

	getstreamAddy = (void*)0x00C12DA8;
	fcloseAddy = (void*)0x00C03D8B;
	openfileAddy = (void*)0x00C03EA1;
}
