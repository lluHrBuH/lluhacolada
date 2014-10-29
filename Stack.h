struct stack_t
{
	int *headStack;
	int stackSize;
	int topOfStack;
};

int stack_Ok(stack_t *stack, int minOfElement)
{
	if (!stack) return 0;
	if (!(stack->headStack)) return 0;
	return 1;
}

void createStack(stack_t * stack, int stackSize)
{
	stack->headStack = (int *)calloc(stackSize, sizeof(*(stack->headStack)));
	stack->stackSize = stackSize;
	stack->topOfStack = 0;
}

void destroyStack(stack_t * stack)
{
	free(stack->headStack);
	stack->headStack = NULL;
	stack->stackSize = -1;
	stack->topOfStack = -1;
}

void stack_push(stack_t *stack, int element)
{
	stack->headStack[stack->topOfStack] = element;
	stack->topOfStack++;
}

int * stack_pop(stack_t *stack)
{
	stack->topOfStack--;
	return &(stack->headStack[stack->topOfStack]);
}