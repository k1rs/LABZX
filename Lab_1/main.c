#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE 4294967296 //2^32

struct BigSize //Структура данных
{
	unsigned long int Count;
	unsigned int *Number;
};

struct BigSize LevelUp(struct BigSize Number) //Нужно для реализации деления
{
	struct BigSize res;
	unsigned long int i;

	res.Count = Number.Count;
	res.Number = (unsigned int *)malloc((res.Count + 1) * sizeof(unsigned int));

	for (i = 0; i < Number.Count; i++) res.Number[i] = Number.Number[i];
	res.Number[res.Count] = 0;

	for (i = res.Count; i >= 1; i--) res.Number[i] = res.Number[i - 1];
	if (res.Number[res.Count] != 0) res.Count += 1;

	return res;
}

int CompareBigSize(struct BigSize Number1, struct BigSize Number2) //Функция сравнения двух больших чисел
{
	int k;
	unsigned long int j = 0;

	if (Number1.Count < Number2.Count) k = -1; //Проверка Number1 < Number2
	else if (Number1.Count > Number2.Count) k = 1;
	else if (Number1.Number[Number1.Count - 1] < Number2.Number[Number2.Count - 1]) k = -1;
	else if (Number1.Number[Number1.Count - 1] > Number2.Number[Number2.Count - 1]) k = 1;
	else
	{
		j = Number1.Count - 1;
		if (j == 0)
		{
			if (Number1.Number[j] < Number2.Number[j]) k = -1;
			else if (Number1.Number[j] > Number2.Number[j]) k = 1;
			else if (j == 0) k = 0;
		}
		else
		{
			while (Number1.Number[j] == Number2.Number[j] && j != 0)
			{
				j -= 1;
				if (Number1.Number[j] < Number2.Number[j]){ k = -1; break; }
				else if (Number1.Number[j] > Number2.Number[j]){ k = 1; break; }
				else if (j == 0) k = 0;
			}
		}
	}

	return k;
}

struct BigSize SumBigSize(struct BigSize Number1, struct BigSize Number2)
{
	struct BigSize res, a, b;
	int r = 0;
	unsigned long int i;
	unsigned long long int help;

	a.Count = Number1.Count;
	b.Count = Number2.Count;

	if (a.Count > b.Count)
	{
		res.Count = a.Count;
		a.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
		b.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));

		for (i = 0; i < res.Count; i++)
		{
			a.Number[i] = Number1.Number[i];
			if (i < Number2.Count) b.Number[i] = Number2.Number[i];
			else b.Number[i] = 0;
		}
	}
	else
	{
		res.Count = b.Count;
		a.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
		b.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));

		for (i = 0; i < res.Count; i++)
		{
			b.Number[i] = Number2.Number[i];
			if (i < Number1.Count) a.Number[i] = Number1.Number[i];
			else a.Number[i] = 0;
		}
	}

	res.Number = (unsigned int *)malloc((res.Count + 1) * sizeof(unsigned int));
	res.Number[res.Count] = 0;

	for (i = 0; i < res.Count; i++)
	{
		help = (unsigned long long int)a.Number[i] + (unsigned long long int)b.Number[i] + r;
		if (help >= BASE)
		{
			help -= BASE;
			r = 1;
		}
		else r = 0;

		res.Number[i] = help;
	}

	if (r == 1)
	{
		res.Number[res.Count] += 1;
		res.Count += 1;
	}

	return res;
}

struct BigSize SubBigSize(struct BigSize Number1, struct BigSize Number2, unsigned long long int Osn) //Функция разности
{
	struct BigSize res, a, b, def;
	unsigned long int i, j = 0, p = 0;
	long long int help;
	int k = 0;
	char str[256];

	a.Count = Number1.Count;
	b.Count = Number2.Count;

