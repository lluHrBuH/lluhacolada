//{=================================================================================
//! @file    main.cpp
//! @date    2014.09.26 01:11
//! @author  Vlad Bondarenko <lluhacolada@gmail.com>
//!
//! Home work from 22.09.2014
//}=================================================================================
#include <stdio.h>
#include <process.h>
#include <math.h>
#include <memory.h>
#include <float.h>


#ifdef _DEBUG
	#define DBG printf("#"),
#else
	#define DBG if(0)
#endif 

#ifndef NDEBUG
#define ASSERT(cond)	 if(!cond)\
							printf("Fail: %s, int %s %d %s\n",\
							#cond,__FILE__,__LINE__,\
							__FUNCTION__);
#else
#define ASSERT(cond) ;
#endif

//Check symbol is alphabet (using ASCII code)
#define CHECKISALPHABET(cond) ((65<=(int)(cond) && (int)(cond)<=90)||(97<=(int)(cond)&&(int)(cond)<=122))

#define SQR(cond) ((cond)*(cond))

//Max prime number < 2^16
#define MAX_PRIME 65521

//{=================================================================================
//! SelectTask - Selection problem to solution       
//}=================================================================================
int SelectTask();

//{=================================================================================
//! Task_4C_InvertWords - invert all worlds in string except symbols. 
//!
//! @note  Input release inside function       
//}=================================================================================
void Task_4C_InvertWords();

//{=================================================================================
//! Task_1C_Weighting -  check, is posible to weighting with weights (1, 4^1, 4^2 ...)
//! 
//! @note  Input release inside function                
//}=================================================================================
void Task_1C_Weighting();
//{=================================================================================
//! CheckWeight - main function of Task_1C_Weighting
//!
//! @param      n	what weight it is necessary to weigh	 
//!
//! @return         True - when possible; False - when inpossible         
//}=================================================================================
bool CheckWeight(int n);

//{=================================================================================
//! Task_3C_SumOf_4_Squares - decomposition number into four square      
//!
//! @note  Input release inside function          
//}=================================================================================
void Task_3C_SumOf_4_Squares();

//{=================================================================================
//! Task_2C_NPrimeNumber - calculation of N-th prime number        
//!
//! @note  Input release inside function              
//}=================================================================================
void Task_2C_NPrimeNumber();
//{=================================================================================
//! PrimeNumberMassGenerator - Generator prime number (using Sieve of Eratosthenes)
//!
//! @param      primeNumber[] Array which records prime number
//!
//! @param[out] primeNumber[] Array with prime number until 65521       
//}=================================================================================
void PrimeNumberMassGenerator(int primeNumber[]);

//{=================================================================================
//! Task_3B_PrintPrimeNumber - Print N prime numbers
//!
//! @note    Input release inside function         
//}=================================================================================
void Task_3B_PrintPrimeNumber();

//{=================================================================================
//! Task_6C_NumberOfSquareFree - Finding the numbers of divisors which are not squares        
//!
//! @note  Input release inside function           
//}=================================================================================
void Task_6C_NumberOfSquareFree();

//{=================================================================================
//! Task_8B_IsSquare - Check number is square       
//!
//! @note  Input release inside function           
//}=================================================================================
void Task_8B_IsSquare();
//{=================================================================================
//! is_square - function check checks whether the number is a perfect square
//!
//! @param  n	number to check  
//!
//! @return		True - if number is a perfect square; False - other       
//}=================================================================================
int is_square(int n);

//{=================================================================================
//! Task_6D_NumbersOfGoodWords - Calculate the number of binary words of length n in 
//!								which exactly k "1", and no two consecutive "1"
//!
//! @note   Input release inside function            
//}=================================================================================
void Task_1D_NumbersOfGoodWords();
//{=================================================================================
//! numberOfGoodWords - function Calculate the number of binary words of length n in 
//!								which exactly k "1", and no two consecutive "1"
//! @param      int n			length of binary words
//! @param      int k			number of k "1" in words
//! @param      int lastByte	last found byte in words 
//! @param      int * result	
//!
//! @note           
//}=================================================================================
void numberOfGoodWords(int n, int k, int lastByte, int * result);

//{=================================================================================
//! Task_10C_SumOfTwoBigByteNumbers - Summa of two big byte numbers
//!
//! @note	Input release inside function        
//}=================================================================================
void Task_10C_SumOfTwoBigByteNumbers();

//{=================================================================================
//! Task_5B_SummaDividers - Summa of all dividers of number
//!
//! @note	Input release inside function              
//}=================================================================================
void Task_5B_SummaDividers();

