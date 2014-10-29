#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <assert.h>

const int MaxStackSize = 1000;
const int MaxTaskLength = 1000;
struct stack_t
{
	double *headStack;
	int stackSize;
	int topOfStack;
};

enum Command_t
{
#define DEF_CMD_(name, num, pref , code) CMD_##name = num,
#include "commands.h"
#undef DEF_CMD_
	CMD_MAX
};

int stack_Ok(stack_t *stack);
void calculator();
void createStack(stack_t * stack, int stackSize);
void destroyStack(stack_t * stack);
void stack_push(stack_t *stack, double element);
double stack_pop(stack_t *stack);

int main()
{
	calculator();
}
int parseCommand(char *command)
{
	for (int i = 0; i < CMD_MAX; i++)
	{
#define DEF_CMD_(name, num, pref , code) if(!strcmpi(#name,command)) return num;
#include "commands.h"
#undef DEF_CMD_
		return 0;
	}
}
void calculator()
{
	bool isProcess = true;
	stack_t stack = {};
	createStack(&stack, MaxStackSize);
	char * task = (char *)calloc(MaxTaskLength, sizeof(char));
	while (isProcess)
	{
		scanf("%s", task);
		int command = parseCommand(task);
#define DEF_CMD_(name, num, pref , code) if (command == (num)) {printf(#name); printf("\n");}
#include "commands.h"
#undef DEF_CMD_
		if (!command) printf("Command not found\n");
	}
}

int stack_Ok(stack_t *stack)
{
	if (!stack) return 0;
	if (!(stack->headStack)) return 0;
	return 1;
}

void createStack(stack_t * stack, int MaxStackSize)
{
	stack->headStack = (double *)calloc(MaxStackSize, sizeof(*(stack->headStack)));
	stack->stackSize = MaxStackSize;
	stack->topOfStack = 0;
}

void destroyStack(stack_t * stack)
{
	assert(stack_Ok(stack));
	free(stack->headStack);
	stack->headStack = NULL;
	stack->stackSize = -1;
	stack->topOfStack = -1;
}

void stack_push(stack_t *stack, double element)
{
	assert(stack_Ok(stack));
	stack->headStack[stack->topOfStack] = element;
	stack->topOfStack++;
}

double stack_pop(stack_t *stack)
{
	assert(stack_Ok(stack));
	stack->topOfStack--;
	return (stack->headStack[stack->topOfStack]);
}