	k = CompareBigSize(Number1, Number2);
	if (k == 0 || k == 1)
	{
		res.Count = a.Count;
		a.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
		b.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));

		for (i = 0; i < res.Count; i++)
		{
			a.Number[i] = Number1.Number[i];
			if (i < Number2.Count) b.Number[i] = Number2.Number[i];
			else b.Number[i] = 0;
		}
	}
	else
	{
		res.Count = b.Count;
		a.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
		b.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));

		for (i = 0; i < res.Count; i++)
		{
			b.Number[i] = Number2.Number[i];
			if (i < Number1.Count) a.Number[i] = Number1.Number[i];
			else a.Number[i] = 0;
		}
	}

	res.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));

	if (k == 0 || k == 1) for (i = 0; i < res.Count; i++) res.Number[i] = a.Number[i];
	else for (i = 0; i < res.Count; i++){ res.Number[i] = b.Number[i]; b.Number[i] = a.Number[i]; }

	for (i = 0; i < res.Count; i++)
	{
		help = (long long int)res.Number[i] - (long long int)b.Number[i];
		if (help < 0)
		{
			help += Osn;
			if (res.Number[i + 1] != 0) res.Number[i + 1] -= 1;
			else
			{
				j = i + 1;
				while (res.Number[j] == 0)
				{
					j++;
					if (res.Number[j] != 0) break;
				}
				res.Number[j] -= 1;
				for (p = i + 1; p < j; p++) res.Number[p] = Osn - 1;
			}
		}
		res.Number[i] = help;
	}

	p = res.Count - 1;
	if (res.Number[p] == 0)
	{
		while (res.Number[p] == 0 && p != 0)
		{
			p--;
			if (res.Number[p] != 0) break;
		}
		res.Count = p + 1;
	}

	return res;
}

struct BigSize MulBigSize(struct BigSize Number1, struct BigSize Number2) //Функция умножения
{
	struct BigSize res;
	unsigned long int i, j, p;
	unsigned long long int r = 0, help;

	res.Count = Number1.Count + Number2.Count + 1;
	res.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
	memset(res.Number, 0, res.Count * sizeof(unsigned int));

	for (i = 0; i < Number1.Count; i++)
	{
		r = 0;
		for (j = 0; j < Number2.Count; j++)
		{
			help = (unsigned long long int)res.Number[i + j] + (unsigned long long int)Number1.Number[i] * (unsigned long long int)Number2.Number[j] + (unsigned long long int)r;
			r = help / BASE;
			help -= r * BASE;
			res.Number[i + j] = help;
		}
		if (r != 0) res.Number[i + j] += r;
	}

	p = res.Count - 1;
	if (res.Number[p] == 0)
	{
		while (res.Number[p] == 0 && p != 0)
		{
			p--;
			if (res.Number[p] != 0) break;
		}
		res.Count = p + 1;
	}

	return res;
}

struct BigSize MulSimpleBigSize(struct BigSize Number, unsigned int Simple, unsigned long long int Osn) //Функция умножения длинного числа на короткое (<BASE)
{
	struct BigSize res;
	unsigned long int i;
	unsigned long long int r = 0, help;

	if ((Number.Count == 1 && Number.Number[0] == 0) || Simple == 0)
	{
		res.Count = 1;
		res.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
		res.Number[0] = 0;
		return res;
	}

	res.Count = Number.Count;
	res.Number = (unsigned int *)malloc((res.Count + 1) * sizeof(unsigned int));
	res.Number[res.Count] = 0;

	for (i = 0; i < res.Count; i++)
	{
		help = (unsigned long long int)Number.Number[i] * (unsigned long long int)Simple + (unsigned long long int)r;
		r = help / Osn;
		help -= r * Osn;
		res.Number[i] = help;
	}
	if (r != 0) res.Number[res.Count] += r;
	if (res.Number[res.Count]) res.Count += 1;

	return res;
}

struct BigSize DivModBigSize(struct BigSize Number1, struct BigSize Number2, int param, unsigned long long int Osn) //Функция целочисленного деления
{
	struct BigSize res, curValue, cur, b, pr;
	unsigned long int i, j = 0;
	unsigned long long int x = 0, l = 0, r = Osn, m = 0, k = 0, p = 0;

	if (Number2.Number[0] == 0 && Number2.Count == 1)
	{
		res.Count = 1;
		res.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
		res.Number[0] = 0;
		return res;
	}

	res.Count = Number1.Count + Number2.Count;
	curValue.Count = Number1.Count + Number2.Count;
	cur.Count = Number1.Count + Number2.Count;
	b.Count = Number2.Count;
	pr.Count = Number2.Count;

