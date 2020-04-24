#pragma once

#include <stack.h>

typedef void (__cdecl t_free(void *));

typedef void (__cdecl t_lock(int));
typedef void (__cdecl t_unlock(int));

typedef void (__cdecl t_lock_file(FILE *));
typedef int (__cdecl t_fclose_nolock(FILE *));
typedef void (__cdecl t_unlock_file(FILE *));

typedef void (__cdecl t__SEH_prolog4(int, int));
typedef void (__cdecl t__SEH_epilog4(void));

DWORD filePtr = 0x01270A70;
DWORD oldAddy = *(DWORD*)filePtr;
DWORD newAddy = 0x0;
DWORD maxAddy = 0x01271A80;

t_free* f_free = (t_free*)0x00ECD291;

t_lock* f_lock = (t_lock*)0x00EDDF3B;
t_unlock* f_unlock = (t_unlock*)0x00EDDE61;

t_lock_file* f_lock_file = (t_lock_file*)0x00ECE01D;
t_fclose_nolock* f_fclose_nolock = (t_fclose_nolock*)0x00EC9892;
t_unlock_file* f_unlock_file = (t_unlock_file*)0x00ECE090;

t__SEH_prolog4* f__SEH_prolog4 = (t__SEH_prolog4*)0x00ED1714;
t__SEH_epilog4* f__SEH_epilog4 = (t__SEH_epilog4*)0x00ED1759;

void CreateHook(void* addy, void* jump, int size)
{
	DWORD oldProt;
	VirtualProtect(addy, size, PAGE_EXECUTE_READWRITE, &oldProt);
	memset(addy, 0x90, size);
	*(BYTE*)(addy) = 0xE9;
	*(DWORD*)((DWORD)addy + 1) = (DWORD)jump - (DWORD)addy - 5;
	VirtualProtect(addy, size, oldProt, &oldProt);
}

__declspec(naked) void *f_getstream()
{
	__asm
	{
		push 0x10
		push 0x01180368

		call f__SEH_prolog4

		xor edi, edi
		mov dword ptr ss : [ebp - 0x4], 0
		mov dword ptr ss : [ebp - 0x1C], 0
		mov dword ptr ss : [ebp - 0x20], 0

		push 0x1
		call f_lock
		pop ecx

		push stack
		call spop
		pop ecx
		push eax

		mov ebx, [eax]
		push ebx
		test ebx, ebx
		je CFILENULLPTR

	CFILEPTR:
		mov ecx, [ebx + 0xC]
		test cl, 0x83
		jne END
		test ecx, 0x8000
		jne END

		add ebx, 0x20
		push ebx
		call EnterCriticalSection

		mov ebx, ss : dword ptr[ebp - 0x38]
		test byte ptr ds : [ebx + 0xC], 0x83
		jne UNLOCK

		mov edi, ebx
		mov dword ptr ss : [ebp - 0x1C], edi

		and dword ptr ds : [edi + 0xC], 0x8000
		mov dword ptr ds : [edi + 0x4], 0x0
		mov dword ptr ds : [edi + 0x8], 0x0
		mov dword ptr ds : [edi + 0x0], 0x0
		mov dword ptr ds : [edi + 0x1C], 0x0
		mov dword ptr ds : [edi + 0x10], 0xFFFFFFFF

		mov dword ptr ss : [ebp - 0x4], 0xFFFFFFFE

		jmp END

	UNLOCK:
		add ebx, 0x20
		push ebx
		call LeaveCriticalSection
		jmp END

	CFILENULLPTR:
		push 0x3C
		call f_malloc_crt
		pop ecx

		test eax, eax
		je END

		mov dword ptr ss : [ebp - 0x38], eax

		push 4000
		add eax, 0x20
		push eax
		call InitializeCriticalSectionAndSpinCount
		test eax, eax
		je FREE

		mov ebx, ss : dword ptr[ebp - 0x38]
		add ebx, 0x20
		push ebx
		call EnterCriticalSection

		mov edi, dword ptr ss : [ebp - 0x38]

		mov dword ptr ss : [ebp - 0x1C], edi

		mov dword ptr ds : [edi + 0xC], 0x0
		mov dword ptr ds : [edi + 0x4], 0x0
		mov dword ptr ds : [edi + 0x8], 0x0
		mov dword ptr ds : [edi + 0x0], 0x0
		mov dword ptr ds : [edi + 0x1C], 0x0
		mov dword ptr ds : [edi + 0x10], 0xFFFFFFFF

		mov eax, ss : dword ptr [ebp - 0x34]
		mov dword ptr ds : [eax], edi

		mov dword ptr ds : [edi + 0x38], eax

		jmp END

	FREE:
		call f_free

	END:
		add esp, 0x8

		push 0x1
		call f_unlock
		pop ecx

		mov eax, edi
		call f__SEH_epilog4
		ret
	}
}

__declspec(naked) int f_fclose()
{
	__asm
	{
		push 0xC
		push 0x0117FD28
		call f__SEH_prolog4

		or dword ptr ss : [ebp - 0x1C], 0xFFFFFFFF

		xor eax, eax
		xor edi, edi

		mov esi, dword ptr ss : [ebp + 0x8]
		cmp esi, edi
		je NULLPTR

		test byte ptr ds : [esi + 0xC], 0x40
		je CLOSE

		mov dword ptr ds : [esi + 0xC], edi
		mov eax, dword ptr ss : [ebp - 0x1C]

		jmp END
		
	CLOSE:
		push esi
		call f_lock_file
		pop ecx

		mov dword ptr ss : [ebp - 0x4], edi

		push 0x1
		call f_lock

		push dword ptr ss : [esi + 0x38]
		push stack
		call spush

		push 0x1
		call f_unlock

		push esi
		call f_fclose_nolock

		add esp, 0x14

		mov dword ptr ss : [ebp - 0x1C], eax
		mov dword ptr ss : [ebp - 0x4], 0xFFFFFFFE

		push esi
		call f_unlock_file
		pop ecx

		mov eax, dword ptr ss : [ebp - 0x1C]

		jmp END

	NULLPTR:
		mov eax, 0xFFFFFFFF

	END:
	   call f__SEH_epilog4
	   ret
	}
}
