#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Customer.h"
#include "General.h"
#include "fileHelper.h"

int	initCustomer(Customer* pCustomer)
{
	do {
		pCustomer->name = getStrExactLength("Enter customer name\n");
		if (!pCustomer->name)
			return 0;
	} while (checkEmptyString(pCustomer->name));
	
	pCustomer->shopTimes = 0;
	pCustomer->totalSpend = 0;
	pCustomer->pCart = NULL;
	return 1;
}

void	printCustomer(const Customer* pCustomer)
{
	printf("Name: %s\t", pCustomer->name);
	printf("has shoped %d times spent:%.2f IS\t", pCustomer->shopTimes,
		pCustomer->totalSpend);
	if (pCustomer->pCart == NULL)
		printf("Shopping cart is empty!\n");
	else 
	{
		printf("Doing shopping now!!!\n");
	}
}


void	pay(Customer* pCustomer)
{
	if (!pCustomer->pCart)
		return;
	printf("---------- Cart info and bill for %s ----------\n", pCustomer->name);
	float p = printShoppingCart(pCustomer->pCart);
	printf("!!! --- Payment was recived!!!! --- \n");
	pCustomer->shopTimes++;
	pCustomer->totalSpend += p;
	freeShoppingCart(pCustomer->pCart);
	free(pCustomer->pCart);
	pCustomer->pCart = NULL;
}


int isCustomer(const Customer* pCust, const char* name)
{
	if (strcmp(pCust->name, name) == 0)
		return 1;
	return 0;
}

int		compareCustomerByName(const void* var1, const void* var2)
{
	const Customer* pCust1 = (const Customer*)var1;
	const Customer* pCust2 = (const Customer*)var2;


	return strcmp(pCust1->name, pCust2->name);

}

int		compareCustomerByShopTime(const void* var1, const void* var2)
{
	const Customer* pCust1 = (const Customer*)var1;
	const Customer* pCust2 = (const Customer*)var2;


	return pCust1->shopTimes -  pCust2->shopTimes;
}

int		compareCustomerBySpent(const void* var1, const void* var2)
{
	const Customer* pCust1 = (const Customer*)var1;
	const Customer* pCust2 = (const Customer*)var2;

	if (pCust1->totalSpend > pCust2->totalSpend)
		return 1;

	if (pCust1->totalSpend < pCust2->totalSpend)
		return -1;

	return 0;
}



int	saveCustomerToTextFile(const Customer* customerArr,int  customerCount,const char* customersFileName)
{
	FILE* fp;

	fp = fopen(customersFileName, "w");
	if (!fp) {
		printf("Error open customers file to write\n");
		return 0;
	}

	fprintf(fp, "%d\n", customerCount);
	for (int i = 0; i < customerCount; i++)
	{
		fprintf(fp, "%s\n%d %.2f\n", customerArr[i].name, customerArr[i].shopTimes, 
			customerArr[i].totalSpend);
	}
	fclose(fp);
	return 1;
}

Customer*	loadCustomerFromTextFile(const char* customersFileName,int* pCount)
{
	FILE* fp;

	fp = fopen(customersFileName, "r");
	if (!fp) {
		printf("Error open customers file to write\n");
		return NULL;
	}
	Customer* customerArr = NULL;
	int customerCount;
	fscanf(fp, "%d\n", &customerCount);
	if (customerCount > 0)
	{
		customerArr = (Customer*)calloc(customerCount , sizeof(Customer)); //cart will be NULL!!!
		if (!customerArr)
		{
			fclose(fp);
			return NULL;
		}
		for (int i = 0; i < customerCount; i++)
		{
			customerArr[i].name = readDynStringFromTextFile(fp);
			if (!customerArr[i].name)
			{
				for (int j = 0; j < i; j++)
					free(customerArr[j].name);
				free(customerArr);
				fclose(fp);
				return NULL;
			}
			fscanf(fp, "%d %f", &customerArr[i].shopTimes, &customerArr[i].totalSpend);
			fgetc(fp); //clean the enter
		}
	}

	fclose(fp);
	*pCount = customerCount;
	return customerArr;
}





void	freeCustomer(Customer* pCust)
{
	if (pCust->pCart)
		pay(pCust); //will free every thing
	free(pCust->name);
}