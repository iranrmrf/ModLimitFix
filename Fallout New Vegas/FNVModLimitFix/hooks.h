#pragma once

#include <offsets.h>
#include <stack.h>

std::map<CFILE*, char*> addys;

void Hook(void* addy, void* jump, int size)
{
	DWORD oldProt;
	VirtualProtect(addy, size, PAGE_EXECUTE_READWRITE, &oldProt);
	memset(addy, 0x90, size);
	*(BYTE*)(addy) = 0xE9;
	*(DWORD*)((DWORD)addy + 1) = (DWORD)jump - (DWORD)addy - 5;
	VirtualProtect(addy, size, oldProt, &oldProt);
}

void __cdecl LogAndSaveName(CFILE** cfile, char *fileName)
{
	addys.insert(std::pair<CFILE*, char*>(*cfile, fileName));
	D("N %p %s", *cfile, fileName);
}

void __cdecl LogAndUpdateName(CFILE** cfile, char *fileName)
{
	addys[*cfile] = fileName;
	D("U %p %s", *cfile, fileName);
}

void __cdecl LogAndDeleteName(CFILE* cfile)
{
	D("R %p %s", cfile, addys[cfile]);
	addys.erase(cfile);
}

void __cdecl LogFileError(CFILE* cfile)
{
	D("E %p %s", cfile, addys[cfile]);
}

CFILE *__cdecl f_getstream()
{
	EnterCriticalSection(&stack->lock);
	CFILE **filePtr = spop(stack);
	LeaveCriticalSection(&stack->lock);
	if (!filePtr)
	{
		F("S N");
		return nullptr;
	}
	CFILE *newFile;
	if (newFile = *filePtr)
	{
		if (!(newFile->file._flag & 0x8083))
		{
			EnterCriticalSection(&newFile->lpcs);
			if (!(newFile->file._flag & 0x83))
			{
				newFile->file._flag &= 0x8000u;
				newFile->file._cnt = 0;
				newFile->file._base = 0;
				newFile->file._ptr = 0;
				newFile->file._tmpfname = 0;
				newFile->file._file = -1;
				if (stack->dbg)
				{
					__asm
					{
						mov eax, dword ptr ss : [ebp + 0x0]
						push dword ptr ss : [eax + 0x8]
						push filePtr
						call LogAndUpdateName
						add esp, 0x8
					}
				}
				return newFile;
			}
			LeaveCriticalSection(&newFile->lpcs);
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
		if (InitializeCriticalSectionAndSpinCount(&newFile->lpcs, 0xFA0u))
		{
			EnterCriticalSection(&newFile->lpcs);
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
					mov eax, dword ptr ss : [ebp + 0x0]
					push dword ptr ss : [eax + 0x8]
					push filePtr
					call LogAndSaveName
					add esp, 0x8
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

int __cdecl f_fclose(CFILE *cfile)
{
	int result = -1;
	if (cfile)
	{
		if (cfile->file._flag & 0x40)
		{
			cfile->file._flag = 0;
			D("F S");
		}
		else
		{
			EnterCriticalSection(&cfile->lpcs);
			result = f_fclose_nolock(cfile);
			LeaveCriticalSection(&cfile->lpcs);
		}
		EnterCriticalSection(&stack->lock);
		if (stack->dbg) { LogAndDeleteName(cfile); }
		spush(stack, cfile->ref);
		LeaveCriticalSection(&stack->lock);
	}
	else
	{
		D("F N");
	}
	return result;
}

void __declspec(naked) f_fail()
{
	__asm
	{
		test eax, eax
		je LBL_ERROR
		jmp LBL_END
	LBL_ERROR :
		call LogFileError
		call f_fclose
	LBL_END :
		add dword ptr ss : [esp + 0x0], 0x20
		call LeaveCriticalSection
		ret
	}
}
