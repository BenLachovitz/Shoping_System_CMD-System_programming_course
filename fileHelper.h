#pragma once

#include "General.h"

int		writeStringToFile(const char* str, FILE* fp,const char* msg);
int		writeCharsToFile(const char* arr,int size, FILE* fp, const char* msg);
int		writeIntToFile(int val, FILE* fp, const char* msg);

char*	readStringFromFile(FILE* fp,const char* msg);
char*	readDynStringFromTextFile(FILE* fp);
int		readFixSizeStrFromFile(char* arr, FILE* fp, const char* msg);
int		readCharsFromFile(char* arr, int size, FILE* fp, const char* msg);
int		readIntFromFile(int* val, FILE* fp, const char* msg);

int writeStringAsChars(char* str, FILE* fp, int len);
int readStringAsChars(char* str, FILE* fp, int len);

void getTheProductBarcodeFromBits(int* pVal, BYTE* data, int firstRead);
void getCountAndPriceComp(int* pCount, float* pPrice, BYTE* data);
void saveCountAndPriceToComp(int pCount, float pPrice, BYTE* data);
void convertValuesToBarcode(const char* pBarcode, int* pVal, int len);
char fixLoadedBarcodeChar(int val);
int changeBarcodeCharToCompFile(char val);

