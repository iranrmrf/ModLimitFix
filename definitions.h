#pragma once

#define MLF_GAME FNV

#if MLF_GAME == FNV

#define MLF_EXTENDER_NAME	NVSE
#define MLF_N_STREAM		(0x01271A80)
#define MLF_PIOB			(0x01270A70)
#define MLF_MALLOC_CRT		(0x00ED0CDF)
#define MLF_RECALLOC_CRT	(0x00ED0DBE)
#define MLF_UNLOCK_FILE		(0x00ECE08E)
#define MLF_LOCK			(0x00EDDF39)
#define MLF_UNLOCK			(0x00EDDE5F)

#endif

#pragma warning(disable : 5105)