int main()
{
	int result = 0;
	result = SelectTask();
	
	if (result == 0)
	{
		DBG printf("Goodbye. Have a nice day/night :)\n");
		DBG system("pause");
		return 0;
	}
	else
	{
		DBG printf("An error has occurred! Try again later.");
		DBG system("pause>>void");
		return -1;
	}
	
	
}

int SelectTask()
{
	int numberOfTask = -1;
	printf("Write number of task to run:\n\
		   1 - Task_1C_Weighting\n\
		   2 - Task_2C_NPrimeNumber\n\
		   3 - Task_3C_SumOf_4_Squares\n\
		   4 - Task_4C_InvertWords\n\
		   5 - Task_6C_NumberOfSquareFree\n\
		   6 - Task_8B_IsSquare\n\
		   7 - Task_1D_NumbersOfGoodWords\n\
		   8 - Task_3B_PrintPrimeNumber\n\
		   9 - Task_10C_SumOfTwoBigByteNumbers\n\
		   10 - Task_5B_SummaDividers\n");
	scanf("%d", &numberOfTask);
	switch (numberOfTask)
	{
	case 	1: {DBG printf("Your chose: Task_1C_Weighting\n");
							Task_1C_Weighting(); 
							break; }
	case 	2: {DBG printf("Your chose: Task_2C_NPrimeNumber\n"); 
							Task_2C_NPrimeNumber(); 
							break; }
	case	3: {DBG printf("Your chose: Task_3C_SumOf_4_Squares\n"); 
							Task_3C_SumOf_4_Squares();
							break; }
	case	4: {DBG printf("Your chose: Task_4C_InvertWords\n");
							Task_4C_InvertWords();
							break; }
	case	5: {DBG printf("Your chose: Task_6C_NumberOfSquareFree\n"); 
							Task_6C_NumberOfSquareFree();
							break; }
	case	6: {DBG printf("Your chose: Task_8B_IsSquare\n"); 
							Task_8B_IsSquare(); 
							break; }
	case	7: {DBG printf("Your chose: Task_1D_NumbersOfGoodWords\n");
							Task_1D_NumbersOfGoodWords(); break; }
	case    8: {DBG printf("Your chose: Task_3B_PrintPrimeNumber\n"); 
							Task_3B_PrintPrimeNumber(); 
							break; }
	case	9: {DBG printf("Your chose: Task_10C_SumOfTwoBigByteNumbers\n"); Task_10C_SumOfTwoBigByteNumbers(); break; }
	case   10: {DBG printf("Your chose: Task_5B_SummaDividers\n");  Task_5B_SummaDividers(); break; }
	default: return(-1);
	}
	return 0;
}

void Task_5B_SummaDividers()
{
	int n;
	DBG printf("Enter number to calculate summa dividers:\n");
	scanf("%d", &n);
	long summa = 1;
	for (int i = 2; i <= n; i++)
	{
		if (n % i == 0)
		{
			summa += i;
		}
	}
	DBG printf("Summa of dividers:\n");
	printf("%d\n", summa);
}

void Task_10C_SumOfTwoBigByteNumbers()
{
	int a[2000];
	int b[2000];
	memset(a, 0, 2000 * sizeof(int));
	memset(b, 0, 2000 * sizeof(int));
	int summa[1000];
	int lengthA = 0;
	int lengthB = 0;
	char c;
	scanf("%c", &c);
	DBG printf("Enter first number:\n");
	while ((scanf("%c", &c)) && (c != '\n'))
	{
		if (int(c) == 48)	a[lengthA+1000] = 0;
		else				a[lengthA+1000] = 1;
		lengthA++;
	}
	DBG printf("Enter second number:\n");
	while ((scanf("%c", &c)) && (c != '\n'))
	{
		if (int(c) == 48)	b[lengthB+1000] = 0;
		else				b[lengthB+1000] = 1;
		lengthB++;
	}
	int rank = 0;
	int length = 0;
	if (lengthA >= lengthB) length = lengthA;
	else					length = lengthB;
	for (int i = 1; i <= length; i++)
	{
		if ((a[1000 + lengthA - i] == 1) && (b[1000 + lengthB - i] == 1))
		{
			if (!rank)	summa[length - i] = 0;
			else		summa[length - i] = 1;
			rank = 1;
		}
		else
		{
			if (rank && ((a[1000 + lengthA - i] == 1) || (b[1000 + lengthB - i] == 1)))
			{
				summa[length - i] = 0;
				rank = 1;
			}
			else
			{
				if ((rank || ((a[1000 + lengthA - i] == 1) || (b[1000 + lengthB - i] == 1))))		summa[length - i] = 1;
				else																				summa[length - i] = 0;
				rank = 0;
			}
		}
	}
	DBG printf("Summa of numbers:\n");
	if (rank) printf("1");
	for (int i = 0; i < length; i++)
		printf("%d", summa[i]);
	printf("\n");
}

