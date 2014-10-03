#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <locale>	
#include <assert.h>

#define isNSymbol(x) ((128<=(unsigned char)(x)))

#ifdef _DEBUG
#define DBG printf("#");
#else 
#define DBG if(0)
#endif // _DEBUG

//{=================================================================================
//! Onegin - Read and sort novel "Eugene Onegin"  written by Alexander Pushkin.
//!     
//! @note For humanists: we don`t edit original novel!          
//}=================================================================================
void Onegin();

//{=================================================================================
//! readStringFromFile - read string from file
//!
//! @param      textLength  - numbers of symbols to read
//! @param[out]	errorNumb   - if error return -1
//! @return     pointer to string
//}=================================================================================
char * readStringFromFile(int *textLength, int *errorNumb);

//{=================================================================================
//! partitionToLine - partition of the text into lines
//!
//! @param      text		 - text to partition
//! @param      textLength   - numbers of symbols in text
//! @param[out] numberOfLine - numbers of lines in text
//!
//! @return     array of pointer to line
//}=================================================================================
char* * partitionToLine(char *text, int textLength, int numberOfLine);

//{=================================================================================
//! countLine - Counts the number of lines
//!
//! @param      text			  - text for counting lines
//! @param      numberOfcharacter -numbers of symbols in text  
//!
//! @return     count of lines    
//}=================================================================================
int countLine(char *text, int numberOfcharacter);

//{=================================================================================
//! compareString - Comparison of strings in alphabetical order
//!
//! @param       a  first string
//! @param       b  second string
//!
//! @return    -1 if first string alphabetically first
//!				0 if string are equivalent
//!				1 if second string alphabetically first
//! @note  string equivalent without last symbols (! , . ; etc.)
//}=================================================================================
int compareString(const void *a, const void *b);

//{=================================================================================
//! compareInverString - Comparison of invert strings in alphabetical order
//!
//! @param       a  first string
//! @param       b  second string
//!
//! @return    -1 if first invert string alphabetically first
//!				0 if string are equivalent
//!				1 if second invert string alphabetically first
//! @note  string equivalent without last symbols (! , . ; etc.)       
//}=================================================================================
int compareInverString(const void * a, const void * b);

//{=================================================================================
//! sortLineAlphabet - sort all line in Text in alphabetical order
//!
//! @param      arrayOfTextLines - array with pointer to lines in text
//! @param      numberOfLines	 - numbers of lines
//!
//! @return      array of pointer to line with sort text
//!
//! @note  original text don`t edit
//}=================================================================================
char* * sortLineAlphabet(char* * arrayOfTextLines, int numberOfLines);

//{=================================================================================
//! sortLineInvert - sort all invert line in Text in alphabetical order 
//!
//! @param      arrayOfTextLines - array with pointer to lines in text
//! @param      numberOfLines	 - numbers of lines
//!
//! @return      array of pointer to line with invert sort text
//!
//! @note  original text don`t edit         
//}=================================================================================
char* * sortLineInvert(char* * arrayOfTextLines, int numberOfLines);

//{=================================================================================
//! printToFile - Print all text to file "oneginNEW.txt"
//!
//! @param      arrayOfText   - array with pointer to lines in text
//! @param      numberOfLines - numbers of lines     
//!
//! @note  if file not exists, it will be create
//}=================================================================================
void printToFile(char* * arrayOfText, int numberOfLines);

//{=================================================================================
//! printToConsole - Print all text to console
//!
//! @param      arrayOfText   - array with pointer to lines in text
//! @param      numberOfLines - numbers of lines     
//}=================================================================================
void printToConsole(char* * arrayOfText, int numberOfLines);


int main()
{
	setlocale(LC_ALL, "Russian");
	Onegin();
	system("pause>>nul");
	return 0;
}

void Onegin()
{
	char *textOnegin;
	int textLength;
	int errorNumber;
	textOnegin = readStringFromFile(&textLength, &errorNumber);
	if (!errorNumber)
	{
		int PrintToConsole = 0;
		DBG printf("Select where to print: 1 - to console; 2 - to file 'oneginNew.txt'\n");
		scanf("%d", &PrintToConsole);

		int numberOfLines = countLine(textOnegin, textLength);

		char* * originalText = (char* *)calloc(numberOfLines, sizeof(char* *));
		originalText = partitionToLine(textOnegin, textLength, numberOfLines);

		char* * linesOfSortText = (char* *)calloc(numberOfLines, sizeof(char* *));
		linesOfSortText = sortLineAlphabet(originalText, numberOfLines);

		char* * linesOfInvertSortText = (char* *)calloc(numberOfLines, sizeof(char* *));
		linesOfInvertSortText = sortLineInvert(originalText, numberOfLines);
		if (PrintToConsole == 1)
		{
			printToConsole(originalText, numberOfLines);
			printToConsole(linesOfSortText, numberOfLines);
			printToConsole(linesOfInvertSortText, numberOfLines);
		}
		else
		{
			printToFile(originalText, numberOfLines);
			printToFile(linesOfSortText, numberOfLines);
			printToFile(linesOfInvertSortText, numberOfLines);
		}
		free(textOnegin);
		textOnegin = NULL;
		free(originalText);
		originalText = NULL;
		free(linesOfSortText);
		linesOfSortText = NULL;
		free(linesOfInvertSortText);
		linesOfInvertSortText = NULL;

	}
	else
	{
		DBG printf("Error file reading!\n");
	}
}

