#pragma once

typedef void *(__cdecl t_malloc_crt(size_t));
typedef void *(__cdecl t_calloc_crt(size_t, int));

t_malloc_crt* f_malloc_crt = (t_malloc_crt*)0x00ED0CE1;
t_calloc_crt* f_calloc_crt = (t_calloc_crt*)0x00ED0D26;

typedef struct CFILE
{
	FILE file;
	LPCRITICAL_SECTION lpcs;
	BYTE unk[20];
	CFILE* ref;
} CFILE;

typedef struct FSS
{
	int size;
	int top;
	CFILE*** items;
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

void spush(FSS *stack, CFILE **file)
{
	if (stack->top < stack->size - 1)
	{
		stack->items[++stack->top] = file;
	}
}

CFILE **spop(FSS *stack)
{
	if (stack->top > -1)
	{
		return stack->items[stack->top--];
	}
	return NULL;
}

FSS *stack;