	pr.Number = (unsigned int *)malloc(pr.Count * sizeof(unsigned int));
	b.Number = (unsigned int *)malloc(b.Count * sizeof(unsigned int));
	res.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
	curValue.Number = (unsigned int *)malloc(curValue.Count * sizeof(unsigned int));
	cur.Number = (unsigned int *)malloc(cur.Count * sizeof(unsigned int));

	curValue.Count = 1;

	for (i = 0; i < b.Count; i++) b.Number[i] = Number2.Number[i];
	for (i = 0; i < res.Count; i++){ res.Number[i] = 0; curValue.Number[i] = 0; cur.Number[i] = 0; }

	for (i = Number1.Count - 1; i >= 1; i--)
	{
		curValue = LevelUp(curValue);
		curValue.Number[0] = Number1.Number[i];

		x = 0; l = 0; r = Osn;
		while (l <= r)
		{
			m = (l + r) >> 1;
			cur = MulSimpleBigSize(b, m, Osn);
			k = CompareBigSize(cur, curValue); //Проверка cur <= curValue
			if (k == -1 || k == 0)
			{
				x = m;
				l = m + 1;
			}
			else r = m - 1;
		}
		res.Number[i] = x; //curValue = curValue - b * x;
		pr = MulSimpleBigSize(b, x, Osn);
		curValue = SubBigSize(curValue, pr, Osn);
	}

	curValue = LevelUp(curValue); //Делаем всё то что в for только для i = 0
	curValue.Number[0] = Number1.Number[0];

	x = 0; l = 0; r = Osn;
	while (l <= r)
	{
		m = (l + r) >> 1;
		cur = MulSimpleBigSize(b, m, Osn);

		k = CompareBigSize(cur, curValue); //Проверка cur <= curValue
		if (k == -1 || k == 0)
		{
			x = m;
			l = m + 1;
		}
		else r = m - 1;
	}
	res.Number[0] = x; //curValue = curValue - b * x;
	pr = MulSimpleBigSize(b, x, Osn);
	curValue = SubBigSize(curValue, pr, Osn);

	if (param == 0) return curValue;

	p = Number1.Count;
	while (p != 0 && res.Number[p] == 0) p--;
	res.Count = p + 1;

	return res;
}

struct BigSize DegBigSize(struct BigSize Number1, struct BigSize Number2, struct BigSize Osn) //Функция возведения в степень
{
	struct BigSize cur, decrement, res;

	cur.Number = NULL; decrement.Number = NULL; res.Number = NULL;
	cur.Count = 0; decrement.Count = 1;

	decrement.Number = (unsigned int *)malloc(decrement.Count * sizeof(unsigned int));
	decrement.Number[0] = 1;

	if (Number2.Count == 1 && Number2.Number[0] == 0)
	{
		res.Count = 1;
		res.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
		res.Number[0] = 1;
		return res;
	}

	res = DivModBigSize(Number1, Osn, 0, BASE); //Number1 % Osn

	if (Number2.Count == 1 && Number2.Number[0] == 1) return res;

	cur = MulBigSize(res, res);
	res = DivModBigSize(cur, Osn, 0, BASE);

	if (Number2.Count == 1 && Number2.Number[0] == 2) return res;

	while ((Number2.Number[0] - 2) != 0 || Number2.Count != 1)
	{
		cur = MulBigSize(Number1, res);
		res = DivModBigSize(cur, Osn, 0, BASE);
		Number2 = SubBigSize(Number2, decrement, BASE);
	}

	return res;
}

struct BigSize RemoveTenBin(struct BigSize Number) //Перевод числа в бинарный вид
{
	struct BigSize BinNumber, Help;
	struct BigSize Two, Ost, Num;
	unsigned long int i, j = 0;
	int x = 0;

	if (Number.Count == 1 && Number.Number[0] == 0)
	{
		BinNumber.Count = 1;
		BinNumber.Number = (unsigned int *)malloc(BinNumber.Count * sizeof(unsigned int));
		BinNumber.Number[0] = 0;
		return BinNumber;
	}

	BinNumber.Count = 1;
	Two.Count = 1;
	Ost.Count = 1;
	Num.Count = Number.Count;

	BinNumber.Number = (unsigned int *)malloc(1 * sizeof(unsigned int));
	Two.Number = (unsigned int *)malloc(1 * sizeof(unsigned int));
	Ost.Number = (unsigned int *)malloc(1 * sizeof(unsigned int));
	Num.Number = (unsigned int *)malloc(Num.Count * sizeof(unsigned int));

