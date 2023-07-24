#pragma once
#include "ShoppingCart.h"

typedef struct
{
	char*			name;
	int				shopTimes; 
	float			totalSpend;
	ShoppingCart*	pCart;
}Customer;

int		initCustomer(Customer* pCustomer);
void	printCustomer(const Customer* pCustomer);

int		isCustomer(const Customer* pCust, const char* name);

void	pay(Customer* pCustomer);

int		compareCustomerByName(const void* var1, const void* var2);
int		compareCustomerByShopTime(const void* var1, const void* var2);
int		compareCustomerBySpent(const void* var1, const void* var2);


int	saveCustomerToTextFile(const Customer* arr, int  customerCount, const char* customersFileName);
Customer*	loadCustomerFromTextFile(const char* customersFileName, int* pCount);
void	freeCustomer(Customer* pCust);



