#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "definitions.h"

struct Stack
{
	int size;
	int top;
	int* items;
	CRITICAL_SECTION lock;
};

inline void stack_init(struct Stack* stack, int size)
{
	stack->size = size;
	stack->top = -1;
	stack->items = (int *)((void* (__cdecl*)(size_t))MLF_MALLOC_CRT)(stack->size * sizeof(int));
	InitializeCriticalSection(&stack->lock);
}

inline void stack_push(struct Stack *stack, int value)
{
	EnterCriticalSection(&stack->lock);
	if (stack->top < stack->size - 1)
		stack->items[++stack->top] = value;
	LeaveCriticalSection(&stack->lock);
}

inline int stack_pop(struct Stack* stack)
{
	int ret;

	EnterCriticalSection(&stack->lock);
	if (stack->top > -1) {
		ret = stack->items[stack->top--];
		goto end;
	}
	ret = stack->size;
end:
	LeaveCriticalSection(&stack->lock);

	return	ret;
}
