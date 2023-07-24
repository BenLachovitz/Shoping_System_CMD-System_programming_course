#pragma once
#include "Address.h"
#include "Customer.h"
#include "Product.h"
#include "ShoppingCart.h"
#include "GeneralList.h"

typedef enum { eNone, eName, eTime, eSpend, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt] = {"None","Name", "Shope Times" ,
		"Money Spent"};


typedef struct
{
	char*		name;
	Address		location;
	Customer*	customerArr;
	int			customerCount;
	eSortOption	sortOpt;
	LIST		productList;
}SuperMarket;


int		initSuperMarket(SuperMarket* pMarket, const char* fileName, const char* customersFileName,int isComp);
void	printSuperMarket(const SuperMarket* pMarket);
int		addProduct(SuperMarket* pMarket);
int		insertNewProductToList(LIST* pProductList, Product* pProduct);
int		addNewProduct(SuperMarket* pMarket, const char* barcode);
int		addCustomer(SuperMarket* pMarket);
int		isCustomerInMarket(SuperMarket* pMarket, Customer* pCust);
int		doShopping(SuperMarket* pMarket);
void	handleCustomerStillShoppingAtExit(SuperMarket* pMarket);
Customer*	doPrintCart(SuperMarket* pMarket);
int		doPayment(SuperMarket* pMarket);
Customer*		getCustomerShopPay(SuperMarket* pMarket);
void fillCart(SuperMarket* pMarket, ShoppingCart* pCart);

eSortOption showSortMenu();
void	sortCustomers(SuperMarket* pMarket);
void	findCustomer(const SuperMarket* pMarket);
void*	getCompareFunction(eSortOption sort);


void	printProductByType(SuperMarket* pMarket);
void	printAllProducts(const SuperMarket* pMarket);
void	printAllCustomers(const SuperMarket* pMarket);

Product* getProductByBarcode(SuperMarket* pMarket, const char* barcode);
Product* getProductFromUser(SuperMarket* pMarket, char* barcode);
void	getUniquBarcode(char* barcode, SuperMarket* pMarket);
Customer* FindCustomerByName(SuperMarket* pMarket, const char* name);

Customer* getCustomerWhoShop(SuperMarket* pMarket);
Product* getProductAndCount(SuperMarket* pMarket, int* pCount);
int		getNumOfProductsInList(const SuperMarket* pMarket);
void	freeMarket(SuperMarket* pMarket);

int loadProductListFromCompFile(SuperMarket* pMarket, FILE* fp, int prodCount);
int saveProductListToCompFile(const SuperMarket* pMarket, FILE* fp);

