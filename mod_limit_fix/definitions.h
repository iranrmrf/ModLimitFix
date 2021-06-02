#pragma once

#define MLF_GAME FNV

#if MLF_GAME == FNV

#define MLF_EXTENDER_NAME	NVSE
#define MLF_N_STREAM		(*(int*)(0x01271A80))
#define MLF_PIOB			(*(void***)(0x01270A70))
#define MLF_LOCK			((void(__cdecl*)(int))(0x00EDDF39))
#define MLF_RECALLOC_CRT	((void* (__cdecl*)(void*, size_t, size_t))(0x00ED0DBE))
#define MLF_UNLOCK			((void(__cdecl*)(int))(0x00EDDE5F))

#elif MLF_GAME == FO3

#define MLF_EXTENDER_NAME	FOSE
#define MLF_N_STREAM		(*(int*)(0x0117B780))
#define MLF_PIOB			(*(void***)(0x0117A770))
#define MLF_LOCK			((void(__cdecl*)(int))(0x00C16621))
#define MLF_RECALLOC_CRT	((void* (__cdecl*)(void*, size_t, size_t))(0x00C0AC12))
#define MLF_UNLOCK			((void(__cdecl*)(int))(0x00C16549))

#elif MLF_GAME == OBL

#define MLF_EXTENDER_NAME	OBSE
#define MLF_N_STREAM		(*(int*)(0x00BABC00))
#define MLF_PIOB			(*(void***)(0x00BAABE4))
#define MLF_LOCK			((void(__cdecl*)(int))(0x0098C9D3))
#define MLF_RECALLOC_CRT	((void* (__cdecl*)(void*, size_t, size_t))(0x00989EB5))
#define MLF_UNLOCK			((void(__cdecl*)(int))(0x0098C8FB))

#endif

#pragma warning(disable : 5105)
