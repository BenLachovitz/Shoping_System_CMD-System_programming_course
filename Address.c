#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Address.h"
#include "General.h"
#include "fileHelper.h"

#define ELEMENT_SEP "#"
#define WORD_SEP "  "

int	initAddress(Address* pAd)
{
	char allData[MAX_STR_LEN];
	char** elements=NULL;
	int count;
	int ok = 1;
	int totalLength;
	char msg[MAX_STR_LEN];
	sprintf(msg, "Enter address data\nFormat: street%shouse number%scity\nstreet and city can have spaces\n", 
			ELEMENT_SEP, ELEMENT_SEP);
	do {

		getsStrFixSize(allData, sizeof(allData), msg);
		int countSep = countCharInString(allData, ELEMENT_SEP[0]);
		if (countSep > 2)
		{
			printf("Too many separators in address\n");
			ok = 0;
		} else {
			elements = splitCharsToWords(allData, &count, ELEMENT_SEP, &totalLength);
			if (!elements)
				continue;
			ok = checkElements(elements, count);
			if (!ok)
			{
				printf("!!!incorrect address format!!!\n");
				freeElements(elements, count);
			}
		}
	} while (!ok);

	//get the house number
	sscanf(elements[1], "%d", &pAd->num);
	pAd->street = fixAddressParam(elements[0]);
	if (!pAd->street)
	{
		freeElements(elements, count);
		return 0;
	}

	pAd->city = fixAddressParam(elements[2]);
	if (!pAd->city)
	{
		free(pAd->street);
		freeElements(elements, count);
		return 0;
	}

	freeElements(elements, count);
	return 1;
}

int saveAddressToFile(const Address* pAdd, FILE* fp)
{
	if (!writeIntToFile(pAdd->num, fp, "error write house number\n"))
		return 0;

	if(!writeStringToFile(pAdd->street,fp,"error write street name\n"))
		return 0;

	if (!writeStringToFile(pAdd->city, fp, "error write city name\n"))
		return 0;
	return 1;
}

int loadAddressFromFile(Address* pAdd, FILE* fp)
{
	if (!readIntFromFile(&pAdd->num, fp, "error read house number\n"))
		return 0;

	pAdd->street = readStringFromFile(fp, "error read street name\n");
	if(!pAdd->street)
		return 0;

	pAdd->city = readStringFromFile(fp, "error read city name\n");
	if(!pAdd->city)
	{
		free(pAdd->street);
		return 0;
	}

	return 1;
}

int loadAddressFromCompFile(Address* pAdd, FILE* fp)
{
	BYTE data;
	int strLen;
	if (fread(&data, sizeof(BYTE), 1, fp) != 1)
		return 0;
	pAdd->num = data;
	if (fread(&strLen, sizeof(int), 1, fp) != 1)
		return 0;
	pAdd->street = (char*)calloc(strLen + 1, sizeof(char));
	if (!pAdd->street)
		return 0;
	if (fread(pAdd->street, sizeof(char), strLen, fp) != strLen)
	{
		free(pAdd->street);
		return 0;
	}
	if (fread(&strLen, sizeof(int), 1, fp) != 1)
		return 0;
	pAdd->city = (char*)calloc(strLen + 1, sizeof(char));
	if (!pAdd->city)
	{
		free(pAdd->street);
		return 0;
	}
	if (fread(pAdd->city, sizeof(char), strLen, fp) != strLen)
	{
		free(pAdd->city);
		free(pAdd->street);
		return 0;
	}
	return 1;
}

int saveAddressToCompFile(const Address* pAdd, FILE* fp)
{
	BYTE data;
	int len;
	data = pAdd->num;
	if (fwrite(&data, sizeof(BYTE), 1, fp) != 1)
		return 0;
	len = strlen(pAdd->street);
	if (fwrite(&len, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(pAdd->street, sizeof(char), len, fp) != len)
		return 0;
	len = strlen(pAdd->city);
	if (fwrite(&len, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(pAdd->city, sizeof(char), len, fp) != len)
		return 0;
	return 1;
}

char*	fixAddressParam(char* param)
{
	char* fixParamStr;
	char** wordsArray = NULL;
	int totalLength;
	int count;

	wordsArray = splitCharsToWords(param, &count," ", &totalLength);
	if (!wordsArray)
		return NULL;
	//add size for the WORD_SEP between words and for '\0'
	size_t length = (count - 1) * strlen(WORD_SEP) + 1;
	fixParamStr = (char*)calloc(totalLength + length, sizeof(char));
	if (!fixParamStr)
	{
		freeElements(wordsArray, count);
		return NULL;
	}

	if(count == 1)
		wordsArray[0][0] = toupper(wordsArray[0][0]); //upper
	else {
		for (int i = 0; i < count - 1; i++)
		{
			wordsArray[i][0] = toupper(wordsArray[i][0]); //upper
		}
		wordsArray[count - 1][0] = tolower(wordsArray[count - 1][0]); //lower
	}
	for (int i = 0; i < count - 1; i++)
	{
		strcat(fixParamStr, wordsArray[i]);
		strcat(fixParamStr, WORD_SEP);
	}
	strcat(fixParamStr, wordsArray[count - 1]);

	freeElements(wordsArray, count);
	return fixParamStr;
}


int checkElements(char**  elements, int count)
{
	if (count != 3)
		return 0;
	//check second word is a number;
	char* streetNum = elements[1];
	while (*streetNum)
	{
		if (!isdigit(*streetNum))
			return 0;
		streetNum++;
	}

	if (checkEmptyString(elements[0]))
		return 0;
	if (checkEmptyString(elements[2]))
		return 0;

	return 1;
}

void freeElements(char**  elements, int count)
{
	for (int i = 0; i < count; i++)
		free(elements[i]);
	free(elements);
}

void printAddress(const Address* pAd)
{
	printf("%s %d, %s\n", pAd->street, pAd->num, pAd->city);
}

void	freeAddress(Address* pAd)
{
	free(pAd->city);
	free(pAd->street);
}