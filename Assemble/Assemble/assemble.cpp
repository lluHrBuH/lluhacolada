#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <process.h>
#define isStringEquivalent(a,b) !strcmpi((a), (b))
#define withOperator 1
#define withoutOperator 0
#define COMMAND_NOT_FOUND -2
#define LABEL_NOT_FOUND -1
#define NOTCOMMAND -10
#define isNoRegisteNeed 0
#define isRegisterOnly 1
#define isRegisterOrNumber 2
#define deltaToOperWithRegister 2
#define deltaToOperWithNumb 1
#define isJumpOrCall -1
#define OK 1
const char * inputFile = "asmcode.txt";
const char * outputFile = "bytecode.txt";

struct Label_t
{
	char* labelName;
	int pointToProg;
};

enum Command_t
{
#define DEF_CMD_(name, num, pref , code) name = num,
#include "commands.h"
#undef DEF_CMD_
	CMD_MAX
};
enum Registers_t
{
#define REGISTER_(name, num) name = num,
#include "registers.h"
#undef REGISTER_
	ebp
};


char * readCommandFromFile(int *commandLength, int *errorNumber);
char* * partitionToLine_and_deleteNewLineSymb(char *text, int textLength, int numbersOfLine);
int convertToByteCode(char* * listOfCommands, int numberOfLines, int commandLength);
int countLine(char *text, int numberOfcharacter);
int identCommand(char *commandLine, char* *commnd, char* *opertr);
int parseCommand(char * command);
int operandIsRegister(char * operand);
int findLabel(Label_t *label, char* JmpCallLabel, int numberOfJmpCall, int numbersOfLabel);
void printToFile(double* byteCode, int numberOfCommand);

#define DEF_CMD_(name, num, pref, code) name = num,


int main()
{
	int commandLength = -1;
	int errorNumber;
	char* inputCommand = readCommandFromFile(&commandLength, &errorNumber);
	int numberOfLines = countLine(inputCommand, commandLength);
	char* * listOfCommands = (char* *)calloc(numberOfLines, sizeof(char* *));
	listOfCommands = partitionToLine_and_deleteNewLineSymb(inputCommand, commandLength, numberOfLines);
	convertToByteCode(listOfCommands, numberOfLines, commandLength);

	system("pause>>nul");

}
int convertToByteCode(char* * listOfCommands, int numberOfLines, int commandLength)
{
	char *command = nullptr;
	char *operand = nullptr;
	double *byteCode = (double *)calloc(commandLength,sizeof(double));
	Label_t *label = (Label_t *)calloc(numberOfLines, sizeof(Label_t));
	char * jumpAndCallLabel = (char *)calloc(commandLength, sizeof(char));
	int numberOfCommand = 0;
	int numberOfCodeLine = 0;
	int numbersOfLabel = 0;
	for (int i = 0; i < numberOfLines; i++)
	{
	
		int operandPresent = identCommand(listOfCommands[i], &command, &operand);
		printf("Command:%s Operand:%s\n", command, operand);
		int registr = -1;
		double number = 0;
		if (operandPresent)
		{
			registr = operandIsRegister(operand);
			if (!registr)
			{
				number = atof(operand);
			}
		}
		switch (parseCommand(command))
		{
#define DEF_CMD_(name,num,pref,code) case(name): \
		{byteCode[numberOfCommand] = num; \
		if (pref == isJumpOrCall) {strcat(jumpAndCallLabel,operand); strcat(jumpAndCallLabel, ":"); byteCode[++numberOfCommand] = -1;}\
		else if((pref == isRegisterOrNumber) && operandPresent) \
				if(registr) {byteCode[numberOfCommand]+=deltaToOperWithRegister; byteCode[++numberOfCommand] = registr;}\
				else {byteCode[numberOfCommand]+=deltaToOperWithNumb; byteCode[++numberOfCommand] = number;}\
			else if(pref == isRegisterOnly) byteCode[++numberOfCommand] = registr;\
				else if(operandPresent) byteCode[++numberOfCommand] = number;\
			numberOfCommand++; numberOfCodeLine++; break;}

#include "commands.h"
#undef DEF_CMD_
		default:
		{
			if (command[strlen(command)-1] == ':')
			{
				label[numbersOfLabel].labelName = (char *)calloc(strlen(command), sizeof(char));
				memcpy(label[numbersOfLabel].labelName, command, strlen(command) - 1);
				label[numbersOfLabel].pointToProg = numberOfCodeLine + 1;
				numbersOfLabel++;

			}
			else return COMMAND_NOT_FOUND;
		}
		}
		
		if (operand) free(operand);
		operand = nullptr;
		if (command) free(command);
		command = nullptr;
	}
	int numberOfJumpCall = 0;

	for (int i = 0; i < commandLength; i++)
	{
		if (jumpAndCallLabel[i] == ':') jumpAndCallLabel[i] = '\0';
	}

	for (int i = 0; i < numberOfCommand; i++)
	{
#define DEF_CMD_(name,num,pref,code) if((pref == isJumpOrCall)&&(num == byteCode[i])) {int pointToProg = findLabel(label, jumpAndCallLabel, numberOfJumpCall, numbersOfLabel);\
	if(pointToProg) {byteCode[i+1]=pointToProg; numberOfJumpCall++;}\
	else return LABEL_NOT_FOUND;}
#include "commands.h"
#undef DEF_CMD_
}
	for (int i = 0; i < numbersOfLabel; i++)
	{
		free(label[i].labelName);
		label[i].labelName = NULL;
	}
	free(jumpAndCallLabel);
	jumpAndCallLabel = NULL;
	free(label);
	label = NULL;
	for (int i = 0; i < numberOfCommand; i++)
	{
		printf("%lg ", byteCode[i]);
	}
	printToFile(byteCode, numberOfCommand);
	free(byteCode);
	byteCode = NULL;
	return OK;
}

