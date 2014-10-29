#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <assert.h>
#include "stack.h"
#include <process.h>

int EIP = 0;
char * InputFile = "bytecodeFibon.txt";
int StackMaxSize = 1000;

enum Command_t
{
#define DEF_CMD_(name, num, pref , code) CMD_##name = num,
#include "commands.h"
#undef DEF_CMD_
	CMD_MAX
};
struct CPU_t
{
	stack_t stack;
	stack_t callStack;
#define REGISTER_(name, num)  double name = 0;
#include "registers.h"
#undef REGISTER_
};

void commandExecution();
double * readCommandFromFile(int *commandLength, int *errorNumber);
int initCPU(CPU_t *cpu, int stackSize, int maxCommand);
void pushRegister(CPU_t *cpu, int registr);
void popRegister(CPU_t *cpu, int registr);
void inputToRegister(CPU_t *cpu, double * command);
void outputFromRegister(CPU_t *cpu, double * command);
void printCommand(double *command);
void dump_CPU(CPU_t *cpu);

int main()
{
	commandExecution();
}

void commandExecution()
{
	int error = 0,
		commandLength = 0;
	double * command = readCommandFromFile(&commandLength, &error);
	assert(command);

	CPU_t cpu = {};
	initCPU(&cpu, StackMaxSize, commandLength);

	while ((EIP < commandLength)&&(EIP >= 0))
	{
  //		system("pause>>nil");
		printCommand(command);
		printf("command[eip+1] = %f,  eip = %d, operand = %f\n", command[EIP+1], EIP, command[EIP+1]);
		switch ((int)command[EIP])
		{
#define DEF_CMD_(name,num,pref,code) case num : {code; break;}
#include "commands.h"
#undef DEF_CMD_
		}
	}
}
void printCommand(double *command)
{
	int comnd = (int)command[EIP];
#define DEF_CMD_(name, num, pref , code) if(comnd == num ) {printf(#name); printf(" ");}
#include "commands.h"
#undef DEF_CMD_
}
void pushRegister(CPU_t *cpu, int registr)
{
	switch (registr){
#define REGISTER_(name, num) case(num) : {stack_push(&cpu->stack, cpu->name); break;}
#include "registers.h" 
#undef REGISTER_ 
	}
}

void inputToRegister(CPU_t *cpu, double * command)
{
	switch ((int)command[EIP + 1]){
#define REGISTER_(name, num) case(num) : {scanf("%lf", &cpu->name); break;}
#include "registers.h" 
#undef REGISTER_ 
	}
}
void outputFromRegister(CPU_t *cpu, double * command)
{
	switch ((int)command[EIP + 1]){
#define REGISTER_(name, num) case(num) : {printf(#name); printf(" %lf \n", cpu->name); break;}
#include "registers.h" 
#undef REGISTER_ 
	}
}
void popRegister(CPU_t *cpu, int registr)
{
	switch (registr){
#define REGISTER_(name, num) case(num) : {cpu->name = stack_pop(&cpu->stack); break;}
#include "registers.h" 
#undef REGISTER_ 
	}
}

int cpu_Ok(CPU_t *cpu)
{
	if (!stack_Ok(&(cpu->callStack))) return 0;
	if (!stack_Ok(&(cpu->stack)) )return 0;
	return 1;
}

void dump_CPU(CPU_t *cpu)
{
	printf("---Start_CPU_DUMP---\n");
	printf("Stack:\n");
	dumpStack(&cpu->stack);
	printf("Call stack:\n");
	dumpStack(&cpu->callStack);
	printf("Registers: \n");
#define REGISTER_(name, num)  printf(#name); printf(" :%lf\n",cpu->name);
#include "registers.h"
#undef REGISTER_
	printf("----End_CPU_DUMP----\n");

}
int initCPU(CPU_t *cpu, int stackSize, int maxCommand)
{
	stack_t stack,
		callStack;
	createStack(&stack, stackSize);
	createStack(&callStack, maxCommand);
	cpu->callStack = callStack;
	cpu->stack = stack;
	return 1;
}

double * readCommandFromFile(int *commandLength, int *errorNumber)
{
	assert(commandLength);
	assert(errorNumber);
	FILE *inpFile = fopen(InputFile, "rb");
	assert(inpFile);
	if (!(inpFile == NULL))
	{
		*commandLength = filelength(fileno(inpFile));
		double *buff = (double *)calloc(*commandLength, sizeof(double));
// Don`t work :\	
//		fread(buff, length, sizeof(double), inpFile);
//		printf("commandLength = %d; fRead = %d\n", *commandLength,frd);
		double tmpNumb = 0;
		int i = 0;
		while (!feof(inpFile))
		{
			fscanf(inpFile, "%lf", &tmpNumb);
			buff[i] = tmpNumb;
			i++;
		} 
		buff[i - 1] = 0;
		*commandLength = i;
		fclose(inpFile);
		*errorNumber = 0;
		return buff;
	}
	else
	{
		*errorNumber = -1;
		return NULL;
	}
}