void Task_3B_PrintPrimeNumber()
{
	int n;
	int PrimeNumber[MAX_PRIME];
	PrimeNumberMassGenerator(PrimeNumber);
	DBG printf("Enter number of prime numbers to calculate:\n");
	scanf("%d", &n);
	int numberToCalculate[10000];
	DBG printf("Enter number of prime number to calculate:\n");
	for (int i = 0; i < n; i++)
	{	
		scanf("%d", &numberToCalculate[i]);
	}
	DBG printf("Here this number:\n");
	for (int i = 0; i < n; i++)
	{
		int numberOfElement = 2;
		int numberOfPrime = numberToCalculate[i];
		while (numberOfPrime > 0)
		{
			if (PrimeNumber[numberOfElement] == 0)
			{
				numberOfPrime--;
			}
			numberOfElement++;
		}
		printf("%d ", numberOfElement - 1);
	}
}

void Task_1D_NumbersOfGoodWords()
{
	int n, k;
	DBG printf("Enter length of words N, and number K of '1' \n");
	scanf("%d %d", &n, &k);
	int result = 0;
	numberOfGoodWords(n, k, 0, &result);
	DBG printf("Number of binary words:\n");
	printf("%d\n", result);
}
void numberOfGoodWords(int n, int k, int lastByte, int * result)
{
	if ((n == 0) && (k == 0)) *result = *result + 1;
	if (n > 0)
	{
		numberOfGoodWords(n-1, k, 0, result);
		if ((k > 0) && (lastByte == 0)) numberOfGoodWords(n - 1, k - 1, 1, result);
	}
	
}

void Task_8B_IsSquare()
{
	int n;
	bool isPerfectSquareExist = false;
	bool isDebuggWord = false;
	DBG printf("Enter the number of numbers check:\n");
	scanf("%d", &n);
	int numbers[100];
	DBG printf("Enter N number to check for perfect squares:\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%d",&numbers[i]);
	}
	for (int i = 0; i < n; i++)
	{
		if (is_square(numbers[i]))
		{
			isPerfectSquareExist = true;
			if (!isDebuggWord)
			{
				DBG printf("Perfect squares number:\n");
				isDebuggWord = true;
			}
			printf("%d ", numbers[i]);
		}
	}
	
	if (!isPerfectSquareExist)
	{
		DBG printf("No perfect squares number found\n");
	}
	else
	{
		printf("\n");
	}
}
int is_square(int n)
{
	if (n == SQR((int)sqrt((double)n))) return 1;
	else return 0;
}

void Task_6C_NumberOfSquareFree()
{
	int n;
	int Number[200];
	int PrimeNumber[MAX_PRIME+100];
	PrimeNumberMassGenerator(PrimeNumber);
	bool noFree = false;
	bool Free = false;
	DBG printf("Enter a number of numbers to check is square free");
	scanf("%d", &n);
	DBG printf("Enter numbers to check:");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &Number[i]);
	}
	int numberOfSquareFree[65535];
	int countOfSqureFree = 0;
	for (int i = 0; i < n; i++)
	{
		int tmpNumber = Number[i];
		int PrimeDivisors [MAX_PRIME];
		memset(PrimeDivisors, 0, MAX_PRIME*sizeof(int));
		int numberOfPrimeNumber = 2;
		while (tmpNumber > 1)
		{
			if (PrimeNumber[numberOfPrimeNumber] == 0)
			{
				while (tmpNumber % numberOfPrimeNumber == 0)
				{
					PrimeDivisors[numberOfPrimeNumber]++;
					if (PrimeDivisors[numberOfPrimeNumber] > 1) noFree = true;
					tmpNumber = tmpNumber / numberOfPrimeNumber;
				}
			}
			numberOfPrimeNumber++;
			if (noFree)
			{
				break;
			}
		}
		if (!noFree) { numberOfSquareFree[countOfSqureFree] = Number[i]; countOfSqureFree++; }
		else noFree = false;
	}
	if (countOfSqureFree > 0) DBG printf("Numbers, square free");
	for (int i = 0; i < countOfSqureFree; i++)
	{
		printf("%d ", numberOfSquareFree[i]);
	}
}

