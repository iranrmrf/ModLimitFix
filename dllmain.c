#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "stack.h"
#include "definitions.h"

#define EXPORT __declspec(dllexport)

#define EXPAND(x) x
#define MLF_PREPEND_EXTENDER(f) EXPAND(MLF_EXTENDER_NAME)##f

int* pnstream = (int*)MLF_N_STREAM;
void*** ppiob = (void***)MLF_PIOB;
struct Stack stack;

struct Interface
{
	DWORD extenderVersion;
	DWORD runtimeVersion;
	DWORD editorVersion;
	DWORD isEditor;
};

struct PluginInfo
{
	DWORD infoVersion;
	const char* name;
	DWORD version;
};

void patch_byte(void* addr, BYTE value)
{
	DWORD p;
	VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &p);
	*(BYTE*)addr = value;
	VirtualProtect(addr, 1, p, &p);
}

void patch_call(void* addr, void* jump, int size)
{
	DWORD p;
	VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &p);
	memset(addr, 0x90, size);
	*(BYTE*)addr = 0xE8;
	*(DWORD*)((DWORD)addr + 1) = (DWORD)jump - (DWORD)addr - 5;
	VirtualProtect(addr, size, p, &p);
}

__declspec(naked) void open_hook(void) {
	__asm {
		push offset stack
		call stack_pop
		add esp, 0x4
		mov esi, eax
		mov[ebp - 20h], eax
		mov edx, [ppiob]
		mov edx, [edx]
		lea eax, [edx + eax * 4]
		retn
	}
}

__declspec(naked) void index_hook(void) {
	__asm {
		mov eax, [ppiob]
		mov eax, [eax]
		mov edi, [esi + eax]
		mov[edi + 0Ch], ebx
		mov eax, [ebp - 20h]
		mov[edi + 38h], eax
		retn
	}
}

__declspec(naked) void close_hook(void) {
	__asm {
		push[esi + 0x38]
		push offset stack
		call stack_push
		add esp, 0x8
		mov ecx, MLF_UNLOCK_FILE
		jmp ecx
	}
}

BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	return TRUE;
}

EXPORT int MLF_PREPEND_EXTENDER(Plugin_Query)(const struct Interface* iface, struct PluginInfo* info)
{
	info->infoVersion = 1;
	info->name = "MLF";
	info->version = 3.1;
	return !iface->isEditor;
}

EXPORT int MLF_PREPEND_EXTENDER(Plugin_Load)(const struct Interface* iface)
{
	((void(__cdecl*)(int))MLF_LOCK)(1);

	*pnstream = 2048;
	*ppiob = (void**)((void* (__cdecl*)(void*, size_t, size_t))MLF_RECALLOC_CRT)(*ppiob, *pnstream, sizeof(void*));

	stack_init(&stack, *pnstream);

	for (int i = *pnstream - 1; i >= 20; i--)
		if (ppiob[i] == NULL)
			stack_push(&stack, i);


	patch_call((void*)0x00ED851C, open_hook, 0x1C);
	patch_call((void*)0x00ED85F1, index_hook, 0x8);
	patch_call((void*)0x00EC997C, close_hook, 0x5);
	patch_byte((void*)0x00ED859B, 0x3C);

	((void(__cdecl*)(int))MLF_UNLOCK)(1);

	return 1;
}
