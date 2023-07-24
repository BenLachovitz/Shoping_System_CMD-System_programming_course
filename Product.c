#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "General.h"
#include "Product.h"
#include "fileHelper.h"


#define MIN_DIG 3
#define MAX_DIG 5

void	initProduct(Product* pProduct)
{
	initProductNoBarcode(pProduct);
	getBorcdeCode(pProduct->barcode);
}

void	initProductNoBarcode(Product* pProduct)
{
	initProductName(pProduct);
	pProduct->type = getProductType();
	pProduct->price = getPositiveFloat("Enter product price\t");
	pProduct->count = getPositiveInt("Enter product number of items\t");
}

void initProductName(Product* pProduct)
{
	do {
		printf("enter product name up to %d chars\n", NAME_LENGTH );
		myGets(pProduct->name, sizeof(pProduct->name),stdin);
	} while (checkEmptyString(pProduct->name));
}

void	printProduct(const Product* pProduct)
{
	printf("%-20s %-10s\t", pProduct->name, pProduct->barcode);
	printf("%-20s %5.2f %10d\n", typeStr[pProduct->type], pProduct->price, pProduct->count);
}

int		saveProductToFile(const Product* pProduct, FILE* fp)
{
	if (fwrite(pProduct, sizeof(Product), 1, fp) != 1)
	{
		puts("Error saving product to file\n");
		return 0;
	}
	return 1;
}

int		loadProductFromFile(Product* pProduct, FILE* fp)
{
	if (fread(pProduct, sizeof(Product), 1, fp) != 1)
	{
		puts("Error reading product from file\n");
		return 0;
	}
	return 1;
}

int		loadProductFromCompFile(Product* pProduct, FILE* fp)
{
	BYTE data[3];
	int val[7];
	int nameLen;
	if (fread(&data, sizeof(BYTE), 3, fp) != 3)
		return 0;	
	getTheProductBarcodeFromBits(val, data, 1);

	if (fread(&data, sizeof(BYTE), 3, fp) != 3)
		return 0;
	getTheProductBarcodeFromBits(val + 4, data, 0);

	convertValuesToBarcode(pProduct->barcode, val,BARCODE_LENGTH);

	nameLen = (data[2] >> 2) & 0xf;
	pProduct->type = data[2] & 0x3;
	if (!readStringAsChars(pProduct->name, fp, nameLen))
		return 0;
	pProduct->name[nameLen] = '\0';

	if (fread(&data, sizeof(BYTE), 3, fp) != 3)
		return 0;
	getCountAndPriceComp(&pProduct->count,&pProduct->price, data);
	return 1;
}

int		saveProductToCompFile(const Product* pProduct, FILE* fp)
{
	BYTE data[3];
	int nameLen = strlen(pProduct->name);
	int val[7];
	for (int i = 0;i < BARCODE_LENGTH;i++)
		val[i] = changeBarcodeCharToCompFile(pProduct->barcode[i]);
	data[0] = val[0] << 2 | val[1] >> 4;
	data[1] = val[1] << 4 | val[2] >> 2;
	data[2] = val[2] << 6 | val[3];
	if (fwrite(&data, sizeof(BYTE), 3, fp) != 3)
		return 0;
	data[0] = val[4] << 2 | val[5] >> 4;
	data[1] = val[5] << 4 | val[6] >> 2;
	data[2] = val[6] << 6 | nameLen << 2 | pProduct->type;
	if (fwrite(&data, sizeof(BYTE), 3, fp) != 3)
		return 0;
	if (!writeStringAsChars(pProduct->name, fp, nameLen))
		return 0;
	saveCountAndPriceToComp(pProduct->count, pProduct->price, data);
	if (fwrite(&data, sizeof(BYTE), 3, fp) != 3)
		return 0;
	return 1;
}

void getBorcdeCode(char* code)
{
	char temp[MAX_STR_LEN];
	char msg[MAX_STR_LEN];
	sprintf(msg,"Code should be of %d length exactly\n"
				"UPPER CASE letter and digits\n"
				"Must have %d to %d digits\n"
				"First and last chars must be UPPER CASE letter\n"
				"For example A12B40C\n",
				BARCODE_LENGTH, MIN_DIG, MAX_DIG);
	int ok = 1;
	int digCount = 0;
	do {
		ok = 1;
		digCount = 0;
		printf("Enter product barcode "); 
		getsStrFixSize(temp, MAX_STR_LEN, msg);
		if (strlen(temp) != BARCODE_LENGTH)
		{
			puts(msg);
			ok = 0;
		}
		else {
			//check and first upper letters
			if(!isupper(temp[0]) || !isupper(temp[BARCODE_LENGTH-1]))
			{
				puts("First and last must be upper case letters\n");
				ok = 0;
			} else {
				for (int i = 1; i < BARCODE_LENGTH - 1; i++)
				{
					if (!isupper(temp[i]) && !isdigit(temp[i]))
					{
						puts("Only upper letters and digits\n");
						ok = 0;
						break;
					}
					if (isdigit(temp[i]))
						digCount++;
				}
				if (digCount < MIN_DIG || digCount > MAX_DIG)
				{
					puts("Incorrect number of digits\n");
					ok = 0;
				}
			}
		}
		
	} while (!ok);

	strcpy(code, temp);
}


eProductType getProductType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofProductType; i++)
			printf("%d for %s\n", i, typeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofProductType);
	getchar();
	return (eProductType)option;
}

const char* getProductTypeStr(eProductType type)
{
	if (type < 0 || type >= eNofProductType)
		return NULL;
	return typeStr[type];
}

int		isProduct(const Product* pProduct, const char* barcode)
{
	if (strcmp(pProduct->barcode, barcode) == 0)
		return 1;
	return 0;
}

int		compareProductByBarcode(const void* var1, const void* var2)
{
	const Product* pProd1 = (const Product*)var1;
	const Product* pProd2 = (const Product*)var2;

	return strcmp(pProd1->barcode, pProd2->barcode);
}


void	updateProductCount(Product* pProduct)
{
	int count;
	do {
		printf("How many items to add to stock?");
		scanf("%d", &count);
	} while (count < 1);
	pProduct->count += count;
}


void	freeProduct(Product* pProduct)
{
	//nothing to free!!!!
}