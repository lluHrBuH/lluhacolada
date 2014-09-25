#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <process.h>
#include <math.h>
#include <memory.h>
#include <float.h>


#define MAX_PRIME 65000
#ifdef _DEBUG
#define DBG printf("#");
#else
#define DBG if(0)
#endif 

#define CHECKISALPHABET(cond) ((65<=(int)(cond) && (int)(cond)<=90)||(97<=(int)(cond)&&(int)(cond)<=122))
#define SQR(cond) ((cond)*(cond))

void Task_4C_InvertWords();
void Task_1C_Weighting();
bool CheckWeight(int n);
void Task_3C_SumOf_4_Squares();
void PrimeNumberMassGenerator(int primeNumber[]);
void Task_2C_NPrimeNumber();
void Task_6C_NumberOfSquareFree();
void Task_8B_IsSquare();
int is_square(int n);

int main()
{
	int numberOfProblem = -1;
//	DBG printf("Enter number of problem (V1C = 1), (V4C = 2): \n");
// Task_4C_InvertWords();
//	weighting();
//	Task_3C_SumOf_4_Squares();	
//	Task_2C_NPrimeNumber();
//	Task_6C_NumberOfSquareFree();
	Task_8B_IsSquare();
	system("pause>>void");
	return 0;
}

void Task_8B_IsSquare()
{
	int n;
	scanf("%d", &n);
	int numbers[100];
	for (int i = 0; i < n; i++)
	{
		scanf("%d",&numbers[i]);
	}
	for (int i = 0; i < n; i++)
	{
		if (is_square(numbers[i]))
		{
			printf("%d ", numbers[i]);
		}
	}
}
int is_square(int n)
{
	if ((n - SQR((int)sqrt((double)n))) <= DBL_EPSILON) return 1;
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
	scanf("%d", &n);
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
	printf("%d", numberOfElement-1);
}

void Task_1C_Weighting()
{
	int n = 0;
	scanf("%d", &n);
	printf("%d", CheckWeight(n));
	
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
}

void Task_3C_SumOf_4_Squares()
{
	int N, a, b, c, d;
	bool solution = false;

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
		printf("%d %d %d %d", a, b, c, d);
	}
}