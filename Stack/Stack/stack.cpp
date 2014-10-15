#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define MAXTASKLENGTH 100

const int quit = -100;
const int error = -1;
const int help = 0;
const int ADD = 1;
const int SUB = 2;
const int DIV = 3;
const int MUL = 4;
const int SQR = 5;
const int SQRT = 6;
const int CreateSTACK = 7;
const int DestroySTACK = 8;
const int POP = 9;
const int PUSH = 10;
const int numbersOfOperation = 10;
const char * Operation[numbersOfOperation] = { "ADD", "SUB", "DIV", "MUL", "SQR", "SQRT", "CreateStack", "DestroyStack", "POP", "PUSH" };


struct stack_t
{
	int *headStack;
	int stackSize;
	int topOfStack;
};

int stack_Ok(stack_t *stack, int minOfElement);
void createStack(stack_t * stack, int stackSize);
void destroyStack(stack_t * stack);
void stack_push(stack_t *stack, int element);
int * stack_pop(stack_t *stack);
void calculator();
int parsingInputString(char * inputString);

void stack_ADD(stack_t *stack, int numb);
void stack_SUB(stack_t *stack, int numb);
void stack_DIV(stack_t *stack, int numb);
void stack_MUL(stack_t *stack, int numb);
void stack_SQR(stack_t *stack);
void stack_SQRT(stack_t *stack);

int main()
{
	calculator();
}

int parsingInputString(char * inputString)
{
	if (!strcmp(inputString, "help")) return help;
	if (!strcmp(inputString, "quit")) return quit;
	for (int i = 0; i < numbersOfOperation; i++)
	{
		if (!strcmp(inputString, Operation[i])) return (i+1);
	}
	return error;
}

void calculator()
{
	bool isNotExit = true;
	bool isStackPresent = false;
	stack_t stack = {};
	char * task = (char *)calloc(MAXTASKLENGTH, sizeof(char));
	while (isNotExit)
	{
		printf("Enter command:\n");
		scanf("%s", task);
		switch (parsingInputString(task))
		{
		case quit:
		{
			isNotExit = false;
			if (isStackPresent)
			{
				destroyStack(&stack);
			}
			printf("bye\n");
			break;
		}
		case help:
		{
			printf("Hello to calculator witch using Stack!\nAvailable commands:\n'ADD', 'SUB', 'DIV', 'MUL', 'SQR',\n'CreateStack', 'DestroyStack', 'POP', 'PUSH'\n");
			break;
		}
		case CreateSTACK:
		{

			if (isStackPresent) printf("Stack already create with size: %d\n", stack.stackSize);
			else
			{
				int stackSize = 0;
				printf("Enter size of stack:\n");
				scanf("%d", &stackSize);
				createStack(&stack, stackSize);
				isStackPresent = true;
				printf("Stack created!\n");
			}
			break;
		}
		case DestroySTACK:
		{
			if (!isStackPresent) printf("Nothing to destroy\n");
			else
			{
				destroyStack(&stack);
				isStackPresent = false;
			}
			break;
		}
		case ADD:

		{
			if (isStackPresent)
			{
				printf("Enter number to add to head of stack\n");
				int number = 0;
				scanf("%d", &number);
				stack_ADD(&stack, number);
			}
			else (printf("Stack not exists. Type 'help' for read help\n"));
			break;
		}
		case SUB:
		{
			if (isStackPresent)
			{
				printf("Enter number to sub from head of stack\n");
				int number = 0;
				scanf("%d", &number);
				stack_SUB(&stack, number);
			}
			else (printf("Stack not exists. Type 'help' for read help\n"));
			break;
		}
		case DIV:
		{
			if (isStackPresent)
			{
				printf("Enter number to div head of stack\n");
				int number = 1;
				scanf("%d", &number);
				stack_DIV(&stack, number);
			}
			else (printf("Stack not exists. Type 'help' for read help\n"));
			break;
		}
		case MUL:
		{
			if (isStackPresent)
			{
				printf("Enter number to mull to head of stack\n");
				int number = 1;
				scanf("%d", &number);
				stack_MUL(&stack, number);
			}
			else (printf("Stack not exists. Type 'help' for read help\n"));
			break;
		}
		case SQR:
		{
			if (isStackPresent)
				stack_SQR(&stack);
			else (printf("Stack not exists. Type 'help' for read help\n"));
			break;
		}
		/*case SQRT:
		{
			if (isStackPresent)
				stack_SQRT(&stack);
			else (printf("Stack not exists. Type 'help' for read help\n"));
			break;
		}
		*/
		case POP:
		{
			if (isStackPresent)
			{
				if (int *tmpNumb = stack_pop(&stack))
					printf("Pop number from stack: %d\n", *tmpNumb);
			}
			else (printf("Stack not exists. Type 'help' for read help\n"));
			break;
		}
		case PUSH:
		{
			if (isStackPresent)
			{
				int number = 0;
				scanf("%d", &number);
				stack_push(&stack, number);
			}
			else (printf("Stack not exists. Type 'help' for read help\n"));
			break;
		}

		default: printf("Command not found. Type 'help' for list of command\n");
		}
	}
 free(task);
}

