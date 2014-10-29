struct stack_t
{
	double *headStack;
	int stackSize;
	int topOfStack;
};
void dumpStack(stack_t *stack)
{
	printf("---Start-DUMP---\n");
	for (int i = 0; i < stack->topOfStack; i++)
	{
		printf("Stack[%d]: %lf\n", i, stack->headStack[i]);	
	}
	printf("----End-DUMP----\n");
}
int stack_Ok(stack_t *stack)
{
	if (!stack) return 0;
	if (!(stack->headStack)) return 0;
	return 1;
}

void createStack(stack_t * stack, int stackSize)
{
	stack->headStack = (double *)calloc(stackSize, sizeof(*(stack->headStack)));
	stack->stackSize = stackSize;
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