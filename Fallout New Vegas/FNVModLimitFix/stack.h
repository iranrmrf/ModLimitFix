#pragma once

#include <log.h>
#include <types.h>

FSS *createstack(int size)
{
	FSS *s = (FSS*)f_malloc_crt(sizeof(FSS));
	if (!s) { return nullptr; }
	s->size = size;
	s->top = -1;
	s->dbg = 0;
	s->items = (CFILE***)f_calloc_crt(s->size, (int)sizeof(CFILE***));
	if (!s->items) { return nullptr; }
	InitializeCriticalSection(&s->lock);
	return s;
}

void __fastcall spush(FSS *stack, CFILE **ref)
{
	if (stack->top < stack->size - 1)
	{
		stack->items[++stack->top] = ref;
		if (stack->dbg)	{ D("+ %p %04d", ref, stack->top + 1); }
		return;
	}
	F("S F");
}

CFILE **__fastcall spop(FSS *stack)
{
	if (stack->top > -1)
	{
		CFILE **ref = stack->items[stack->top--];
		if (stack->dbg)	{ D("- %p %04d", ref, stack->top + 1); }
		return ref;
	}
	F("S E");
	return nullptr;
}

FSS *stack;