//Function to work with stack
void stack_ADD(stack_t *stack, int numb)
{
	if (int *tmpNumb = stack_pop(stack))
	{
		*tmpNumb += numb;
		stack_push(stack, *tmpNumb);
	}
}

void stack_SUB(stack_t *stack, int numb)
{
	if (int *tmpNumb = stack_pop(stack))
	{
		*tmpNumb -= numb;
		stack_push(stack, *tmpNumb);
	}
}

void stack_DIV(stack_t *stack, int numb)
{
	if (int *tmpNumb = stack_pop(stack))
	{
		if (*tmpNumb == 0)
		{
			*tmpNumb /= numb;
			stack_push(stack, *tmpNumb);
		}
		else printf("Integer division by zero!\n");
		
	}
}

void stack_MUL(stack_t *stack, int numb)
{
	if (int *tmpNumb = stack_pop(stack))
	{
		*tmpNumb *= numb;
		stack_push(stack, *tmpNumb);
	}
}

void stack_SQR(stack_t *stack)
{
	if (int *tmpNumb = stack_pop(stack))
	{
		*tmpNumb *= *tmpNumb;
		stack_push(stack, *tmpNumb);
	}
}
/*
void stack_SQRT(stack_t *stack)
{
	int tmpNumb = stack_pop(stack);
	tmpNumb = (int) sqrt(tmpNumb);
	stack_push(stack, tmpNumb);
}
*/

//END function to work with stack
int stack_Ok(stack_t *stack,int minOfElement)
{
	if (!stack) return 0;
//	if (!IsBadReadPtr(stack,sizeof(stack_t))) return 0;
	if (!(stack->headStack)) return 0;
//	if (!IsBadReadPtr(stack->headStack,sizeof(int))) return 0;
	if (stack->topOfStack < minOfElement) return 0;
	if (!minOfElement && (stack->topOfStack == stack->stackSize)) return 0;
	return 1;
}
	
void createStack(stack_t * stack, int stackSize)
{
	int * stackArray = (int *)calloc(stackSize, sizeof(int));
	stack->headStack = stackArray;
	stack->stackSize = stackSize;
	stack->topOfStack = 0;
}

void destroyStack(stack_t * stack)
{
	stack->headStack = NULL;
	stack->stackSize = -1;
	stack->topOfStack = -1;
}

void stack_push(stack_t *stack, int element)
{
	if (stack_Ok(stack, 0))
	{
		stack->headStack[stack->topOfStack] = element;
		stack->topOfStack++;
	}
	else printf("Stack is corrupt!\n");
}

int * stack_pop(stack_t *stack)
{
	if (stack_Ok(stack, 1))
	{
		stack->topOfStack--;
		return &(stack->headStack[stack->topOfStack]);
	}
	else printf("Stack is corrupt!\n");
	return NULL;
}