void printToFile(char* * arrayOfText, int numberOfLines)
{
	FILE *f = fopen("oneginNew.txt", "a");
	for (int i = 0; i < numberOfLines; i++)
	{
		fprintf(f,"%s\n", arrayOfText[i]);
	}
	fprintf(f, "\n");
	fclose(f);

}

void printToConsole(char* * arrayOfText, int numberOfLines)
{
	for (int i = 0; i < numberOfLines; i++)
	{
		printf("%s\n", arrayOfText[i]);
	}
	printf("\n");
}


int compareInverString(const void * a, const void * b)
{
	char * tmpString1 = *(char* *)a;
	char * tmpString2 = *(char* *)b;
	int lengthOfString1 = strlen(tmpString1);
	int lengthOfString2 = strlen(tmpString2);
	int minLengthString = 0;

	while (!isNSymbol(tmpString1[lengthOfString1])) lengthOfString1--;
	while (!isNSymbol(tmpString2[lengthOfString2])) lengthOfString2--;

	if (lengthOfString1 <= lengthOfString2) minLengthString = lengthOfString1;
	else									minLengthString = lengthOfString2;
	bool equivalent = true;
	int firstString = 0;
	for (int i = 0; i < minLengthString; i++)
	{
		if (equivalent)
		{
			if ((unsigned char)(tmpString1[lengthOfString1 - i]) < (unsigned char)(tmpString2[lengthOfString2 - i]))
			{
				firstString = -1;
				equivalent = false;
			}
			else if ((unsigned char)(tmpString1[lengthOfString1 - i]) > (unsigned char)(tmpString2[lengthOfString2 - i]))
			{
				firstString = 1;
				equivalent = false;
			}
		}
	}
	if (equivalent) { if (lengthOfString1 == lengthOfString2) return 0; }
	else return firstString;
}
char* * sortLineInvert(char* * arrayOfTextLines, int numberOfLines)
{
	char * *textLines = (char * *)calloc(numberOfLines, sizeof(char *));
	memcpy(textLines, arrayOfTextLines, sizeof(char * *)*numberOfLines);
	qsort(textLines, numberOfLines, sizeof(char* *), compareInverString);
	return textLines;
}

char* * sortLineAlphabet(char* * arrayOfTextLines, int numberOfLines)
{
	char * *textLines = (char * *)calloc(numberOfLines, sizeof(char *));
	memcpy(textLines, arrayOfTextLines, sizeof(char * *)*numberOfLines);
	qsort(textLines, numberOfLines, sizeof(char* *), compareString);
	return textLines;
}
int compareString(const void * a, const void * b) 
{
	return (strcmp(*(const char* *)a, * (const char* *)b));
}

int countLine(char *text,int numberOfcharacter)
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

char* * partitionToLine(char *text, int textLength, int numbersOfLine)
{
	char *tmpText = text;
	char * * linesOfText = (char * *)calloc(numbersOfLine, sizeof(char *));
	bool isLineEnd = true;
	int numberOfLine = 0;
	linesOfText[numberOfLine] =tmpText;
	numberOfLine++;
	for (int i = 0; i < textLength; i++)
	{
		isLineEnd = false;
		if (tmpText[i] == '\n')
		{
			tmpText[i] = '\0';
			linesOfText[numberOfLine] = &tmpText[i+1];
			numberOfLine++;
		}
	}
	return linesOfText;
}

char * readStringFromFile(int *textLength, int *errorNumb)
{
	FILE *f = fopen("onegin.txt", "r");
	if (!(f == NULL))
	{
		*textLength = filelength(fileno(f));
		char *buff = (char *)calloc(*textLength, sizeof(textLength));
		fread(buff, *textLength, sizeof(char), f);
		fclose(f);
		*errorNumb = 0;
		return buff;
	}
	else
	{
		*errorNumb = -1;
		return NULL;
	}
}