void printToFile(double* byteCode, int numberOfCommand)
{
	FILE *f = fopen(outputFile, "w");
	for (int i = 0; i < numberOfCommand; i++)
	{
		fprintf(f, "%f ", byteCode[i]);
	}
	fprintf(f, "\n");
	fclose(f);

}
int findLabel(Label_t *label, char* JmpCallLabel, int numberOfJmpCall, int numbersOfLabel)
{
	int i = 0;
	char *startOfLabel = JmpCallLabel;
	while (numberOfJmpCall > 0)
	{
		if (JmpCallLabel[i] == '\0')
		{
			startOfLabel = &JmpCallLabel[i + 1];
			numberOfJmpCall--;
		}
		i++;
	}
	for (i = 0; i < numbersOfLabel; i++)
	{
		if (isStringEquivalent(startOfLabel, label[i].labelName))
		{
			return label[i].pointToProg;
		}
	}
	return LABEL_NOT_FOUND;
}

int identCommand(char *commandLine, char* *cmd, char* *oprnd)
{
	int numberOfletter = 0;
	char * command = (char *)calloc(strlen(commandLine)+1, sizeof(char));
	int endOfCommand = 0;
	while (commandLine[numberOfletter] != '\0')
	{
		if (!(commandLine[numberOfletter] == ' '))
		{
			command[numberOfletter] = commandLine[numberOfletter];
		}
		else
		{
			endOfCommand = numberOfletter + 1;
			break;
		}
		numberOfletter++;
	}
	*cmd = command;
	if (numberOfletter != strlen(commandLine))
	{
		char * operand = (char *)calloc((strlen(commandLine) - endOfCommand + 1), sizeof(char));
		numberOfletter = endOfCommand;
		
		while ((commandLine[numberOfletter] != '\0') && (commandLine[numberOfletter] != ';'))
		{
			operand[numberOfletter - endOfCommand] = commandLine[numberOfletter];
			numberOfletter++;
		}
		*oprnd = operand;
		return withOperator;
	}
	else
	{
		oprnd = nullptr;
		return withoutOperator;
	}
}
int operandIsRegister(char * operand)
{
#define REGISTER_(name, num) if(isStringEquivalent(operand, #name)) return num;
#include "registers.h"
#undef REGISTER_
	return 0;
}
int parseCommand(char * command)
{
#define DEF_CMD_(name, num, pref, code) if(isStringEquivalent(command, #name)) return num;
#include "commands.h"
#undef DEF_CMD_
	return NOTCOMMAND;
}
int countLine(char *text, int numberOfcharacter)
{
	int numberOfLine = 0;
	bool isLineEnd = true;
	for (int i = 0; i < numberOfcharacter; i++)
	{
		isLineEnd = false;
		if (text[i] == '\n')
		{
			numberOfLine++;
			isLineEnd = true;
		}
	}
	if (!isLineEnd) numberOfLine++;
	return numberOfLine;
}

char* * partitionToLine_and_deleteNewLineSymb(char *text, int textLength, int numbersOfLine)
{
	char *tmpText = text;
	char * * linesOfText = (char * *)calloc(numbersOfLine, sizeof(char *));
	bool isLineEnd = true;
	int numberOfLine = 0;
	linesOfText[numberOfLine] = tmpText;
	numberOfLine++;
	for (int i = 0; i < textLength; i++)
	{
		isLineEnd = false;
		if (tmpText[i] == '\n')
		{
			tmpText[i] = '\0';
			linesOfText[numberOfLine] = &tmpText[i + 1];
			numberOfLine++;
		}
	}
	return linesOfText;
}

char * readCommandFromFile(int *commandLength, int *errorNumber)
{
	FILE *f = fopen(inputFile, "r");
	if (!(f == NULL))
	{
		*commandLength = filelength(fileno(f));
		char *buff = (char *)calloc(*commandLength, sizeof(commandLength));
		fread(buff, *commandLength, sizeof(char), f);
		fclose(f);
		*errorNumber = 0;
		return buff;
	}
	else
	{
		*errorNumber = -1;
		return NULL;
	}
}