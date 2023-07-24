#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

#include "fileHelper.h"


int	 writeStringToFile(const char* str, FILE* fp,const char* msg)
{
	int length = (int)strlen(str);
	length++;
	if (!writeIntToFile(length, fp,msg))
		return 0;

	if (!writeCharsToFile(str, length, fp, msg))
		return 0;


	return 1;
}

int	 writeCharsToFile(const char* arr, int size, FILE* fp, const char* msg)
{
	if (fwrite(arr, sizeof(char), size, fp) != size)
	{
		puts(msg);
		return 0;
	}
	return 1;

}

int	 writeIntToFile(int val, FILE* fp, const char* msg)
{
	if (fwrite(&val, sizeof(int), 1, fp) != 1)
	{
		puts(msg);
		return 0;
	}
	return 1;
}

char* readStringFromFile(FILE* fp, const char* msg)
{
	char* str;
	int length;
	if (!readIntFromFile(&length, fp,msg))
		return NULL;
	str = (char*)malloc((length) * sizeof(char));
	if (!str)
	{
		puts(msg);
		return NULL;
	}
	if (fread(str, sizeof(char), length, fp) != length)
	{
		free(str);
		puts(msg);
		return NULL;
	}
	return str;
}

int readFixSizeStrFromFile(char* arr,FILE* fp, const char* msg)
{
	int len;
	if (!readIntFromFile(&len, fp, msg))
		return 0;
	
	if (!readCharsFromFile(arr, len, fp, msg))
		return 0;

	return 1;
}

int	 readCharsFromFile(char* arr, int length, FILE* fp, const char* msg)
{
	if (fread(arr, sizeof(char), length, fp) != length)
	{
		puts(msg);
		return 0;
	}
	return 1;
}

int	  readIntFromFile(int* pVal, FILE* fp, const char* msg)
{
	if (fread(pVal, sizeof(int), 1, fp) != 1)
	{
		puts(msg);
		return 0;
	}
	return 1;

}


char* readDynStringFromTextFile(FILE* fp)
{
	char temp[MAX_STR_LEN];
	myGets(temp, sizeof(temp), fp);
	return getDynStr(temp);
}

int readStringAsChars(char* str, FILE* fp, int len)
{
	for (int i = 0;i < len;i++)
		if (fread(&str[i], sizeof(char), 1, fp) != 1)
			return 0;
	return 1;
}

int writeStringAsChars(const char* str, FILE* fp, int len)
{
	for (int i = 0;i < len;i++)
		if (fwrite(&str[i], sizeof(char), 1, fp) != 1)
			return 0;
	return 1;
}

void getTheProductBarcodeFromBits(int* pVal, BYTE* data, int firstRead)
{
	pVal[0] = (data[0] >> 2);
	pVal[1] = ((data[0] & 0x3) << 4 | data[1] >> 4);
	pVal[2] = ((data[1] & 0xf) << 2 | data[2] >> 6);
	if (firstRead)
	{
		pVal[3] = data[2] & 0x3f;
	}
}

void convertValuesToBarcode(char* pBarcode, int* pVal,int len)
{
	for (int i = 0;i < len;i++)
		pBarcode[i] = fixLoadedBarcodeChar(pVal[i]);
	pBarcode[len] = '\0';
}

char fixLoadedBarcodeChar(int val)
{
	if (val < 10)
		return val + '0';
	else
		return val - 10 + 'A';
}

int changeBarcodeCharToCompFile(char val)
{
	if (isdigit(val))
		return val - '0';
	else
		return val - 'A' + 10;
}

void getCountAndPriceComp(int* pCount,float* pPrice, BYTE* data)
{
	*pCount = data[0];
	*pPrice = (data[1] >> 1);
	*pPrice /= 100;
	*pPrice += (data[1] & 0x1) << 8 | data[2];
}

void saveCountAndPriceToComp(int pCount, float pPrice, BYTE* data)
{
	int pennis,priceWithoutPennis;
	data[0] = pCount;
	pennis = (int)(pPrice * 100) % 100;
	priceWithoutPennis = pPrice;
	data[1] = pennis << 1 | priceWithoutPennis >> 8;
	data[2] = priceWithoutPennis;
}