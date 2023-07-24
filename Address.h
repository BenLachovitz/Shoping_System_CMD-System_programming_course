#pragma once

typedef struct
{
	int		num;
	char*	street;
	char*	city;
}Address;

int		initAddress(Address* pAd);
void	printAddress(const Address* pAd);
int		saveAddressToFile(const Address* pAdd, FILE* fp);
int		loadAddressFromFile(Address* pAdd, FILE* fp);
int loadAddressFromCompFile(Address* pAdd, FILE* fp);
int saveAddressToCompFile(const Address* pAdd, FILE* fp);
void	freeAddress(Address* pAd);

int		checkElements(char**  elements, int count);
char*	fixAddressParam(char* param);
void	freeElements(char**  elements, int count);