void PrimeNumberMassGenerator(int primeNumber[])
{
	memset(primeNumber, 0,  MAX_PRIME*sizeof(int));
	primeNumber[1] = 1;
	int primeCounter = 2;
	while (primeCounter < MAX_PRIME)
	{
		if (primeNumber[primeCounter] == 0)
		{
			int i = 2;
			while ((primeCounter*i) < MAX_PRIME)
			{
				primeNumber[primeCounter*i] = 1;
				i++;
			}
		}
		primeCounter++;
	}
}
void Task_2C_NPrimeNumber()
{
	int n;
	int PrimeNumber[MAX_PRIME];
	PrimeNumberMassGenerator(PrimeNumber);
	DBG printf("Enter number of prime numbers to calculate:\n");
	scanf("%d", &n);
	
	int numberOfElement=2;
	while (n>0)
	{
		if (PrimeNumber[numberOfElement]==0)
		{
			n--;
		}
		numberOfElement++;
	}
	DBG printf("Here this number:\n");
	printf("%d\n", numberOfElement-1);
}

void Task_1C_Weighting()
{
	int n = 0;
	DBG	printf("Enter a number for 'weighing':\n");
	scanf("%d", &n);
	if (CheckWeight(n))
	{
		printf("YES ");
		DBG printf("it can be weighed.\n");
	}
	else
	{
		printf("NO ");
		DBG printf("it can`t be weighed.\n");
	}
	
}
bool CheckWeight(int n)
{
	if (n > 4)
	{
		switch (n % 4)
		{
		case 0: { n = n / 4; break; }
		case 1: { n = (n - 1) / 4; break; }
		case 2: { return 0; }
		case 3: { n = (n + 1) / 4; break; }
		}
		CheckWeight(n);
	} 
	else
	{
		if (n == 2) return 0;
		else return 1;
	}
}

void Task_4C_InvertWords()
{
	bool word = false;
	char str[1000];
	char c;
	int wordlength[2][1000];
	int numbOfInpCharacter = 0;
	int numberOfWords = 0; 
	DBG printf("Enter string to invert:\n");
	scanf("%c", &c);
	while ((scanf("%c",&c)) && (c!= '\n'))
	{
		if (CHECKISALPHABET(c)) 
		{
			if (!word)
			{
				wordlength[0][numberOfWords] = numbOfInpCharacter;
				word = true;
			}
			str[numbOfInpCharacter] = c; 
		}
		else
		{
			if (word)
			{
				wordlength[1][numberOfWords] = numbOfInpCharacter-1;
				word = false;
				numberOfWords++;
			}
			str[numbOfInpCharacter] = c;
		}
		numbOfInpCharacter++;
	}
	if (word) { wordlength[1][numberOfWords] = --numbOfInpCharacter; numberOfWords++; }
	int numbOfOutputCharacter = 0;

	int numbOfOutputWord = 0;
	int i = 0;
	DBG printf("Here inverted string:\n");
	while (i<numbOfInpCharacter)
	{
		if (numberOfWords == 0)
		{
			for (i = numbOfOutputCharacter; i < numbOfInpCharacter; i++)
			{
				printf("%c", str[i]);
			}
		}
		else
		{
			for (i = numbOfOutputCharacter; i < wordlength[0][numbOfOutputWord]; i++)
			{
				printf("%c", str[i]);
				numbOfOutputCharacter++;
			}
			for (i = wordlength[1][numbOfOutputWord]; i >= wordlength[0][numbOfOutputWord]; i--)	printf("%c", str[i]);
			numberOfWords--;
			numbOfOutputCharacter = wordlength[1][numbOfOutputWord] + 1;
			numbOfOutputWord++;
		}
	}

#ifdef _DEBUG
	printf("\n");
#endif // _DEBUG
}

void Task_3C_SumOf_4_Squares()   
{
	int N, a, b, c, d;
	bool solution = false;
	DBG printf("Enter number to decompose to four squares:\n");
	scanf("%d", &N);

	for (d = ((int)(sqrt(((double)N) / 2))); d <= (int)sqrt((double)N)+1; d++)
	{
		for (c = 0; c <= d; c++)
		{
			for (b = 0; b <= c; b++)
			{
				for (a = 0; a <= b; a++)
				{
					if ((a*a)+(b*b)+(c*c)+(d*d)==N)
					{
						solution = true;
						break;
					}
				}
				if (solution) break;
			}
			if (solution) break;
		}
		if (solution) break;
	}
	if (solution)
	{
		DBG printf("Here is it (n = a^2 + b^2 + c^2 + d^2):\n");
		printf("%d %d %d %d\n", a, b, c, d);
	}
}