	for (i = 0; i < Num.Count; i++) Num.Number[i] = Number.Number[i];
	BinNumber.Number[0] = 0;
	Two.Number[0] = 2;
	Ost.Number[0] = 0;

	while (Num.Count != 1 || Num.Number[0] != 0)
	{
		Ost = DivModBigSize(Num, Two, 0, 10);
		Num = DivModBigSize(Num, Two, 1, 10);

		Ost.Number[0] = Ost.Number[0] << x;
		BinNumber.Number[j] |= Ost.Number[0];

		x++;
		if (x == 32)
		{
			j++;
			x = 0;
			Help.Count = BinNumber.Count;
			Help.Number = (unsigned int *)malloc(Help.Count * sizeof(unsigned int));
			for (i = 0; i < BinNumber.Count; i++) Help.Number[i] = BinNumber.Number[i];
			free(BinNumber.Number);
			BinNumber.Count += 1;
			BinNumber.Number = (unsigned int *)malloc(BinNumber.Count * sizeof(unsigned int));
			for (i = 0; i < Help.Count; i++) BinNumber.Number[i] = Help.Number[i];
			BinNumber.Number[BinNumber.Count - 1] = 0;
			free(Help.Number);
		}
	}

	if (BinNumber.Number[BinNumber.Count - 1] == 0) BinNumber.Count -= 1;
	return BinNumber;
}

struct BigSize RemoveBinTen(struct BigSize BinNumber) //Перевод числа в десятичный вид
{
	struct BigSize res;
	struct BigSize Number;
	long long int i, tmp;
	unsigned int p, j = 0;
	char carry = 0;

	Number.Count = BinNumber.Count;
	Number.Number = (unsigned int *)malloc(Number.Count * sizeof(unsigned int));
	for (i = 0; i < BinNumber.Count; i++) Number.Number[i] = BinNumber.Number[i];

	if (Number.Count == 1 && Number.Number[0] == 0)
	{
		res.Count = 1;
		res.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
		res.Number[0] = 0;
		return res;
	}

	res.Count = Number.Count * 10;
	res.Number = (unsigned int *)malloc(res.Count * sizeof(unsigned int));
	memset(res.Number, 0, res.Count * sizeof(unsigned int));

	while (Number.Count != 1 || Number.Number[0] != 0)
	{
		carry = 0;
		for (i = Number.Count - 1; i >= 0; i--)
		{
			tmp = carry * BASE + Number.Number[i];
			Number.Number[i] = tmp / 10;
			carry = tmp - (long long int) Number.Number[i] * 10;
		}

		res.Number[j] = carry;
		j++;

		p = Number.Count - 1;
		if (Number.Number[p] == 0 && res.Count != 1)
		{
			while (Number.Number[p] == 0 && p != 0)
			{
				p--;
				if (Number.Number[p] != 0) break;
			}
			Number.Count = p + 1;
		}
	}

	p = res.Count - 1;
	if (res.Number[p] == 0 && res.Count != 1)
	{
		while (res.Number[p] == 0 && p != 0)
		{
			p--;
			if (res.Number[p] != 0) break;
		}
		res.Count = p + 1;
	}

	return res;
}

struct BigSize ReadTextFile(const char* file) //Функия считывания числа из текстового файла
{
	struct BigSize BinNumber;
	struct BigSize Number;
	unsigned long int i = 0;
	char str[256];
	FILE *in;

	in = fopen(file, "r");
	fseek(in, 0, SEEK_END);
	Number.Number = (unsigned int *)malloc(ftell(in) * sizeof(unsigned int));
	Number.Count = ftell(in);
	Number.Count -= 1;
	fclose(in);

	in = fopen(file, "r");

	for (i = Number.Count - 1; i >= 1; i--)
	{
		fscanf(in, "%c", &str[0]);
		Number.Number[i] = str[0] - '0';
	}

	fscanf(in, "%c", &str[0]);
	Number.Number[0] = str[0] - '0';
	BinNumber = RemoveTenBin(Number);

	fclose(in);
	return BinNumber;
}

struct BigSize ReadBinFile(const char* file)
{
	struct BigSize Number;
	unsigned int quotient, remainder, size;
	unsigned char ch;
	int i, j;
	FILE *in;

