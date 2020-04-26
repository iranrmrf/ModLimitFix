void SafeWrite8(UInt32 addr, UInt32 data)
{
	UInt32	oldProtect;

	VirtualProtect((void *)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt8 *)addr) = data;
	VirtualProtect((void *)addr, 4, oldProtect, &oldProtect);
}

void SafeWrite16(UInt32 addr, UInt32 data)
{
	UInt32	oldProtect;

	VirtualProtect((void *)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt16 *)addr) = data;
	VirtualProtect((void *)addr, 4, oldProtect, &oldProtect);
}

void SafeWrite32(UInt32 addr, UInt32 data)
{
	UInt32	oldProtect;

	VirtualProtect((void *)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt32 *)addr) = data;
	VirtualProtect((void *)addr, 4, oldProtect, &oldProtect);
}

void SafeWriteBuf(UInt32 addr, void * data, UInt32 len)
{
	UInt32	oldProtect;

	VirtualProtect((void *)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void *)addr, data, len);
	VirtualProtect((void *)addr, len, oldProtect, &oldProtect);
}

void WriteRelJump(UInt32 jumpSrc, UInt32 jumpTgt)
{
	// jmp rel32
	SafeWrite8(jumpSrc, 0xE9);
	SafeWrite32(jumpSrc + 1, jumpTgt - jumpSrc - 1 - 4);
}

void WriteRelCall(UInt32 jumpSrc, UInt32 jumpTgt)
{
	// call rel32
	SafeWrite8(jumpSrc, 0xE8);
	SafeWrite32(jumpSrc + 1, jumpTgt - jumpSrc - 1 - 4);
}
