#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "General.h"



char* getStrExactLength(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	getsStrFixSize(temp, MAX_STR_LEN, msg);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

char*	getsStrFixSize(char* buffer, int size, const char* msg)
{
	puts(msg);
	return myGets(buffer, size,stdin);
}

char*  myGets(char* buffer, int size, FILE* source)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, source))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char**	splitCharsToWords(char* str, int* pCount, const char* del, int* pTotalLength)
{
	char* word;
	int count = 0;
	char* temp = _strdup(str);
	*pTotalLength = 0;
	char** wordsArray = NULL;

	word = strtok(temp, del);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray, (count + 1) * sizeof(char*));
		if (!wordsArray)
			return 0;
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, del);
	}
	*pCount = count;
	free(temp);
	return wordsArray;
}


float	getPositiveFloat(const char* msg)
{
	float val;
	do {
		puts(msg);
		scanf("%f", &val);
	} while (val < 0);
	return val;
}

int		getPositiveInt(const char* msg)
{
	int val;
	do {
		puts(msg);
		scanf("%d", &val);
	} while (val < 0);
	return val;
}

int		countCharInString(const char* str, char tav)
{
	int count = 0;
	while (*str)
	{
		if (*str == tav)
			count++;
		str++;
	}
	return count;
}

void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element))
{
	for (int i = 0; i < size; i++)
		func((char*)(arr)+i * typeSize);

}

int		checkEmptyString(char* str)
{
	while (*str)
	{
		if (!isspace(*str))
			return 0;
		str++;
	}
	return 1;
}

void printMessage(const char* str, ...)
{
	va_list words;
	va_start(words, str);
	const char* curr = str;
	while (curr)
	{
		printf("%s ", curr);
		curr = va_arg(words, char*);
	}
	printf("\b \n");
}