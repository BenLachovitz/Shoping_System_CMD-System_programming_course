#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255

typedef unsigned char BYTE;

char*	getStrExactLength(const char* msg);
char*	getsStrFixSize(char* buffer, int size, const char* msg);
char*	myGets(char* buffer, int size, FILE* source);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str, int* pCount, const char* del, int* pTotalLength);
void	generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));

float	getPositiveFloat(const char* msg);
int		getPositiveInt(const char* msg);
int		countCharInString(const char* str, char tav);
int		checkEmptyString(char* str);

void printMessage(const char* str, ...);

#endif

