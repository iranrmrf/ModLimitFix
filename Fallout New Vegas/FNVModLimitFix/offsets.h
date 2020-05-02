#pragma once

#include <types.h>

CFILE ***filePtr;
DWORD *maxAddy;

void *getstreamAddy;
void *fcloseAddy;
void* failAddy;

void InitOffsets()
{
	f_malloc_crt = (t_malloc_crt*)0x00ED0CDF;
	f_calloc_crt = (t_calloc_crt*)0x00ED0D24;
	f_free = (t_free*)0x00ECD291;

	f_lock = (t_lock*)0x00EDDF39;
	f_fclose_nolock = (t_fclose_nolock*)0x00EC9890;
	f_unlock = (t_unlock*)0x00EDDE5F;

	filePtr = (CFILE***)0x01270A70;
	maxAddy = (DWORD*)0x01271A80;

	getstreamAddy = (void*)0x00ED8501;
	fcloseAddy = (void*)0x00EC9907;
	failAddy = (void*)0x00EC9A40;
}
