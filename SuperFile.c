#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Address.h"
#include "General.h"
#include "fileHelper.h"
#include "SuperFile.h"
#include "myMacros.h"

int loadSuperMarketFromSelectedType(SuperMarket* pMarket, const char* fileName,
	const char* customersFileName,int isComp)
{
	if (isComp == 0)
	{
		if (!loadSuperMarketFromFile(pMarket, fileName))
			return 0;
	}
	else
		if (!loadSuperMarketFromCompFile(pMarket, fileName))
			return 0;
	pMarket->customerArr = loadCustomerFromTextFile(customersFileName, &pMarket->customerCount);
	if (!pMarket->customerArr)
		return 0;
	return 1;
}

int saveSuperMarketFromSelectedType(SuperMarket* pMarket, const char* fileName,
	const char* customersFileName, int isComp)
{
	if (isComp == 0)
	{
		if (!saveSuperMarketToFile(pMarket, fileName))
			return 0;
	}
	else
		if (!saveSuperMarketToCompFile(pMarket, fileName))
			return 0;

	saveCustomerToTextFile(pMarket->customerArr, pMarket->customerCount, customersFileName);
	return 1;
}

int	saveSuperMarketToFile(const SuperMarket* pMarket, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	CHECK_MSG_RETURN_0(fp, "Error open supermarket file to write");

	if (!writeStringToFile(pMarket->name, fp, "Error write supermarket name\n"))
		CLOSE_RETURN_0(fp);

	if (!saveAddressToFile(&pMarket->location, fp))
		CLOSE_RETURN_0(fp);

	int count = getNumOfProductsInList(pMarket);

	if (!writeIntToFile(count, fp, "Error write product count\n"))
		CLOSE_RETURN_0(fp);

	Product* pTemp;
	NODE* pN = pMarket->productList.head.next; //first Node
	while (pN != NULL)
	{
		pTemp = (Product*)pN->key;
		if (!saveProductToFile(pTemp, fp))
			CLOSE_RETURN_0(fp);
		pN = pN->next;
	}

	fclose(fp);
	return 1;
}

int loadSuperMarketFromCompFile(SuperMarket* pMarket, const char* fileName)
{
	FILE* fp;
	BYTE data[2];
	int prodCount,nameLen;
	fp = fopen(fileName, "rb");
	CHECK_MSG_RETURN_0(fp, "Error open company file");

	if (fread(&data, sizeof(BYTE), 2, fp) != 2)
		CLOSE_RETURN_0(fp);
	prodCount = data[0]<<2 | data[1] >> 6;
	nameLen = data[1] & 0x3f;
	pMarket->name = (char*)calloc(nameLen + 1, sizeof(char));
	if (!pMarket->name)
		CLOSE_RETURN_0(fp);
	if(!readStringAsChars(pMarket->name,fp,nameLen))
		FREE_CLOSE_FILE_RETURN_0(fp, pMarket->name);

	if(!loadAddressFromCompFile(&pMarket->location, fp))
		FREE_CLOSE_FILE_RETURN_0(fp, pMarket->name);

	if (!loadProductListFromCompFile(pMarket, fp, prodCount))
	{
		freeAddress(&pMarket->location);
		L_free(&pMarket->productList, freeProduct);
		FREE_CLOSE_FILE_RETURN_0(fp, pMarket->name);
	}
	return 1;
}

int saveSuperMarketToCompFile(const SuperMarket* pMarket, const char* fileName)
{
	FILE* fp;
	BYTE data[2];

	fp = fopen(fileName, "wb");
	CHECK_MSG_RETURN_0(fp, "Error open company file");
	int prodCount = getNumOfProductsInList(pMarket);
	data[0] = (prodCount >> 2);
	data[1] = (prodCount << 6) | (strlen(pMarket->name));
	if (fwrite(&data, sizeof(BYTE), 2, fp) != 2)
		CLOSE_RETURN_0(fp);
	if (!writeStringAsChars(pMarket->name, fp, strlen(pMarket->name)))
		CLOSE_RETURN_0(fp);
	if (!saveAddressToCompFile(&pMarket->location, fp))
		CLOSE_RETURN_0(fp);
	if (!saveProductListToCompFile(pMarket, fp))
		CLOSE_RETURN_0(fp);

	fclose(fp);
	return 1;
}

#define BIN
#ifdef BIN
int	loadSuperMarketFromFile(SuperMarket* pMarket, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	CHECK_MSG_RETURN_0(fp, "Error open company file");


	pMarket->name = readStringFromFile(fp, "Error reading supermarket name\n");
	if (!pMarket->name)
		CLOSE_RETURN_0(fp);


	if (!loadAddressFromFile(&pMarket->location, fp))
		FREE_CLOSE_FILE_RETURN_0(fp, pMarket->name);

	int count;
	if (!readIntFromFile(&count, fp, "Error reading product count\n"))
		FREE_CLOSE_FILE_RETURN_0(fp, pMarket->name);

	if (count > 0)
	{
		Product* pTemp;
		for (int i = 0; i < count; i++)
		{
			pTemp = (Product*)calloc(1, sizeof(Product));
			if (!pTemp)
			{
				printf("Allocation error\n");
				L_free(&pMarket->productList, freeProduct);
				FREE_CLOSE_FILE_RETURN_0(fp, pMarket->name);
			}
			if (!loadProductFromFile(pTemp, fp))
			{
				L_free(&pMarket->productList, freeProduct);
				FREE_CLOSE_FILE_RETURN_0(fp, pMarket->name);
			}
			if (!insertNewProductToList(&pMarket->productList, pTemp))
			{
				L_free(&pMarket->productList, freeProduct);
				FREE_CLOSE_FILE_RETURN_0(fp, pMarket->name);
			}
		}
	}

	fclose(fp);
	return	1;
}
#else
int	loadSuperMarketFromFile(SuperMarket* pMarket, const char* fileName,
	const char* customersFileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open company file\n");
		return 0;
	}

	//L_init(&pMarket->productList);


	pMarket->name = readStringFromFile(fp, "Error reading supermarket name\n");
	if (!pMarket->name)
	{
		fclose(fp);
		return 0;
	}

	if (!loadAddressFromFile(&pMarket->location, fp))
	{
		free(pMarket->name);
		fclose(fp);
		return 0;
	}

	fclose(fp);

	loadProductFromTextFile(pMarket, "Products.txt");


	pMarket->customerArr = loadCustomerFromTextFile(customersFileName, &pMarket->customerCount);
	if (!pMarket->customerArr)
		return 0;

	return	1;

}
#endif

int		loadProductFromTextFile(SuperMarket* pMarket, const char* fileName)
{
	FILE* fp;
	//L_init(&pMarket->productList);
	fp = fopen(fileName, "r");
	int count;
	fscanf(fp, "%d\n", &count);


	//Product p;
	Product* pTemp;
	for (int i = 0; i < count; i++)
	{
		pTemp = (Product*)calloc(1, sizeof(Product));
		myGets(pTemp->name, sizeof(pTemp->name), fp);
		myGets(pTemp->barcode, sizeof(pTemp->barcode), fp);
		fscanf(fp, "%d %f %d\n", &pTemp->type, &pTemp->price, &pTemp->count);
		insertNewProductToList(&pMarket->productList, pTemp);
	}

	fclose(fp);
	return 1;
}