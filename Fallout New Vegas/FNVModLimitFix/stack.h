#pragma once

#include <log.h>
#include <offsets.h>

typedef struct CFILE
{
	FILE file;
	LPCRITICAL_SECTION lpcs;
	CFILE* ref;
} CFILE;

typedef struct FSS
{
	int size;
	int top;
	CFILE*** items;
	bool dbg;
} FSS;

FSS *createstack(int size)
{
	FSS *stack = (FSS*)malloc(sizeof(FSS));
	stack->size = size;
	stack->top = -1;
	stack->items = (CFILE***)calloc(stack->size, sizeof(CFILE***));
	if (!stack->items)
	{
		return NULL;
	}
	return stack;
}

void __forceinline spush(FSS *stack, CFILE **file)
{
	if (stack->top < stack->size - 1)
	{
		if (stack->dbg)
		{
			DMESSAGE("Pushed %#.8x | Stack size %d", file, stack->top + 1);
		}
		stack->items[++stack->top] = file;
	}
}

CFILE __forceinline **spop(FSS *stack)
{
	if (stack->top > -1)
	{
		CFILE **file = stack->items[stack->top--];
		if (stack->dbg)
		{
			DMESSAGE("Popped %#.8x | Stack size %d", file, stack->top + 1);
		}
		return file;
	}
	return NULL;
}

FSS *stack;