	in = fopen(file, "rb");
	Number.Count = 0;

	fseek(in, 0, SEEK_END);
	size = ftell(in);

	quotient = size / sizeof(unsigned int);
	remainder = size % sizeof(unsigned int);

	if (remainder == 0) Number.Number = (unsigned int *)malloc(quotient * sizeof(unsigned int));
	else Number.Number = (unsigned int *)malloc((quotient + 1) * sizeof(unsigned int));

	fseek(in, SEEK_SET, 0); //Переход на начало строки

	for (i = 0; i < quotient; i++) fread(&Number.Number[i], sizeof(unsigned int), 1, in);

	Number.Count = quotient;

	if (remainder != 0)
	{
		Number.Count += 1;
		Number.Number[quotient] = 0;
		for (j = 0; j < remainder; j++)
		{
			fread(&ch, sizeof(unsigned char), 1, in);
			Number.Number[quotient] |= (ch << j * 8);
		}
	}

	fclose(in);
	return Number;
}

void WriteBinFile(struct BigSize Number, const char* file) //Вывод числа в бинарный файл
{
	unsigned long int i;
	FILE *out;

	out = fopen(file, "wb");
	for (i = 0; i < Number.Count; i++) fwrite(&Number.Number[i], sizeof(unsigned int), 1, out);
	fclose(out);
}

void WriteTextFile(struct BigSize Number, const char* file)
{
	struct BigSize DecNumber;
	unsigned long int i;
	FILE *out;

	out = fopen(file, "w");
	DecNumber = RemoveBinTen(Number);
	for (i = DecNumber.Count - 1; i >= 1; i--) fprintf(out, "%u", DecNumber.Number[i]);
	fprintf(out, "%u", DecNumber.Number[0]);
	fclose(out);
}

void PrintBigSize(struct BigSize Number) //Вывод числа
{
	unsigned long int i;

	for (i = Number.Count - 1; i >= 1; i--) printf("%u", Number.Number[i]);
	printf("%u", Number.Number[0]);
}

void PrintScr(struct BigSize Number) //Вывод числа на экран
{
	struct BigSize DecNumber;

	DecNumber = RemoveBinTen(Number);
	PrintBigSize(DecNumber);
}

struct BigSize Clear(struct BigSize Number)
{
	free(Number.Number);
	return Number;
}

struct BigSize Zero(struct BigSize Number, unsigned int Size)
{
	memset(Number.Number, 0, Size * sizeof(unsigned int));
	return Number;
}

struct BigSize Allocate(struct BigSize Number, unsigned int Size)
{
	Number.Number = (unsigned int *)malloc(Size * sizeof(unsigned int));
	Number.Count = Size;
	Number = Zero(Number, Number.Count);
	return Number;
}

struct BigSize Copy(struct BigSize Number)
{
	struct BigSize Cpy;

	Cpy.Count = Number.Count;
	Cpy = Allocate(Cpy, Cpy.Count);
	memcpy(Cpy.Number, Number.Number, Cpy.Count * sizeof(unsigned int));

	return Cpy;
}

