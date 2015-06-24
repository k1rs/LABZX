#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct BigSize
{
	unsigned long int Count;
	unsigned int *Number;
};

struct BigSize LevelUp(struct BigSize Number);

int CompareBigSize(struct BigSize Number1, struct BigSize Number2);

struct BigSize SumBigSize(struct BigSize Number1, struct BigSize Number2);

struct BigSize SubBigSize(struct BigSize Number1, struct BigSize Number2, unsigned long long int Osn);

struct BigSize MulBigSize(struct BigSize Number1, struct BigSize Number2);

struct BigSize MulSimpleBigSize(struct BigSize Number, unsigned int Simple, unsigned long long int Osn);

struct BigSize DivModBigSize(struct BigSize Number1, struct BigSize Number2, int param, unsigned long long int Osn);

struct BigSize DegBigSize(struct BigSize Number1, struct BigSize Number2, struct BigSize Osn);

struct BigSize RemoveTenBin(struct BigSize Number);

struct BigSize RemoveBinTen(struct BigSize BinNumber);

struct BigSize ReadTextFile(const char* file);

struct BigSize ReadBinFile(const char* file);

void WriteBinFile(struct BigSize Number, const char* file);

void WriteTextFile(struct BigSize Number, const char* file);

void PrintBigSize(struct BigSize Number);

void PrintScr(struct BigSize Number);

void Clear(struct BigSize *Number);

struct BigSize Allocate(struct BigSize Number, unsigned int Size);

struct BigSize Zero(struct BigSize Number, unsigned int Size);

struct BigSize Normalize(struct BigSize Number);

struct BigSize Copy(struct BigSize Number);

struct BigSize ReadFromString(char* buffer);

char* ToString(struct BigSize number);
