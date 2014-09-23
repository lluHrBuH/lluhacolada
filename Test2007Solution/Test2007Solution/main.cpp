#include <stdio.h>
#include <process.h>
#define CHECKISALPHABET(cond) ((65<=(int)(cond) && (int)(cond)<=90)||(97<=(int)(cond)&&(int)(cond)<=122))

void InvertWords();
void weighting();
bool CheckWeight(int n);


int main()
{
	int numberOfProblem;
//	scanf("%d", numberOfProblem);
//	InvertWords(); - WORKED
	weighting();
	system("pause>>void");
	return 0;
}
void weighting()
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

void InvertWords()
{
	bool word = false;
	char str[1000];
	char c;
	int wordlength[2][1000];
	int numbOfInpCharacter = 0;
	int numberOfWords = 0;
	while ((c = getchar()) != '\n')
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
	if (word) { wordlength[1][numberOfWords] = numbOfInpCharacter; numberOfWords++; }
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
	system("pause>>void");
}