int main(int argc, const char * argv[])
{
	unsigned char binary = 0;

	if (argc < 5)
	{
		printf("Error: Too few arguments. <first_long_number_filename> [ + (sum) | - (subtract) | * (multiply) | / (divide) | %% (module) | ^ (power) ] <second_long_number_filename> [<third_long_number_filename> (only for power operation) ] <result_long_number_filename> [ -b ]\n");
		return 0;
	}

	const char* operation = argv[2];
	if ((strlen(operation) > 1 || operation[0] == '\0') || operation[0] != '+' && operation[0] != '-' && operation[0] != '*' && operation[0] != '/' && operation[0] != '%' && operation[0] != '^')
	{
		printf("Error: Wrong operation: %s \n", operation);
		return 0;
	}

	if (operation[0] != '^')
	{
		if (argc < 5)
		{
			printf("Error: Too few arguments. <first_long_number_filename> [ + (sum) | - (subtract) | * (multiply) | / (divide) | %% (module) | ^ (power) ] <second_long_number_filename> [<third_long_number_filename> (only for power operation) ] <result_long_number_filename> [ -b ]\n");
			return 0;
		}

		if (argc > 6)
		{
			printf("Error: Too many arguments. <first_long_number_filename> [ + (sum) | - (subtract) | * (multiply) | / (divide) | %% (module) | ^ (power) ] <second_long_number_filename> [<third_long_number_filename> (only for power operation) ] <result_long_number_filename> [ -b ]\n");
			return 0;
		}
	}
	else
	{
		if (argc < 6)
		{
			printf("Error: Too few arguments. <first_long_number_filename> [ + (sum) | - (subtract) | * (multiply) | / (divide) | %% (module) | ^ (power) ] <second_long_number_filename> [<third_long_number_filename> (only for power operation) ] <result_long_number_filename> [ -b ]\n");
			return 0;
		}

		if (argc > 7)
		{
			printf("Error: Too many arguments. <first_long_number_filename> [ + (sum) | - (subtract) | * (multiply) | / (divide) | %% (module) | ^ (power) ] <second_long_number_filename> [<third_long_number_filename> (only for power operation) ] <result_long_number_filename> [ -b ]\n");
			return 0;
		}
	}

	const char* firstLongNumFileName = argv[1];
	FILE* firstLongNumFile = fopen(firstLongNumFileName, "rb");
	if (!firstLongNumFile)
	{
		printf("Error: Unable to open file: %s \n", firstLongNumFileName);
		return 0;
	}

	const char* secondLongNumFileName = argv[3];
	FILE* secondLongNumFile = fopen(secondLongNumFileName, "rb");
	if (!secondLongNumFile)
	{
		printf("Error: Unable to open file: %s \n", secondLongNumFileName);
		return 0;
	}

	const char* thirdLongNumFileName = NULL;
	FILE* thirdLongNumFile = NULL;
	if (operation[0] == '^')
	{
		thirdLongNumFileName = argv[4];
		thirdLongNumFile = fopen(thirdLongNumFileName, "rb");
		if (!thirdLongNumFile)
		{
			printf("Error: Unable to open file: %s \n", thirdLongNumFileName);
			return 0;
		}
	}

	const char* resultLongNumFileName = (operation[0] != '^') ? argv[4] : argv[5];
	FILE* resultLongNumFile = NULL;

	if (binary == 1) resultLongNumFile = fopen(resultLongNumFileName, "wb");
	else resultLongNumFile = fopen(resultLongNumFileName, "w+");

	if (!resultLongNumFile)
	{
		printf("Error: Unable to open file: %s \n", resultLongNumFileName);
		return 0;
	}

	const char* ifBinary = (operation[0] != '^') ? argv[5] : argv[6];
	if (argc == 6 && operation[0] != '^' || argc == 7 && operation[0] == '^')
	{
		if (strcmp(ifBinary, "-b"))
		{
			printf("Error: Invalid flag: %s \n", ifBinary);
			return 0;
		}
		binary = 1;
	}

	struct BigSize a;
	struct BigSize b;
	struct BigSize c;

	if (binary == 1)
	{
		a.Count = 0;
		a = ReadBinFile(firstLongNumFileName);

		b.Count = 0;
		b = ReadBinFile(secondLongNumFileName);

		c.Count = 0;
		c.Number = NULL;

		if (operation[0] == '^') c = ReadBinFile(thirdLongNumFileName);
	}
	else
	{
		a.Count = 0;
		a = ReadTextFile(firstLongNumFileName);

		b.Count = 0;
		b = ReadTextFile(secondLongNumFileName);

		c.Count = 0;
		c.Number = NULL;

		if (operation[0] == '^') c = ReadTextFile(thirdLongNumFileName);
	}

	struct BigSize res;
	res.Count = 0;
	res.Number = NULL;

	switch (operation[0])
	{
	case '+':
		res = SumBigSize(a, b);
		break;

	case '-':
		res = SubBigSize(a, b, BASE);
		break;

	case '*':
		res = MulBigSize(a, b);
		break;

	case '/':
		res = DivModBigSize(a, b, 1, BASE);
		break;

	case '%':
		res = DivModBigSize(a, b, 0, BASE);
		break;

	case '^':
		res = DegBigSize(a, b, c);
		break;

	default:
		break;
	}

	if (binary == 1) WriteBinFile(res, resultLongNumFile);
	else WriteTextFile(res, resultLongNumFileName);

	a=Clear(a);
	b=Clear(b);
	c=Clear(c);

	return 0;
}
