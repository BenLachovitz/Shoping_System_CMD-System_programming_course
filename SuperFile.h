#pragma once

#include <stdio.h>
#include "Supermarket.h"

int saveSuperMarketFromSelectedType(SuperMarket* pMarket, const char* fileName,
	const char* customersFileName, int isComp);
int		saveSuperMarketToFile(const SuperMarket* pMarket, const char* fileName);
int saveSuperMarketToCompFile(const SuperMarket* pMarket, const char* fileName);

int loadSuperMarketFromSelectedType(SuperMarket* pMarket, const char* fileName,
	const char* customersFileName, int isComp);
int		loadSuperMarketFromFile(SuperMarket* pMarket, const char* fileName);
int loadSuperMarketFromCompFile(SuperMarket* pMarket, const char* fileName);

//int		loadCustomerFromTextFile(SuperMarket* pMarket, const char* customersFileName);

int loadSuperMarketFromSelectedType(SuperMarket* pMarket, const char* fileName, 
	const char* customersFileName, int isComp);
int		loadProductFromTextFile(SuperMarket* pMarket, const char* fileName);
