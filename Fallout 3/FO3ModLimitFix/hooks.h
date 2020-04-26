#pragma once

#include <offsets.h>
#include <stack.h>

void Hook(void* addy, void* jump, int size)
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
		push 0x00F43B70
		call f__SEH_prolog4

		xor edi, edi

		mov dword ptr ss : [ebp - 0x1C], 0x0

		push 0x1
		call f_lock
		pop ecx

		mov dword ptr ss : [ebp - 0x4], 0x0
		mov dword ptr ss : [ebp - 0x20], 0x0

		push stack
		call spop
		mov dword ptr ss : [esp + 0x0], eax

		mov ebx, [eax]
		test ebx, ebx
		je CFILENULLPTR

		mov ecx, dword ptr ds : [ebx + 0xC]
		test cl, 0x83
		jne END
		test ecx, 0x8000
		jne END

		mov eax, ebx
		add eax, 0x20
		push eax
		call EnterCriticalSection

		test byte ptr ds : [ebx + 0xC], 0x83
		jne UNLOCK

		mov edi, ebx
		mov dword ptr ss : [ebp - 0x1C], edi

		mov dword ptr ds : [edi + 0x0], 0x0
		mov dword ptr ds : [edi + 0x4], 0x0
		mov dword ptr ds : [edi + 0x8], 0x0
		and dword ptr ds : [edi + 0xC], 0x8000
		mov dword ptr ds : [edi + 0x10], 0xFFFFFFFF
		mov dword ptr ds : [edi + 0x1C], 0x0

		mov dword ptr ss : [ebp - 0x4], 0xFFFFFFFE

		jmp END

	UNLOCK :
		add ebx, 0x20
		push ebx
		call LeaveCriticalSection
		jmp END

	CFILENULLPTR :
		push 0x3C
		call f_malloc_crt
		pop ecx

		test eax, eax
		je END

		mov ebx, eax

		push 4000
		add eax, 0x20
		push eax
		call InitializeCriticalSectionAndSpinCount
		test eax, eax
		je FREE

		mov edi, ebx

		add ebx, 0x20
		push ebx
		call EnterCriticalSection

		mov dword ptr ss : [ebp - 0x1C], edi

		mov dword ptr ds : [edi + 0x0], 0x0
		mov dword ptr ds : [edi + 0x4], 0x0
		mov dword ptr ds : [edi + 0x8], 0x0
		mov dword ptr ds : [edi + 0xC], 0x0
		mov dword ptr ds : [edi + 0x10], 0xFFFFFFFF
		mov dword ptr ds : [edi + 0x1C], 0x0

		mov eax, dword ptr ss : [ebp - 0x34]
		mov dword ptr ds : [eax], edi

		mov dword ptr ds : [edi + 0x38], eax

		jmp END

	FREE :
		call f_free

	END :
		push 0x1
		call f_unlock

		add esp, 0x8

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
		push 0x00F435A0
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

	CLOSE :
		push esi
		call f_lock_file

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

		add esp, 0x18

		mov dword ptr ss : [ebp - 0x1C], eax
		mov dword ptr ss : [ebp - 0x4], 0xFFFFFFFE

		push esi
		call f_unlock_file
		pop ecx

		mov eax, dword ptr ss : [ebp - 0x1C]

		jmp END

	NULLPTR :
		call f__errno_0
		mov dword ptr ds : [eax], 0x16

		push edi
		push edi
		push edi
		push edi
		push edi
		call f_invalid_parameter
		add esp, 0x14

		or eax, 0xFFFFFFFF

		END:
		call f__SEH_epilog4
			ret
	}
}
