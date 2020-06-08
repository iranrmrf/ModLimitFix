#pragma once

#include <offsets.h>
#include <stack.h>

std::map<CFILE*, char*> filenames;
CRITICAL_SECTION filenameCS;

void PatchBytes(void* address, BYTE* data, DWORD size)
{
	DWORD p = 0;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &p);
	memcpy(address, data, size);
	VirtualProtect(address, size, p, &p);
	FlushInstructionCache(GetCurrentProcess(), address, size);
}

void __fastcall PatchCall(void* address, void* destination)
{
	BYTE bytes[5];
	bytes[0] = 0xE8;
	*(DWORD*)((DWORD)bytes + 1) = (DWORD)destination - (DWORD)address - 5;
	PatchBytes(address, bytes, 5);
}

void __fastcall PatchJump(void* address, void* destination)
{
	BYTE bytes[5];
	bytes[0] = 0xE9;
	*(DWORD*)((DWORD)bytes + 1) = (DWORD)destination - (DWORD)address - 5;
	PatchBytes(address, bytes, 5);
}

void __fastcall LogAndAddName(CFILE** cfile, char* filename)
{
	EnterCriticalSection(&filenameCS);
	filenames.insert(std::pair<CFILE*, char*>(*cfile, filename));
	LeaveCriticalSection(&filenameCS);
	D("N %p %s", *cfile, filename);
}

void __fastcall LogAndUpdateName(CFILE** cfile, char* filename)
{
	EnterCriticalSection(&filenameCS);
	filenames[*cfile] = filename;
	LeaveCriticalSection(&filenameCS);
	D("U %p %s", *cfile, filename);
}

void __fastcall LogAndDeleteName(CFILE* cfile)
{
	D("R %p %s", cfile, filenames[cfile]);
	EnterCriticalSection(&filenameCS);
	filenames.erase(cfile);
	LeaveCriticalSection(&filenameCS);
}

void __fastcall LogFileError(CFILE* cfile)
{
	EnterCriticalSection(&filenameCS);
	D("E %p %s", cfile, filenames[cfile]);
	LeaveCriticalSection(&filenameCS);
}

CFILE* __cdecl f_getstream()
{
	EnterCriticalSection(&stack->cs);
	CFILE** filePtr = spop(stack);
	LeaveCriticalSection(&stack->cs);
	if (!filePtr)
	{
		F("S N");
		return nullptr;
	}
	CFILE* newFile;
	if (newFile = *filePtr)
	{
		if (!(newFile->file._flag & (_IOREAD | _IOWRT | _IORW | _IOLK)))
		{
			EnterCriticalSection(&newFile->cs);
			if (!(newFile->file._flag & (_IOREAD | _IOWRT | _IORW)))
			{
				newFile->file._flag &= _IOLK;
				newFile->file._cnt = 0;
				newFile->file._base = 0;
				newFile->file._ptr = 0;
				newFile->file._tmpfname = 0;
				newFile->file._file = -1;
				if (stack->dbg)
				{
					__asm
					{
						mov edx, dword ptr ss : [ebp + 0x0]
						mov edx, dword ptr ss : [edx + 0x8]
						mov ecx, filePtr
						call LogAndUpdateName
					}
				}
				return newFile;
			}
			LeaveCriticalSection(&newFile->cs);
		}
	}
	else
	{
		newFile = (CFILE*)f_malloc_crt(sizeof(CFILE));
		if (!newFile)
		{
			F("F A");
			return nullptr;
		}
		if (InitializeCriticalSectionAndSpinCount(&newFile->cs, 0xFA0u))
		{
			EnterCriticalSection(&newFile->cs);
			newFile->file._flag = 0;
			newFile->file._cnt = 0;
			newFile->file._base = 0;
			newFile->file._ptr = 0;
			newFile->file._tmpfname = 0;
			newFile->file._file = -1;
			newFile->ref = filePtr;
			f_lock(1);
			*filePtr = newFile;
			f_unlock(1);
			if (stack->dbg)
			{
				__asm
				{
					mov edx, dword ptr ss : [ebp + 0x0]
					mov edx, dword ptr ss : [edx + 0x8]
					mov ecx, filePtr
					call LogAndAddName
				}
			}
			return newFile;
		}
		else
		{
			F("C I");
			f_free(newFile);
		}
	}
	return nullptr;
}

int __cdecl f_fclose(CFILE* cfile)
{
	int result = -1;
	if (cfile)
	{
		if (cfile->file._flag & _IOSTRG)
		{
			cfile->file._flag = 0;
			D("F S");
		}
		else
		{
			EnterCriticalSection(&cfile->cs);
			result = f_fclose_nolock(cfile);
			LeaveCriticalSection(&cfile->cs);
		}
		if (stack->dbg)
		{
			LogAndDeleteName(cfile);
		}
		EnterCriticalSection(&stack->cs);
		spush(stack, cfile->ref);
		LeaveCriticalSection(&stack->cs);
	}
	else
	{
		D("F N");
	}
	return result;
}

CFILE* __cdecl f_openfile_w(const char* filename, const char* mode, int flag, CFILE* cfileout)
{
	CFILE* cfile = f_openfile(filename, mode, flag, cfileout);
	if (!cfile)
	{
		if (stack->dbg)
		{
			LogFileError(cfileout);
		}
		f_fclose(cfileout);
	}
	LeaveCriticalSection(&cfileout->cs);
	return cfile;
}
